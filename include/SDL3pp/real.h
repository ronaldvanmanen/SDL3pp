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

#define SDL3PP_REAL_DECL(NAME, BASE_TYPE)            \
    struct NAME##_tag {};                               \
    using NAME = sdl3::real<NAME##_tag, BASE_TYPE>;

namespace sdl3
{
    template<typename Tag, typename T>
    class real : boost::operators<real<Tag, T>>
    {
    public:
        explicit real(T value);

        real(real<Tag, T> const& other);

        real<Tag, T>& operator=(real<Tag, T> const& other);

        real<Tag, T>& operator*=(real<Tag, T> const& other);

        real<Tag, T>& operator/=(real<Tag, T> const& other);

        real<Tag, T>& operator+=(real<Tag, T> const& other);

        real<Tag, T>& operator-=(real<Tag, T> const& other);

        real<Tag, T>& operator++();

        real<Tag, T>& operator--();

        bool operator==(real<Tag, T> const& other) const;

        bool operator<(real<Tag, T> const& other) const;

        operator T() const;

    private:
        T _value;
    };

    template<typename Tag, typename T>
    real<Tag, T>::real(T value)
    : _value(value)
    { }

    template<typename Tag, typename T>
    real<Tag, T>::real(real<Tag, T> const& other)
    : _value(other._value)
    { }

    template<typename Tag, typename T>
    real<Tag, T> &
    real<Tag, T>::operator=(real<Tag, T> const& other)
    {
        if (*this != other)
        {
            _value = other._value;
        }
        return *this;
    }

    template<typename Tag, typename T>
    real<Tag, T> &
    real<Tag, T>::operator*=(real<Tag, T> const& other)
    {
        _value *= other._value;
        return *this;
    }

    template<typename Tag, typename T>
    real<Tag, T> &
    real<Tag, T>::operator/=(real<Tag, T> const& other)
    {
        _value /= other._value;
        return *this;
    }

    template<typename Tag, typename T>
    real<Tag, T> &
    real<Tag, T>::operator+=(real<Tag, T> const& other)
    {
        _value += other._value;
        return *this;
    }

    template<typename Tag, typename T>
    real<Tag, T> &
    real<Tag, T>::operator-=(real<Tag, T> const& other)
    {
        _value -= other._value;
        return *this;
    }

    template<typename Tag, typename T>
    real<Tag, T> &
    real<Tag, T>::operator++()
    {
        ++_value;
        return *this;
    }

    template<typename Tag, typename T>
    real<Tag, T> &
    real<Tag, T>::operator--()
    {
        --_value;
        return *this;
    }

    template<typename Tag, typename T>
    bool
    real<Tag, T>::operator==(real<Tag, T> const& other) const
    {
        return _value == other._value;
    }

    template<typename Tag, typename T>
    bool
    real<Tag, T>::operator<(real<Tag, T> const& other) const
    {
        return _value < other._value;
    }

    template<typename Tag, typename T>
    real<Tag, T>::operator T() const
    {
        return _value;
    }
}
