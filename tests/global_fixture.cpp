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

#if !defined(NDEBUG) && defined(_MSC_VER)
#   define SDL3PP_MS_CRT_BASED_DEBUG
#   include <crtdbg.h>
#endif

#include <boost/test/debug.hpp>
#include <boost/test/unit_test.hpp>

struct global_fixture
{
    global_fixture();

    ~global_fixture();
};

global_fixture::global_fixture()
{
#ifdef SDL3PP_MS_CRT_BASED_DEBUG
    _CrtSetDbgFlag(0);
#endif

    boost::debug::detect_memory_leaks(false);
}

global_fixture::~global_fixture() { }

BOOST_TEST_GLOBAL_FIXTURE(global_fixture);
