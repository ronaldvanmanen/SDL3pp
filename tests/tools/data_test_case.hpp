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

#include <boost\test\data\test_case.hpp>

namespace sdl3::unit_test::tools
{
    template<typename TestCase,typename DataSet>
    class data_test_case_generator : public boost::unit_test::test_unit_generator {
    public:
        // Constructor
    #ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
        data_test_case_generator( boost::unit_test::const_string tc_name, boost::unit_test::const_string tc_file, std::size_t tc_line, DataSet&& ds )
        : m_dataset( std::forward<DataSet>( ds ) )
        , m_generated( false )
        , m_tc_name( boost::unit_test::ut_detail::normalize_test_case_name( tc_name ) )
        , m_tc_file( tc_file )
        , m_tc_line( tc_line )
        {}
        data_test_case_generator( data_test_case_generator&& gen )
        : m_dataset( std::move( gen.m_dataset ) )
        , m_generated( gen.m_generated )
        , m_tc_name( gen.m_tc_name )
        , m_tc_file( gen.m_tc_file )
        , m_tc_line( gen.m_tc_line )
        , m_test_cases( std::move(gen.m_test_cases) )
        {}
    #else
        data_test_case_generator( const_string tc_name, const_string tc_file, std::size_t tc_line, DataSet const& ds )
        : m_dataset( ds )
        , m_generated( false )
        , m_tc_name( ut_detail::normalize_test_case_name( tc_name ) )
        , m_tc_file( tc_file )
        , m_tc_line( tc_line )
        {}
    #endif

    public:
        virtual boost::unit_test::test_unit* next() const
        {
            if(!m_generated) {
                boost::unit_test::data::for_each_sample( m_dataset, *this );
                m_generated = true;
            }

            if( m_test_cases.empty() )
                return 0;

            boost::unit_test::test_unit* res = m_test_cases.front();
            m_test_cases.pop_front();

            return res;
        }


    #if !defined(BOOST_TEST_DATASET_VARIADIC)
        // see BOOST_TEST_DATASET_MAX_ARITY to increase the default supported arity
        // there is also a limit on boost::bind
    #define TC_MAKE(z,arity,_)                                                                                  \
        template<BOOST_PP_ENUM_PARAMS(arity, typename Arg)>                                                     \
        void    operator()( BOOST_PP_ENUM_BINARY_PARAMS(arity, Arg, const& arg) ) const                         \
        {                                                                                                       \
            m_test_cases.push_back( new boost::unit_test::test_case( genTestCaseName(), m_tc_file, m_tc_line,   \
            boost::bind( &TestCase::template test_method<BOOST_PP_ENUM_PARAMS(arity,Arg)>,                      \
            BOOST_PP_ENUM_PARAMS(arity, arg) ) ) );                                                             \
        }                                                                                                       \
        /**/

        BOOST_PP_REPEAT_FROM_TO(1, BOOST_TEST_DATASET_MAX_ARITY, TC_MAKE, _)
    #else
        template<typename ...Arg>
        void operator()(Arg&& ... arg) const
        {
            m_test_cases.push_back(
                new boost::unit_test::test_case(
                    generate_test_case_name(arg...),
                    m_tc_file,
                    m_tc_line,
                    std::bind( &TestCase::template test_method<Arg...>,
                        boost::unit_test::data::ds_detail::boost_bind_rvalue_holder_helper(std::forward<Arg>(arg))...
                    )
                )
            );
        }
    #endif

    private:
        template<typename Head, typename ...Tail>
        std::string generate_test_case_name(Head&& head, Tail&& ... tail) const
        {
            return boost::unit_test::utils::string_cast(head) + "_" + generate_test_case_name(tail...);
        }

        template<typename Head>
        std::string generate_test_case_name(Head&& head) const
        {
            return boost::unit_test::utils::string_cast(head);
        }

        // Data members
        DataSet                                         m_dataset;
        mutable bool                                    m_generated;
        std::string                                     m_tc_name;
        boost::unit_test::const_string                  m_tc_file;
        std::size_t                                     m_tc_line;
        mutable std::list<boost::unit_test::test_unit*> m_test_cases;
    };

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
    template<typename TestCase,typename DataSet>
    boost::shared_ptr<boost::unit_test::test_unit_generator>
    make_data_test_case_generator( boost::unit_test::const_string tc_name, boost::unit_test::const_string tc_file, std::size_t tc_line, DataSet&& ds )
    {
        return boost::shared_ptr<
            boost::unit_test::test_unit_generator
        >(new data_test_case_generator<TestCase,DataSet>( tc_name, tc_file, tc_line, std::forward<DataSet>(ds) ));
    }
#else
    template<typename TestCase,typename DataSet>
    data_test_case_generator<TestCase,DataSet>
    make_data_test_case_generator( const_string tc_name, const_string tc_file, std::size_t tc_line, DataSet const& ds )
    {
        return data_test_case_generator<TestCase,DataSet>( tc_name, tc_file, tc_line, ds );
    }
#endif

}

