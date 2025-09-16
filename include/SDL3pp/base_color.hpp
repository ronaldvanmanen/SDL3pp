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
#include <limits>
#include <iostream>
#include <type_traits>

#include <boost/operators.hpp>

#include "numerics.hpp"

namespace sdl3
{
    template<typename T, typename Tag>
    class base_color;

    template<typename T>
    struct base_color_limits { };

    template<typename T, typename Tag>
    struct base_color_limits<base_color<T, Tag>>
    {
        static constexpr base_color<T, Tag>(min)()
        {
            return base_color<T, Tag>(std::numeric_limits<T>::min());
        }

        static constexpr base_color<T, Tag>(max)()
        {
            return base_color<T, Tag>(std::numeric_limits<T>::max());
        }
    };

    template<typename T, typename Tag>
    class alignas(alignof(T)) base_color
    : boost::totally_ordered<base_color<T, Tag>
    , boost::additive<base_color<T, Tag>
    , boost::multiplicative<base_color<T, Tag>
    , boost::multiplicative<base_color<T, Tag>, T
    , boost::unit_steppable<base_color<T, Tag>
    > > > > >
    {
    public:
        using base_type = T;

    public:
        base_color();

        explicit base_color(T value);

        template<class From>
            requires (!std::is_same_v<From, T> && std::is_convertible_v<From, T>)
        explicit base_color(From value);

        base_color(base_color<T, Tag> const& other);

        base_color<T, Tag> & operator=(base_color<T, Tag> const& other);

        base_color<T, Tag> & operator*=(base_color<T, Tag> const& other);

        base_color<T, Tag> & operator/=(base_color<T, Tag> const& other);

        base_color<T, Tag> & operator+=(base_color<T, Tag> const& other);

        base_color<T, Tag> & operator-=(base_color<T, Tag> const& other);

        base_color<T, Tag> & operator*=(T scalar);

        base_color<T, Tag> & operator/=(T scalar);

        base_color<T, Tag> & operator++();

        base_color<T, Tag> & operator--();

        bool operator==(base_color<T, Tag> const& other) const;

        bool operator<(base_color<T, Tag> const& other) const;

        operator T() const;

        template<class To>
            requires (!std::is_same_v<T, To> && std::is_convertible_v<T, To>)
        operator To() const;

    public:
        template<typename CharT, typename Traits>
        friend
        std::basic_ostream<CharT, Traits> &
        operator<<(std::basic_ostream<CharT, Traits> & stream, base_color<T, Tag> const& value)
        {
            return stream << value._value;
        }

    private:
        T _value;
    };

    template<typename T, typename Tag>
    base_color<T, Tag>::base_color()
    : _value()
    { }

    template<typename T, typename Tag>
    base_color<T, Tag>::base_color(T value)
    : _value(value)
    { }

    template<typename T, typename Tag>
        template<typename From>
            requires (!std::is_same_v<From, T> && std::is_convertible_v<From, T>)
    base_color<T, Tag>::base_color(From value)
    : _value(value)
    { }

    template<typename T, typename Tag>
    base_color<T, Tag>::base_color(base_color<T, Tag> const& other)
    : _value(other._value)
    { }

    template<typename T, typename Tag>
    base_color<T, Tag> &
    base_color<T, Tag>::operator=(base_color<T, Tag> const& other)
    {
        if (*this != other)
        {
            _value = other._value;
        }
        return *this;
    }

    template<typename T, typename Tag>
    base_color<T, Tag> &
    base_color<T, Tag>::operator*=(base_color<T, Tag> const& other)
    {
        _value *= other._value;
        return *this;
    }

    template<typename T, typename Tag>
    base_color<T, Tag> &
    base_color<T, Tag>::operator/=(base_color<T, Tag> const& other)
    {
        _value /= other._value;
        return *this;
    }

    template<typename T, typename Tag>
    base_color<T, Tag> &
    base_color<T, Tag>::operator+=(base_color<T, Tag> const& other)
    {
        _value += other._value;
        return *this;
    }

    template<typename T, typename Tag>
    base_color<T, Tag> &
    base_color<T, Tag>::operator-=(base_color<T, Tag> const& other)
    {
        _value -= other._value;
        return *this;
    }

    template<typename T, typename Tag>
    base_color<T, Tag> &
    base_color<T, Tag>::operator*=(T scalar)
    {
        _value *= scalar;
        return *this;
    }

