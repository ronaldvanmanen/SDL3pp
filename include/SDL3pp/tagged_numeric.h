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

#include <boost/operators.hpp>

namespace sdl3
{
    template<typename T, typename Tag>
    class tagged_numeric;
}

namespace std
{
    template<typename T, typename Tag>
    struct numeric_limits<sdl3::tagged_numeric<T, Tag> >
    {
        static constexpr bool has_infinity             = numeric_limits<T>::has_infinity;
        
        static constexpr bool has_quiet_NaN            = numeric_limits<T>::has_quiet_NaN;
        
        static constexpr bool has_signaling_NaN        = numeric_limits<T>::has_signaling_NaN;
        
        static constexpr bool is_bounded               = numeric_limits<T>::is_bounded;
        
        static constexpr bool is_exact                 = numeric_limits<T>::is_exact;
        
        static constexpr bool is_iec559                = numeric_limits<T>::is_iec559;
        
        static constexpr bool is_integer               = numeric_limits<T>::is_integer;
        
        static constexpr bool is_modulo                = numeric_limits<T>::is_modulo;
        
        static constexpr bool is_signed                = numeric_limits<T>::is_signed;
        
        static constexpr bool tinyness_before          = numeric_limits<T>::tinyness_before;
        
        static constexpr bool traps                    = numeric_limits<T>::traps;
        
        static constexpr float_round_style round_style = numeric_limits<T>::round_style;
        
        static constexpr int digits                    = numeric_limits<T>::digits;
        
        static constexpr int digits10                  = numeric_limits<T>::digits10;
        
        static constexpr int max_digits10              = numeric_limits<T>::max_digits10;
        
        static constexpr int max_exponent              = numeric_limits<T>::max_exponent;
        
        static constexpr int max_exponent10            = numeric_limits<T>::max_exponent10;
        
        static constexpr int min_exponent              = numeric_limits<T>::min_exponent;
        
        static constexpr int min_exponent10            = numeric_limits<T>::min_exponent10;
        
        static constexpr int radix                     = numeric_limits<T>::radix;

        static constexpr sdl3::tagged_numeric<T, Tag>(min)() noexcept {
            return sdl3::tagged_numeric<T, Tag>(
                numeric_limits<T>::min()
            );
        }

        static constexpr sdl3::tagged_numeric<T, Tag>(max)() noexcept {
            return sdl3::tagged_numeric<T, Tag>(
                numeric_limits<T>::max()
            );
        }

        static constexpr sdl3::tagged_numeric<T, Tag> lowest() noexcept {
            return sdl3::tagged_numeric<T, Tag>(
                numeric_limits<T>::lowest()
            );
        }

        static constexpr sdl3::tagged_numeric<T, Tag> epsilon() noexcept {
            return sdl3::tagged_numeric<T, Tag>(
                numeric_limits<T>::epsilon()
            );
        }

        static constexpr sdl3::tagged_numeric<T, Tag> round_error() noexcept {
            return sdl3::tagged_numeric<T, Tag>(
                numeric_limits<T>::round_error()
            );
        }

        static constexpr sdl3::tagged_numeric<T, Tag> denorm_min() noexcept {
            return sdl3::tagged_numeric<T, Tag>(
                numeric_limits<T>::denorm_min()
            );
        }

        static constexpr sdl3::tagged_numeric<T, Tag> infinity() noexcept {
            return sdl3::tagged_numeric<T, Tag>(
                numeric_limits<T>::infinity()
            );
        }

        static constexpr sdl3::tagged_numeric<T, Tag> quiet_NaN() noexcept {
            return sdl3::tagged_numeric<T, Tag>(
                numeric_limits<T>::quiet_NaN()
            );
        }

        static constexpr sdl3::tagged_numeric<T, Tag> signaling_NaN() noexcept {
            return sdl3::tagged_numeric<T, Tag>(
                numeric_limits<T>::signaling_NaN()
            );
        }
    };
}

namespace sdl3
{
    template<typename T, typename Tag>
    class tagged_numeric : boost::operators<tagged_numeric<T, Tag>>
    {
    public:
        tagged_numeric(T value);

        tagged_numeric(tagged_numeric<T, Tag> const& other);

        tagged_numeric<T, Tag> & operator=(tagged_numeric<T, Tag> const& other);

        tagged_numeric<T, Tag> & operator*=(tagged_numeric<T, Tag> const& other);

        tagged_numeric<T, Tag> & operator/=(tagged_numeric<T, Tag> const& other);

        tagged_numeric<T, Tag> & operator+=(tagged_numeric<T, Tag> const& other);

        tagged_numeric<T, Tag> & operator-=(tagged_numeric<T, Tag> const& other);

        tagged_numeric<T, Tag> & operator++();

        tagged_numeric<T, Tag> & operator--();

        bool operator==(tagged_numeric<T, Tag> const& other) const;

        bool operator<(tagged_numeric<T, Tag> const& other) const;

        operator T() const;

    private:
        T _value;
    };

    template<typename T, typename Tag>
    tagged_numeric<T, Tag>::tagged_numeric(T value)
    : _value(value)
    { }

    template<typename T, typename Tag>
    tagged_numeric<T, Tag>::tagged_numeric(tagged_numeric<T, Tag> const& other)
    : _value(other._value)
    { }

    template<typename T, typename Tag>
    tagged_numeric<T, Tag> &
    tagged_numeric<T, Tag>::operator=(tagged_numeric<T, Tag> const& other)
    {
        if (*this != other)
        {
            _value = other._value;
        }
        return *this;
    }

    template<typename T, typename Tag>
    tagged_numeric<T, Tag> &
    tagged_numeric<T, Tag>::operator*=(tagged_numeric<T, Tag> const& other)
    {
        _value *= other._value;
        return *this;
    }

    template<typename T, typename Tag>
    tagged_numeric<T, Tag> &
    tagged_numeric<T, Tag>::operator/=(tagged_numeric<T, Tag> const& other)
    {
        _value /= other._value;
        return *this;
    }

    template<typename T, typename Tag>
    tagged_numeric<T, Tag> &
    tagged_numeric<T, Tag>::operator+=(tagged_numeric<T, Tag> const& other)
    {
        _value += other._value;
        return *this;
    }

    template<typename T, typename Tag>
    tagged_numeric<T, Tag> &
    tagged_numeric<T, Tag>::operator-=(tagged_numeric<T, Tag> const& other)
    {
        _value -= other._value;
        return *this;
    }

    template<typename T, typename Tag>
    tagged_numeric<T, Tag> &
    tagged_numeric<T, Tag>::operator++()
    {
        ++_value;
        return *this;
    }

    template<typename T, typename Tag>
    tagged_numeric<T, Tag> &
    tagged_numeric<T, Tag>::operator--()
    {
        --_value;
        return *this;
    }

    template<typename T, typename Tag>
    bool
    tagged_numeric<T, Tag>::operator==(tagged_numeric<T, Tag> const& other) const
    {
        return _value == other._value;
    }

    template<typename T, typename Tag>
    bool
    tagged_numeric<T, Tag>::operator<(tagged_numeric<T, Tag> const& other) const
    {
        return _value < other._value;
    }

    template<typename T, typename Tag>
    tagged_numeric<T, Tag>::operator T() const
    {
        return _value;
    }
}
