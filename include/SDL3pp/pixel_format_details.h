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

#include <SDL3/SDL_pixels.h>

#include "pixels.h"

namespace sdl3
{
    class pixel_format_details
    {
    public:
        pixel_format_details(pixel_format format);

        pixel_format_details(SDL_PixelFormatDetails const* native_handle);

        pixel_format_details(pixel_format_details const& other);

        pixel_format_details(pixel_format_details && other);

        std::uint8_t bits_per_pixel() const;

        std::uint8_t bytes_per_pixel() const;

        std::uint32_t r_mask() const;

        std::uint32_t g_mask() const;

        std::uint32_t b_mask() const;

        std::uint32_t a_mask() const;

        std::uint8_t g_bits() const;

        std::uint8_t r_bits() const;

        std::uint8_t b_bits() const;

        std::uint8_t a_bits() const;

        std::uint8_t r_shift() const;

        std::uint8_t g_shift() const;

        std::uint8_t b_shift() const;

        std::uint8_t a_shift() const;
        
        SDL_PixelFormatDetails const* native_handle();

    private:
        SDL_PixelFormatDetails const* _native_handle;
    };
}
