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

#include <SDL3/SDL_events.h>

#include "keyboard_event.h"
#include "mouse_wheel_event.h"

namespace sdl3
{
    template<class... Ts>
    struct event_handler : Ts...
    {
        using Ts::operator()...;
    };

    template<class... Ts>
    event_handler(Ts...) -> event_handler<Ts...>;

    class event
    {
    public:
        event();

        template<class Self, class EventHandler>
        void handle(this Self&& self, EventHandler&& handler);

        SDL_Event * native_handle();

    private:
        SDL_Event _native_handle;
    };

    struct quit_event {};

    template<class Self, class EventHandler>
    void
    event::handle(this Self && self, EventHandler && handler)
    {
        switch (self._native_handle.type)
        {
            case SDL_EVENT_QUIT:
                handler(quit_event());
                break;

            case SDL_EVENT_KEY_DOWN:
                handler(key_down_event(std::move(self._native_handle)));
                break;

            case SDL_EVENT_KEY_UP:
                handler(key_up_event(std::move(self._native_handle)));
                break;

            case SDL_EVENT_MOUSE_WHEEL:
                handler(mouse_wheel_event(std::move(self._native_handle)));
                break;
        }
    }
}
