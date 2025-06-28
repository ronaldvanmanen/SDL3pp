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

#include <boost/operators.hpp>

#include "pixel_format.h"

namespace sdl3
{
    class alignas(alignof(float)) rgb96f
    : boost::equality_comparable<rgb96f
    , boost::addable<rgb96f
    , boost::multipliable<rgb96f
    , boost::multipliable<rgb96f, float
    > > > >
    {
    public:
        static constexpr pixel_format format = pixel_format::rgb96f;

        static const rgb96f black;

        static const rgb96f white;

    public:
        rgb96f();

        rgb96f(float r, float g, float b);

        rgb96f(rgb96f const& other);

        bool operator==(rgb96f const& other) const;

        rgb96f& operator+=(rgb96f const& other);
        
        rgb96f& operator*=(rgb96f const& other);

        rgb96f& operator*=(float scalar);

        rgb96f& clamp();

        rgb96f clamped() const;

    public:
        float r, g, b;
    };

    inline
    rgb96f
    mix(rgb96f const& color0, rgb96f const& color1, float value)
    {
        return (1.0f - value) * color0 + value * color1;
    }    
}
