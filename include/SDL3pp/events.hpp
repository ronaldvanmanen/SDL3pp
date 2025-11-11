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

#include <SDL3/SDL.h>

#include "key_code.hpp"
#include "scan_code.hpp"

namespace sdl3
{
    class quit_event
    { };

    class keyboard_event
    {
    protected:
        keyboard_event() = delete;

        keyboard_event(keyboard_event const &) = delete;

        keyboard_event(SDL_Event && native_handle);

        keyboard_event & operator=(keyboard_event const &) = delete;

    public:
        std::uint64_t timestamp() const;

        std::uint32_t window_id() const;

        bool released() const;

        bool pressed() const;

        bool repeated() const;

        scan_code scan_code() const;

        key_code key_code() const;

        key_modifier_set key_modifiers() const;

    private:
        SDL_Event _native_handle;
    };

    class key_up_event : public keyboard_event
    {
    public:
        key_up_event() = delete;

        key_up_event(key_up_event const &) = delete;

        key_up_event(SDL_Event && native_handle);

        key_up_event & operator=(key_up_event const &) = delete;
    };

    class key_down_event : public keyboard_event
    {
    public:
        key_down_event() = delete;

        key_down_event(key_down_event const &) = delete;

        key_down_event(SDL_Event && native_handle);

        key_down_event & operator=(key_down_event const &) = delete;
    };

    class mouse_wheel_event
    {
    public:
        mouse_wheel_event() = delete;

        mouse_wheel_event(mouse_wheel_event const &) = delete;

        mouse_wheel_event(SDL_Event && native_handle);

        mouse_wheel_event & operator=(mouse_wheel_event const &) = delete;

        std::uint64_t timestamp() const;

        std::uint32_t window_id() const;

        std::uint32_t which() const;

        float x() const;

        float y() const;

        std::uint32_t direction() const;

        float mouse_x() const;

        float mouse_y() const;

    private:
        SDL_Event _native_handle;
    };

    template <class... Ts>
    struct event_handler : Ts...
    {
        using Ts::operator()...;
    };

    template <class... Ts>
    event_handler(Ts...) -> event_handler<Ts...>;

    class event
    {
    public:
        event();

        template <class Self, class EventHandler>
        void handle(this Self && self, EventHandler && handler);

        SDL_Event * native_handle();

    private:
        SDL_Event _native_handle;
    };

    class event_queue
    {
    public:
        event_queue();

        ~event_queue();

        bool poll(event & event);

        bool pending() const;
    };

    inline keyboard_event::keyboard_event(SDL_Event && native_handle)
    : _native_handle(native_handle)
    { }

    inline std::uint64_t
    keyboard_event::timestamp() const
    {
        return _native_handle.key.timestamp;
    }

    inline std::uint32_t
    keyboard_event::window_id() const
    {
        return _native_handle.key.windowID;
    }

    inline bool
    keyboard_event::released() const
    {
        return !pressed();
    }

    inline bool
    keyboard_event::pressed() const
    {
        return _native_handle.key.down;
    }

    inline bool
    keyboard_event::repeated() const
    {
        return _native_handle.key.repeat;
    }

    inline scan_code
    keyboard_event::scan_code() const
    {
        return static_cast<::sdl3::scan_code>(_native_handle.key.scancode);
    }

    inline key_code
    keyboard_event::key_code() const
    {
        return static_cast<::sdl3::key_code>(_native_handle.key.key);
    }

    inline key_modifier_set
    keyboard_event::key_modifiers() const
    {
        return key_modifier_set(static_cast<key_modifier>(_native_handle.key.mod));
    }

    inline key_up_event::key_up_event(SDL_Event && native_handle)
    : keyboard_event(std::move(native_handle))
    { }

    inline key_down_event::key_down_event(SDL_Event && native_handle)
    : keyboard_event(std::move(native_handle))
    { }

    inline mouse_wheel_event::mouse_wheel_event(SDL_Event && native_handle)
    : _native_handle(native_handle)
    { }

    inline std::uint64_t
    mouse_wheel_event::timestamp() const
    {
        return _native_handle.wheel.timestamp;
    }

    inline std::uint32_t
    mouse_wheel_event::window_id() const
    {
        return _native_handle.wheel.windowID;
    }

    inline std::uint32_t
    mouse_wheel_event::which() const
    {
        return _native_handle.wheel.which;
    }

    inline float
    mouse_wheel_event::x() const
    {
        return _native_handle.wheel.x;
    }

    inline float
    mouse_wheel_event::y() const
    {
        return _native_handle.wheel.y;
    }

    inline std::uint32_t
    mouse_wheel_event::direction() const
    {
        return _native_handle.wheel.direction;
    }

    inline float
    mouse_wheel_event::mouse_x() const
    {
        return _native_handle.wheel.mouse_x;
    }

    inline float
    mouse_wheel_event::mouse_y() const
    {
        return _native_handle.wheel.mouse_y;
    }

    inline event::event()
    : _native_handle(SDL_Event())
    {
        SDL_zero(_native_handle);
    }

    template <class Self, class EventHandler>
    void
    event::handle(this Self && self, EventHandler && handler)
    {
        switch (self._native_handle.type)
        {
            case SDL_EVENT_QUIT:        handler(quit_event()); break;
            case SDL_EVENT_KEY_DOWN:    handler(key_down_event(std::move(self._native_handle))); break;
            case SDL_EVENT_KEY_UP:      handler(key_up_event(std::move(self._native_handle))); break;
            case SDL_EVENT_MOUSE_WHEEL: handler(mouse_wheel_event(std::move(self._native_handle))); break;
        }
    }

    inline SDL_Event *
    event::native_handle()
    {
        return &_native_handle;
    }

    inline event_queue::event_queue()
    {
        SDL_InitSubSystem(SDL_INIT_EVENTS);
    }

    inline event_queue::~event_queue()
    {
        SDL_QuitSubSystem(SDL_INIT_EVENTS);
    }

    inline bool
    event_queue::poll(event & event)
    {
        return 1 == SDL_PollEvent(event.native_handle());
    }

    inline bool
    event_queue::pending() const
    {
        return 1 == SDL_PollEvent(nullptr);
    }
}  // namespace sdl3
