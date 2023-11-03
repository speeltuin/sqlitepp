# SPDX-License-Identifier: MIT

add_library(sqlitepp INTERFACE)
add_library(SQLitepp::sqlitepp ALIAS sqlitepp)

target_compile_features(sqlitepp INTERFACE cxx_std_17)

target_include_directories(
    sqlitepp INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:include>"
)

target_link_libraries(sqlitepp INTERFACE SQLite::SQLite3)

add_library(sqlitepp_ext INTERFACE)
add_library(SQLitepp::sqlitepp_ext ALIAS sqlitepp_ext)

target_compile_definitions(sqlitepp_ext INTERFACE SQLITEPP_INCLUDE_SQLITE3EXT)

target_link_libraries(sqlitepp_ext INTERFACE sqlitepp)

if (BUILD_TESTING)
    add_subdirectory(test)
endif()

install(TARGETS sqlitepp sqlitepp_ext EXPORT SQLiteppTargets)
install(DIRECTORY include/ TYPE INCLUDE)
