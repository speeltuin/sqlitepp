// SPDX-License-Identifier: MIT

#include <sqlitepp/sqlitepp_error.hpp>

#include <gmock/gmock.h>

using namespace sqlitepp;

using ::testing::Eq;
using ::testing::StrEq;

class SqliteppErrorTest : public ::testing::Test
{
};

static_assert(std::is_error_code_enum<sqlitepp_errc>::value);
static_assert(not std::is_error_condition_enum<sqlitepp_errc>::value);

TEST_F(SqliteppErrorTest, Category)
{
    EXPECT_THAT(sqlitepp_category().name(), StrEq("sqlitepp"));
}

TEST_F(SqliteppErrorTest, InvalidHandle)
{
    std::error_code ec = sqlitepp_errc::invalid_handle;
    EXPECT_THAT(ec.message(), StrEq("Invalid handle"));
    EXPECT_THAT(ec.category().name(), StrEq("sqlitepp"));
    EXPECT_THAT(ec, Eq(sqlitepp_errc::invalid_handle));
}

TEST_F(SqliteppErrorTest, InvalidArgument)
{
    std::error_code ec = sqlitepp_errc::invalid_argument;
    EXPECT_THAT(ec.message(), StrEq("Invalid argument"));
    EXPECT_THAT(ec.category().name(), StrEq("sqlitepp"));
    EXPECT_THAT(ec, Eq(sqlitepp_errc::invalid_argument));
}

TEST_F(SqliteppErrorTest, UnknownError)
{
    std::error_code ec = static_cast<sqlitepp_errc>(-1);
    EXPECT_THAT(ec.message(), StrEq("Unknown error"));
}
