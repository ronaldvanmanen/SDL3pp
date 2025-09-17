cmake_minimum_required (VERSION 3.30)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("SDL3pp-tests")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake")
include(BoostTestDiscoverTests)
include(CodeCoverage)

add_executable("${PROJECT_NAME}"
  "global_fixture.cpp"
  "test_blend_mode.cpp"
  "test_color.cpp"
  "test_event_queue.cpp"
  "test_main.cpp"
  "test_packed_color.cpp"
  "test_palette.cpp"
  "test_pixel_format_details.cpp"
  "test_renderer.cpp"
  "test_surface.cpp"
  "test_texture.cpp"
  "test_window.cpp"
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 23)

find_package(boost_unit_test_framework REQUIRED CONFIG)
target_link_libraries("${PROJECT_NAME}"
  PRIVATE
    SDL3pp
    Boost::unit_test_framework
)

add_code_coverage("${PROJECT_NAME}"
  WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
  PRE_RUN_COVERAGE_TARGET "pre-run-coverage"
  POST_RUN_COVERAGE_TARGET "post-run-coverage"
)

boost_test_discover_tests("${PROJECT_NAME}"
  WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
  TEST_PREFIX ""
  TEST_SUFFIX ""
  TEST_NAME_SEPARATOR "::"
  SKIP_DISABLED_TESTS
  DISCOVERY_TIMEOUT 1
  DISCOVERY_MODE PRE_TEST
  PROPERTIES
    ENVIRONMENT "LLVM_PROFILE_FILE=${PROJECT_NAME}-%m-%p.profraw"
)
