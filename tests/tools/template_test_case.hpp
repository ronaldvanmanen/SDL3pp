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

#include <boost/mpl/identity.hpp>
#include <boost/test/unit_test.hpp>

namespace sdl3::unit_test::tools
{
    template<typename TestType>
    struct test_type_name_generator
    {
        static std::string value()
        {
            // replacing ',' by ', ' first, and then removing any double space
            static const std::string to_replace[] =  { "class ", "struct ", ",", "  ", " <", " >"};
            static const std::string replacement[] = { "", "" , ", ", " ", "<" , ">"};

            std::string full_name = typeid(TestType).name();
            
            full_name = boost::unit_test::utils::replace_all_occurrences_of(
                full_name,
                to_replace, to_replace + sizeof(to_replace)/sizeof(to_replace[0]),
                replacement, replacement + sizeof(replacement)/sizeof(replacement[0]));

            typedef typename boost::remove_reference<TestType>::type TestTypewoRef;
            if( boost::is_const<TestTypewoRef>::value )
                full_name += "_const";
            if( boost::is_volatile<TestTypewoRef>::value )
                full_name += "_volatile";
            if( boost::is_rvalue_reference<TestType>::value )
                full_name += "_refref";
            else if( boost::is_lvalue_reference<TestType>::value )
                full_name += "_ref";

            return full_name;
        }
    };

    template<typename Generator, typename TestCaseTemplate>
    struct typed_test_case_generator
    {
        explicit typed_test_case_generator(boost::unit_test::const_string tc_name, boost::unit_test::const_string tc_file, std::size_t tc_line, Generator& G)
        : m_test_case_name(tc_name)
        , m_test_case_file(tc_file)
        , m_test_case_line(tc_line)
        , m_holder(G)
        {}

        template<typename TestType>
        void operator()(boost::mpl::identity<TestType>)
        {
            std::string test_case_name;
            assign_op(test_case_name, m_test_case_name, 0);
            //test_case_name += '<';
            test_case_name += "_for_";
            test_case_name += test_type_name_generator<TestType>::value();
            //test_case_name += '>';

            m_holder.m_test_cases.push_back(
                new boost::unit_test::test_case(
                    boost::unit_test::ut_detail::normalize_test_case_name(test_case_name),
                    m_test_case_file,
                    m_test_case_line,
                    boost::unit_test::ut_detail::test_case_template_invoker<TestCaseTemplate,TestType>()
                )
            );
        }

    private:
        // Data members
        boost::unit_test::const_string  m_test_case_name;
        boost::unit_test::const_string  m_test_case_file;
        std::size_t                     m_test_case_line;
        Generator&                      m_holder;
    };

    template<typename TestCaseTemplate, typename TestTypesList, typename enabler = void>
    class template_test_case_generator : public boost::unit_test::ut_detail::template_test_case_gen_base
    {
    public:
        // Constructor
        template_test_case_generator(boost::unit_test::const_string tc_name, boost::unit_test::const_string tc_file, std::size_t tc_line)
        {
            typedef typed_test_case_generator<
                template_test_case_generator<
                    TestCaseTemplate, TestTypesList
                >,
                TestCaseTemplate
            > single_test_case_generator;

            boost::mpl::for_each<
                TestTypesList, boost::mpl::make_identity<boost::mpl::_>
            >(single_test_case_generator(tc_name, tc_file, tc_line, *this));
        }
    };
}

#define SDL3PP_FIXTURE_TEST_CASE_TEMPLATE(test_name, type_name, type_list, fixture) \
template<typename type_name>                                                        \
struct test_name : public fixture                                                   \
{ void test_method(); };                                                            \
                                                                                    \
struct BOOST_AUTO_TC_INVOKER(test_name) {                                           \
    template<typename TestType>                                                     \
    static void run(boost::type<TestType>* = 0)                                     \
    {                                                                               \
        BOOST_TEST_CHECKPOINT('"' << #test_name << "\" fixture ctor");              \
        test_name<TestType> t;                                                      \
        BOOST_TEST_CHECKPOINT('"' << #test_name << "\" fixture setup");             \
        boost::unit_test::setup_conditional(t);                                     \
        BOOST_TEST_CHECKPOINT('"' << #test_name << "\" test entry");                \
        t.test_method();                                                            \
        BOOST_TEST_CHECKPOINT('"' << #test_name << "\" fixture teardown");          \
        boost::unit_test::teardown_conditional(t);                                  \
        BOOST_TEST_CHECKPOINT('"' << #test_name << "\" fixture dtor");              \
    }                                                                               \
};                                                                                  \
                                                                                    \
BOOST_AUTO_TU_REGISTRAR( test_name )(                                               \
    sdl3::unit_test::tools::template_test_case_generator<                               \
        BOOST_AUTO_TC_INVOKER(test_name), type_list>(                               \
          BOOST_STRINGIZE(test_name), __FILE__, __LINE__),                          \
    boost::unit_test::decorator::collector_t::instance());                          \
                                                                                    \
template<typename type_name>                                                        \
void test_name<type_name>::test_method()                                            \
/**/

#define SDL3PP_AUTO_TEST_CASE_TEMPLATE(test_name, type_name, type_list)     \
SDL3PP_FIXTURE_TEST_CASE_TEMPLATE(test_name, type_name, type_list,          \
    BOOST_AUTO_TEST_CASE_FIXTURE )                                          \
/**/
