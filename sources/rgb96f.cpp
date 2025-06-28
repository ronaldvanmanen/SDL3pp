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

#include <algorithm>

#include "SDL3pp/rgb96f.h"

const sdl3::rgb96f sdl3::rgb96f::black(0.0f, 0.0f, 0.0f);

const sdl3::rgb96f sdl3::rgb96f::white(1.0f, 1.0f, 1.0f);

sdl3::rgb96f::rgb96f()
: b(0.0f)
, g(0.0f)
, r(0.0f)
{ }

sdl3::rgb96f::rgb96f(float r, float g, float b)
: b(b)
, g(g)
, r(r)
{ }

sdl3::rgb96f::rgb96f(rgb96f const& other)
: b(other.b)
, g(other.g)
, r(other.r)
{ }

sdl3::rgb96f&
sdl3::rgb96f::clamp()
{
    b = std::clamp(b, 0.0f, 1.0f);
    g = std::clamp(g, 0.0f, 1.0f);
    r = std::clamp(r, 0.0f, 1.0f);
    return *this;
}

sdl3::rgb96f
sdl3::rgb96f::clamped() const
{
    return sdl3::rgb96f(
        std::clamp(r, 0.0f, 1.0f),
        std::clamp(g, 0.0f, 1.0f),
        std::clamp(b, 0.0f, 1.0f)
    );
}

bool
sdl3::rgb96f::operator==(sdl3::rgb96f const& other) const
{
    return r == other.r && g == other.g && b == other.b;
}

sdl3::rgb96f&
sdl3::rgb96f::operator+=(sdl3::rgb96f const& other)
{
    b += other.b;
    g += other.g;
    r += other.r;
    return *this;
}
        
sdl3::rgb96f&
sdl3::rgb96f::operator*=(sdl3::rgb96f const& other)
{
    b *= other.b;
    g *= other.g;
    r *= other.r;
    return *this;
}

sdl3::rgb96f&
sdl3::rgb96f::operator*=(float scalar)
{
    b *= scalar;
    g *= scalar;
    r *= scalar;
    return *this;
}
