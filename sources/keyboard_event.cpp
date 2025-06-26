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

#include "SDL3pp/keyboard_event.h"

sdl3::keyboard_event::keyboard_event(SDL_Event const& native_handle)
: _native_handle(native_handle)
{ }

sdl3::key_event_type
sdl3::keyboard_event::type() const
{
    return static_cast<sdl3::key_event_type>(_native_handle.key.type);
}

std::uint64_t
sdl3::keyboard_event::timestamp() const
{
    return _native_handle.key.timestamp;
}

std::uint32_t
sdl3::keyboard_event::window_id() const
{
    return _native_handle.key.windowID;
}

bool
sdl3::keyboard_event::released() const
{
    return !pressed();
}

bool
sdl3::keyboard_event::pressed() const
{
    return _native_handle.key.down;
}

bool
sdl3::keyboard_event::repeated() const
{
    return _native_handle.key.repeat;
}

sdl3::scan_code
sdl3::keyboard_event::scan_code() const
{
    return static_cast<sdl3::scan_code>(_native_handle.key.scancode);
}        

sdl3::key_code
sdl3::keyboard_event::key_code() const
{
    return static_cast<sdl3::key_code>(_native_handle.key.key);
}

sdl3::key_modifier_set
sdl3::keyboard_event::key_modifiers() const
{
    return key_modifier_set(static_cast<sdl3::key_modifier>(_native_handle.key.mod));
}
