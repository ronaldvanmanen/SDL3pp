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

#include <cstdint>
#include <optional>
#include <string>
#include <type_traits>

#include <SDL3/SDL.h>

#include "display_mode.hpp"
#include "flags.hpp"
#include "size.hpp"
#include "surface.hpp"
#include "units.hpp"

namespace sdl3
{
    enum class window_flags : std::uint32_t
    {
        none = 0,
        fullscreen = SDL_WINDOW_FULLSCREEN,
        opengl = SDL_WINDOW_OPENGL,
        hidden = SDL_WINDOW_HIDDEN,
        borderless = SDL_WINDOW_BORDERLESS,
        resizable = SDL_WINDOW_RESIZABLE,
        minimized = SDL_WINDOW_MINIMIZED,
        maximized = SDL_WINDOW_MAXIMIZED,
        input_grabbed = SDL_WINDOW_MOUSE_GRABBED,
        input_focus = SDL_WINDOW_INPUT_FOCUS,
        mouse_focus = SDL_WINDOW_MOUSE_FOCUS,
        allow_high_dpi = SDL_WINDOW_HIGH_PIXEL_DENSITY,
        mouse_capture = SDL_WINDOW_MOUSE_CAPTURE,
        always_on_top = SDL_WINDOW_ALWAYS_ON_TOP,
        skip_taskbar = SDL_WINDOW_UTILITY,
        utility = SDL_WINDOW_UTILITY,
        tooltip = SDL_WINDOW_TOOLTIP,
        popup_menu = SDL_WINDOW_POPUP_MENU,
        vulkan = SDL_WINDOW_VULKAN,
        metal = SDL_WINDOW_METAL
    };

    template <>
    struct is_flags_enum<window_flags>
    {
        static const bool value = true;
    };

    class window
    {
    public:
        window(std::string const & title, length<std::int32_t> width, length<std::int32_t> height);

        window(std::string const & title, length<std::int32_t> width, length<std::int32_t> height, window_flags flags);

        window(window const & other) = delete;

        window(window && other);

        ~window();

        window & operator=(window const & other) = delete;

        bool relative_mouse_mode() const;

        void relative_mouse_mode(bool enable);

        std::optional<display_mode> fullscreen_mode() const;

        size_2d<std::int32_t> size() const;

        void raise();

        bool has_surface() const;

        surface_base surface();

        void update_surface();

        SDL_Window * native_handle();

    private:
        SDL_Window * _native_handle;
    };

    namespace details
    {
        inline SDL_Window *
        create_window(
            std::string const & title,
            length<std::int32_t> width,
            length<std::int32_t> height,
            window_flags flags
        )
        {
            SDL_Window * native_handle = SDL_CreateWindow(
                title.c_str(),
                quantity_cast<std::int32_t>(width),
                quantity_cast<std::int32_t>(height),
                static_cast<std::uint32_t>(flags)
            );
            throw_last_error(native_handle != nullptr);
            return native_handle;
        }
    }  // namespace details

    inline window::window(std::string const & title, length<std::int32_t> width, length<std::int32_t> height)
    : _native_handle(details::create_window(title, width, height, window_flags::none))
    { }

    inline window::window(
        std::string const & title,
        length<std::int32_t> width,
        length<std::int32_t> height,
        window_flags flags
    )
    : _native_handle(details::create_window(title, width, height, flags))
    { }

    inline window::window(window && other)
    : _native_handle(std::exchange(other._native_handle, nullptr))
    { }

    inline window::~window()
    {
        if (_native_handle != nullptr)
        {
            SDL_DestroyWindow(_native_handle);
        }
    }

    inline void
    window::relative_mouse_mode(bool enabled)
    {
        throw_last_error(SDL_SetWindowRelativeMouseMode(_native_handle, enabled));
    }

    inline bool
    window::relative_mouse_mode() const
    {
        return SDL_GetWindowRelativeMouseMode(_native_handle);
    }

    inline std::optional<display_mode>
    window::fullscreen_mode() const
    {
        auto native_handle = SDL_GetWindowFullscreenMode(_native_handle);
        if (native_handle == nullptr)
        {
            return std::nullopt;
        }
        return display_mode(native_handle);
    }

    inline size_2d<std::int32_t>
    window::size() const
    {
        int width, height;
        throw_last_error(SDL_GetWindowSize(_native_handle, &width, &height));
        return size_2d<std::int32_t>(width * px, height * px);
    }

    inline void
    window::raise()
    {
        throw_last_error(SDL_RaiseWindow(_native_handle));
    }

    inline bool
    window::has_surface() const
    {
        return SDL_WindowHasSurface(_native_handle);
    }

    inline surface_base
    window::surface()
    {
        auto native_handle = SDL_GetWindowSurface(_native_handle);
        throw_last_error(native_handle != nullptr);
        return surface_base(native_handle, false);
    }

    inline void
    window::update_surface()
    {
        throw_last_error(SDL_UpdateWindowSurface(_native_handle));
    }

    inline SDL_Window *
    window::native_handle()
    {
        return _native_handle;
    }
}  // namespace sdl3
