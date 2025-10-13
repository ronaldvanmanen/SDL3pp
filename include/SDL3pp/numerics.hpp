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
    template<typename T, typename R, R RMin, R RMax>
    R clamped_cast(T value)
    {
        if (value < static_cast<T>(RMin))
        {
            return RMin;
        }
        if (value > static_cast<T>(RMax))
        {
            return RMax;
        }
        return static_cast<R>(value);
    }

    template<typename T, T Min, T Max>
    class clamped_numeric
    : boost::totally_ordered<clamped_numeric<T, Min, Max>
    , boost::additive<clamped_numeric<T, Min, Max>
    , boost::multiplicative<clamped_numeric<T, Min, Max>
    , boost::unit_steppable<clamped_numeric<T, Min, Max>
    > > > >
    {
    public:
        clamped_numeric();

        /* explicit */ clamped_numeric(T value);

        template<class From>
            requires (!std::is_same_v<From, T> && std::is_convertible_v<From, T>)
        /* explicit */ clamped_numeric(From value);

        clamped_numeric(clamped_numeric<T, Min, Max> const& other);

        clamped_numeric<T, Min, Max> & operator=(clamped_numeric<T, Min, Max> const& other);

        clamped_numeric<T, Min, Max> & operator*=(clamped_numeric<T, Min, Max> const& other);

        clamped_numeric<T, Min, Max> & operator/=(clamped_numeric<T, Min, Max> const& other);

        clamped_numeric<T, Min, Max> & operator+=(clamped_numeric<T, Min, Max> const& other);

        clamped_numeric<T, Min, Max> & operator-=(clamped_numeric<T, Min, Max> const& other);

        clamped_numeric<T, Min, Max> & operator++();

        clamped_numeric<T, Min, Max> & operator--();

        bool operator==(clamped_numeric<T, Min, Max> const& other) const;

        bool operator<(clamped_numeric<T, Min, Max> const& other) const;

        operator T() const;

        template<class To>
            requires (!std::is_same_v<T, To> && std::is_convertible_v<T, To>)
        operator To() const;

    private:
        T _value;
    };

    template<typename T, T Min, T Max, typename CharT, typename Traits>
    std::basic_ostream<CharT, Traits> &
    operator<<(std::basic_ostream<CharT, Traits> & stream, clamped_numeric<T, Min, Max> const& value)
    {
        return stream << static_cast<T>(value);
    }

    template<std::uint8_t Min, std::uint8_t Max, typename CharT, typename Traits>
    std::basic_ostream<CharT, Traits> &
    operator<<(std::basic_ostream<CharT, Traits> & stream, clamped_numeric<std::uint8_t, Min, Max> const& value)
    {
        return stream << static_cast<std::uint32_t>(value);
    }

    template<class T>
    struct is_clamped_numeric
    {
        static const bool value = false;
    };

    template<class T, T Min, T Max>
    struct is_clamped_numeric<clamped_numeric<T, Min, Max> >
    {
        static const bool value = true;
    };

    template<class T>
    constexpr bool is_clamped_numeric_v = is_clamped_numeric<T>::value;

    template<class T>
    struct is_clamped_integral
    {
        const bool value = false;
    };

    template<class T, T Min, T Max>
    struct is_clamped_integral<clamped_numeric<T, Min, Max> >
    {
        static constexpr bool value = std::is_integral_v<T>;
    };

    template<class T>
    constexpr bool is_clamped_integral_v = is_clamped_integral<T>::value;

    template<class T>
    struct is_clamped_floating_point
    {
        const bool value = false;
    };

    template<class T, T Min, T Max>
    struct is_clamped_floating_point<clamped_numeric<T, Min, Max> >
    {
        static constexpr bool value = std::is_floating_point_v<T>;
    };

    template<class T>
    constexpr bool is_clamped_floating_point_v = is_clamped_floating_point<T>::value;

    template<typename T, T Min, T Max>
    clamped_numeric<T, Min, Max>::clamped_numeric()
    : _value()
    { }

    template<typename T, T Min, T Max>
    clamped_numeric<T, Min, Max>::clamped_numeric(T value)
    : _value(value)
    { }

    template<typename T, T Min, T Max>
        template<typename From>
            requires (!std::is_same_v<From, T> && std::is_convertible_v<From, T>)
    clamped_numeric<T, Min, Max>::clamped_numeric(From value)
    : _value(value)
    { }

    template<typename T, T Min, T Max>
    clamped_numeric<T, Min, Max>::clamped_numeric(clamped_numeric<T, Min, Max> const& other)
    : _value(other._value)
    { }

    template<typename T, T Min, T Max>
    clamped_numeric<T, Min, Max> &
    clamped_numeric<T, Min, Max>::operator=(clamped_numeric<T, Min, Max> const& other)
    {
        if (*this != other)
        {
            _value = other._value;
        }
        return *this;
    }

    template<typename T, T Min, T Max>
    clamped_numeric<T, Min, Max> &
    clamped_numeric<T, Min, Max>::operator*=(clamped_numeric<T, Min, Max> const& other)
    {
        auto const value = _value * other._value;
        _value = clamped_cast<decltype(value), T, Min, Max>(value);
        return *this;
    }

    template<typename T, T Min, T Max>
    clamped_numeric<T, Min, Max> &
    clamped_numeric<T, Min, Max>::operator/=(clamped_numeric<T, Min, Max> const& other)
    {
        auto const value = _value / other._value;
        _value = clamped_cast<decltype(value), T, Min, Max>(value);
        return *this;
    }

    template<typename T, T Min, T Max>
    clamped_numeric<T, Min, Max> &
    clamped_numeric<T, Min, Max>::operator+=(clamped_numeric<T, Min, Max> const& other)
    {
        auto const value = _value + other._value;
        _value = clamped_cast<decltype(value), T, Min, Max>(value);
        return *this;
    }

    template<typename T, T Min, T Max>
    clamped_numeric<T, Min, Max> &
    clamped_numeric<T, Min, Max>::operator-=(clamped_numeric<T, Min, Max> const& other)
    {
        auto const value = _value - other._value;
        _value = clamped_cast<decltype(value), T, Min, Max>(value);
        return *this;
    }

    template<typename T, T Min, T Max>
    clamped_numeric<T, Min, Max> &
    clamped_numeric<T, Min, Max>::operator++()
    {
        auto const value = _value + 1;
        _value = clamped_cast<decltype(value), T, Min, Max>(value);
        return *this;
    }

    template<typename T, T Min, T Max>
    clamped_numeric<T, Min, Max> &
    clamped_numeric<T, Min, Max>::operator--()
    {
        auto const value = _value - 1;
        _value = clamped_cast<decltype(value), T, Min, Max>(value);
        return *this;
    }

    template<typename T, T Min, T Max>
    bool
    clamped_numeric<T, Min, Max>::operator==(clamped_numeric<T, Min, Max> const& other) const
    {
        return _value == other._value;
    }

    template<typename T, T Min, T Max>
    bool
    clamped_numeric<T, Min, Max>::operator<(clamped_numeric<T, Min, Max> const& other) const
    {
        return _value < other._value;
    }

    template<typename T, T Min, T Max>
    clamped_numeric<T, Min, Max>::operator T() const
    {
        return _value;
    }

    template<typename T, T Min, T Max>
        template<class To>
            requires (!std::is_same_v<T, To> && std::is_convertible_v<T, To>)
    clamped_numeric<T, Min, Max>::operator To() const
    {
        return static_cast<To>(_value);
    }

    template<typename T>
    struct base_type
    {
        using type = T;
    };

    template<typename T, T Min, T Max>
    struct base_type<clamped_numeric<T, Min, Max> >
    {
        using type = T;
    };

    using clamped_uint1_t   = clamped_numeric<std::uint8_t, 0, 1>;
    using clamped_uint2_t   = clamped_numeric<std::uint8_t, 0, 3>;
    using clamped_uint3_t   = clamped_numeric<std::uint8_t, 0, 7>;
    using clamped_uint4_t   = clamped_numeric<std::uint8_t, 0, 15>;
    using clamped_uint5_t   = clamped_numeric<std::uint8_t, 0, 31>;
    using clamped_uint6_t   = clamped_numeric<std::uint8_t, 0, 63>;
    using clamped_uint8_t   = clamped_numeric<std::uint8_t, 0, 255>;
    using clamped_uint10_t  = clamped_numeric<std::uint16_t, 0, 1023>;
    using clamped_uint16_t  = clamped_numeric<std::uint16_t, 0, 65535>;

    using clamped_unorm_float = clamped_numeric<float, 0.0f, 1.0f>;

    template<typename T, typename Tag>
    class tagged_numeric : boost::operators<tagged_numeric<T, Tag> >
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

    template<class T>
    struct is_tagged_numeric
    {
        static const bool value = false;
    };

    template<class T, class Tag>
    struct is_tagged_numeric<tagged_numeric<T, Tag> >
    {
        static const bool value = true;
    };

    template<class T>
    constexpr bool is_tagged_numeric_v = is_tagged_numeric<T>::value;

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

