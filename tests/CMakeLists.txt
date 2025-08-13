cmake_minimum_required (VERSION 3.30)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("SDL3pp-tests")

macro("add_boost_test" TEST_MODULE_SOURCE)

  get_filename_component(TEST_MODULE_EXE ${TEST_MODULE_SOURCE} NAME_WE)
  
  add_executable("${TEST_MODULE_EXE}" "global_fixture.cpp" ${TEST_MODULE_SOURCE})

  set_property(TARGET ${TEST_MODULE_EXE} PROPERTY CXX_STANDARD 23)

  find_package(boost_unit_test_framework REQUIRED CONFIG)

  target_link_libraries("${TEST_MODULE_EXE}"
    PRIVATE
    SDL3pp
    Boost::unit_test_framework
  )

  file(READ "${TEST_MODULE_SOURCE}" TEST_MODULE_SOURCE_CONTENTS)

  string(REGEX MATCH "BOOST_TEST_MODULE *([A-Za-z_0-9]+)" TEST_MODULE_DEFINE ${TEST_MODULE_SOURCE_CONTENTS})
  string(REGEX REPLACE "BOOST_TEST_MODULE *([A-Za-z_0-9]+)" "\\1" TEST_MODULE_NAME ${TEST_MODULE_DEFINE})
  string(REGEX MATCHALL "BOOST_AUTO_TEST_CASE\\( *([A-Za-z_0-9]+) *\\)" TEST_CASE_DEFS ${TEST_MODULE_SOURCE_CONTENTS})

  foreach(TEST_CASE_DEF ${TEST_CASE_DEFS})
    string(REGEX REPLACE "BOOST_AUTO_TEST_CASE\\( *([A-Za-z_0-9]+) *\\).*" "\\1" TEST_CASE_NAME ${TEST_CASE_DEF})
    set(TEST_CASE_LOGICAL_NAME "${TEST_MODULE_NAME}.${TEST_CASE_NAME}")
    add_test(NAME "${TEST_CASE_LOGICAL_NAME}" COMMAND ${TEST_MODULE_EXE} --run_test=${TEST_CASE_NAME} --catch_system_error=yes)
  endforeach()
endmacro()

file(GLOB_RECURSE TEST_MODULE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR} test_*.cpp)

foreach(TEST_MODULE_SOURCE ${TEST_MODULE_SOURCES})
  add_boost_test(${TEST_MODULE_SOURCE})
endforeach()
