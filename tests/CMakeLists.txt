cmake_minimum_required (VERSION 3.20)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("SDL3pp-tests")

add_executable("${PROJECT_NAME}"
  "global_fixture.cpp"
  "test_argb8888.cpp"
  "test_xrgb8888.cpp"
  "test_color.cpp"
  "test_event_queue.cpp"
  "test_main.cpp"
  "test_palette.cpp"
  "test_pixel_format_details.cpp"
  "test_renderer.cpp"
  "test_surface.cpp"
  "test_texture.cpp"
  "test_window.cpp"
)

find_package(boost_unit_test_framework REQUIRED CONFIG)
target_link_libraries("${PROJECT_NAME}"
  PRIVATE
  SDL3pp
  Boost::unit_test_framework
)

add_test("${PROJECT_NAME}" "${PROJECT_NAME}")
