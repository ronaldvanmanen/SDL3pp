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

#include <SDL3/SDL.h>
#include "SDL3pp/error.h"
#include "SDL3pp/window.h"

namespace sdl3
{
    SDL_Window* create_window(std::string const& title, sdl3::length<std::int32_t> width, sdl3::length<std::int32_t> height, sdl3::window_flags flags)
    {
        SDL_Window* native_handle =
            SDL_CreateWindow(
                title.c_str(),
                quantity_cast<std::int32_t>(width),
                quantity_cast<std::int32_t>(height),
                static_cast<std::uint32_t>(flags)
            );
        sdl3::throw_last_error(native_handle != nullptr);        
        return native_handle;
    }
}

sdl3::window::window(std::string const& title, sdl3::length<std::int32_t> width, sdl3::length<std::int32_t> height)
: _native_handle(sdl3::create_window(title, width, height, sdl3::window_flags::none))
{ }

sdl3::window::window(std::string const& title, sdl3::length<std::int32_t> width, sdl3::length<std::int32_t> height, sdl3::window_flags flags)
: _native_handle(sdl3::create_window(title, width, height, flags))
{ }

sdl3::window::window(sdl3::window&& other)
: _native_handle(std::exchange(other._native_handle, nullptr))
{ }

sdl3::window::~window()
{
    if (_native_handle != nullptr)
    {
        SDL_DestroyWindow(_native_handle);
    }
}

sdl3::size_2d<std::int32_t>
sdl3::window::size() const
{
    int width, height;
    SDL_GetWindowSize(_native_handle, &width, &height);
    return sdl3::size_2d<std::int32_t>(
        width * px,
        height * px
    );
}

void
sdl3::window::raise()
{
    throw_last_error(
        SDL_RaiseWindow(_native_handle)
    );
}

void
sdl3::window::update_surface()
{
    throw_last_error(
        SDL_UpdateWindowSurface(_native_handle)
    );
}

void
sdl3::window::relative_mouse_mode(bool enabled)
{
    throw_last_error(
        SDL_SetWindowRelativeMouseMode(_native_handle, enabled)
    );
}

bool
sdl3::window::relative_mouse_mode() const
{
    return SDL_GetWindowRelativeMouseMode(_native_handle);
}

SDL_Window*
sdl3::window::native_handle()
{
    return _native_handle;
}
