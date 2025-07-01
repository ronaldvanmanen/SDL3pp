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

#include "color_space.h"
#include "pixel_format.h"

namespace sdl3
{
    template<color_space ColorSpace>
    class alignas(alignof(std::uint8_t)) index8
    : public boost::operators<index8<ColorSpace>
    >
    {
    public:
        static constexpr pixel_format format = pixel_format::index8;

        static constexpr color_space color_space = ColorSpace;

    public:
        index8();

        index8(std::uint8_t value);

        index8(index8<ColorSpace> const& other);

        index8<ColorSpace> & operator=(index8 const& other);

        index8<ColorSpace> & operator+=(index8 const& other);

        index8<ColorSpace> & operator-=(index8 const& other);

        index8<ColorSpace> & operator++();

        index8<ColorSpace> & operator--();

        bool operator==(index8<ColorSpace> const& other) const;

        bool operator<(index8<ColorSpace> const& other) const;

        operator std::uint8_t() const;

    private:
        std::uint8_t _value;
    };

    using sindex8 = index8<color_space::srgb>;

    template<color_space ColorSpace>
    index8<ColorSpace>::index8() { }

    template<color_space ColorSpace>
    index8<ColorSpace>::index8(std::uint8_t value)
    : _value(value)
    { }

    template<color_space ColorSpace>
    index8<ColorSpace>::index8(index8 const& other)
    : _value(other._value)
    { }

    template<color_space ColorSpace>
    index8<ColorSpace> &
    index8<ColorSpace>::operator=(index8<ColorSpace> const& other)
    {
        if (this != &other)
        {
            _value = other._value;
        }
        return *this;    
    }

    template<color_space ColorSpace>
    index8<ColorSpace> &
    index8<ColorSpace>::operator+=(index8<ColorSpace> const& other)
    {
        _value += other._value;
        return *this;    
    }

    template<color_space ColorSpace>
    index8<ColorSpace> &
    index8<ColorSpace>::operator-=(index8<ColorSpace> const& other)
    {
        _value += other._value;
        return *this;    
    }

    template<color_space ColorSpace>
    index8<ColorSpace> &
    index8<ColorSpace>::operator++()
    {
        ++_value;
        return *this;
    }

    template<color_space ColorSpace>
    index8<ColorSpace> &
    index8<ColorSpace>::operator--()
    {
        --_value;
        return *this;
    }

    template<color_space ColorSpace>
    bool
    index8<ColorSpace>::operator==(index8<ColorSpace> const& other) const
    {
        return _value == other._value;
    }

    template<color_space ColorSpace>
    bool
    index8<ColorSpace>::operator<(index8<ColorSpace> const& other) const
    {
        return _value < other._value;
    }

    template<color_space ColorSpace>
    index8<ColorSpace>::operator std::uint8_t() const
    {
        return _value;
    }    
}
 