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
#include "color.h"
#include "pixel_format.h"

namespace sdl3
{
    template<color_space ColorSpace, typename T>
    class alignas(alignof(T)) array_color
    : boost::equality_comparable<array_color<ColorSpace, T>
    , boost::additive<array_color<ColorSpace, T>
    , boost::multiplicative<array_color<ColorSpace, T>
    , boost::multiplicative<array_color<ColorSpace, T>, T
    > > > >
    {
    public:
        static constexpr pixel_format format = pixel_format::rgb96f;

        static constexpr color_space color_space = ColorSpace;

        static const array_color<ColorSpace, T> black;

        static const array_color<ColorSpace, T> white;

    public:
        array_color();

        array_color(red<T> r, green<T> g, blue<T> b);

        array_color(array_color<ColorSpace, T> const& other);

        array_color<ColorSpace, T> & operator=(array_color<ColorSpace, T> const& other);

        array_color<ColorSpace, T> & operator*=(array_color<ColorSpace, T> const& other);

        array_color<ColorSpace, T> & operator/=(array_color<ColorSpace, T> const& other);

        array_color<ColorSpace, T> & operator+=(array_color<ColorSpace, T> const& other);

        array_color<ColorSpace, T> & operator-=(array_color<ColorSpace, T> const& other);
        
        array_color<ColorSpace, T> & operator*=(T scalar);

        array_color<ColorSpace, T> & operator/=(T scalar);

        bool operator==(array_color<ColorSpace, T> const& other) const;

    public:
        red<T> r;
        green<T> g;
        blue<T> b;
    };

    using srgb96f = array_color<color_space::srgb, float>;

    template<color_space ColorSpace, typename T>
    array_color<ColorSpace, T> const array_color<ColorSpace, T>::black(0.0f, 0.0f, 0.0f);

    template<color_space ColorSpace, typename T>
    array_color<ColorSpace, T> const array_color<ColorSpace, T>::white(1.0f, 1.0f, 1.0f);

    template<color_space ColorSpace, typename T>
    array_color<ColorSpace, T>::array_color()
    : r(0.0f)
    , g(0.0f)
    , b(0.0f)
    { }

    template<color_space ColorSpace, typename T>
    array_color<ColorSpace, T>::array_color(red<T> r, green<T> g, blue<T> b)
    : r(r)
    , g(g)
    , b(b)
    { }

    template<color_space ColorSpace, typename T>
    array_color<ColorSpace, T>::array_color(array_color<ColorSpace, T> const& other)
    : r(other.r)
    , g(other.g)
    , b(other.b)
    { }

    template<color_space ColorSpace, typename T>
    array_color<ColorSpace, T> &
    array_color<ColorSpace, T>::operator=(array_color<ColorSpace, T> const& other)
    {
        r = other.r;
        g = other.g;
        b = other.b;
        return *this;
    }
            
    template<color_space ColorSpace, typename T>
    array_color<ColorSpace, T> &
    array_color<ColorSpace, T>::operator*=(array_color<ColorSpace, T> const& other)
    {
        r *= other.r;
        g *= other.g;
        b *= other.b;
        return *this;
    }

    template<color_space ColorSpace, typename T>
    array_color<ColorSpace, T> &
    array_color<ColorSpace, T>::operator/=(array_color<ColorSpace, T> const& other)
    {
        r /= other.r;
        g /= other.g;
        b /= other.b;
        return *this;
    }

    template<color_space ColorSpace, typename T>
    array_color<ColorSpace, T> &
    array_color<ColorSpace, T>::operator+=(array_color<ColorSpace, T> const& other)
    {
        r += other.r;
        g += other.g;
        b += other.b;
        return *this;
    }

    template<color_space ColorSpace, typename T>
    array_color<ColorSpace, T> &
    array_color<ColorSpace, T>::operator-=(array_color<ColorSpace, T> const& other)
    {
        r -= other.r;
        g -= other.g;
        b -= other.b;
        return *this;
    }

    template<color_space ColorSpace, typename T>
    array_color<ColorSpace, T> &
    array_color<ColorSpace, T>::operator*=(T scalar)
    {
        r *= scalar;
        g *= scalar;
        b *= scalar;
        return *this;
    }

    template<color_space ColorSpace, typename T>
    array_color<ColorSpace, T> &
    array_color<ColorSpace, T>::operator/=(T scalar)
    {
        r /= scalar;
        g /= scalar;
        b /= scalar;
        return *this;
    }

    template<color_space ColorSpace, typename T>
    bool
    array_color<ColorSpace, T>::operator==(array_color<ColorSpace, T> const& other) const
    {
        return r == other.r && g == other.g && b == other.b;
    }

    template<color_space ColorSpace, typename T>
    inline
    array_color<ColorSpace, T>
    mix(array_color<ColorSpace, T> const& color0, array_color<ColorSpace, T> const& color1, float value)
    {
        return (1.0f - value) * color0 + value * color1;
    }    
}
