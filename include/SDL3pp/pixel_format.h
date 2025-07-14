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
    enum class pixel_format : std::uint32_t
    {
        unknown = SDL_PIXELFORMAT_UNKNOWN,
        index1lsb = SDL_PIXELFORMAT_INDEX1LSB,
        index1msb = SDL_PIXELFORMAT_INDEX1MSB,
        index4lsb = SDL_PIXELFORMAT_INDEX4LSB,
        index4msb = SDL_PIXELFORMAT_INDEX4MSB,
        index8 = SDL_PIXELFORMAT_INDEX8,
        rgb332 = SDL_PIXELFORMAT_RGB332,
        xrgb4444 = SDL_PIXELFORMAT_XRGB4444,
        rgb444 = SDL_PIXELFORMAT_XRGB4444,
        xbgr4444 = SDL_PIXELFORMAT_XBGR4444,
        bgr444 = SDL_PIXELFORMAT_XBGR4444,
        xrgb1555 = SDL_PIXELFORMAT_XRGB1555,
        rgb555 = SDL_PIXELFORMAT_XRGB1555,
        xbgr1555 = SDL_PIXELFORMAT_XBGR1555,
        bgr555 = SDL_PIXELFORMAT_XBGR1555,
        argb4444 = SDL_PIXELFORMAT_ARGB4444,
        rgba4444 = SDL_PIXELFORMAT_RGBA4444,
        abgr4444 = SDL_PIXELFORMAT_ABGR4444,
        bgra4444 = SDL_PIXELFORMAT_BGRA4444,
        argb1555 = SDL_PIXELFORMAT_ARGB1555,
        rgba5551 = SDL_PIXELFORMAT_RGBA5551,
        abgr1555 = SDL_PIXELFORMAT_ABGR1555,
        bgra5551 = SDL_PIXELFORMAT_BGRA5551,
        rgb565 = SDL_PIXELFORMAT_RGB565,
        bgr565 = SDL_PIXELFORMAT_BGR565,
        rgb24 = SDL_PIXELFORMAT_RGB24,
        bgr24 = SDL_PIXELFORMAT_BGR24,
        xrgb8888 = SDL_PIXELFORMAT_XRGB8888,
        rgb888 = SDL_PIXELFORMAT_XRGB8888,
        rgbx8888 = SDL_PIXELFORMAT_RGBX8888,
        xbgr8888 = SDL_PIXELFORMAT_XBGR8888,
        bgr888 = SDL_PIXELFORMAT_XBGR8888,
        bgrx8888 = SDL_PIXELFORMAT_BGRX8888,
        argb8888 = SDL_PIXELFORMAT_ARGB8888,
        rgba8888 = SDL_PIXELFORMAT_RGBA8888,
        abgr8888 = SDL_PIXELFORMAT_ABGR8888,
        bgra8888 = SDL_PIXELFORMAT_BGRA8888,
        argb2101010 = SDL_PIXELFORMAT_ARGB2101010,
        rgba32 = SDL_PIXELFORMAT_RGBA32,
        argb32 = SDL_PIXELFORMAT_ARGB32,
        bgra32 = SDL_PIXELFORMAT_BGRA32,
        abgr32 = SDL_PIXELFORMAT_ABGR32,

        rgb96f = SDL_PIXELFORMAT_RGB96_FLOAT,

        yv12 = SDL_PIXELFORMAT_YV12,
        iyuv = SDL_PIXELFORMAT_IYUV,
        yuy2 = SDL_PIXELFORMAT_YUY2,
        uyvy = SDL_PIXELFORMAT_UYVY,
        yvyu = SDL_PIXELFORMAT_YVYU,
        nv12 = SDL_PIXELFORMAT_NV12,
        nv21 = SDL_PIXELFORMAT_NV21,
        external_oes = SDL_PIXELFORMAT_EXTERNAL_OES
    };

    template<class CharT, class Traits>
    std::basic_ostream<CharT, Traits>&
    operator<<(std::basic_ostream<CharT, Traits>& stream, sdl3::pixel_format const& value)
    {
        switch (value)
        {
            case pixel_format::unknown: stream << "unknown"; break;
            case pixel_format::index1lsb: stream << "index1lsb"; break;
            case pixel_format::index1msb: stream << "index1msb"; break;
            case pixel_format::index4lsb: stream << "index4lsb"; break;
            case pixel_format::index4msb: stream << "index4msb"; break;
            case pixel_format::index8: stream << "index8"; break;
            case pixel_format::rgb332: stream << "rgb332"; break;
            case pixel_format::xrgb4444: stream << "xrgb4444"; break;
            case pixel_format::xbgr4444: stream << "xbgr4444"; break;
            case pixel_format::xrgb1555: stream << "xrgb1555"; break;
            case pixel_format::xbgr1555: stream << "xbgr1555"; break;
            case pixel_format::argb4444: stream << "argb4444"; break;
            case pixel_format::rgba4444: stream << "rgba4444"; break;
            case pixel_format::abgr4444: stream << "abgr4444"; break;
            case pixel_format::bgra4444: stream << "bgra4444"; break;
            case pixel_format::argb1555: stream << "argb1555"; break;
            case pixel_format::rgba5551: stream << "rgba5551"; break;
            case pixel_format::abgr1555: stream << "abgr1555"; break;
            case pixel_format::bgra5551: stream << "bgra5551"; break;
            case pixel_format::rgb565: stream << "rgb565"; break;
            case pixel_format::bgr565: stream << "bgr565"; break;
            case pixel_format::rgb24: stream << "rgb24"; break;
            case pixel_format::bgr24: stream << "bgr24"; break;
            case pixel_format::xrgb8888: stream << "xrgb8888"; break;
            case pixel_format::rgbx8888: stream << "rgbx8888"; break;
            case pixel_format::xbgr8888: stream << "xbgr8888"; break;
            case pixel_format::bgrx8888: stream << "bgrx8888"; break;
            case pixel_format::argb8888: stream << "argb8888"; break;
            case pixel_format::rgba8888: stream << "rgba8888"; break;
            case pixel_format::abgr8888: stream << "abgr8888"; break;
            case pixel_format::bgra8888: stream << "bgra8888"; break;
            case pixel_format::argb2101010: stream << "argb2101010"; break;
            case pixel_format::yv12: stream << "yv12"; break;
            case pixel_format::iyuv: stream << "iyuv"; break;
            case pixel_format::yuy2: stream << "yuy2"; break;
            case pixel_format::uyvy: stream << "uyvy"; break;
            case pixel_format::yvyu: stream << "yvyu"; break;
            case pixel_format::nv12: stream << "nv12"; break;
            case pixel_format::nv21: stream << "nv21"; break;
            case pixel_format::external_oes: stream << "external_oes"; break;
        }
        return stream;
    }
}
