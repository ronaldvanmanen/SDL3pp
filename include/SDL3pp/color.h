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

#include <iostream>
#include <cstdint>

#include <boost/operators.hpp>

#include <SDL3/SDL_pixels.h>

#include "base_color.h"

namespace sdl3
{
    class alignas(alignof(SDL_Color)) color
    : boost::equality_comparable<color
    , boost::additive<color
    , boost::multiplicative<color
    , boost::multiplicative<color, std::uint8_t
    > > > >
    {
    public:
        static const color black;

        static const color white;

        static const color red;

        static const color green;

        static const color blue;

    public:
        color();
        
        color(r8 r, g8 g, b8 b, a8 a);

        color(color const& other);

        color & operator=(color const& other);

        color & operator*=(color const& other);

        color & operator/=(color const& other);

        color & operator+=(color const& other);

        color & operator-=(color const& other);

        color & operator*=(std::uint8_t scalar);

        color & operator/=(std::uint8_t scalar);

        bool operator==(color const& other) const;

    public:
        r8 r;
        g8 g;
        b8 b;
        a8 a;
    };

    template<class CharT, class Traits>
    std::basic_ostream<CharT, Traits>&
    operator<<(std::basic_ostream<CharT, Traits>& stream, color const& value)
    {
        return stream << value.r << ',' << value.g << ',' << value.b << ',' << value.a;
    }
}
