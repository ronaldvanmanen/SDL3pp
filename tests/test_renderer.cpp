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

#define BOOST_TEST_MODULE renderer
#include <boost/test/unit_test.hpp>
#include <boost/units/io.hpp>

#include "SDL3pp/renderer.h"

using namespace sdl3;

BOOST_AUTO_TEST_CASE(test_constructors)
{
    window test_window("test_constructors", 640*px, 480*px, window_flags::hidden);

    BOOST_REQUIRE_NO_THROW(
        renderer test_renderer(test_window);
    );
}

BOOST_AUTO_TEST_CASE(test_output_size)
{
    auto test_window = window("test_output_size", 640*px, 480*px, window_flags::hidden);
    auto test_renderer = renderer(test_window);
    auto test_renderer_output_size = test_renderer.output_size();
    BOOST_TEST(test_renderer_output_size.width == 640*px);
    BOOST_TEST(test_renderer_output_size.height == 480*px);
}

BOOST_AUTO_TEST_CASE(test_draw_color)
{
    auto test_window = window("test_draw_color", 640*px, 480*px, window_flags::hidden);
    auto test_renderer = renderer(test_window);
    auto test_color = color(0xDE_r8, 0xAD_g8, 0xBE_b8, 0xEF_a8);
    
    test_renderer.draw_color(test_color);

    BOOST_TEST(test_color == test_renderer.draw_color());
}

BOOST_AUTO_TEST_CASE(test_draw_blend_mode)
{
    window test_window("test_draw_blend_mode", 640*px, 480*px, window_flags::hidden);
    renderer test_renderer(test_window);
    blend_mode test_mode = blend_mode::blend;
    
    test_renderer.draw_blend_mode(test_mode);

    BOOST_TEST(test_mode == test_renderer.draw_blend_mode());
}
