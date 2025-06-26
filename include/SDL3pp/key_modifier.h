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

#include <SDL3/SDL_events.h>

namespace sdl3
{    
    enum class key_modifier : std::uint16_t
    {
        none = SDL_KMOD_NONE,

        left_shift = SDL_KMOD_LSHIFT,
        right_shift = SDL_KMOD_RSHIFT,
        left_ctrl = SDL_KMOD_LCTRL,
        right_ctrl = SDL_KMOD_RCTRL,
        left_alt = SDL_KMOD_LALT,
        right_alt = SDL_KMOD_RALT,
        left_gui = SDL_KMOD_LGUI,
        right_gui = SDL_KMOD_RGUI,
        num_lock = SDL_KMOD_NUM,
        caps_lock = SDL_KMOD_CAPS,
        mode = SDL_KMOD_MODE,
        scroll_lock = SDL_KMOD_SCROLL,

        ctrl = SDL_KMOD_CTRL,
        shift = SDL_KMOD_SHIFT,
        alt = SDL_KMOD_ALT,
        gui = SDL_KMOD_GUI
    };

    class key_modifier_set
    : boost::equality_comparable<key_modifier_set
    , boost::equality_comparable<key_modifier_set, key_modifier
    , boost::bitwise<key_modifier_set
    , boost::bitwise<key_modifier_set, key_modifier
    , boost::bitwise<key_modifier, key_modifier
    > > > > >
    {
    private:
        key_modifier_set(uint16_t values);

    public:
        key_modifier_set();

        key_modifier_set(key_modifier value);

        key_modifier_set& operator|=(key_modifier_set const& other);

        key_modifier_set& operator&=(key_modifier_set const& other);

        key_modifier_set& operator^=(key_modifier_set const& other);

        key_modifier_set& operator|=(key_modifier const& value);

        key_modifier_set& operator&=(key_modifier const& value);

        key_modifier_set& operator^=(key_modifier const& value);

        key_modifier_set operator~() const;

        bool operator==(key_modifier_set const& other) const;

        bool operator==(key_modifier const& value) const;

        bool test(key_modifier value) const;

    private:
        uint16_t _values;

    private:
        friend key_modifier_set operator|(key_modifier left, key_modifier right);

        friend key_modifier_set operator&(key_modifier left, key_modifier right);

        friend key_modifier_set operator^(key_modifier left, key_modifier right);

        friend key_modifier_set operator~(key_modifier value);
    };

    key_modifier_set operator|(key_modifier left, key_modifier right);

    key_modifier_set operator&(key_modifier left, key_modifier right);

    key_modifier_set operator^(key_modifier left, key_modifier right);

    key_modifier_set operator~(key_modifier value);
}
