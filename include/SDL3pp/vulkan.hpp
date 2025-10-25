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

#pragma once

#include <algorithm>
#include <vector>

#include <vulkan/vulkan.hpp>

#include <SDL3/SDL_vulkan.h>

#include "error.hpp"
#include "window.hpp"

namespace sdl3::vulkan
{
    class surface
    {
    public:
        surface(sdl3::window & window, vk::Instance const & instance)
        : _native_handle()
        , _instance(instance)
        {
            check_result(SDL_Vulkan_CreateSurface(window.native_handle(), instance, nullptr, &_native_handle));
        }

        ~surface()
        {
            SDL_Vulkan_DestroySurface(_instance, _native_handle, nullptr);
        }

        [[nodiscard]]
        VkSurfaceKHR native_handle()
        {
            return _native_handle;
        }

    private:
        VkSurfaceKHR _native_handle;

        vk::Instance _instance;
    };

    [[nodiscard]]
    inline std::vector<std::string> instance_extensions()
    {
        auto extension_count = 0u;
        auto extension_name_array = check_pointer(SDL_Vulkan_GetInstanceExtensions(&extension_count));
        auto extension_names = std::vector<std::string>();
        extension_names.reserve(extension_count);
        for (auto extension_index = 0u; extension_index < extension_count; ++extension_index)
        {
            extension_names.push_back(std::string(extension_name_array[extension_index]));
        }
        return extension_names;
    }
}  // namespace sdl3::vulkan
