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

#include <iostream>
#include <cstdint>
#include <boost/operators.hpp>

namespace sdl3
{
    template<typename Tag, typename T>
    class alignas(alignof(T)) primary_color
    : boost::equality_comparable<primary_color<Tag, T>
    , boost::less_than_comparable<primary_color<Tag, T>
    , boost::addable<primary_color<Tag, T>
    , boost::subtractable<primary_color<Tag, T>
    , boost::multipliable<primary_color<Tag, T>
    , boost::multipliable<primary_color<Tag, T>, float
    , boost::dividable<primary_color<Tag, T>
    , boost::dividable<primary_color<Tag, T>, float
    > > > > > > > >
    {
    public:
        explicit primary_color(T value);

        primary_color(primary_color<Tag, T> const& other);

        primary_color<Tag, T>& operator=(primary_color<Tag, T> const& other);

        primary_color<Tag, T>& operator*=(primary_color<Tag, T> const& other);

        primary_color<Tag, T>& operator/=(primary_color<Tag, T> const& other);

        primary_color<Tag, T>& operator+=(primary_color<Tag, T> const& other);

        primary_color<Tag, T>& operator-=(primary_color<Tag, T> const& other);

        primary_color<Tag, T>& operator*=(T scalar);

        primary_color<Tag, T>& operator/=(T scalar);

        primary_color<Tag, T>& operator++();

        primary_color<Tag, T>& operator--();

        bool operator==(primary_color<Tag, T> const& other) const;

        bool operator<(primary_color<Tag, T> const& other) const;

        operator T() const;

    private:
        T _value;
    };

    template<typename Tag, typename T>
    primary_color<Tag, T>::primary_color(T value)
    : _value(value)
    { }

    template<typename Tag, typename T>
    primary_color<Tag, T>::primary_color(primary_color<Tag, T> const& other)
    : _value(other._value)
    { }

    template<typename Tag, typename T>
    primary_color<Tag, T> &
    primary_color<Tag, T>::operator=(primary_color<Tag, T> const& other)
    {
        if (*this != other)
        {
            _value = other._value;
        }
        return *this;
    }

    template<typename Tag, typename T>
    primary_color<Tag, T> &
    primary_color<Tag, T>::operator*=(primary_color<Tag, T> const& other)
    {
        _value *= other._value;
        return *this;
    }

    template<typename Tag, typename T>
    primary_color<Tag, T> &
    primary_color<Tag, T>::operator/=(primary_color<Tag, T> const& other)
    {
        _value /= other._value;
        return *this;
    }

    template<typename Tag, typename T>
    primary_color<Tag, T> &
    primary_color<Tag, T>::operator+=(primary_color<Tag, T> const& other)
    {
        _value += other._value;
        return *this;
    }

    template<typename Tag, typename T>
    primary_color<Tag, T> &
    primary_color<Tag, T>::operator-=(primary_color<Tag, T> const& other)
    {
        _value -= other._value;
        return *this;
    }

    template<typename Tag, typename T>
    primary_color<Tag, T> &
    primary_color<Tag, T>::operator*=(T scalar)
    {
        _value *= scalar;
        return *this;
    }

    template<typename Tag, typename T>
    primary_color<Tag, T> &
    primary_color<Tag, T>::operator/=(T scalar)
    {
        _value /= scalar;
        return *this;
    }

    template<typename Tag, typename T>
    primary_color<Tag, T> &
    primary_color<Tag, T>::operator++()
    {
        ++_value;
        return *this;
    }

    template<typename Tag, typename T>
    primary_color<Tag, T> &
    primary_color<Tag, T>::operator--()
    {
        --_value;
        return *this;
    }

    template<typename Tag, typename T>
    bool
    primary_color<Tag, T>::operator==(primary_color<Tag, T> const& other) const
    {
        return _value == other._value;
    }

    template<typename Tag, typename T>
    bool
    primary_color<Tag, T>::operator<(primary_color<Tag, T> const& other) const
    {
        return _value < other._value;
    }

    template<typename Tag, typename T>
    primary_color<Tag, T>::operator T() const
    {
        return _value;
    }

#define SDL3PP_PRIMARY_COLOR(NAME, BASE_TYPE)                   \
    struct NAME##_tag {};                                       \
                                                                \
    using NAME = sdl3::primary_color<NAME##_tag, BASE_TYPE>;    \
                                                                \
    inline                                                      \
    sdl3::NAME operator""_##NAME(unsigned long long value)      \
    {                                                           \
        return sdl3::NAME(static_cast<BASE_TYPE>(value));       \
    }                                                           \
                                                                \
    inline                                                      \
    sdl3::NAME operator""_##NAME(long double value)             \
    {                                                           \
        return sdl3::NAME(static_cast<BASE_TYPE>(value));       \
    }                                                           \
    // 

    SDL3PP_PRIMARY_COLOR(a8, std::uint8_t)
    SDL3PP_PRIMARY_COLOR(b8, std::uint8_t)
    SDL3PP_PRIMARY_COLOR(g8, std::uint8_t)
    SDL3PP_PRIMARY_COLOR(r8, std::uint8_t)

    SDL3PP_PRIMARY_COLOR(a32f, float)
    SDL3PP_PRIMARY_COLOR(b32f, float)
    SDL3PP_PRIMARY_COLOR(g32f, float)
    SDL3PP_PRIMARY_COLOR(r32f, float)
}
