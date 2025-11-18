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

#include <boost/operators.hpp>

#include <SDL3/SDL.h>

#include "base_color.hpp"

namespace sdl3
{
    class alignas(alignof(SDL_Color)) color
    // clang-format off
    : boost::equality_comparable<color
    , boost::additive<color
    , boost::multiplicative<color
    , boost::multiplicative<color, clamped_uint8_t
    > > > >
    // clang-format on
    {
    public:
        static const color black;

        static const color white;

        static const color red;

        static const color green;

        static const color blue;

    public:
        color()
        : r(0_r8)
        , g(0_g8)
        , b(0_b8)
        , a(0_a8)
        { }

        color(r8 r, g8 g, b8 b, a8 a)
        : r(r)
        , g(g)
        , b(b)
        , a(a)
        { }

        color(color const & other)
        : r(other.r)
        , g(other.g)
        , b(other.b)
        , a(other.a)
        { }

        color & operator=(color const & other)
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

        color & operator*=(color const & other)
        {
            r *= other.r;
            g *= other.g;
            b *= other.b;
            a *= other.a;
            return *this;
        }

        color & operator/=(color const & other)
        {
            r /= other.r;
            g /= other.g;
            b /= other.b;
            a /= other.a;
            return *this;
        }

        color & operator+=(color const & other)
        {
            r += other.r;
            g += other.g;
            b += other.b;
            a += other.a;
            return *this;
        }

        color & operator-=(color const & other)
        {
            r -= other.r;
            g -= other.g;
            b -= other.b;
            a -= other.a;
            return *this;
        }

        color & operator*=(clamped_uint8_t scalar)
        {
            r *= scalar;
            g *= scalar;
            b *= scalar;
            a *= scalar;
            return *this;
        }

        color & operator/=(clamped_uint8_t scalar)
        {
            r /= scalar;
            g /= scalar;
            b /= scalar;
            a /= scalar;
            return *this;
        }

        bool operator==(color const & other) const
        {
            return r == other.r && g == other.g && b == other.b && a == other.a;
        }

    public:
        r8 r;
        g8 g;
        b8 b;
        a8 a;
    };

    inline const color color::black(0_r8, 0_g8, 0_b8, 255_a8);

    inline const color color::white(255_r8, 255_g8, 255_b8, 255_a8);

    inline const color color::red(255_r8, 0_g8, 0_b8, 255_a8);

    inline const color color::green(0_r8, 255_g8, 0_b8, 255_a8);

    inline const color color::blue(0_r8, 0_g8, 255_b8, 255_a8);

    template <class CharT, class Traits>
    std::basic_ostream<CharT, Traits> & operator<<(std::basic_ostream<CharT, Traits> & stream, color const & value)
    {
        return stream << value.r << ',' << value.g << ',' << value.b << ',' << value.a;
    }
}  // namespace sdl3
