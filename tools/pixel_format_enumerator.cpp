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

#include <iostream>
#include <vector>

#include "SDL3/SDL_pixels.h"

using namespace std;

int main()
{
    vector<SDL_PixelFormat> formats = {
        SDL_PIXELFORMAT_UNKNOWN,
        SDL_PIXELFORMAT_INDEX1LSB,
        SDL_PIXELFORMAT_INDEX1MSB,
        SDL_PIXELFORMAT_INDEX2LSB,
        SDL_PIXELFORMAT_INDEX2MSB,
        SDL_PIXELFORMAT_INDEX4LSB,
        SDL_PIXELFORMAT_INDEX4MSB,
        SDL_PIXELFORMAT_INDEX8,
        SDL_PIXELFORMAT_RGB332,
        SDL_PIXELFORMAT_XRGB4444,
        SDL_PIXELFORMAT_XBGR4444,
        SDL_PIXELFORMAT_XRGB1555,
        SDL_PIXELFORMAT_XBGR1555,
        SDL_PIXELFORMAT_ARGB4444,
        SDL_PIXELFORMAT_RGBA4444,
        SDL_PIXELFORMAT_ABGR4444,
        SDL_PIXELFORMAT_BGRA4444,
        SDL_PIXELFORMAT_ARGB1555,
        SDL_PIXELFORMAT_RGBA5551,
        SDL_PIXELFORMAT_ABGR1555,
        SDL_PIXELFORMAT_BGRA5551,
        SDL_PIXELFORMAT_RGB565,
        SDL_PIXELFORMAT_BGR565,
        SDL_PIXELFORMAT_RGB24,
        SDL_PIXELFORMAT_BGR24,
        SDL_PIXELFORMAT_XRGB8888,
        SDL_PIXELFORMAT_RGBX8888,
        SDL_PIXELFORMAT_XBGR8888,
        SDL_PIXELFORMAT_BGRX8888,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_PIXELFORMAT_ABGR8888,
        SDL_PIXELFORMAT_BGRA8888,
        SDL_PIXELFORMAT_XRGB2101010,
        SDL_PIXELFORMAT_XBGR2101010,
        SDL_PIXELFORMAT_ARGB2101010,
        SDL_PIXELFORMAT_ABGR2101010,
        SDL_PIXELFORMAT_RGB48,
        SDL_PIXELFORMAT_BGR48,
        SDL_PIXELFORMAT_RGBA64,
        SDL_PIXELFORMAT_ARGB64,
        SDL_PIXELFORMAT_BGRA64,
        SDL_PIXELFORMAT_ABGR64,
        SDL_PIXELFORMAT_RGB48_FLOAT,
        SDL_PIXELFORMAT_BGR48_FLOAT,
        SDL_PIXELFORMAT_RGBA64_FLOAT,
        SDL_PIXELFORMAT_ARGB64_FLOAT,
        SDL_PIXELFORMAT_BGRA64_FLOAT,
        SDL_PIXELFORMAT_ABGR64_FLOAT,
        SDL_PIXELFORMAT_RGB96_FLOAT,
        SDL_PIXELFORMAT_BGR96_FLOAT,
        SDL_PIXELFORMAT_RGBA128_FLOAT,
        SDL_PIXELFORMAT_ARGB128_FLOAT,
        SDL_PIXELFORMAT_BGRA128_FLOAT,
        SDL_PIXELFORMAT_ABGR128_FLOAT,
        SDL_PIXELFORMAT_YV12,
        SDL_PIXELFORMAT_IYUV,
        SDL_PIXELFORMAT_YUY2,
        SDL_PIXELFORMAT_UYVY,
        SDL_PIXELFORMAT_YVYU,
        SDL_PIXELFORMAT_NV12,
        SDL_PIXELFORMAT_NV21,
        SDL_PIXELFORMAT_P010,
        SDL_PIXELFORMAT_EXTERNAL_OES,
        SDL_PIXELFORMAT_MJPG,
    };

    for (auto format : formats)
    {
        SDL_PixelFormatDetails const* format_details = SDL_GetPixelFormatDetails(format);

        cout << "format: " << SDL_GetPixelFormatName(format) << endl;
        cout << "    bits_per_pixel: "  << dec << static_cast<Uint32>(format_details->bits_per_pixel) << endl;
        cout << "    bytes_per_pixel: " << dec << static_cast<Uint32>(format_details->bytes_per_pixel) << endl;
        cout << "    Rmask: "           << hex << "0x" << static_cast<Uint32>(format_details->Rmask) << endl;
        cout << "    Gmask: "           << hex << "0x" << static_cast<Uint32>(format_details->Gmask) << endl;
        cout << "    Bmask: "           << hex << "0x" << static_cast<Uint32>(format_details->Bmask) << endl;
        cout << "    Amask: "           << hex << "0x" << static_cast<Uint32>(format_details->Amask) << endl;
        cout << "    Rbits: "           << dec << static_cast<Uint32>(format_details->Rbits) << endl;
        cout << "    Gbits: "           << dec << static_cast<Uint32>(format_details->Gbits) << endl;
        cout << "    Bbits: "           << dec << static_cast<Uint32>(format_details->Bbits) << endl;
        cout << "    Abits: "           << dec << static_cast<Uint32>(format_details->Abits) << endl;
        cout << "    Rshift: "          << dec << static_cast<Uint32>(format_details->Rshift) << endl;
        cout << "    Gshift: "          << dec << static_cast<Uint32>(format_details->Gshift) << endl;
        cout << "    Bshift: "          << dec << static_cast<Uint32>(format_details->Bshift) << endl;
        cout << "    Ashift: "          << dec << static_cast<Uint32>(format_details->Ashift) << endl;
    }
   
    return 0;
}
