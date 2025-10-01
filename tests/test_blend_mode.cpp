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

#include <string>
#include <iostream>

#include <boost/test/unit_test.hpp>

#include "tools/data_test_case.hpp"

#include "SDL3pp/blend_mode.hpp"

BOOST_AUTO_TEST_SUITE(blend_mode);

sdl3::blend_mode blend_modes[] =
{
    sdl3::blend_mode::none,
    sdl3::blend_mode::blend,
    sdl3::blend_mode::additive,
    sdl3::blend_mode::modulate,
    sdl3::blend_mode::multiply,
    sdl3::blend_mode::invalid
};

std::map<sdl3::blend_mode, std::string> blend_mode_names
{
    { sdl3::blend_mode::none, "none" },
    { sdl3::blend_mode::blend, "blend" },
    { sdl3::blend_mode::additive, "additive" },
    { sdl3::blend_mode::modulate, "modulate" },
    { sdl3::blend_mode::multiply, "multiply" },
    { sdl3::blend_mode::invalid, "invalid" }
};

SDL3PP_DATA_TEST_CASE(test_stream_insertion_operator,
    boost::unit_test::data::make(blend_modes),
    test_blend_mode
)
{
    std::stringstream s;
    s << test_blend_mode;
    BOOST_TEST(blend_mode_names[test_blend_mode] == s.str());
}

BOOST_AUTO_TEST_SUITE_END();
