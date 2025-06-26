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

#include "SDL3pp/mouse_wheel_event.h"

sdl3::mouse_wheel_event::mouse_wheel_event(SDL_Event const& native_handle)
: _native_handle(native_handle)
{ }

sdl3::event_type
sdl3::mouse_wheel_event::type() const
{
    return static_cast<sdl3::event_type>(_native_handle.wheel.type);
}

std::uint64_t
sdl3::mouse_wheel_event::timestamp() const
{
    return _native_handle.wheel.timestamp;
}

std::uint32_t
sdl3::mouse_wheel_event::window_id() const
{
    return _native_handle.wheel.windowID;
}

std::uint32_t
sdl3::mouse_wheel_event::which() const
{
    return _native_handle.wheel.which;
}

float
sdl3::mouse_wheel_event::x() const
{
    return _native_handle.wheel.x;
}

float
sdl3::mouse_wheel_event::y() const
{
    return _native_handle.wheel.y;
}

std::uint32_t
sdl3::mouse_wheel_event::direction() const
{
    return _native_handle.wheel.direction;
}

float
sdl3::mouse_wheel_event::mouse_x() const
{
    return _native_handle.wheel.mouse_x;
}

float
sdl3::mouse_wheel_event::mouse_y() const
{
    return _native_handle.wheel.mouse_y;
}
