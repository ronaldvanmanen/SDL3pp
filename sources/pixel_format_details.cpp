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

#include "SDL3pp/error.h"
#include "SDL3pp/pixel_format_details.h"

namespace sdl3
{
    SDL_PixelFormatDetails const*
    get_pixel_format_details(sdl3::pixel_format format)
    {
        auto native_handle = SDL_GetPixelFormatDetails(static_cast<SDL_PixelFormat>(format));
        sdl3::throw_last_error(native_handle != nullptr);
        return native_handle;
    }
}

sdl3::pixel_format_details::pixel_format_details(sdl3::pixel_format format)
: _native_handle(sdl3::get_pixel_format_details(format))
{ }

sdl3::pixel_format_details::pixel_format_details(SDL_PixelFormatDetails const* native_handle)
: _native_handle(native_handle)
{ }

SDL_PixelFormatDetails const*
sdl3::pixel_format_details::native_handle()
{
    return _native_handle;
}
