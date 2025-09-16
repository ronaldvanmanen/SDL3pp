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

#include "SDL3pp/color.hpp"

const sdl3::color sdl3::color::black(0_r8, 0_g8, 0_b8, 255_a8);

const sdl3::color sdl3::color::white(255_r8, 255_g8, 255_b8, 255_a8);

const sdl3::color sdl3::color::red(255_r8, 0_g8, 0_b8, 255_a8);

const sdl3::color sdl3::color::green(0_r8, 255_g8, 0_b8, 255_a8);

const sdl3::color sdl3::color::blue(0_r8, 0_g8, 255_b8, 255_a8);

sdl3::color::color()
: r(0_r8), g(0_g8), b(0_b8), a(0_a8)
{ }

sdl3::color::color(sdl3::r8 r, sdl3::g8 g, sdl3::b8 b, sdl3::a8 a)
: r(r), g(g), b(b), a(a)
{ }

sdl3::color::color(sdl3::color const& other)
: r(other.r), g(other.g), b(other.b), a(other.a)
{ }

sdl3::color &
sdl3::color::operator=(sdl3::color const& other)
{
    if (*this != other)
    {
        r = other.r;
        g = other.g;
        b = other.b;
        a = other.a;
    }
    return *this;
}

sdl3::color &
sdl3::color::operator*=(sdl3::color const& other)
{
    // NOTE: Call member operator*=, otherwise MSVC will fail with error C2968: recursive
    // alias declaration. See https://github.com/boostorg/safe_numerics/issues/135 for
    // more details.
    r.operator*=(other.r);
    g.operator*=(other.g);
    b.operator*=(other.b);
    a.operator*=(other.a);
    return *this;
}

sdl3::color &
sdl3::color::operator/=(sdl3::color const& other)
{
    // NOTE: Call member operator/=, otherwise MSVC will fail with error C2968: recursive
    // alias declaration. See https://github.com/boostorg/safe_numerics/issues/135 for
    // more details.
    r.operator/=(other.r);
    g.operator/=(other.g);
    b.operator/=(other.b);
    a.operator/=(other.a);
    return *this;
}

sdl3::color &
sdl3::color::operator+=(sdl3::color const& other)
{
    // NOTE: Call member operator+=, otherwise MSVC will fail with error C2968: recursive
    // alias declaration. See https://github.com/boostorg/safe_numerics/issues/135 for
    // more details.
    r.operator+=(other.r);
    g.operator+=(other.g);
    b.operator+=(other.b);
    a.operator+=(other.a);
    return *this;
}

sdl3::color &
sdl3::color::operator-=(sdl3::color const& other)
{
    // NOTE: Call member operator-=, otherwise MSVC will fail with error C2968: recursive
    // alias declaration. See https://github.com/boostorg/safe_numerics/issues/135 for
    // more details.
    r.operator-=(other.r);
    g.operator-=(other.g);
    b.operator-=(other.b);
    a.operator-=(other.a);
    return *this;
}

sdl3::color &
sdl3::color::operator*=(safe_uint8_t scalar)
{
    // NOTE: Call member operator*=, otherwise MSVC will fail with error C2968: recursive
    // alias declaration. See https://github.com/boostorg/safe_numerics/issues/135 for
    // more details.
    r.operator*=(scalar);
    g.operator*=(scalar);
    b.operator*=(scalar);
    a.operator*=(scalar);
    return *this;
}

sdl3::color &
sdl3::color::operator/=(safe_uint8_t scalar)
{
    // NOTE: Call member operator/=, otherwise MSVC will fail with error C2968: recursive
    // alias declaration. See https://github.com/boostorg/safe_numerics/issues/135 for
    // more details.
    r.operator/=(scalar);
    g.operator/=(scalar);
    b.operator/=(scalar);
    a.operator/=(scalar);
    return *this;
}

bool
sdl3::color::operator==(sdl3::color const& other) const
{
    return r == other.r && g == other.g && b == other.b && a == other.a;
}
