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

#include <random>

#include <boost/mpl/list.hpp>
#include <boost/test/unit_test.hpp>

#include "SDL3pp/array_color.hpp"

#include "tools/random.hpp"
#include "tools/template_test_case.hpp"

template <sdl3::pixel_format P>
using pixel_format_constant = std::integral_constant<sdl3::pixel_format, P>;

namespace sdl3::unit_test::tools
{
    template <sdl3::pixel_format P>
    struct test_type_name_generator<pixel_format_constant<P>>
    {
        static std::string
        value()
        {
            return name<char>(P);
        }
    };
}  // namespace sdl3::unit_test::tools

typedef boost::mpl::list<
    pixel_format_constant<sdl3::pixel_format::rgba128f>,
    pixel_format_constant<sdl3::pixel_format::argb128f>,
    pixel_format_constant<sdl3::pixel_format::bgra128f>,
    pixel_format_constant<sdl3::pixel_format::abgr128f>
>
    test_pixel_formats;

BOOST_AUTO_TEST_SUITE(rgba_array_color)

    SDL3PP_AUTO_TEST_CASE_TEMPLATE(test_default_constructor, PixelFormat, test_pixel_formats)
    {
        using packed_color_t = sdl3::rgba_array_color<PixelFormat::value>;
        using r_t = packed_color_t::r_type;
        using g_t = packed_color_t::g_type;
        using b_t = packed_color_t::b_type;
        using a_t = packed_color_t::a_type;

        packed_color_t test_color;

        BOOST_TEST(test_color.r() == r_t(0));
        BOOST_TEST(test_color.g() == g_t(0));
        BOOST_TEST(test_color.b() == b_t(0));
        BOOST_TEST(test_color.a() == a_t(0));
    }

    SDL3PP_AUTO_TEST_CASE_TEMPLATE(test_component_constructor, PixelFormat, test_pixel_formats)
    {
        using packed_color_t = sdl3::rgba_array_color<PixelFormat::value>;
        using r_t = packed_color_t::r_type;
        using g_t = packed_color_t::g_type;
        using b_t = packed_color_t::b_type;
        using a_t = packed_color_t::a_type;

        auto random_engine = std::default_random_engine(0);
        auto r_distribution = sdl3::unit_test::tools::uniform_color_distribution<r_t>();
        auto g_distribution = sdl3::unit_test::tools::uniform_color_distribution<g_t>();
        auto b_distribution = sdl3::unit_test::tools::uniform_color_distribution<b_t>();
        auto a_distribution = sdl3::unit_test::tools::uniform_color_distribution<a_t>();

        auto r = r_distribution(random_engine);
        auto g = g_distribution(random_engine);
        auto b = b_distribution(random_engine);
        auto a = a_distribution(random_engine);

        auto test_color = packed_color_t(r, g, b, a);

        BOOST_TEST(r == test_color.r());
        BOOST_TEST(g == test_color.g());
        BOOST_TEST(b == test_color.b());
        BOOST_TEST(a == test_color.a());
    }

    SDL3PP_AUTO_TEST_CASE_TEMPLATE(test_copy_constructor, PixelFormat, test_pixel_formats)
    {
        using packed_color_t = sdl3::rgba_array_color<PixelFormat::value>;
        using r_t = packed_color_t::r_type;
        using g_t = packed_color_t::g_type;
        using b_t = packed_color_t::b_type;
        using a_t = packed_color_t::a_type;

        auto random_engine = std::default_random_engine(0);
        auto r_distribution = sdl3::unit_test::tools::uniform_color_distribution<r_t>();
        auto g_distribution = sdl3::unit_test::tools::uniform_color_distribution<g_t>();
        auto b_distribution = sdl3::unit_test::tools::uniform_color_distribution<b_t>();
        auto a_distribution = sdl3::unit_test::tools::uniform_color_distribution<a_t>();

        auto r = r_distribution(random_engine);
        auto g = g_distribution(random_engine);
        auto b = b_distribution(random_engine);
        auto a = a_distribution(random_engine);

        auto source_color = packed_color_t(r, g, b, a);

        auto target_color(source_color);

        BOOST_TEST(source_color == target_color);
    }

    SDL3PP_AUTO_TEST_CASE_TEMPLATE(test_assignment_operator, PixelFormat, test_pixel_formats)
    {
        using packed_color_t = sdl3::rgba_array_color<PixelFormat::value>;
        using r_t = packed_color_t::r_type;
        using g_t = packed_color_t::g_type;
        using b_t = packed_color_t::b_type;
        using a_t = packed_color_t::a_type;

        auto random_engine = std::default_random_engine(0);
        auto r_distribution = sdl3::unit_test::tools::uniform_color_distribution<r_t>();
        auto g_distribution = sdl3::unit_test::tools::uniform_color_distribution<g_t>();
        auto b_distribution = sdl3::unit_test::tools::uniform_color_distribution<b_t>();
        auto a_distribution = sdl3::unit_test::tools::uniform_color_distribution<a_t>();

        auto r = r_distribution(random_engine);
        auto g = g_distribution(random_engine);
        auto b = b_distribution(random_engine);
        auto a = a_distribution(random_engine);

        auto source_color = packed_color_t(r, g, b, a);

        auto target_color = packed_color_t();

        BOOST_TEST(source_color != target_color);
        target_color = source_color;
        BOOST_TEST(source_color == target_color);
    }

    SDL3PP_AUTO_TEST_CASE_TEMPLATE(test_addition_is_commutative, PixelFormat, test_pixel_formats)
    {
        using packed_color_t = sdl3::rgba_array_color<PixelFormat::value>;

        auto random_engine = std::default_random_engine(0);
        auto color_distribution = sdl3::unit_test::tools::uniform_color_distribution<packed_color_t>();
        auto x = color_distribution(random_engine);
        auto y = color_distribution(random_engine);

        BOOST_TEST(x + y == y + x);
    }

    SDL3PP_AUTO_TEST_CASE_TEMPLATE(test_multiplication_is_commutative, PixelFormat, test_pixel_formats)
    {
        using packed_color_t = sdl3::rgba_array_color<PixelFormat::value>;

        auto random_engine = std::default_random_engine(0);
        auto color_distribution = sdl3::unit_test::tools::uniform_color_distribution<packed_color_t>();
        auto x = color_distribution(random_engine);
        auto y = color_distribution(random_engine);

        BOOST_TEST(x * y == y * x);
    }

BOOST_AUTO_TEST_SUITE_END()