namespace std
{
    template<typename T, T Min, T Max>
    struct numeric_limits<sdl3::clamped_numeric<T, Min, Max> >
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

        static constexpr sdl3::clamped_numeric<T, Min, Max>(min)() noexcept {
            return sdl3::clamped_numeric<T, Min, Max>(Min);
        }

        static constexpr sdl3::clamped_numeric<T, Min, Max>(max)() noexcept {
            return sdl3::clamped_numeric<T, Min, Max>(Max);
        }

        static constexpr sdl3::clamped_numeric<T, Min, Max> lowest() noexcept {
            return sdl3::clamped_numeric<T, Min, Max>(
                numeric_limits<T>::lowest()
            );
        }

        static constexpr sdl3::clamped_numeric<T, Min, Max> epsilon() noexcept {
            return sdl3::clamped_numeric<T, Min, Max>(
                numeric_limits<T>::epsilon()
            );
        }

        static constexpr sdl3::clamped_numeric<T, Min, Max> round_error() noexcept {
            return sdl3::clamped_numeric<T, Min, Max>(
                numeric_limits<T>::round_error()
            );
        }

        static constexpr sdl3::clamped_numeric<T, Min, Max> denorm_min() noexcept {
            return sdl3::clamped_numeric<T, Min, Max>(
                numeric_limits<T>::denorm_min()
            );
        }

        static constexpr sdl3::clamped_numeric<T, Min, Max> infinity() noexcept {
            return sdl3::clamped_numeric<T, Min, Max>(
                numeric_limits<T>::infinity()
            );
        }

        static constexpr sdl3::clamped_numeric<T, Min, Max> quiet_NaN() noexcept {
            return sdl3::clamped_numeric<T, Min, Max>(
                numeric_limits<T>::quiet_NaN()
            );
        }

        static constexpr sdl3::clamped_numeric<T, Min, Max> signaling_NaN() noexcept {
            return sdl3::clamped_numeric<T, Min, Max>(
                numeric_limits<T>::signaling_NaN()
            );
        }
    };
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
