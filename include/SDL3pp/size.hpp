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

#include <boost/operators.hpp>

#include "units.hpp"

namespace sdl3
{
    template <typename Y>
    struct size_2d : boost::equality_comparable<size_2d<Y>>
    {
    public:
        explicit size_2d(length<Y> width_and_height)
        : _width(width_and_height)
        , _height(width_and_height)
        { }

        size_2d(length<Y> width, length<Y> height)
        : _width(width)
        , _height(height)
        { }

        [[nodiscard]]
        bool operator==(size_2d<Y> const & other) const
        {
            return _width == other._width && _height == other._height;
        }

        [[nodiscard]]
        length<Y> width() const
        {
            return _width;
        }

        [[nodiscard]]
        length<Y> height() const
        {
            return _height;
        }

    private:
        length<Y> _width;

        length<Y> _height;
    };

}  // namespace sdl3
