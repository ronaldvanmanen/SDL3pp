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

#include <boost/safe_numerics/safe_integer_range.hpp>
#include <boost/safe_numerics/safe_integer_literal.hpp>
#include <boost/safe_numerics/exception.hpp>
#include <boost/safe_numerics/native.hpp>

namespace sdl3
{
    template <
        typename Stored,
        Stored Min,
        Stored Max,
        class P = boost::safe_numerics::native,
        class E = boost::safe_numerics::loose_exception_policy
    >
    using safe_numeric_range = boost::safe_numerics::safe_base<
        Stored, Min, Max, P, E
    >;

    using safe_uint1_t   = safe_numeric_range<std::uint8_t, 0, 1>;
    using safe_uint2_t   = safe_numeric_range<std::uint8_t, 0, 3>;
    using safe_uint3_t   = safe_numeric_range<std::uint8_t, 0, 7>;
    using safe_uint4_t   = safe_numeric_range<std::uint8_t, 0, 15>;
    using safe_uint5_t   = safe_numeric_range<std::uint8_t, 0, 31>;
    using safe_uint6_t   = safe_numeric_range<std::uint8_t, 0, 63>;
    using safe_uint8_t   = safe_numeric_range<std::uint8_t, 0, 255>;
    using safe_uint10_t  = safe_numeric_range<std::uint16_t, 0, 1023>;
    using safe_uint16_t  = safe_numeric_range<std::uint16_t, 0, 65535>;

    using safe_unorm_float = safe_numeric_range<float, 0.0f, 1.0f>;
}
