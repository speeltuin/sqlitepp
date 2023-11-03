# SPDX-License-Identifier: MIT

include(CustomConfigurationType)

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_custom_configuration_type(
        Coverage
        POSTFIX -cov
        BASED_ON Debug
        C_FLAGS -O0 -fprofile-instr-generate -fcoverage-mapping
        CXX_FLAGS -O0 -fprofile-instr-generate -fcoverage-mapping
        EXE_LINKER_FLAGS -fprofile-instr-generate -fcoverage-mapping
        SHARED_LINKER_FLAGS -fprofile-instr-generate -fcoverage-mapping
    )
else()
    add_custom_configuration_type(
        Coverage
        POSTFIX -cov
        BASED_ON Debug
        C_FLAGS -O0 --coverage
        CXX_FLAGS -O0 --coverage
        EXE_LINKER_FLAGS --coverage
        SHARED_LINKER_FLAGS --coverage
    )
endif()
