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

#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>

#include <boost/test/unit_test.hpp>

#include "SDL3pp/color.hpp"

#include "tools/random.hpp"

using sdl3::operator""_r8;
using sdl3::operator""_g8;
using sdl3::operator""_b8;
using sdl3::operator""_a8;

BOOST_AUTO_TEST_SUITE(color);

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
    auto random_engine = std::default_random_engine(0);
    auto r_distribution = sdl3::unit_test::tools::uniform_color_distribution<sdl3::r8>();
    auto g_distribution = sdl3::unit_test::tools::uniform_color_distribution<sdl3::g8>();
    auto b_distribution = sdl3::unit_test::tools::uniform_color_distribution<sdl3::b8>();
    auto a_distribution = sdl3::unit_test::tools::uniform_color_distribution<sdl3::a8>();
 
    auto r = r_distribution(random_engine);
    auto g = g_distribution(random_engine);
    auto b = b_distribution(random_engine);
    auto a = a_distribution(random_engine);

    auto test_color = sdl3::color(r, g, b, a);

    BOOST_TEST(test_color.r == r);
    BOOST_TEST(test_color.g == g);
    BOOST_TEST(test_color.b == b);
    BOOST_TEST(test_color.a == a);
}

BOOST_AUTO_TEST_CASE(test_copy_constructor)
{
    auto random_engine = std::default_random_engine(0);
    auto r_distribution = sdl3::unit_test::tools::uniform_color_distribution<sdl3::r8>();
    auto g_distribution = sdl3::unit_test::tools::uniform_color_distribution<sdl3::g8>();
    auto b_distribution = sdl3::unit_test::tools::uniform_color_distribution<sdl3::b8>();
    auto a_distribution = sdl3::unit_test::tools::uniform_color_distribution<sdl3::a8>();

    auto r = r_distribution(random_engine);
    auto g = g_distribution(random_engine);
    auto b = b_distribution(random_engine);
    auto a = a_distribution(random_engine);

    auto source_color = sdl3::color(r, g, b, a);

    auto target_color(source_color);

    BOOST_TEST(source_color == target_color);
}

BOOST_AUTO_TEST_CASE(test_assignment_operator)
{
    auto random_engine = std::default_random_engine(0);
    auto r_distribution = sdl3::unit_test::tools::uniform_color_distribution<sdl3::r8>();
    auto g_distribution = sdl3::unit_test::tools::uniform_color_distribution<sdl3::g8>();
    auto b_distribution = sdl3::unit_test::tools::uniform_color_distribution<sdl3::b8>();
    auto a_distribution = sdl3::unit_test::tools::uniform_color_distribution<sdl3::a8>();

    auto r = r_distribution(random_engine);
    auto g = g_distribution(random_engine);
    auto b = b_distribution(random_engine);
    auto a = a_distribution(random_engine);

    auto source_color = sdl3::color(r, g, b, a);
    
    auto target_color = sdl3::color();

    BOOST_TEST(source_color != target_color);
    target_color = source_color;
    BOOST_TEST(source_color == target_color);
}

BOOST_AUTO_TEST_CASE(test_addition_is_commutative)
{
    auto random_engine = std::default_random_engine(0);
    auto color_distribution = sdl3::unit_test::tools::uniform_color_distribution<sdl3::color>();
    auto x = color_distribution(random_engine);
    auto y = color_distribution(random_engine);

    BOOST_TEST(x + y == y + x);
}

BOOST_AUTO_TEST_CASE(test_compatibility)
{
    auto random_engine = std::default_random_engine(0);
    auto r_distribution = sdl3::unit_test::tools::uniform_color_distribution<sdl3::r8>();
    auto g_distribution = sdl3::unit_test::tools::uniform_color_distribution<sdl3::g8>();
    auto b_distribution = sdl3::unit_test::tools::uniform_color_distribution<sdl3::b8>();
    auto a_distribution = sdl3::unit_test::tools::uniform_color_distribution<sdl3::a8>();
 
    auto r = r_distribution(random_engine);
    auto g = g_distribution(random_engine);
    auto b = b_distribution(random_engine);
    auto a = a_distribution(random_engine);

    sdl3::color test_color(r, g, b, a);

    SDL_Color* ri_test_color = reinterpret_cast<SDL_Color*>(&test_color);

    BOOST_TEST(ri_test_color->r == static_cast<Uint8>(r));
    BOOST_TEST(ri_test_color->g == static_cast<Uint8>(g));
    BOOST_TEST(ri_test_color->b == static_cast<Uint8>(b));
    BOOST_TEST(ri_test_color->a == static_cast<Uint8>(a));
}

BOOST_AUTO_TEST_CASE(test_stream_insertion_operator)
{
    sdl3::color test_color(0xDE_r8, 0xAD_g8, 0xBE_b8, 0xEF_a8);

    std::stringstream s;
    s << std::hex << std::showbase << std::uppercase << test_color;
    BOOST_TEST("0XDE,0XAD,0XBE,0XEF" == s.str());
}

BOOST_AUTO_TEST_SUITE_END();
