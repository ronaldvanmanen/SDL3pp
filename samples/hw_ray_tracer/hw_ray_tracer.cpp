// SDL3++
//
// Copyright (C) 2025 Ronald van Manen <rvanmanen@gmail.com>
//
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <limits>
#include <ranges>
#include <set>
#include <utility>
#include <vector>

#include <boost/poly_collection/base_collection.hpp>
#include <boost/qvm/all.hpp>

#include <vulkan/vulkan.hpp>

#include "SDL3pp/events.hpp"
#include "SDL3pp/keyboard.hpp"
#include "SDL3pp/mouse.hpp"
#include "SDL3pp/vulkan.hpp"
#include "SDL3pp/window.hpp"

#include "../math.hpp"
#include "../stopwatch.hpp"

using sdl3::px;

namespace sdl3::vulkan
{
    inline std::vector<std::string> instance_layers()
    {
        auto layers = vk::enumerateInstanceLayerProperties();
        auto layer_names = std::vector<std::string>();
        layer_names.reserve(layers.size());
        for (auto layer : layers)
        {
            layer_names.push_back(std::string(layer.layerName));
        }
        return layer_names;
    }

    inline vk::Instance create_instance(
        std::string const & application_name = {},
        std::uint32_t application_version = {},
        std::string const & engine_name = {},
        std::uint32_t engine_version = {},
        std::uint32_t api_version = {},
        std::vector<std::string> const & instance_extensions = {},
        std::vector<std::string> const & instance_layers = {}
    )
    {
        auto application_info = vk::ApplicationInfo(
            application_name.c_str(),
            application_version,
            engine_name.c_str(),
            engine_version,
            api_version
        );

        auto instance_extensions_names = std::vector<const char *>();
        instance_extensions_names.reserve(instance_extensions.size());
        for (auto const & instance_extension : instance_extensions)
        {
            instance_extensions_names.push_back(instance_extension.data());
        }

        auto instance_layer_names = std::vector<const char *>();
        instance_layer_names.reserve(instance_layers.size());
        for (auto const & instance_layer : instance_layers)
        {
            instance_layer_names.push_back(instance_layer.data());
        }

        auto instance_create_info = vk::InstanceCreateInfo(
            {},
            &application_info,
            static_cast<std::uint32_t>(instance_layer_names.size()),
            instance_layer_names.data(),
            static_cast<std::uint32_t>(instance_extensions_names.size()),
            instance_extensions_names.data()
        );

        return vk::createInstance(instance_create_info);
    }

    template <typename Predicate>
    std::optional<vk::PhysicalDevice> find_physical_device(vk::Instance const & instance, Predicate predicate)
    {
        auto devices = instance.enumeratePhysicalDevices();
        auto device_position = std::ranges::find_if(devices, predicate);
        if (device_position != devices.end())
        {
            return std::make_optional(*device_position);
        }
        return std::nullopt;
    };

    inline bool has_extension(vk::PhysicalDevice const & physical_device, const char * extension_name)
    {
        auto all_extension_properties = physical_device.enumerateDeviceExtensionProperties();
        for (auto extension_properties : all_extension_properties)
        {
            if (strcmp(extension_properties.extensionName, extension_name) == 0)
            {
                return true;
            }
        }
        return false;
    }

    inline bool has_extension(vk::PhysicalDevice const & physical_device, std::string const & extension_name)
    {
        return has_extension(physical_device, extension_name.c_str());
    }

    inline std::optional<std::pair<std::uint32_t, std::uint32_t>> find_graphics_and_present_queue_family_indices(
        vk::PhysicalDevice const & physical_device,
        surface & surface
    )
    {
        auto queue_family_properties = physical_device.getQueueFamilyProperties();
        for (auto index = 0u; index < queue_family_properties.size(); ++index)
        {
            auto const supports_graphics = queue_family_properties[index].queueFlags & vk::QueueFlagBits::eGraphics;
            if (supports_graphics)
            {
                auto const supports_presentation = physical_device.getSurfaceSupportKHR(index, surface.native_handle());
                if (supports_presentation)
                {
                    return std::make_pair(index, index);
                }
            }
        }

        return std::nullopt;
    }

