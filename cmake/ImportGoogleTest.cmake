# SPDX-License-Identifier: MIT

find_package(GTest 1.11.0)

if (NOT GTest_FOUND)
    include(FetchContent)

    FetchContent_Declare(
        googletest
        GIT_REPOSITORY "https://github.com/google/googletest.git"
        GIT_TAG main
        SOURCE_DIR ${PROJECT_SOURCE_DIR}/extern/googletest
    )

    option(INSTALL_GTEST "" OFF)

    FetchContent_MakeAvailable(googletest)

    include(GoogleTest)
endif()
