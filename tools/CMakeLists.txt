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

add_tool("pixel_format_enumerator"
  SOURCES
    "pixel_format_enumerator.cpp"
)
