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
#include <boost/units/io.hpp>

#include "SDL3pp/renderer.hpp"

using sdl3::px;
using sdl3::operator""_r8;
using sdl3::operator""_g8;
using sdl3::operator""_b8;
using sdl3::operator""_a8;

BOOST_AUTO_TEST_SUITE(renderer)

    BOOST_AUTO_TEST_CASE(test_renderer_constructors)
    {
        sdl3::window test_window("test_renderer_constructors", 640 * px, 480 * px, sdl3::window_flags::hidden);

        BOOST_REQUIRE_NO_THROW(sdl3::renderer test_renderer(test_window););
    }

    BOOST_AUTO_TEST_CASE(test_renderer_output_size)
    {
        sdl3::window test_window("test_renderer_constructors", 640 * px, 480 * px, sdl3::window_flags::hidden);
        sdl3::renderer test_renderer(test_window);
        sdl3::size_2d test_renderer_output_size = test_renderer.output_size();
        BOOST_TEST(test_renderer_output_size.width == 640 * px);
        BOOST_TEST(test_renderer_output_size.height == 480 * px);
    }

    BOOST_AUTO_TEST_CASE(test_renderer_draw_color)
    {
        sdl3::window test_window("test_renderer_draw_color", 640 * px, 480 * px, sdl3::window_flags::hidden);
        sdl3::renderer test_renderer(test_window);
        sdl3::color test_color(0xDE_r8, 0xAD_g8, 0xBE_b8, 0xEF_a8);

        test_renderer.draw_color(test_color);

        BOOST_TEST(test_color == test_renderer.draw_color());
    }

    BOOST_AUTO_TEST_CASE(test_renderer_draw_blend_mode)
    {
        sdl3::window test_window("test_renderer_draw_blend_mode", 640 * px, 480 * px, sdl3::window_flags::hidden);
        sdl3::renderer test_renderer(test_window);
        sdl3::blend_mode test_mode = sdl3::blend_mode::blend;

        test_renderer.draw_blend_mode(test_mode);

        BOOST_TEST(test_mode == test_renderer.draw_blend_mode());
    }

BOOST_AUTO_TEST_SUITE_END()
