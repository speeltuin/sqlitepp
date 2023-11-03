// SPDX-License-Identifier: MIT

#include <sqlitepp/detail/sqlite3.hpp>

#include <gmock/gmock.h>

using ::testing::StrEq;

TEST(Sqlite3Test, LibVersion)
{
    EXPECT_THAT(sqlite3_libversion(), StrEq(SQLITE_VERSION));
}
