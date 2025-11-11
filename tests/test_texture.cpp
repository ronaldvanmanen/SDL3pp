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

#include "SDL3pp/packed_color.hpp"
#include "SDL3pp/renderer.hpp"
#include "SDL3pp/texture.hpp"
#include "SDL3pp/window.hpp"

using sdl3::px;

BOOST_AUTO_TEST_SUITE(texture)

    BOOST_AUTO_TEST_CASE(test_texture_constructors)
    {
        auto test_case = []() {
            auto test_window = sdl3::window(
                "test_renderer_constructors",
                640 * px,
                480 * px,
                sdl3::window_flags::hidden
            );

            sdl3::renderer test_renderer(test_window);

            sdl3::streaming_texture<sdl3::pixel_format::argb8888> test_texture(
                test_renderer,
                test_renderer.output_size()
            );
        };

        BOOST_REQUIRE_NO_THROW(test_case());
    }

BOOST_AUTO_TEST_SUITE_END()
