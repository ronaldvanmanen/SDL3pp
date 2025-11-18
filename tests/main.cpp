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

#include <iostream>
#include <vector>

#include <boost/cstdlib.hpp>

#define BOOST_TEST_NO_MAIN
#include <boost/test/debug.hpp>
#include <boost/test/results_reporter.hpp>
#include <boost/test/tree/test_unit.hpp>
#include <boost/test/tree/traverse.hpp>
#include <boost/test/tree/visitor.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_parameters.hpp>

struct test_case_reporter : boost::unit_test::test_tree_visitor
{
public:
    explicit test_case_reporter(std::ostream & os)
    : m_os(os)
    , m_test_suites()
    { }

private:
    void report_test_unit(boost::unit_test::test_unit const & test_unit)
    {
        for (auto test_suite : m_test_suites)
        {
            m_os << test_suite << "/";
        }
        m_os << test_unit.p_name;
        m_os << (test_unit.p_default_status == boost::unit_test::test_unit::RS_ENABLED ? "*" : "");
        if (!test_unit.p_file_name.empty())
        {
            m_os << " (" << test_unit.p_file_name << ":" << test_unit.p_line_num << ")";
        }
        m_os << std::endl;
    }

    void visit(boost::unit_test::test_case const & test_case) override
    {
        report_test_unit(test_case);
    }

    bool test_suite_start(boost::unit_test::test_suite const & test_suite) override
    {
        if (&test_suite != &boost::unit_test::framework::master_test_suite())
        {
            m_test_suites.push_back(test_suite.p_name);
        }
        return true;
    }

    void test_suite_finish(boost::unit_test::test_suite const & test_suite) override
    {
        if (&test_suite != &boost::unit_test::framework::master_test_suite())
        {
            m_test_suites.pop_back();
        }
    }

private:
    std::ostream & m_os;
    std::vector<std::string> m_test_suites;
};

bool initialize_unit_tests()
{
    return true;
}

int main(int argc, char * argv[])
{
    if (argc == 2 && argv[1] == std::string("--list_test_cases"))
    {
        auto exit_code = boost::exit_success;

        try
        {
            boost::unit_test::framework::init(&initialize_unit_tests, 1, argv);
            boost::unit_test::framework::finalize_setup_phase();
            boost::debug::detect_memory_leaks(false);

            auto & master_test_suite = boost::unit_test::framework::master_test_suite();
            test_case_reporter reporter(boost::unit_test::results_reporter::get_stream());
            boost::unit_test::traverse_test_tree(master_test_suite, reporter, true);
        }
        catch (...)
        {
            exit_code = boost::exit_failure;
        }

        boost::unit_test::framework::shutdown();

        return exit_code;
    }
    else
    {
        return boost::unit_test::unit_test_main(&initialize_unit_tests, argc, argv);
    }
}
