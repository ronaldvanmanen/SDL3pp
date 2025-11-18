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

#include "pixels.hpp"

namespace sdl3
{
    class alignas(alignof(std::uint8_t)) index8
    // clang-format off
    : boost::totally_ordered<index8
    , boost::additive<index8
    , boost::multiplicative<index8
    , boost::unit_steppable<index8
    > > > >
    // clang-format on
    {
    public:
        static constexpr pixel_format format = pixel_format::index8;

    public:
        index8()
        : _value(static_cast<std::uint8_t>(0))
        { }

        index8(std::uint8_t value)
        : _value(value)
        { }

        index8(index8 const & other)
        : _value(other._value)
        { }

        index8 & operator=(index8 const & other)
        {
            if (this != &other)
            {
                _value = other._value;
            }
            return *this;
        }

        index8 & operator+=(index8 const & other)
        {
            _value += other._value;
            return *this;
        }

        index8 & operator-=(index8 const & other)
        {
            _value += other._value;
            return *this;
        }

        index8 & operator++()
        {
            ++_value;
            return *this;
        }

        index8 & operator--()
        {
            --_value;
            return *this;
        }

        bool operator==(index8 const & other) const
        {
            return _value == other._value;
        }

        bool operator<(index8 const & other) const
        {
            return _value < other._value;
        }

        operator std::uint8_t() const
        {
            return _value;
        }

    private:
        std::uint8_t _value;
    };

    template <color_space C>
        requires(is_rgb_color_space<C>())
    struct pixel_color<pixel_format::index8, C>
    {
        using type = index8;
    };
}  // namespace sdl3
