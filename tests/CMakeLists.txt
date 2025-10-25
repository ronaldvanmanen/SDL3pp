list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake")
include(BoostTestDiscoverTests)
include(CodeCoverage)

add_executable("SDL3pp-tests"
  "global_fixture.cpp"
  "main.cpp"
  "test_blend_mode.cpp"
  "test_color.cpp"
  "test_event_queue.cpp"
  "test_palette.cpp"
  "test_pixel_format_details.cpp"
  "test_renderer.cpp"
  "test_rgb_array_color.cpp"
  "test_rgb_packed_color.cpp"
  "test_rgba_array_color.cpp"
  "test_rgba_packed_color.cpp"
  "test_surface.cpp"
  "test_texture.cpp"
  "test_window.cpp"
)

set_property(TARGET "SDL3pp-tests" PROPERTY CXX_STANDARD 23)

find_package(boost_unit_test_framework REQUIRED CONFIG)
target_link_libraries("SDL3pp-tests"
  PRIVATE
    SDL3pp
    Boost::unit_test_framework
)

add_code_coverage("SDL3pp-tests"
  WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
  PRE_RUN_COVERAGE_TARGET "pre-run-coverage"
  POST_RUN_COVERAGE_TARGET "post-run-coverage"
)

boost_test_discover_tests("SDL3pp-tests"
  WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
  TEST_PREFIX ""
  TEST_SUFFIX ""
  TEST_NAME_SEPARATOR "::"
  SKIP_DISABLED_TESTS
  DISCOVERY_TIMEOUT 1
  DISCOVERY_MODE PRE_TEST
  PROPERTIES
    ENVIRONMENT "LLVM_PROFILE_FILE=SDL3pp-tests-%m-%p.profraw"
)
