cmake_minimum_required (VERSION 3.30)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("SDL3pp-tools")

macro("add_tool" TARGET)
  set(multiValueArgs SOURCES PACKAGES)
  cmake_parse_arguments(arg "" "" "${multiValueArgs}" ${ARGN})

  add_executable(${TARGET} ${arg_SOURCES})

  target_link_libraries(${TARGET} PRIVATE SDL3pp)

  if ("${PACKAGES}")
    find_package(Boost REQUIRED COMPONENTS "${PACKAGES}")
    target_link_libraries("${TARGET}"
      PRIVATE
      "$<LIST:TRANSFORM,${PACKAGES},PREPEND,Boost::>"
    )
  endif()
endmacro()

add_tool("pixel_format_enumerator" SOURCES "pixel_format_enumerator.cpp")
