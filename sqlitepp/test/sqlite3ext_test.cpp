// SPDX-License-Identifier: MIT

#include "sqlite3ext_stub.hpp"

#include <sqlitepp/detail/sqlite3.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest-spi.h>

using ::testing::Eq;
using ::testing::StrEq;

SQLITE_EXTENSION_INIT1

class Sqlite3ExtTest : public ::testing::Test
{
protected:
    sqlite3_api_routines stub_;

    void SetUp() override
    {
        stub_ = sqlite3ext_nice_stub::get();
        SQLITE_EXTENSION_INIT2(&stub_)
    }

    void TearDown() override
    {
        SQLITE_EXTENSION_INIT2(nullptr)
    }
};

TEST_F(Sqlite3ExtTest, LibVersionNull)
{
    EXPECT_THAT(sqlite3_libversion(), Eq(nullptr));
}

TEST_F(Sqlite3ExtTest, LibVersionFail)
{
    stub_ = sqlite3ext_strict_stub::get();
    EXPECT_NONFATAL_FAILURE(sqlite3_libversion(), "sqlite3_libversion");
}

TEST_F(Sqlite3ExtTest, LibVersionLambda)
{
    static constexpr const char version[] = "3.14159";
    stub_.libversion = []() { return version; };
    EXPECT_THAT(sqlite3_libversion(), StrEq(version));
}