#define SDL3PP_DATA_TEST_CASE_IMPL(arity, F, test_name, dataset, params)\
struct BOOST_PP_CAT(test_name, case) : public F {                       \
    template<BOOST_PP_ENUM_PARAMS(arity, typename Arg)>                 \
    static void test_method( BOOST_DATA_TEST_CASE_PARAMS( params ) )    \
    {                                                                   \
        BOOST_TEST_CONTEXT( ""                                          \
            BOOST_PP_SEQ_FOR_EACH(BOOST_DATA_TEST_CONTEXT, _, params))  \
        {                                                               \
          BOOST_TEST_CHECKPOINT('"' << #test_name << "\" fixture ctor");\
          BOOST_PP_CAT(test_name, case) t;                              \
          BOOST_TEST_CHECKPOINT('"'                                     \
              << #test_name << "\" fixture setup");                     \
          boost::unit_test::setup_conditional(t);                       \
          BOOST_TEST_CHECKPOINT('"' << #test_name << "\" test entry");  \
          t._impl(BOOST_PP_SEQ_ENUM(params));                           \
          BOOST_TEST_CHECKPOINT('"'                                     \
              << #test_name << "\" fixture teardown");                  \
          boost::unit_test::teardown_conditional(t);                    \
          BOOST_TEST_CHECKPOINT('"' << #test_name << "\" fixture dtor");\
        }                                                               \
    }                                                                   \
private:                                                                \
    template<BOOST_PP_ENUM_PARAMS(arity, typename Arg)>                 \
    void _impl(BOOST_DATA_TEST_CASE_PARAMS( params ));                  \
};                                                                      \
                                                                        \
BOOST_AUTO_TEST_SUITE( test_name,                                       \
                       *boost::unit_test::decorator::stack_decorator()) \
                                                                        \
BOOST_AUTO_TU_REGISTRAR( BOOST_PP_CAT(test_name, case) )(               \
    sdl3::unit_test::tools::make_data_test_case_generator<              \
                                      BOOST_PP_CAT(test_name, case)>(   \
          BOOST_STRINGIZE( test_name ),                                 \
          __FILE__, __LINE__,                                           \
          boost::unit_test::data::ds_detail::seed{} ->* dataset ),      \
    boost::unit_test::decorator::collector_t::instance() );             \
                                                                        \
BOOST_AUTO_TEST_SUITE_END()                                             \
                                                                        \
    template<BOOST_PP_ENUM_PARAMS(arity, typename Arg)>                 \
    void BOOST_PP_CAT(test_name, case)::_impl(                          \
                                BOOST_DATA_TEST_CASE_PARAMS( params ) ) \
/**/

#define SDL3PP_DATA_TEST_CASE_WITH_PARAMS( F, test_name, dataset, ... ) \
    SDL3PP_DATA_TEST_CASE_IMPL( BOOST_PP_VARIADIC_SIZE(__VA_ARGS__),    \
                               F, test_name, dataset,                   \
                               BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__) )  \
/**/
#define SDL3PP_DATA_TEST_CASE_NO_PARAMS( F, test_name, dataset )        \
    SDL3PP_DATA_TEST_CASE_WITH_PARAMS( F, test_name, dataset, sample )  \
/**/

#if BOOST_PP_VARIADICS_MSVC

#define SDL3PP_DATA_TEST_CASE( ... )                                    \
    BOOST_PP_CAT(                                                       \
    BOOST_PP_IIF(BOOST_PP_EQUAL(BOOST_PP_VARIADIC_SIZE(__VA_ARGS__),2), \
                     SDL3PP_DATA_TEST_CASE_NO_PARAMS,                   \
                     SDL3PP_DATA_TEST_CASE_WITH_PARAMS) (               \
                        BOOST_AUTO_TEST_CASE_FIXTURE, __VA_ARGS__), )   \
/**/

#define SDL3PP_DATA_TEST_CASE_F( F, ... )                               \
    BOOST_PP_CAT(                                                       \
    BOOST_PP_IIF(BOOST_PP_EQUAL(BOOST_PP_VARIADIC_SIZE(__VA_ARGS__),2), \
                     SDL3PP_DATA_TEST_CASE_NO_PARAMS,                   \
                     SDL3PP_DATA_TEST_CASE_WITH_PARAMS) (               \
                        F, __VA_ARGS__), )                              \
/**/

#else

#define SDL3PP_DATA_TEST_CASE( ... )                                     \
    BOOST_PP_IIF(BOOST_PP_EQUAL(BOOST_PP_VARIADIC_SIZE(__VA_ARGS__),2), \
                     SDL3PP_DATA_TEST_CASE_NO_PARAMS,                    \
                     SDL3PP_DATA_TEST_CASE_WITH_PARAMS) (                \
                        BOOST_AUTO_TEST_CASE_FIXTURE, __VA_ARGS__)      \
/**/

#define SDL3PP_DATA_TEST_CASE_F( F, ... )                                \
    BOOST_PP_IIF(BOOST_PP_EQUAL(BOOST_PP_VARIADIC_SIZE(__VA_ARGS__),2), \
                     SDL3PP_DATA_TEST_CASE_NO_PARAMS,                    \
                     SDL3PP_DATA_TEST_CASE_WITH_PARAMS) (                \
                        F, __VA_ARGS__)                                 \
/**/
#endif
