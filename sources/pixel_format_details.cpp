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

sdl3::pixel_format_details::pixel_format_details(sdl3::pixel_format_details const& other)
: _native_handle(other._native_handle)
{ }

sdl3::pixel_format_details::pixel_format_details(sdl3::pixel_format_details && other)
: _native_handle(other._native_handle)
{ }

std::uint8_t
sdl3::pixel_format_details::bits_per_pixel() const
{
    return _native_handle->bits_per_pixel;
}

std::uint8_t
sdl3::pixel_format_details::bytes_per_pixel() const
{
    return _native_handle->bytes_per_pixel;
}

std::uint32_t
sdl3::pixel_format_details::r_mask() const
{
    return _native_handle->Rmask;
}

std::uint32_t
sdl3::pixel_format_details::g_mask() const
{
    return _native_handle->Gmask;
}

std::uint32_t
sdl3::pixel_format_details::b_mask() const
{
    return _native_handle->Bmask;
}

std::uint32_t
sdl3::pixel_format_details::a_mask() const
{
    return _native_handle->Amask;
}

std::uint8_t
sdl3::pixel_format_details::g_bits() const
{
    return _native_handle->Gbits;
}

std::uint8_t
sdl3::pixel_format_details::r_bits() const
{
    return _native_handle->Rbits;
}

std::uint8_t
sdl3::pixel_format_details::b_bits() const
{
    return _native_handle->Bbits;
}

std::uint8_t
sdl3::pixel_format_details::a_bits() const
{
    return _native_handle->Abits;
}

std::uint8_t
sdl3::pixel_format_details::r_shift() const
{
    return _native_handle->Rshift;
}

std::uint8_t
sdl3::pixel_format_details::g_shift() const
{
    return _native_handle->Gshift;
}

std::uint8_t
sdl3::pixel_format_details::b_shift() const
{
    return _native_handle->Bshift;
}

std::uint8_t
sdl3::pixel_format_details::a_shift() const
{
    return _native_handle->Ashift;
}

SDL_PixelFormatDetails const*
sdl3::pixel_format_details::native_handle()
{
    return _native_handle;
}
