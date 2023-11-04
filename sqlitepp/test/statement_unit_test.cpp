// SPDX-License-Identifier: MIT

#include "sqlite3ext_stub.hpp"

#include <sqlitepp/connection.hpp>
#include <sqlitepp/statement.hpp>

#include <cassert>
#include <gmock/gmock.h>
#include <utility>

#if defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wpessimizing-move"
#if defined(__clang__) || __GNUC__ >= 13
#pragma GCC diagnostic ignored "-Wself-move"
#endif
#endif

using namespace sqlitepp;

using ::testing::_;
using ::testing::DoAll;
using ::testing::InSequence;
using ::testing::Return;
using ::testing::SetArgPointee;

SQLITE_EXTENSION_INIT1

struct sqlite3
{
    int id;
};

struct sqlite3_stmt
{
    int id;
};

class StatementUnitTest : public ::testing::Test
{
public:
    MOCK_METHOD(const char*, errstr, (int), (noexcept));
    MOCK_METHOD(int, open_v2, (const char*, sqlite3**, int, const char*), (noexcept));
    MOCK_METHOD(int, close_v2, (sqlite3*), (noexcept));
    MOCK_METHOD(int, prepare_v3, (sqlite3*, const char*, int, unsigned int, sqlite3_stmt**, const char**), (noexcept));
    MOCK_METHOD(int, finalize, (sqlite3_stmt*), (noexcept));

protected:
    void SetUp() override
    {
        this_ = this;
        stub_ = sqlite3ext_strict_stub::get();
        stub_.errstr = mock_errstr;
        stub_.open_v2 = mock_open_v2;
        stub_.close_v2 = mock_close_v2;
        stub_.prepare_v3 = mock_prepare_v3;
        stub_.finalize = mock_finalize;
        SQLITE_EXTENSION_INIT2(&stub_)
    }

    void TearDown() override
    {
        SQLITE_EXTENSION_INIT2(nullptr)
        this_ = nullptr;
    }

private:
    inline static StatementUnitTest* this_ = nullptr;
    sqlite3_api_routines stub_;

    static const char* mock_errstr(int rc) noexcept
    {
        assert(this_ != nullptr);
        return this_->errstr(rc);
    }

    static int mock_open_v2(const char* filename, sqlite3** db, int flags, const char* vfs) noexcept
    {
        assert(this_ != nullptr);
        return this_->open_v2(filename, db, flags, vfs);
    }

    static int mock_close_v2(sqlite3* db) noexcept
    {
        assert(this_ != nullptr);
        return this_->close_v2(db);
    }

    static int mock_prepare_v3(sqlite3* db, const char* sql, int bytes, unsigned int flags, sqlite3_stmt** stmt, const char** tail) noexcept
    {
        assert(this_ != nullptr);
        return this_->prepare_v3(db, sql, bytes, flags, stmt, tail);
    }

    static int mock_finalize(sqlite3_stmt* stmt) noexcept
    {
        assert(this_ != nullptr);
        return this_->finalize(stmt);
    }
};

TEST_F(StatementUnitTest, ConstructEmptyNoError)
{
    sqlite3 db{1};
    std::error_code ec;

    statement stmt = prepare(&db, ec);
    EXPECT_FALSE(ec);

    EXPECT_EQ(stmt.conn_handle(), &db);
    EXPECT_EQ(stmt.stmt_handle(), nullptr);
}

TEST_F(StatementUnitTest, ConstructSelectNoError)
{
    sqlite3 db{1};
    sqlite3_stmt st{1};
    std::error_code ec;

    InSequence seq;
    EXPECT_CALL(*this, open_v2(_, _, _, _)).WillOnce(DoAll(SetArgPointee<1>(&db), Return(SQLITE_OK)));
    EXPECT_CALL(*this, prepare_v3(_, _, _, _, _, _)).WillOnce(DoAll(SetArgPointee<4>(&st), SetArgPointee<5>(nullptr), Return(SQLITE_OK)));
    EXPECT_CALL(*this, finalize(&st));
    EXPECT_CALL(*this, close_v2(&db));

    connection conn = connect(":memory:", ec);

    EXPECT_FALSE(ec);

    statement stmt = prepare(conn, "SELECT 1;", ec);

    EXPECT_FALSE(ec);
    EXPECT_EQ(stmt.conn_handle(), &db);
    EXPECT_EQ(stmt.stmt_handle(), &st);
}

