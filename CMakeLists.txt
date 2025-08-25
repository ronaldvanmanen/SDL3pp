cmake_minimum_required (VERSION 3.30)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("SDL3pp")

set(CMAKE_CXX_STANDARD 23)

# if (MSVC)
#   set(ENV{esp.extensions} cppcorecheck.dll)
#   set(ENV{caexcludepath} "%include%")
#   add_compile_options(/analyze /analyze:plugin EspXEngine.dll)
# endif()

# FIX: Running tests from within VSCode fails unless we
#
# A) Remove "enable_testing()"
# B) Add "include(CTest)" to the root "CMakeLists.txt" before we declare any tests
#
# See: https://github.com/microsoft/vscode-cmake-tools/issues/3917
include(CTest)

add_library("${PROJECT_NAME}"
  "sources/blend_mode.cpp"
  "sources/color.cpp"
  "sources/display_mode.cpp"
  "sources/error.cpp"
  "sources/event_queue.cpp"
  "sources/event.cpp"
  "sources/indexed_color.cpp"
  "sources/key_modifier.cpp"
  "sources/keyboard_event.cpp"
  "sources/keyboard_state.cpp"
  "sources/keyboard.cpp"
  "sources/mouse_wheel_event.cpp"
  "sources/mouse.cpp"
  "sources/palette.cpp"
  "sources/pixel_format_details.cpp"
  "sources/renderer.cpp"
  "sources/surface.cpp"
  "sources/texture.cpp"
  "sources/window.cpp"
)

find_package(Boost REQUIRED
  COMPONENTS
  optional
  safe_numerics
  units
  utility
)

target_link_libraries("${PROJECT_NAME}"
  PRIVATE
  Boost::core
  Boost::optional
  Boost::safe_numerics
  Boost::units
  Boost::utility
)

find_package(SDL3 CONFIG REQUIRED)
target_link_libraries("${PROJECT_NAME}"
    PUBLIC
    $<TARGET_NAME_IF_EXISTS:SDL3::SDL3main>
    $<IF:$<TARGET_EXISTS:SDL3::SDL3>,SDL3::SDL3,SDL3::SDL3-static>
)

target_include_directories("${PROJECT_NAME}" PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/include")

add_subdirectory("${PROJECT_SOURCE_DIR}/samples")

add_subdirectory("${PROJECT_SOURCE_DIR}/tests")
