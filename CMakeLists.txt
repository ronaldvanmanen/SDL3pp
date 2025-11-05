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

find_program(LLVM_COV llvm-cov REQUIRED)
set(COVERAGE_COMMAND "${LLVM_COV}")
set(COVERAGE_EXTRA_FLAGS "")
include(CTest)

add_library("SDL3pp" INTERFACE)

find_package(Boost REQUIRED
  COMPONENTS
    algorithm
    optional
    units
    utility
)

target_link_libraries("SDL3pp"
  INTERFACE
    Boost::algorithm
    Boost::core
    Boost::optional
    Boost::units
    Boost::utility
)

find_package(SDL3 CONFIG REQUIRED)

target_link_libraries("${PROJECT_NAME}"
  INTERFACE
    $<TARGET_NAME_IF_EXISTS:SDL3::SDL3main>
    $<IF:$<TARGET_EXISTS:SDL3::SDL3>,SDL3::SDL3,SDL3::SDL3-static>
)

target_include_directories("${PROJECT_NAME}"
  INTERFACE
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/include"
)

add_subdirectory("samples")
add_subdirectory("tests")
add_subdirectory("tools")
