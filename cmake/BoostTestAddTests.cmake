# Copyright 2020, 2021 Deniz Bahadir and contributors
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
#
# This code is based on an implementation of the `gtest_discover_tests()`
# functionality that was originally distributed together with CMake unter the
# OSI-approved BSD 3-Clause License. The original authors and contributors of
# that code were so kind to agree to dual-license their work also under the
# Boost Software License, Version 1.0, so that this derived worked can be
# distributed under the same license as well.
# A public record of their granted permission can be found in this discussion
# of merge-request 4145 in the CMake issue tracker:
#   https://gitlab.kitware.com/cmake/cmake/-/merge_requests/4145#note_998500
#
# Therefore many thanks go to the following original authors and contributors:
#   Matthew Woehlke <matthew.woehlke@kitware.com>
#   Steffen Seckler <steffen.seckler@smartronic.de>
#   Ryan Thornton   <ThorntonRyan@JohnDeere.com>
#   Kevin Puetz     <PuetzKevinA@JohnDeere.com>
#   Stefan Floeren  <stefan.floeren@smartronic.de>
#   Alexander Stein <alexander.stein@mailbox.org>
#
# Deniz Bahadir in August of 2021.
#

cmake_minimum_required(VERSION ${CMAKE_VERSION})

# Overwrite possibly existing ${__CTEST_FILE} with empty file.
set(flush_tests_MODE WRITE)


# Flushes script to ${__CTEST_FILE}.
macro(flush_script)
  file(${flush_tests_MODE} "${__CTEST_FILE}" "${script}")
  set(flush_tests_MODE APPEND)
  set(script "")
endmacro()


# Flushes tests_buffer to tests variable.
macro(flush_tests_buffer)
  list(APPEND tests "${tests_buffer}")
  set(tests_buffer "")
endmacro()


# Removes surrounding double quotes (if any) from value of given variable VAR.
function(remove_outer_quotes VAR)
  string(REGEX REPLACE "^\"(.*)\"$" "\\1" ${VAR} "${${VAR}}")
  set(${VAR} "${${VAR}}" PARENT_SCOPE)
endfunction()


# Adds commands to script.
macro(add_command NAME)
  set(_args "")
  foreach(_arg ${ARGN})
    if(_arg MATCHES "[^-./:a-zA-Z0-9_]")
      string(APPEND _args " [==[${_arg}]==]")  # form a bracket argument
    else()
      string(APPEND _args " ${_arg}")
    endif()
  endforeach()
  string(APPEND script "${NAME}(${_args})\n")
  string(LENGTH "${script}" _script_len)
  if(${_script_len} GREATER "50000")
    flush_script()
  endif()
  # Unsets macro local variables to prevent leakage outside of this macro.
  unset(_args)
  unset(_script_len)
endmacro()

# Adds another test to the script.
macro(write_test_to_file test_path test_enabled test_source_line)
  string(REPLACE "/" "::" test_name "${test_path}")
  set(full_test_name "${prefix}${test_name}${suffix}")
  # ...and add to script.
  add_command(add_test
      "${full_test_name}"
      ${__TEST_EXECUTOR}
      "${__TEST_EXECUTABLE}"
      "--run_test=${test_path}"
      ${extra_args}
  )

  set(maybe_disabled "")
  if(NOT ${test_enabled} STREQUAL "*")
    set(maybe_disabled DISABLED TRUE)
  endif()

  set(maybe_source_line "")
  if(NOT ${test_source_line} STREQUAL "")
    set(maybe_source_line DEF_SOURCE_LINE ${test_source_line})
  endif()

  add_command(set_tests_properties
    "${full_test_name}"
    PROPERTIES
      ${maybe_disabled}
      ${maybe_source_line}
      WORKING_DIRECTORY "${__TEST_WORKING_DIR}"
      ${properties}
  )
  list(APPEND tests_buffer "${full_test_name}")
  list(LENGTH tests_buffer tests_buffer_length)
  if(${tests_buffer_length} GREATER "250")
    # Chunk updates to the final "tests" variable, keeping the
    # "tests_buffer" variable that we append each test to relatively
    # small. This mitigates worsening performance impacts for the
    # corner case of having many thousands of tests.
    flush_tests_buffer()
  endif()
endmacro()


