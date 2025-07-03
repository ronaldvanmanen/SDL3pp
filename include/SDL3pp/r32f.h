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

#include "real.h"

namespace sdl3
{
    SDL3PP_REAL_DECL(r32f, float)

    inline
    sdl3::r32f operator""_r32f(unsigned long long value) 
    {
        return sdl3::r32f(static_cast<float>(value));
    }

    inline
    sdl3::r32f operator""_r32f(long double value) 
    {
        return sdl3::r32f(static_cast<float>(value));
    }
}