    template<typename T, typename Tag>
    base_color<T, Tag> &
    base_color<T, Tag>::operator/=(T scalar)
    {
        _value /= scalar;
        return *this;
    }

    template<typename T, typename Tag>
    base_color<T, Tag> &
    base_color<T, Tag>::operator++()
    {
        ++_value;
        return *this;
    }

    template<typename T, typename Tag>
    base_color<T, Tag> &
    base_color<T, Tag>::operator--()
    {
        --_value;
        return *this;
    }

    template<typename T, typename Tag>
    bool
    base_color<T, Tag>::operator==(base_color<T, Tag> const& other) const
    {
        return _value == other._value;
    }

    template<typename T, typename Tag>
    bool
    base_color<T, Tag>::operator<(base_color<T, Tag> const& other) const
    {
        return _value < other._value;
    }

    template<typename T, typename Tag>
    base_color<T, Tag>::operator T() const
    {
        return _value;
    }

    template<typename T, typename Tag>
        template<class To>
            requires (!std::is_same_v<T, To> && std::is_convertible_v<T, To>)
    base_color<T, Tag>::operator To() const
    {
        return static_cast<To>(_value);
    }

    template<typename T>
    using red = base_color<T, struct red_tag>;

    using r3 = red<safe_uint3_t>;
    using r4 = red<safe_uint4_t>;
    using r5 = red<safe_uint5_t>;
    using r8 = red<safe_uint8_t>;
    using r10 = red<safe_uint10_t>;
    using r32f = red<safe_unorm_float>;

    inline auto operator""_r3(unsigned long long value) { return r3(value); };
    inline auto operator""_r4(unsigned long long value) { return r4(value); };
    inline auto operator""_r5(unsigned long long value) { return r5(value); };
    inline auto operator""_r8(unsigned long long value) { return r8(value); };
    inline auto operator""_r10(unsigned long long value) { return r10(value); };
    inline auto operator""_r32f(long double value) { return r32f(value); };

    template<typename T>
    using green = base_color<T, struct green_tag>;

    using g3 = green<safe_uint3_t>;
    using g4 = green<safe_uint4_t>;
    using g5 = green<safe_uint5_t>;
    using g6 = green<safe_uint6_t>;
    using g8 = green<safe_uint8_t>;
    using g10 = green<safe_uint10_t>;
    using g32f = green<safe_unorm_float>;

    inline auto operator""_g3(unsigned long long value) { return g3(value); };
    inline auto operator""_g4(unsigned long long value) { return g4(value); };
    inline auto operator""_g5(unsigned long long value) { return g5(value); };
    inline auto operator""_g6(unsigned long long value) { return g6(value); };
    inline auto operator""_g8(unsigned long long value) { return g8(value); };
    inline auto operator""_g10(unsigned long long value) { return g10(value); };
    inline auto operator""_g32f(long double value) { return g32f(value); };

    template<typename T>
    using blue = base_color<T, struct blue_tag>;

    using b2 = blue<safe_uint2_t>;
    using b4 = blue<safe_uint4_t>;
    using b5 = blue<safe_uint5_t>;
    using b8 = blue<safe_uint8_t>;
    using b10 = blue<safe_uint10_t>;
    using b32f = blue<safe_unorm_float>;

    inline auto operator""_b2(unsigned long long value) { return b2(value); };
    inline auto operator""_b4(unsigned long long value) { return b4(value); };
    inline auto operator""_b5(unsigned long long value) { return b5(value); };
    inline auto operator""_b8(unsigned long long value) { return b8(value); };
    inline auto operator""_b10(unsigned long long value) { return b10(value); };
    inline auto operator""_b32f(long double value) { return b32f(value); };

    template<typename T>
    using alpha = base_color<T, struct alpha_tag>;

    using a1 = alpha<safe_uint1_t>;
    using a2 = alpha<safe_uint2_t>;
    using a4 = alpha<safe_uint4_t>;
    using a8 = alpha<safe_uint8_t>;
    using a32f = alpha<safe_unorm_float>;

    inline auto operator""_a1(unsigned long long value) { return a1(value); };
    inline auto operator""_a2(unsigned long long value) { return a2(value); };
    inline auto operator""_a4(unsigned long long value) { return a4(value); };
    inline auto operator""_a8(unsigned long long value) { return a8(value); };
    inline auto operator""_a32f(long double value) { return a32f(value); };
}
