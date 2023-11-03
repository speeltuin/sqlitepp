# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.22...3.27)

file(STRINGS sqlitepp/include/sqlitepp/version.hpp _ver_line
    REGEX "^#define SQLITEPP_VERSION +\"[0-9]+\\.[0-9]+\\.[0-9]+\""
    LIMIT_COUNT 1)
string(REGEX MATCH "[0-9]+\\.[0-9]+\\.[0-9]+"
    SQLITEPP_VERSION ${_ver_line})
unset(_ver_line)

project(
    SQLitepp
    VERSION "${SQLITEPP_VERSION}"
    DESCRIPTION "C++ binding for SQLite v3"
    LANGUAGES C CXX
)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

include(CodeCoverage)
include(GNUInstallDirs)
include(ImportSQLite3)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    include(CTest)
endif()

if (BUILD_TESTING)
    include(ImportGoogleTest)
endif()

add_subdirectory(sqlitepp)

install(EXPORT SQLiteppTargets
    FILE SQLiteppTargets.cmake
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/SQLitepp"
    NAMESPACE SQLitepp::)

export(EXPORT SQLiteppTargets
    FILE "${CMAKE_CURRENT_BINARY_DIR}/SQLiteppTargets.cmake")

include(CMakePackageConfigHelpers)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/SQLiteppConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/SQLiteppConfig.cmake"
    INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/SQLitepp"
    NO_SET_AND_CHECK_MACRO
    NO_CHECK_REQUIRED_COMPONENTS_MACRO)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/SQLiteppConfigVersion.cmake"
    COMPATIBILITY AnyNewerVersion)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/SQLiteppConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/SQLiteppConfigVersion.cmake"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/SQLitepp")

include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_VERSION_MAJOR "${SQLitepp_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${SQLitepp_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${SQLitepp_VERSION_PATCH}")
include(CPack)