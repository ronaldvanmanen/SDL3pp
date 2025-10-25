macro("add_sample" TARGET)
  set(multiValueArgs SOURCES PACKAGES LIBRARIES COMPILE_DEFINITIONS)
  cmake_parse_arguments(arg "" "" "${multiValueArgs}" ${ARGN})

  add_executable(${TARGET} ${arg_SOURCES})

  target_link_libraries(${TARGET} PRIVATE SDL3pp)

  if ("${PACKAGES}")
    foreach(PACKAGE "${PACKAGES}")
      find_package("${PACKAGE}" REQUIRED CONFIG)
    endforeach()
  endif()

  if ("${LIBRARIES}")
    foreach(LIBRARY "${LIBRARIES}")
      target_link_libraries("${TARGET}" PRIVATE "${LIBRARY}")
    endforeach()
  endif()

  if ("${COMPILE_DEFINITIONS}")
    target_compile_definitions("${TARGET}" PRIVATE "${COMPILE_DEFINITIONS}")
  endif()

endmacro()

add_subdirectory("hw_ray_tracer")
add_subdirectory("plasma_fractal")
add_subdirectory("sw_ray_tracer")
add_subdirectory("tunnel_effect")