# Internal implementation for boost_test_discover_tests.
function(boost_test_discover_tests_impl)

  cmake_parse_arguments(
    "_"
    ""
    "TEST_TARGET;TEST_EXECUTABLE;TEST_WORKING_DIR;TEST_PREFIX;TEST_SUFFIX;TEST_NAME_SEPARATOR;TEST_LIST;TEST_SKIP_DISABLED;CTEST_FILE;TEST_DISCOVERY_TIMEOUT"
    "TEST_EXTRA_ARGS;TEST_PROPERTIES;TEST_EXECUTOR"
    ${ARGN}
  )

  set(prefix "${__TEST_PREFIX}")
  set(suffix "${__TEST_SUFFIX}")
  set(extra_args ${__TEST_EXTRA_ARGS})
  set(properties ${__TEST_PROPERTIES})
  set(script)
  set(tests)
  set(tests_buffer)

  # Make sure the working directory exists.
  file(MAKE_DIRECTORY "${__TEST_WORKING_DIR}")
  # Run test executable to get list of available tests.
  if(NOT EXISTS "${__TEST_EXECUTABLE}")
    message(FATAL_ERROR
      "Specified test executable does not exist.\n"
      "  Path: '${__TEST_EXECUTABLE}'"
    )
  endif()

  # Custom format is used to build the test suite / test case hierarchy and determine which tests are enabled / disabled
  execute_process(
    COMMAND ${__TEST_EXECUTOR} "${__TEST_EXECUTABLE}" --list_test_cases
    WORKING_DIRECTORY "${__TEST_WORKING_DIR}"
    TIMEOUT ${__TEST_DISCOVERY_TIMEOUT}
    OUTPUT_VARIABLE test_units_list
    ERROR_VARIABLE test_units_list  # Boost.Test writes the requested content to stderr!
    RESULT_VARIABLE result
  )

  if(NOT ${result} EQUAL 0)
    string(REPLACE "\n" "\n    " output "${test_units_list}")
    message(FATAL_ERROR
      "Error running test executable.\n"
      "  Path: '${__TEST_EXECUTABLE}'\n"
      "  Result: ${result}\n"
      "  Output:\n"
      "    ${test_units_list}\n"
    )
  endif()

  # Preserve semicolon in test-parameters
  string(REPLACE [[;]] [[\;]] test_units_list "${test_units_list}")
  string(REPLACE "\n" ";" test_units_list "${test_units_list}")
  string(REPLACE [[\]] [[/]] test_units_list "${test_units_list}")

  # The hierarchy and its depth-level of the test of the former line.
  set(test_hierarchy "${TEST_TARGET}_MISSING_TESTS")
  set(former_level NaN)
  set(test_enabled 0)
  set(test_source_line "")

  # Parse output
  foreach(test_unit_line ${test_units_list})
    # Determine the depth-level of the next test-hierarchy.
    # Note: Each new depth-level (except for the top one) is indented
    #       by 4 spaces. So we need to count the spaces.
    string(REGEX MATCH "([^ *]+)(\\*)?( \\(([^\\)]+)\\))$" _ "${test_unit_line}")
    set(test_path ${CMAKE_MATCH_1})
    set(test_enabled ${CMAKE_MATCH_2})
    set(test_source_line ${CMAKE_MATCH_4})

    # Add test-case to the script.
    write_test_to_file("${test_path}" "${test_enabled}" "${test_source_line}" "${__TEST_NAME_SEPARATOR}")
  endforeach()

  # Create a list of all discovered tests, which users may use to e.g. set
  # properties on the tests.
  flush_tests_buffer()

  add_command(set ${__TEST_LIST} ${tests})

  # Write remaining content to the CTest script
  flush_script()

endfunction()


if(CMAKE_SCRIPT_MODE_FILE)
  # Note: Make sure to remove the outer layer of quotes that were added
  #       to preserve whitespace when handed over via cmdline.
  remove_outer_quotes(TEST_TARGET)
  remove_outer_quotes(TEST_EXECUTABLE)
  remove_outer_quotes(TEST_EXECUTOR)
  remove_outer_quotes(TEST_WORKING_DIR)
  remove_outer_quotes(TEST_EXTRA_ARGS)
  remove_outer_quotes(TEST_PROPERTIES)
  remove_outer_quotes(TEST_PREFIX)
  remove_outer_quotes(TEST_SUFFIX)
  remove_outer_quotes(TEST_NAME_SEPARATOR)
  remove_outer_quotes(TEST_LIST)
  remove_outer_quotes(TEST_SKIP_DISABLED)
  remove_outer_quotes(CTEST_FILE)
  remove_outer_quotes(TEST_DISCOVERY_TIMEOUT)

  boost_test_discover_tests_impl(
    TEST_TARGET ${TEST_TARGET}
    TEST_EXECUTABLE ${TEST_EXECUTABLE}
    TEST_EXECUTOR ${TEST_EXECUTOR}
    TEST_WORKING_DIR ${TEST_WORKING_DIR}
    TEST_PREFIX ${TEST_PREFIX}
    TEST_SUFFIX ${TEST_SUFFIX}
    TEST_NAME_SEPARATOR ${TEST_NAME_SEPARATOR}
    TEST_LIST ${TEST_LIST}
    TEST_SKIP_DISABLED ${TEST_SKIP_DISABLED}
    CTEST_FILE ${CTEST_FILE}
    TEST_DISCOVERY_TIMEOUT ${TEST_DISCOVERY_TIMEOUT}
    TEST_EXTRA_ARGS ${TEST_EXTRA_ARGS}
    TEST_PROPERTIES ${TEST_PROPERTIES}
  )
endif()
