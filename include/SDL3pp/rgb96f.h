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

#include <boost/operators.hpp>

#include "color_space.h"
#include "pixel_format.h"

namespace sdl3
{
    template<color_space ColorSpace>
    class alignas(alignof(float)) rgb96f
    : boost::equality_comparable<rgb96f<ColorSpace>
    , boost::addable<rgb96f<ColorSpace>
    , boost::multipliable<rgb96f<ColorSpace>
    , boost::multipliable<rgb96f<ColorSpace>, float
    , boost::dividable<rgb96f<ColorSpace>, float
    > > > > >
    {
    public:
        static constexpr pixel_format format = pixel_format::rgb96f;

        static constexpr color_space color_space = ColorSpace;

        static const rgb96f black;

        static const rgb96f white;

    public:
        rgb96f();

        rgb96f(float r, float g, float b);

        rgb96f(rgb96f<ColorSpace> const& other);

        bool operator==(rgb96f<ColorSpace> const& other) const;

        rgb96f<ColorSpace>& operator=(rgb96f<ColorSpace> const& other);

        rgb96f<ColorSpace>& operator+=(rgb96f<ColorSpace> const& other);
        
        rgb96f<ColorSpace>& operator*=(rgb96f<ColorSpace> const& other);

        rgb96f<ColorSpace>& operator*=(float scalar);

        rgb96f<ColorSpace>& operator/=(float scalar);

    public:
        float r, g, b;
    };

    using srgb96f = rgb96f<color_space::srgb>;

    template<color_space ColorSpace>
    rgb96f<ColorSpace> const rgb96f<ColorSpace>::black(0.0f, 0.0f, 0.0f);

    template<color_space ColorSpace>
    rgb96f<ColorSpace> const rgb96f<ColorSpace>::white(1.0f, 1.0f, 1.0f);

    template<color_space ColorSpace>
    rgb96f<ColorSpace>::rgb96f()
    : r(0.0f)
    , g(0.0f)
    , b(0.0f)
    { }

    template<color_space ColorSpace>
    rgb96f<ColorSpace>::rgb96f(float r, float g, float b)
    : r(r)
    , g(g)
    , b(b)
    { }

    template<color_space ColorSpace>
    rgb96f<ColorSpace>::rgb96f(rgb96f<ColorSpace> const& other)
    : r(other.r)
    , g(other.g)
    , b(other.b)
    { }

    template<color_space ColorSpace>
    bool
    rgb96f<ColorSpace>::operator==(rgb96f<ColorSpace> const& other) const
    {
        return r == other.r && g == other.g && b == other.b;
    }

    template<color_space ColorSpace>
    rgb96f<ColorSpace> &
    rgb96f<ColorSpace>::operator=(rgb96f<ColorSpace> const& other)
    {
        r = other.r;
        g = other.g;
        b = other.b;
        return *this;
    }

    template<color_space ColorSpace>
    rgb96f<ColorSpace> &
    rgb96f<ColorSpace>::operator+=(rgb96f<ColorSpace> const& other)
    {
        r += other.r;
        g += other.g;
        b += other.b;
        return *this;
    }
            
    template<color_space ColorSpace>
    rgb96f<ColorSpace> &
    rgb96f<ColorSpace>::operator*=(rgb96f<ColorSpace> const& other)
    {
        r *= other.r;
        g *= other.g;
        b *= other.b;
        return *this;
    }

    template<color_space ColorSpace>
    rgb96f<ColorSpace> &
    rgb96f<ColorSpace>::operator*=(float scalar)
    {
        r *= scalar;
        g *= scalar;
        b *= scalar;
        return *this;
    }

    template<color_space ColorSpace>
    rgb96f<ColorSpace> &
    rgb96f<ColorSpace>::operator/=(float scalar)
    {
        r /= scalar;
        g /= scalar;
        b /= scalar;
        return *this;
    }

    template<color_space ColorSpace>
    inline
    rgb96f<ColorSpace>
    mix(rgb96f<ColorSpace> const& color0, rgb96f<ColorSpace> const& color1, float value)
    {
        return (1.0f - value) * color0 + value * color1;
    }    
}