TEST_F(StatementUnitTest, PrepareSelectNoError)
{
    sqlite3 db{1};
    sqlite3_stmt st{1};
    std::error_code ec;

    InSequence seq;
    EXPECT_CALL(*this, open_v2(_, _, _, _)).WillOnce(DoAll(SetArgPointee<1>(&db), Return(SQLITE_OK)));
    EXPECT_CALL(*this, prepare_v3(_, _, _, _, _, _)).WillOnce(DoAll(SetArgPointee<4>(&st), SetArgPointee<5>(nullptr), Return(SQLITE_OK)));
    EXPECT_CALL(*this, finalize(&st));
    EXPECT_CALL(*this, close_v2(&db));

    connection conn = connect(":memory:", ec);

    EXPECT_FALSE(ec);

    statement stmt = prepare(conn, ec);

    EXPECT_FALSE(ec);
    EXPECT_EQ(stmt.conn_handle(), &db);
    EXPECT_EQ(stmt.stmt_handle(), nullptr);

    bool prepared = stmt.prepare("SELECT 1;", ec);

    EXPECT_FALSE(ec);
    EXPECT_EQ(stmt.stmt_handle(), &st);

    stmt.finalize(ec);

    EXPECT_FALSE(ec);
    EXPECT_EQ(stmt.conn_handle(), &db);
    EXPECT_EQ(stmt.stmt_handle(), nullptr);
}

TEST_F(StatementUnitTest, ConstructEmptyNoException)
{
    try {
        sqlite3 db{1};

        statement stmt = prepare(&db);

        EXPECT_EQ(stmt.conn_handle(), &db);
        EXPECT_EQ(stmt.stmt_handle(), nullptr);
    }
    catch (const std::system_error& ec) {
        FAIL() << ec.what();
    }
}

TEST_F(StatementUnitTest, ConstructSelectNoException)
{
    try {
        sqlite3 db{1};
        sqlite3_stmt st{1};

        InSequence seq;
        EXPECT_CALL(*this, open_v2(_, _, _, _)).WillOnce(DoAll(SetArgPointee<1>(&db), Return(SQLITE_OK)));
        EXPECT_CALL(*this, prepare_v3(_, _, _, _, _, _)).WillOnce(DoAll(SetArgPointee<4>(&st), SetArgPointee<5>(nullptr), Return(SQLITE_OK)));
        EXPECT_CALL(*this, finalize(&st));
        EXPECT_CALL(*this, close_v2(&db));

        connection conn = connect(":memory:");
        statement stmt = prepare(conn, "SELECT 1;");

        EXPECT_EQ(stmt.conn_handle(), &db);
        EXPECT_EQ(stmt.stmt_handle(), &st);
    }
    catch (const std::system_error& ec) {
        FAIL() << ec.what();
    }
}

TEST_F(StatementUnitTest, PrepareSelectNoException)
{
    try {
        sqlite3 db{1};
        sqlite3_stmt st{1};

        InSequence seq;
        EXPECT_CALL(*this, open_v2(_, _, _, _)).WillOnce(DoAll(SetArgPointee<1>(&db), Return(SQLITE_OK)));
        EXPECT_CALL(*this, prepare_v3(_, _, _, _, _, _)).WillOnce(DoAll(SetArgPointee<4>(&st), SetArgPointee<5>(nullptr), Return(SQLITE_OK)));
        EXPECT_CALL(*this, finalize(&st));
        EXPECT_CALL(*this, close_v2(&db));

        connection conn = connect(":memory:");
        statement stmt = prepare(conn);

        EXPECT_EQ(stmt.conn_handle(), &db);
        EXPECT_EQ(stmt.stmt_handle(), nullptr);

        stmt.prepare("SELECT 1;");

        EXPECT_EQ(stmt.stmt_handle(), &st);

        stmt.finalize();

        EXPECT_EQ(stmt.conn_handle(), &db);
        EXPECT_EQ(stmt.stmt_handle(), nullptr);
    }
    catch (const std::system_error& ec) {
        FAIL() << ec.what();
    }
}

