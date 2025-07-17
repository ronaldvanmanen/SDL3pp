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

#include <boost/operators.hpp>

namespace sdl3
{
    template<typename T, typename Tag>
    class base_color;

    template<typename T>
    struct base_color_traits { };

    template<typename T, typename Tag>
    struct base_color_traits<base_color<T, Tag>>
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

    template<typename Tag>
    struct base_color_traits<base_color<float, Tag>>
    {
        static constexpr base_color<float, Tag>(min)()
        {
            return base_color<float, Tag>(0.0f);
        }

        static constexpr base_color<float, Tag>(max)()
        {
            return base_color<float, Tag>(1.0f);
        }
    };

    template<typename Tag>
    struct base_color_traits<base_color<double, Tag>>
    {
        static constexpr base_color<double, Tag>(min)()
        {
            return base_color<double, Tag>(0.0);
        }

        static constexpr base_color<double, Tag>(max)()
        {
            return base_color<double, Tag>(1.0);
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
        explicit base_color(T value);

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

    private:
        T _value;
    };

    template<typename T, typename Tag>
    base_color<T, Tag>::base_color(T value)
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

    template<typename CharT, typename Traits, typename Tag, typename T>
    std::basic_ostream<CharT, Traits>&
    operator<<(std::basic_ostream<CharT, Traits>& stream, base_color<T, Tag> const& value)
    {
        return stream << static_cast<T>(value);
    }

    template<typename T>
    using alpha = base_color<T, struct alpha_tag>;
    using a8 = alpha<std::uint8_t>;
    using a32f = alpha<float>;

    template<typename T>
    using blue = base_color<T, struct blue_tag>;
    using b8 = blue<std::uint8_t>;
    using b32f = blue<float>;

    template<typename T>
    using green = base_color<T, struct green_tag>;
    using g8 = green<std::uint8_t>;
    using g32f = green<float>;

    template<typename T>
    using red = base_color<T, struct red_tag>;
    using r8 = red<std::uint8_t>;
    using r32f = red<float>;

    inline auto operator""_a8(unsigned long long value) { return a8(static_cast<a8::base_type>(value)); };
    inline auto operator""_b8(unsigned long long value) { return b8(static_cast<b8::base_type>(value)); };
    inline auto operator""_g8(unsigned long long value) { return g8(static_cast<g8::base_type>(value)); };
    inline auto operator""_r8(unsigned long long value) { return r8(static_cast<r8::base_type>(value)); };

    inline auto operator""_a32f(long double value) { return a32f(static_cast<a32f::base_type>(value)); };
    inline auto operator""_b32f(long double value) { return b32f(static_cast<b32f::base_type>(value)); };
    inline auto operator""_g32f(long double value) { return g32f(static_cast<g32f::base_type>(value)); };
    inline auto operator""_r32f(long double value) { return r32f(static_cast<r32f::base_type>(value)); };

}
