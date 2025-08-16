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

#include <boost/test/unit_test.hpp>

#include "SDL3pp/indexed_color.h"
#include "SDL3pp/packed_color.h"
#include "SDL3pp/surface.h"

using namespace sdl3;

BOOST_AUTO_TEST_CASE(test_surface_constructors)
{
    auto test_case = []() {
        surface<pixel_format::index8, color_space::srgb> test_surface(512*px, 384*px);
    };

    BOOST_REQUIRE_NO_THROW(test_case());
}
