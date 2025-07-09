// SDL2++
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

#include <cstdint>
#include <numbers>

#include <boost/units/quantity.hpp>

namespace sdl2
{
    bool is_power_of_two(std::int32_t value);

    template<typename Unit>
    inline
    bool
    is_power_of_two(boost::units::quantity<Unit, std::int32_t> value)
    {
        return is_power_of_two(
            boost::units::quantity_cast<std::int32_t>(value)
        );
    }

    std::int32_t next_power_of_two(std::int32_t value);

    template<typename Unit>
    inline
    boost::units::quantity<Unit, std::int32_t>
    next_power_of_two(boost::units::quantity<Unit, std::int32_t> value)
    {
        return boost::units::quantity<Unit, std::int32_t>::from_value(
            next_power_of_two(
                boost::units::quantity_cast<std::int32_t>(value)
            )
        );
    }

    inline
    float degrees_to_radians(float degrees)
    {
        return degrees * std::numbers::pi_v<float> / 180.0f;
    }
}
