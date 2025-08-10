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

#include "display_mode.h"
#include "length.h"
#include "size.h"
#include "surface.h"

namespace sdl3
{
    template<class T>
    struct is_flags_enum
    {
        static const bool value = false;
    };

    template<class T>
    constexpr bool is_flags_enum_v = is_flags_enum<T>::value;

    template<typename T>
    constexpr
    typename std::enable_if<std::is_enum_v<T> && is_flags_enum_v<T>, T>::type
    operator~(T value)
    {
        using underlying_type = std::underlying_type_t<T>;
        return static_cast<T>(
            static_cast<underlying_type>(value)
        );
    }

    template<typename T>
    constexpr
    typename std::enable_if<std::is_enum_v<T> && is_flags_enum_v<T>, T>::type
    operator&(T left, T right)
    {
        using underlying_type = std::underlying_type_t<T>;
        return static_cast<T>(
            static_cast<underlying_type>(left) & static_cast<underlying_type>(right)
        );
    }

    template<typename T>
    constexpr
    typename std::enable_if<std::is_enum_v<T> && is_flags_enum_v<T>, T>::type
    operator|(T left, T right)
    {
        using underlying_type = std::underlying_type_t<T>;
        return static_cast<T>(
            static_cast<underlying_type>(left) | static_cast<underlying_type>(right)
        );
    }

    template<typename T>
    constexpr
    typename std::enable_if<std::is_enum_v<T> && is_flags_enum_v<T>, T>::type
    operator^(T left, T right)
    {
        using underlying_type = std::underlying_type_t<T>;
        return static_cast<T>(
            static_cast<underlying_type>(left) & static_cast<underlying_type>(right)
        );
    }

    template<typename T>
    constexpr
    typename std::enable_if<std::is_enum_v<T> && is_flags_enum_v<T>, T>::type &
    operator&=(T & self, T other)
    {
        self = self & other;
        return self;
    }

    template<typename T>
    constexpr
    typename std::enable_if<std::is_enum_v<T> && is_flags_enum_v<T>, T>::type &
    operator|=(T & self, T other)
    {
        self = self | other;
        return self;
    }

    template<typename T>
    constexpr
    typename std::enable_if<std::is_enum_v<T> && is_flags_enum_v<T>, T>::type &
    operator^=(T & self, T other)
    {
        self = self ^ other;
        return self;
    }
}
