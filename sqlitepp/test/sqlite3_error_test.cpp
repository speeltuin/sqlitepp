// SPDX-License-Identifier: MIT

#include "sqlite3ext_stub.hpp"

#include <sqlitepp/sqlite3_error.hpp>

#include <cassert>
#include <functional>
#include <gmock/gmock.h>

using namespace sqlitepp;

using ::testing::Eq;
using ::testing::Return;
using ::testing::StrEq;

SQLITE_EXTENSION_INIT1

class Sqlite3ErrorTest : public ::testing::Test
{
public:
    MOCK_METHOD(const char*, errstr, (int), (noexcept));

protected:
    void SetUp() override
    {
        this_ = this;
        stub_ = sqlite3ext_nice_stub::get();
        stub_.errstr = mock_errstr;
        SQLITE_EXTENSION_INIT2(&stub_)
    }

    void TearDown() override
    {
        SQLITE_EXTENSION_INIT2(nullptr)
        this_ = nullptr;
    }

private:
    inline static Sqlite3ErrorTest* this_ = nullptr;
    sqlite3_api_routines stub_;

    static const char* mock_errstr(int ec) noexcept
    {
        assert(this_ != nullptr);
        return this_->errstr(ec);
    }
};

static_assert(not std::is_error_code_enum<sqlite3_errc>::value);
static_assert(std::is_error_condition_enum<sqlite3_errc>::value);

TEST_F(Sqlite3ErrorTest, Category)
{
    EXPECT_THAT(sqlite3_category().name(), StrEq("sqlite3"));
}

TEST_F(Sqlite3ErrorTest, Condition)
{
    EXPECT_CALL(*this, errstr(SQLITE_ERROR)).WillRepeatedly(Return("Error"));
    std::error_condition cond = sqlite3_errc::generic_error;
    EXPECT_THAT(cond.category().name(), StrEq("sqlite3"));
    EXPECT_THAT(cond.message(), StrEq("Error"));
}

TEST_F(Sqlite3ErrorTest, Error)
{
    std::error_code ec{SQLITE_ERROR, sqlite3_category()};
    EXPECT_THAT(ec.value(), Eq(SQLITE_ERROR));
    EXPECT_THAT(ec, Eq(sqlite3_errc::generic_error));
}

TEST_F(Sqlite3ErrorTest, DefaultCondition)
{
    std::error_code ec{SQLITE_ERROR_RETRY, sqlite3_category()};
    EXPECT_THAT(ec.value(), Eq(SQLITE_ERROR_RETRY));
    EXPECT_THAT(ec, Eq(sqlite3_errc::generic_error));
}