    template <typename... Extension>
    vk::Device create_device(
        vk::PhysicalDevice const & physical_device,
        uint32_t queue_family_index,
        std::vector<std::string> const & extension_names,
        vk::StructureChain<vk::PhysicalDeviceFeatures2, Extension...> const & features_and_extensions
    )
    {
        std::vector<char const *> enabled_extensions;
        enabled_extensions.reserve(extension_names.size());
        for (auto const & extension : extension_names)
        {
            enabled_extensions.push_back(extension.data());
        }

        float queue_priority = 0.0f;
        vk::DeviceQueueCreateInfo device_queue_create_info({}, queue_family_index, 1, &queue_priority);
        vk::DeviceCreateInfo device_create_info(
            {},
            device_queue_create_info,
            {},
            enabled_extensions,
            {},
            &features_and_extensions.template get<vk::PhysicalDeviceFeatures2>()
        );

        vk::Device device = physical_device.createDevice(device_create_info);

        return device;
    }
}  // namespace sdl3::vulkan

int main()
{
    try
    {
        auto window = sdl3::window(
            "Hardware Ray Tracer",
            640 * px,
            480 * px,
            sdl3::window_flags::resizable | sdl3::window_flags::vulkan
        );

        auto instance_extension_names = sdl3::vulkan::instance_extensions();
        auto instance_layer_names = sdl3::vulkan::instance_layers();
        auto instance = sdl3::vulkan::create_instance(
            "Hardware Ray Tracer",
            VK_MAKE_API_VERSION(0, 1, 0, 0),
            "Hardware Ray Tracer Engine",
            VK_MAKE_API_VERSION(0, 1, 0, 0),
            VK_MAKE_API_VERSION(0, 1, 4, 0),
            instance_extension_names,
            instance_layer_names
        );

        auto physical_device_extensions = std::vector<std::string>(
            {VK_EXT_DESCRIPTOR_INDEXING_EXTENSION_NAME,
             VK_KHR_GET_MEMORY_REQUIREMENTS_2_EXTENSION_NAME,
             VK_KHR_MAINTENANCE_3_EXTENSION_NAME,
             VK_KHR_SWAPCHAIN_EXTENSION_NAME,
             VK_NV_RAY_TRACING_EXTENSION_NAME}
        );
        auto physical_device = sdl3::vulkan::find_physical_device(
            instance,
            [&physical_device_extensions](vk::PhysicalDevice const & physical_device)
            {
                for (auto physical_device_extension : physical_device_extensions)
                {
                    if (!sdl3::vulkan::has_extension(physical_device, physical_device_extension))
                    {
                        return false;
                    }
                }
                return true;
            }
        );

        if (!physical_device)
        {
            std::cerr << "Can't find a physical device that supports ray tracing." << std::endl;
            return 1;
        }

        auto surface = sdl3::vulkan::surface(window, instance);
        auto graphics_and_present_queue_family_indices = sdl3::vulkan::find_graphics_and_present_queue_family_indices(
            *physical_device,
            surface
        );

        if (!graphics_and_present_queue_family_indices)
        {
            std::cerr << "Can't find a suitable graphics queue family and/or present queue family" << std::endl;
            return 1;
        }

        auto graphics_queue_family_index = graphics_and_present_queue_family_indices->first;
        auto present_queue_family_index = graphics_and_present_queue_family_indices->second;
        auto physical_device_features_chain = physical_device->getFeatures2<
            vk::PhysicalDeviceFeatures2,
            vk::PhysicalDeviceDescriptorIndexingFeatures
        >();

        auto logical_device = sdl3::vulkan::create_device(
            *physical_device,
            graphics_queue_family_index,
            physical_device_extensions,
            physical_device_features_chain
        );

        auto graphics_queue = logical_device.getQueue(graphics_queue_family_index, 0);
        auto present_queue = logical_device.getQueue(present_queue_family_index, 0);

        auto event_queue = sdl3::event_queue();
        auto running = true;
        while (running)
        {
            sdl3::event event;
            if (event_queue.poll(event))
            {
                auto handler = sdl3::event_handler {
                    [&running](sdl3::quit_event &&)
                    {
                        running = false;
                    },

                    [](auto &&) {}
                };

                event.handle(handler);
            }
        }
    }
    catch (sdl3::error const & e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
