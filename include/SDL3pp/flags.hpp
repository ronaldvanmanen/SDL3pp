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
#include <optional>
#include <string>
#include <type_traits>

#include <SDL3/SDL_video.h>

#include "display_mode.hpp"
#include "size.hpp"
#include "surface.hpp"
#include "units.hpp"

namespace sdl3
{
    template <class T>
        requires(std::is_enum_v<T>)
    struct is_flags_enum
    {
        static const bool value = false;
    };

    template <class T>
        requires(std::is_enum_v<T>)
    constexpr bool is_flags_enum_v = is_flags_enum<T>::value;

    template <class T>
        requires(is_flags_enum_v<T>)
    class flag_set
    // clang-format off
    : boost::equality_comparable<flag_set<T>
    , boost::equality_comparable<flag_set<T>, T
    , boost::bitwise<flag_set<T>
    , boost::bitwise<flag_set<T>, T
    , boost::bitwise<T, T
    > > > > >
    // clang-format on
    {
    public:
        using underlying_type = std::underlying_type_t<T>;

    public:
        flag_set()
        : _values()
        { }

        flag_set(T value)
        : _values(static_cast<underlying_type>(value))
        { }

        flag_set(underlying_type values)
        : _values(values)
        { }

        flag_set & operator|=(flag_set const & other)
        {
            _values |= other._values;
            return *this;
        }

        flag_set & operator&=(flag_set const & other)
        {
            _values &= other._values;
            return *this;
        }

        flag_set & operator^=(flag_set const & other)
        {
            _values ^= other._values;
            return *this;
        }

        flag_set & operator|=(T const & value)
        {
            _values |= static_cast<underlying_type>(value);
            return *this;
        }

        flag_set & operator&=(T const & value)
        {
            _values &= static_cast<underlying_type>(value);
            return *this;
        }

        flag_set & operator^=(T const & value)
        {
            _values ^= static_cast<underlying_type>(value);
            return *this;
        }

        flag_set operator~() const
        {
            return flag_set(~_values);
        }

        bool operator==(flag_set const & other) const
        {
            return _values == other._values;
        }

        bool operator==(T const & value) const
        {
            return _values == static_cast<underlying_type>(value);
        }

        bool test(T value) const
        {
            return _values & static_cast<underlying_type>(value);
        }

        operator underlying_type()
        {
            return _values;
        }

    private:
        underlying_type _values;

    private:
        friend flag_set<T> operator|(T left, T right);

        friend flag_set<T> operator&(T left, T right);

        friend flag_set<T> operator^(T left, T right);

        friend flag_set<T> operator~(T value);
    };

    template <class T>
        requires(is_flags_enum_v<T>)
    [[nodiscard]]
    inline flag_set<T> operator|(T left, T right)
    {
        return flag_set<T>(
            static_cast<flag_set<T>::underlying_type>(left) | static_cast<flag_set<T>::underlying_type>(right)
        );
    }

    template <class T>
        requires(is_flags_enum_v<T>)
    [[nodiscard]]
    inline flag_set<T> operator&(T left, T right)
    {
        return flag_set<T>(
            static_cast<flag_set<T>::underlying_type>(left) & static_cast<flag_set<T>::underlying_type>(right)
        );
    }

    template <class T>
        requires(is_flags_enum_v<T>)
    [[nodiscard]]
    inline flag_set<T> operator^(T left, T right)
    {
        return flag_set<T>(
            static_cast<flag_set<T>::underlying_type>(left) ^ static_cast<flag_set<T>::underlying_type>(right)
        );
    }

    template <class T>
        requires(is_flags_enum_v<T>)
    [[nodiscard]]
    inline flag_set<T> operator~(T value)
    {
        return flag_set<T>(~static_cast<flag_set<T>::underlying_type>(value));
    }
}  // namespace sdl3
