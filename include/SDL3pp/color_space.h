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
#include <iostream>

#include <SDL3/SDL_pixels.h>

namespace sdl3
{
    enum class color_space : std::uint32_t
    {
        unknown = SDL_COLORSPACE_UNKNOWN,
        srgb = SDL_COLORSPACE_SRGB,
        srgb_linear = SDL_COLORSPACE_SRGB_LINEAR,
        hdr10 = SDL_COLORSPACE_HDR10,
        jpeg = SDL_COLORSPACE_JPEG,
        bt601_limited = SDL_COLORSPACE_BT601_LIMITED,
        bt601_full = SDL_COLORSPACE_BT601_FULL,
        bt709_limited = SDL_COLORSPACE_BT709_LIMITED,
        bt709_full = SDL_COLORSPACE_BT709_FULL,
        bt2020_limited = SDL_COLORSPACE_BT2020_LIMITED,
        bt2020_full = SDL_COLORSPACE_BT2020_FULL,
    };

    inline
    std::ostream& operator<<(std::ostream& stream, color_space const& value)
    {
        switch(value)
        {
            case color_space::unknown: stream << "unknown";
            case color_space::srgb: stream << "srgb";
            case color_space::srgb_linear: stream << "srgb_linear";
            case color_space::hdr10: stream << "hdr10";
            case color_space::jpeg: stream << "jpeg";
            case color_space::bt601_limited: stream << "bt601_limited";
            case color_space::bt601_full: stream << "bt601_full";
            case color_space::bt709_limited: stream << "bt709_limited";
            case color_space::bt709_full: stream << "bt709_full";
            case color_space::bt2020_limited: stream << "bt2020_limited";
            case color_space::bt2020_full: stream << "bt2020_full";
        }
        return stream;
    }
}
