# SPDX-License-Identifier: MIT

add_executable(sqlite3_test sqlite3_test.cpp)
target_link_libraries(sqlite3_test PRIVATE SQLitepp::sqlitepp GTest::gmock_main)
gtest_discover_tests(sqlite3_test)

add_executable(sqlite3ext_test sqlite3ext_test.cpp)
target_link_libraries(sqlite3ext_test PRIVATE SQLitepp::sqlitepp_ext GTest::gmock_main)
gtest_discover_tests(sqlite3ext_test)

add_executable(sqlite3_error_test sqlite3_error_test.cpp)
target_link_libraries(sqlite3_error_test PRIVATE SQLitepp::sqlitepp_ext GTest::gmock_main)
gtest_discover_tests(sqlite3_error_test)

add_executable(sqlitepp_error_test sqlitepp_error_test.cpp)
target_link_libraries(sqlitepp_error_test PRIVATE SQLitepp::sqlitepp GTest::gmock_main)
gtest_discover_tests(sqlitepp_error_test)

add_executable(connection_unit_test connection_unit_test.cpp)
target_link_libraries(connection_unit_test PRIVATE SQLitepp::sqlitepp_ext GTest::gmock_main)
gtest_discover_tests(connection_unit_test)

add_executable(connection_system_test connection_system_test.cpp)
target_link_libraries(connection_system_test PRIVATE SQLitepp::sqlitepp GTest::gmock_main)
gtest_discover_tests(connection_system_test)