TEST_F(StatementUnitTest, MoveConstruct)
{
    sqlite3 db{1};
    sqlite3_stmt st{1};
    std::error_code ec;

    InSequence seq;
    EXPECT_CALL(*this, prepare_v3(_, _, _, _, _, _)).WillOnce(DoAll(SetArgPointee<4>(&st), SetArgPointee<5>(nullptr), Return(SQLITE_OK)));
    EXPECT_CALL(*this, finalize(&st));

    statement stmt1 = prepare(&db, "SELECT 1;", ec);

    EXPECT_FALSE(ec);
    EXPECT_EQ(stmt1.conn_handle(), &db);
    EXPECT_EQ(stmt1.stmt_handle(), &st);

    statement stmt2 = std::move(stmt1);

    EXPECT_FALSE(ec);
    EXPECT_EQ(stmt1.conn_handle(), &db);
    EXPECT_EQ(stmt1.stmt_handle(), nullptr);
    EXPECT_EQ(stmt2.conn_handle(), &db);
    EXPECT_EQ(stmt2.stmt_handle(), &st);

    stmt2.finalize(ec);
    EXPECT_FALSE(ec);
    EXPECT_EQ(stmt2.conn_handle(), &db);
    EXPECT_EQ(stmt2.stmt_handle(), nullptr);
}

TEST_F(StatementUnitTest, MoveAssignment)
{
    sqlite3 db1{1};
    sqlite3 db2{2};
    sqlite3_stmt st1{1};
    sqlite3_stmt st2{2};
    std::error_code ec;

    InSequence seq;
    EXPECT_CALL(*this, prepare_v3(_, _, _, _, _, _)).WillOnce(DoAll(SetArgPointee<4>(&st1), SetArgPointee<5>(nullptr), Return(SQLITE_OK)));
    EXPECT_CALL(*this, prepare_v3(_, _, _, _, _, _)).WillOnce(DoAll(SetArgPointee<4>(&st2), SetArgPointee<5>(nullptr), Return(SQLITE_OK)));
    EXPECT_CALL(*this, finalize(&st2));
    EXPECT_CALL(*this, finalize(&st1));

    statement stmt1{&db1, "SELECT 1;", ec};

    EXPECT_FALSE(ec);
    EXPECT_EQ(stmt1.conn_handle(), &db1);
    EXPECT_EQ(stmt1.stmt_handle(), &st1);

    statement stmt2{&db2, "SELECT 2;", ec};

    EXPECT_FALSE(ec);
    EXPECT_EQ(stmt1.conn_handle(), &db1);
    EXPECT_EQ(stmt1.stmt_handle(), &st1);

    stmt2 = std::move(stmt1);

    EXPECT_FALSE(ec);
    EXPECT_EQ(stmt1.conn_handle(), &db1);
    EXPECT_EQ(stmt1.stmt_handle(), nullptr);
    EXPECT_EQ(stmt2.conn_handle(), &db1);
    EXPECT_EQ(stmt2.stmt_handle(), &st1);

    stmt2.finalize(ec);

    EXPECT_FALSE(ec);
    EXPECT_EQ(stmt1.conn_handle(), &db1);
    EXPECT_EQ(stmt1.stmt_handle(), nullptr);
    EXPECT_EQ(stmt2.conn_handle(), &db1);
    EXPECT_EQ(stmt2.stmt_handle(), nullptr);
}

TEST_F(StatementUnitTest, MoveAssignmentSelf)
{
    sqlite3 db{1};
    sqlite3_stmt st{1};
    std::error_code ec;

    InSequence seq;
    EXPECT_CALL(*this, prepare_v3(_, _, _, _, _, _)).WillOnce(DoAll(SetArgPointee<4>(&st), SetArgPointee<5>(nullptr), Return(SQLITE_OK)));
    EXPECT_CALL(*this, finalize(&st));

    statement stmt{&db, "SELECT 1;", ec};

    EXPECT_FALSE(ec);
    EXPECT_EQ(stmt.conn_handle(), &db);
    EXPECT_EQ(stmt.stmt_handle(), &st);

    stmt = std::move(stmt);

    EXPECT_FALSE(ec);
    EXPECT_EQ(stmt.conn_handle(), &db);
    EXPECT_EQ(stmt.stmt_handle(), &st);
}
