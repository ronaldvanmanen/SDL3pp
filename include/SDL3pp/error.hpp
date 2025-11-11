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

#include <stdexcept>

#include <SDL3/SDL_error.h>

namespace sdl3
{
    class error : public std::runtime_error
    {
    public:
        error(std::string const & what_arg);

        error(const char * what_arg);

        error(error const & other);

        error & operator=(error const & other);
    };

    inline error::error(std::string const & what_arg)
    : std::runtime_error(what_arg)
    { }

    inline error::error(const char * what_arg)
    : std::runtime_error(what_arg)
    { }

    inline error::error(error const & other)
    : std::runtime_error(other)
    { }

    inline error &
    error::operator=(error const & other)
    {
        if (this != &other)
        {
            std::runtime_error::operator=(other);
        }
        return *this;
    }

    inline void
    throw_last_error(bool condition)
    {
        if (!condition)
        {
            throw error(SDL_GetError());
        }
    }
}  // namespace sdl3
