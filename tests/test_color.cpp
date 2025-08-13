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

#define BOOST_TEST_MODULE color
#include <boost/test/unit_test.hpp>

#include <SDL3/SDL_pixels.h>

#include "SDL3pp/color.h"

using sdl3::operator""_r8;
using sdl3::operator""_g8;
using sdl3::operator""_b8;
using sdl3::operator""_a8;

BOOST_AUTO_TEST_CASE(test_default_constructor)
{
    sdl3::color test_color;

    BOOST_TEST(test_color.r == 0_r8);
    BOOST_TEST(test_color.g == 0_g8);
    BOOST_TEST(test_color.b == 0_b8);
    BOOST_TEST(test_color.a == 0_a8);
}

BOOST_AUTO_TEST_CASE(test_component_constructor)
{
    sdl3::color test_color(0xDE_r8, 0xAD_g8, 0xBE_b8, 0xEF_a8);

    BOOST_TEST(test_color.r == 0xDE_r8);
    BOOST_TEST(test_color.g == 0xAD_g8);
    BOOST_TEST(test_color.b == 0xBE_b8);
    BOOST_TEST(test_color.a == 0xEF_a8);
}

BOOST_AUTO_TEST_CASE(test_compatibility)
{
    sdl3::color test_color(0xDE_r8, 0xAD_g8, 0xBE_b8, 0xEF_a8);

    SDL_Color* ri_test_color = reinterpret_cast<SDL_Color*>(&test_color);

    BOOST_TEST(ri_test_color->r == 0xDE_r8);
    BOOST_TEST(ri_test_color->g == 0xAD_g8);
    BOOST_TEST(ri_test_color->b == 0xBE_b8);
    BOOST_TEST(ri_test_color->a == 0xEF_a8);
}