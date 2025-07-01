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

#include <boost/operators.hpp>

#include "a8.h"
#include "b8.h"
#include "color_space.h"
#include "g8.h"
#include "pixel_format.h"
#include "r8.h"

namespace sdl3
{
    template<color_space ColorSpace>
    class alignas(alignof(std::uint32_t)) argb8888
    : public boost::equality_comparable<argb8888<ColorSpace> >
    {
    public:
        static constexpr pixel_format format = pixel_format::argb8888;

        static constexpr color_space color_space = ColorSpace;

        static const argb8888 black;

        static const argb8888 white;

    public:
        argb8888();

        argb8888(a8 a, r8 r, g8 g, b8 b);

        argb8888(argb8888 const& other);

        argb8888& operator=(argb8888 const& other);

        bool operator==(argb8888 const& other) const;

    public:
        b8 b;
        g8 g;
        r8 r;
        a8 a;
    };

    using sargb8888 = argb8888<color_space::srgb>;

    template<color_space ColorSpace>
    const argb8888<ColorSpace> argb8888<ColorSpace>::black(255_a8, 0_r8, 0_g8, 0_b8);

    template<color_space ColorSpace>
    const argb8888<ColorSpace> argb8888<ColorSpace>::white(255_a8, 255_r8, 255_g8, 255_b8);

    template<color_space ColorSpace>
    argb8888<ColorSpace>::argb8888()
    : argb8888(0_a8, 0_r8, 0_g8, 0_b8)
    { }

    template<color_space ColorSpace>
    argb8888<ColorSpace>::argb8888(a8 a, r8 r, g8 g, b8 b)
    : b(b), r(r), g(g), a(a)
    { }

    template<color_space ColorSpace>
    argb8888<ColorSpace>::argb8888(argb8888<ColorSpace> const& other)
    : b(other.b), r(other.r), g(other.g), a(other.a)
    { }

    template<color_space ColorSpace>
    argb8888<ColorSpace>&
    argb8888<ColorSpace>::operator=(argb8888<ColorSpace> const& other)
    {
        if (this != &other)
        {
            b = other.b;
            r = other.r;
            g = other.g;
            a = other.a;
        }
        return *this;
    }

    template<color_space ColorSpace>
    bool
    argb8888<ColorSpace>::operator==(argb8888<ColorSpace> const& other) const
    {
        return b == other.b && r == other.r && g == other.g && a == other.a;
    }

    template<color_space ColorSpace>
    std::ostream&
    operator<<(std::ostream& stream, argb8888<ColorSpace> const& value)
    {
        return stream
            << static_cast<unsigned int>(value.a)
            << ','
            << static_cast<unsigned int>(value.r)
            << ','
            << static_cast<unsigned int>(value.g)
            << ','
            << static_cast<unsigned int>(value.b);
    }
}
