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

#include <SDL3/SDL_pixels.h>

#include "SDL3pp/packed_color.h"

using sdl3::operator""_a8;
using sdl3::operator""_r8;
using sdl3::operator""_g8;
using sdl3::operator""_b8;

BOOST_AUTO_TEST_CASE(test_argb8888_traits)
{
    BOOST_TEST(sdl3::sargb8888::color_space == sdl3::color_space::srgb);
    BOOST_TEST(sdl3::sargb8888::format == sdl3::pixel_format::argb8888);
}

BOOST_AUTO_TEST_CASE(test_argb8888_default_constructor)
{
    sdl3::sargb8888 test_color;

    BOOST_TEST(test_color.a == 0);
    BOOST_TEST(test_color.r == 0);
    BOOST_TEST(test_color.g == 0);
    BOOST_TEST(test_color.b == 0);
}

BOOST_AUTO_TEST_CASE(test_argb8888_component_constructor)
{
    sdl3::sargb8888 test_color(0xDE_a8, 0xAD_r8, 0xBE_g8, 0xEF_b8);

    BOOST_TEST(test_color.a == 0xDE);
    BOOST_TEST(test_color.r == 0xAD);
    BOOST_TEST(test_color.g == 0xBE);
    BOOST_TEST(test_color.b == 0xEF);
}

BOOST_AUTO_TEST_CASE(test_argb8888_copy_constructor)
{
    sdl3::sargb8888 temp_color(0xDE_a8, 0xAD_r8, 0xBE_g8, 0xEF_b8);

    sdl3::sargb8888 test_color(temp_color);

    BOOST_TEST(test_color.a == 0xDE);
    BOOST_TEST(test_color.r == 0xAD);
    BOOST_TEST(test_color.g == 0xBE);
    BOOST_TEST(test_color.b == 0xEF);
}

BOOST_AUTO_TEST_CASE(test_argb8888_assignment_operator)
{
    sdl3::sargb8888 test_color;
    
    test_color = sdl3::sargb8888(0xDE_a8, 0xAD_r8, 0xBE_g8, 0xEF_b8);

    BOOST_TEST(test_color.a == 0xDE);
    BOOST_TEST(test_color.r == 0xAD);
    BOOST_TEST(test_color.g == 0xBE);
    BOOST_TEST(test_color.b == 0xEF);
}
