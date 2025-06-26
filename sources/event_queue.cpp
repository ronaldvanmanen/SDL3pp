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

#include <memory>

#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>

#include "SDL3pp/event_queue.h"

sdl3::event_queue::event_queue()
{
    SDL_InitSubSystem(SDL_INIT_EVENTS);
}

sdl3::event_queue::~event_queue()
{
    SDL_QuitSubSystem(SDL_INIT_EVENTS);
}

bool
sdl3::event_queue::poll(sdl3::event& event)
{
    return 1 == SDL_PollEvent(event.native_handle());
}

bool
sdl3::event_queue::pending() const
{
    return 1 == SDL_PollEvent(nullptr);
}
