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

#include "SDL3pp/display_mode.h"

namespace sdl3
{
    SDL_DisplayMode const* get_window_display_mode(window & window)
    { 
        return SDL_GetWindowFullscreenMode(window.native_handle());
    }
}

sdl3::display_mode::display_mode(sdl3::window & window)
: _native_handle(get_window_display_mode(window))
{}

sdl3::pixel_format
sdl3::display_mode::format() const
{
    return static_cast<sdl3::pixel_format>(_native_handle->format);
}
        
sdl3::length<std::int32_t>
sdl3::display_mode::width() const
{
    return _native_handle->w * px;
}

sdl3::length<std::int32_t>
sdl3::display_mode::height() const
{
    return _native_handle->h * px;
}

sdl3::display_rate
sdl3::display_mode::refresh_rate() const
{
    return _native_handle->refresh_rate * boost::units::si::hertz;
}
