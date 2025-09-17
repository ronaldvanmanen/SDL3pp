# Code Coverage
#
# Copyright (C) 2025 Ronald van Manen <rvanmanen@gmail.com>
#
# This software is provided 'as-is', without any express or implied
# warranty.  In no event will the authors be held liable for any damages
# arising from the use of this software.
# 
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
#
# 1. The origin of this software must not be misrepresented; you must not
#    claim that you wrote the original software. If you use this software
#    in a product, an acknowledgment in the product documentation would be
#    appreciated but is not required.
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.

#[=======================================================================[.rst:
BoostTestDiscoverTests
----------------------

This module defines a function to enable code coverage for a specific target.

.. command:: add_code_coverage

  Add support for code coverage to the compiled executable::

    add_code_coverage(target
                      [WORKING_DIRECTORY dir]
                      [PRE_RUN_COVERAGE_TARGET value]
                      [POST_RUN_COVERAGE_TARGET value]
    )

  The options are:

  ``target``
    Specifies the executable to enable code coverage for.

  ``WORKING_DIRECTORY dir``
    Specifies the directory in which to run code coverage.  If this
    option is not provided, the current binary directory is used.

  ``PRE_RUN_COVERAGE_TARGET value``
    Specifies the name of the target to build before running tests with code
    coverage. Set "cmake.preRunCoverageTarget" in the VS Code settings file
    located at .vscode/settings.json to this value to.

  ``POST_RUN_COVERAGE_TARGET value``
    Specifies the name of the target to build after running tests with code
    coverage. Set "cmake.preRunCoverageTarget" in the VS Code settings file
    located at .vscode/settings.json to this value to.

#]=======================================================================]

function(add_code_coverage TARGET)

    cmake_parse_arguments(
        "_"
        ""
        "WORKING_DIRECTORY;PRE_RUN_COVERAGE_TARGET;POST_RUN_COVERAGE_TARGET"
        ""
        ${ARGN}
    )

    if(NOT __PRE_RUN_COVERAGE_TARGET)
        set(__PRE_RUN_COVERAGE_TARGET "pre-run-coverage")
    endif()

    if(NOT __POST_RUN_COVERAGE_TARGET)
        set(__POST_RUN_COVERAGE_TARGET "post-run-coverage")
    endif()

    if (NOT __WORKING_DIRECTORY)
        set(__WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
    endif()

    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        find_program(LLVM_COV llvm-cov REQUIRED)
        find_program(LLVM_PROFDATA llvm-profdata REQUIRED)
        string(CONCAT pre_run_coverage_content
            "file(GLOB profraw *.profraw)\n"
            "file(REMOVE \${profraw})\n"
        )
        file(GENERATE OUTPUT "${TARGET}_pre_coverage.cmake" CONTENT "${pre_run_coverage_content}")
        add_custom_target("${__PRE_RUN_COVERAGE_TARGET}"
            COMMAND ${CMAKE_COMMAND} -P "${TARGET}_pre_coverage.cmake"
            WORKING_DIRECTORY "${__WORKING_DIRECTORY}"
        )
        add_custom_target("${__POST_RUN_COVERAGE_TARGET}"
            COMMAND ${LLVM_PROFDATA} merge *.profraw -o ${TARGET}.profdata
            COMMAND ${LLVM_COV} export
            --format=lcov
            --instr-profile="${TARGET}.profdata"
            --object="${TARGET}.exe"
            > ../../coverage.info
            BYPRODUCTS "${TARGET}.profdata" "../../coverage.info"
            WORKING_DIRECTORY "${__WORKING_DIRECTORY}"
        )
        target_compile_options(${TARGET}
            PRIVATE
                "-fprofile-instr-generate"
                "-fcoverage-mapping"
        )
        if(WIN32)
            if(CMAKE_SIZEOF_VOID_P EQUAL 8)
                target_link_libraries(${TARGET} PRIVATE "clang_rt.profile-x86_64.lib")
            else()
                target_link_libraries(${TARGET} PRIVATE "clang_rt.profile-i386.lib")
            endif()
        else()
            target_link_options(${TARGET}
                PRIVATE
                    "-fprofile-instr-generate"
                    "-fcoverage-mapping"
            )
        endif()
    else()
        add_custom_target("${__PRE_RUN_COVERAGE_TARGET}")
        add_custom_target("${__POST_RUN_COVERAGE_TARGET}")
    endif()
endfunction()
