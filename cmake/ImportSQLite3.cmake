# SPDX-License-Identifier: MIT

find_package(SQLite3 3.44.0)

if (NOT SQLite3_FOUND)
    include(FetchContent)

    FetchContent_Declare(
        sqlite-amalgamation
        GIT_REPOSITORY "https://github.com/algoritnl/sqlite-amalgamation-cmake-buildsystem.git"
        GIT_TAG main
        SOURCE_DIR ${PROJECT_SOURCE_DIR}/extern/sqlite-amalgamation-cmake-buildsystem
    )

    set(SQLITE_DQS "0" CACHE INTERNAL "")
    set(SQLITE_THREADSAFE "2" CACHE INTERNAL "")
    set(SQLITE_DEFAULT_MEMSTATUS "0" CACHE INTERNAL "")
    set(SQLITE_DEFAULT_WAL_SYNCHRONOUS "1" CACHE INTERNAL "")
    set(SQLITE_MAX_EXPR_DEPTH "0" CACHE INTERNAL "")
    set(SQLITE_LIKE_DOESNT_MATCH_BLOBS ON INTERNAL "")
    set(SQLITE_ENABLE_API_ARMOR ON INTERNAL "")
    set(SQLITE_ENABLE_COLUMN_METADATA ON INTERNAL "")
    set(SQLITE_OMIT_DEPRECATED ON INTERNAL "")
    set(SQLITE_OMIT_SHARED_CACHE ON INTERNAL "")
    set(SQLITE_USE_ALLOCA ON INTERNAL "")
    set(SQLITE_BUILD_SHELL ON INTERNAL "")

    FetchContent_MakeAvailable(sqlite-amalgamation)
endif()
