// SPDX-License-Identifier: MIT

#include "sqlite3ext_stub.hpp"

#include <sqlitepp/connection.hpp>

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

class ConnectionUnitTest : public ::testing::Test
{
public:
    MOCK_METHOD(const char*, errstr, (int), (noexcept));
    MOCK_METHOD(int, open_v2, (const char*, sqlite3**, int, const char*), (noexcept));
    MOCK_METHOD(int, close_v2, (sqlite3*), (noexcept));

protected:
    void SetUp() override
    {
        this_ = this;
        stub_ = sqlite3ext_strict_stub::get();
        stub_.errstr = mock_errstr;
        stub_.open_v2 = mock_open_v2;
        stub_.close_v2 = mock_close_v2;
        SQLITE_EXTENSION_INIT2(&stub_)
    }

    void TearDown() override
    {
        SQLITE_EXTENSION_INIT2(nullptr)
        this_ = nullptr;
    }

private:
    inline static ConnectionUnitTest* this_ = nullptr;
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
};

TEST_F(ConnectionUnitTest, ConstructDefault)
{
    connection conn;

    EXPECT_EQ(conn.conn_handle(), nullptr);
    EXPECT_FALSE(conn.is_open());
}

TEST_F(ConnectionUnitTest, ConstructFileName)
{
    sqlite3 db = {1};

    InSequence seq;
    EXPECT_CALL(*this, open_v2(_, _, _, _)).WillOnce(DoAll(SetArgPointee<1>(&db), Return(SQLITE_OK)));
    EXPECT_CALL(*this, close_v2(&db));

    std::error_code ec;
    connection conn = connect(":memory:", ec);

    EXPECT_FALSE(ec);
    EXPECT_EQ(conn.conn_handle(), &db);
    EXPECT_TRUE(conn.is_open());

    conn.close(ec);

    EXPECT_FALSE(ec);
    EXPECT_EQ(conn.conn_handle(), nullptr);
    EXPECT_FALSE(conn.is_open());
}

TEST_F(ConnectionUnitTest, ConstructFileNameOpenMode)
{
    sqlite3 db = {1};

    InSequence seq;
    EXPECT_CALL(*this, open_v2(_, _, _, _)).WillOnce(DoAll(SetArgPointee<1>(&db), Return(SQLITE_OK)));
    EXPECT_CALL(*this, close_v2(_));

    std::error_code ec;
    connection conn = connect(":memory:", connection::openmode::mem, ec);

    EXPECT_FALSE(ec);
    EXPECT_EQ(conn.conn_handle(), &db);
    EXPECT_TRUE(conn.is_open());
}

TEST_F(ConnectionUnitTest, ConstructFileNameOpenModeVfsName)
{
    sqlite3 db = {1};

    InSequence seq;
    EXPECT_CALL(*this, open_v2(_, _, _, _)).WillOnce(DoAll(SetArgPointee<1>(&db), Return(SQLITE_OK)));
    EXPECT_CALL(*this, close_v2(_));

    std::error_code ec;
    connection conn = connect(std::string(":memory:"), connection::openmode::mem, std::string("memdb"), ec);

    EXPECT_FALSE(ec);
    EXPECT_EQ(conn.conn_handle(), &db);
    EXPECT_TRUE(conn.is_open());
}

TEST_F(ConnectionUnitTest, ConstructFileNameOpenModeNullPtr)
{
    sqlite3 db = {1};

    InSequence seq;
    EXPECT_CALL(*this, open_v2(_, _, _, _)).WillOnce(DoAll(SetArgPointee<1>(&db), Return(SQLITE_OK)));
    EXPECT_CALL(*this, close_v2(_));

    std::error_code ec;
    connection conn = connect(std::string(":memory:"), connection::openmode::mem, nullptr, ec);

    EXPECT_FALSE(ec);
    EXPECT_EQ(conn.conn_handle(), &db);
    EXPECT_TRUE(conn.is_open());
}

TEST_F(ConnectionUnitTest, OpenFileName)
{
    sqlite3 db = {1};

    InSequence seq;
    EXPECT_CALL(*this, open_v2(_, _, _, _)).WillOnce(DoAll(SetArgPointee<1>(&db), Return(SQLITE_OK)));
    EXPECT_CALL(*this, close_v2(&db));

    std::error_code ec;
    connection conn;
    bool opened = conn.open(":memory:", ec);

    EXPECT_FALSE(ec);
    EXPECT_TRUE(opened);
    EXPECT_EQ(conn.conn_handle(), &db);
    EXPECT_TRUE(conn.is_open());

    conn.close(ec);

    EXPECT_FALSE(ec);
    EXPECT_EQ(conn.conn_handle(), nullptr);
    EXPECT_FALSE(conn.is_open());
}

TEST_F(ConnectionUnitTest, OpenFileNameOpenMode)
{
    sqlite3 db = {1};

    InSequence seq;
    EXPECT_CALL(*this, open_v2(_, _, _, _)).WillOnce(DoAll(SetArgPointee<1>(&db), Return(SQLITE_OK)));
    EXPECT_CALL(*this, close_v2(&db));

    std::error_code ec;
    connection conn;
    bool opened = conn.open(":memory:", connection::openmode::mem, ec);

    EXPECT_FALSE(ec);
    EXPECT_TRUE(opened);
    EXPECT_EQ(conn.conn_handle(), &db);
    EXPECT_TRUE(conn.is_open());
}

TEST_F(ConnectionUnitTest, OpenFileNameOpenModeVfsName)
{
    sqlite3 db = {1};

    InSequence seq;
    EXPECT_CALL(*this, open_v2(_, _, _, _)).WillOnce(DoAll(SetArgPointee<1>(&db), Return(SQLITE_OK)));
    EXPECT_CALL(*this, close_v2(&db));

    std::error_code ec;
    connection conn;
    bool opened = conn.open(std::string(":memory:"), connection::openmode::mem, std::string("memdb"), ec);

    EXPECT_FALSE(ec);
    EXPECT_TRUE(opened);
    EXPECT_EQ(conn.conn_handle(), &db);
    EXPECT_TRUE(conn.is_open());
}

TEST_F(ConnectionUnitTest, OpenFileNameOpenModeNullPtr)
{
    sqlite3 db = {1};

    InSequence seq;
    EXPECT_CALL(*this, open_v2(_, _, _, _)).WillOnce(DoAll(SetArgPointee<1>(&db), Return(SQLITE_OK)));
    EXPECT_CALL(*this, close_v2(&db));

    std::error_code ec;
    connection conn;
    bool opened = conn.open(std::string(":memory:"), connection::openmode::mem, nullptr, ec);

    EXPECT_FALSE(ec);
    EXPECT_TRUE(opened);
    EXPECT_EQ(conn.conn_handle(), &db);
    EXPECT_TRUE(conn.is_open());
}

TEST_F(ConnectionUnitTest, MoveConstruct)
{
    sqlite3 db = {1};

    InSequence seq;
    EXPECT_CALL(*this, open_v2(_, _, _, _)).WillOnce(DoAll(SetArgPointee<1>(&db), Return(SQLITE_OK)));
    EXPECT_CALL(*this, close_v2(&db));

    std::error_code ec;
    connection conn = std::move(connect(":memory:", ec));

    EXPECT_FALSE(ec);
    EXPECT_EQ(conn.conn_handle(), &db);
    EXPECT_TRUE(conn.is_open());

    conn.close(ec);

    EXPECT_FALSE(ec);
    EXPECT_EQ(conn.conn_handle(), nullptr);
    EXPECT_FALSE(conn.is_open());
}

TEST_F(ConnectionUnitTest, MoveAssignment)
{
    sqlite3 db = {1};

    InSequence seq;
    EXPECT_CALL(*this, open_v2(_, _, _, _)).WillOnce(DoAll(SetArgPointee<1>(&db), Return(SQLITE_OK)));
    EXPECT_CALL(*this, close_v2(&db));

    std::error_code ec;
    connection conn;
    conn = std::move(connect(":memory:", ec));

    EXPECT_FALSE(ec);
    EXPECT_EQ(conn.conn_handle(), &db);
    EXPECT_TRUE(conn.is_open());

    conn.close(ec);

    EXPECT_FALSE(ec);
    EXPECT_EQ(conn.conn_handle(), nullptr);
    EXPECT_FALSE(conn.is_open());
}

TEST_F(ConnectionUnitTest, MoveAssignmentSelf)
{
    sqlite3 db = {1};

    InSequence seq;
    EXPECT_CALL(*this, open_v2(_, _, _, _)).WillOnce(DoAll(SetArgPointee<1>(&db), Return(SQLITE_OK)));
    EXPECT_CALL(*this, close_v2(&db));

    std::error_code ec;
    connection conn = connect(":memory:", ec);

    EXPECT_EQ(conn.conn_handle(), &db);
    EXPECT_TRUE(conn.is_open());

    conn = std::move(conn);

    EXPECT_EQ(conn.conn_handle(), &db);
    EXPECT_TRUE(conn.is_open());
}

TEST_F(ConnectionUnitTest, OpenAlreadyOpenConnection)
{
    sqlite3 db = {1};

    InSequence seq;
    EXPECT_CALL(*this, open_v2(_, _, _, _)).WillOnce(DoAll(SetArgPointee<1>(&db), Return(SQLITE_OK)));
    EXPECT_CALL(*this, close_v2(&db));

    std::error_code ec;
    connection conn;
    bool opened = conn.open(":memory:", ec);

    EXPECT_FALSE(ec);
    EXPECT_TRUE(opened);
    EXPECT_EQ(conn.conn_handle(), &db);
    EXPECT_TRUE(conn.is_open());

    opened = conn.open(":memory:", ec);

    EXPECT_FALSE(ec);
    EXPECT_FALSE(opened);
    EXPECT_EQ(conn.conn_handle(), &db);
    EXPECT_TRUE(conn.is_open());

    conn.close(ec);

    EXPECT_FALSE(ec);
    EXPECT_EQ(conn.conn_handle(), nullptr);
    EXPECT_FALSE(conn.is_open());
}

TEST_F(ConnectionUnitTest, ErrorOnConstruct)
{
    sqlite3 db = {1};

    InSequence seq;
    EXPECT_CALL(*this, open_v2(_, _, _, _)).WillOnce(DoAll(SetArgPointee<1>(&db), Return(SQLITE_CANTOPEN)));
    EXPECT_CALL(*this, close_v2(&db));

    std::error_code ec;
    connection conn = connect(":memory:", ec);

    EXPECT_EQ(ec, sqlite3_errc::database_open_failed);
    EXPECT_EQ(conn.conn_handle(), &db);
    EXPECT_FALSE(conn.is_open());
}

TEST_F(ConnectionUnitTest, ErrorOnOpen)
{
    sqlite3 db = {1};

    InSequence seq;
    EXPECT_CALL(*this, open_v2(_, _, _, _)).WillOnce(DoAll(SetArgPointee<1>(&db), Return(SQLITE_CANTOPEN)));
    EXPECT_CALL(*this, close_v2(&db));

    std::error_code ec;
    connection conn;
    bool opened = conn.open(":memory:", ec);

    EXPECT_EQ(ec, sqlite3_errc::database_open_failed);
    EXPECT_FALSE(opened);
    EXPECT_EQ(conn.conn_handle(), &db);
    EXPECT_FALSE(conn.is_open());
}

TEST_F(ConnectionUnitTest, ErrorOnClose)
{
    sqlite3 db = {1};

    InSequence seq;
    EXPECT_CALL(*this, open_v2(_, _, _, _)).WillOnce(DoAll(SetArgPointee<1>(&db), Return(SQLITE_OK)));
    EXPECT_CALL(*this, close_v2(&db)).WillOnce(Return(SQLITE_BUSY));
    EXPECT_CALL(*this, close_v2(&db));

    std::error_code ec;
    connection conn;
    bool opened = conn.open(":memory:", ec);

    EXPECT_FALSE(ec);
    EXPECT_TRUE(opened);
    EXPECT_EQ(conn.conn_handle(), &db);
    EXPECT_TRUE(conn.is_open());

    conn.close(ec);
    EXPECT_EQ(ec, sqlite3_errc::database_busy);
    EXPECT_EQ(conn.conn_handle(), &db);
    EXPECT_TRUE(conn.is_open());
}

TEST_F(ConnectionUnitTest, ConstructWithExceptionHandling)
{
    try {
        sqlite3 db = {1};

        InSequence seq;
        EXPECT_CALL(*this, open_v2(_, _, _, _)).WillOnce(DoAll(SetArgPointee<1>(&db), Return(SQLITE_OK)));
        EXPECT_CALL(*this, close_v2(&db));

        connection conn = connect(":memory:");

        EXPECT_EQ(conn.conn_handle(), &db);
        EXPECT_TRUE(conn.is_open());

        conn.close();

        EXPECT_EQ(conn.conn_handle(), nullptr);
        EXPECT_FALSE(conn.is_open());
    }
    catch (const std::system_error& ec) {
        FAIL() << ec.what();
    }
}

TEST_F(ConnectionUnitTest, OpenWithExceptionHandling)
{
    try {
        sqlite3 db = {1};

        InSequence seq;
        EXPECT_CALL(*this, open_v2(_, _, _, _)).WillOnce(DoAll(SetArgPointee<1>(&db), Return(SQLITE_OK)));
        EXPECT_CALL(*this, close_v2(&db));

        connection conn;
        bool opened = conn.open(":memory:");

        EXPECT_TRUE(opened);
        EXPECT_EQ(conn.conn_handle(), &db);
        EXPECT_TRUE(conn.is_open());

        conn.close();

        EXPECT_EQ(conn.conn_handle(), nullptr);
        EXPECT_FALSE(conn.is_open());
    }
    catch (const std::system_error& ec) {
        FAIL() << ec.what();
    }
}

TEST_F(ConnectionUnitTest, ExceptionOnConstruct)
{
    try {
        sqlite3 db = {1};

        InSequence seq;
        EXPECT_CALL(*this, open_v2(_, _, _, _)).WillOnce(DoAll(SetArgPointee<1>(&db), Return(SQLITE_CANTOPEN)));
        EXPECT_CALL(*this, errstr(_)).WillOnce(Return("Cannot open"));
        EXPECT_CALL(*this, close_v2(&db));

        connection conn = connect("sample.db", SQLITE_OPEN_READONLY);

        FAIL() << "No exception was thrown";
    }
    catch (const std::system_error& ec) {
        EXPECT_EQ(ec.code(), sqlite3_errc::database_open_failed);
    }
}

TEST_F(ConnectionUnitTest, ExceptionOnOpen)
{
    try {
        sqlite3 db = {1};

        InSequence seq;
        EXPECT_CALL(*this, open_v2(_, _, _, _)).WillOnce(DoAll(SetArgPointee<1>(&db), Return(SQLITE_CANTOPEN)));
        EXPECT_CALL(*this, errstr(_)).WillOnce(Return("Cannot open"));
        EXPECT_CALL(*this, close_v2(&db));

        connection conn;
        bool opened = conn.open("sample.db", SQLITE_OPEN_READONLY);

        FAIL() << "No exception was thrown";
    }
    catch (const std::system_error& ec) {
        EXPECT_EQ(ec.code(), sqlite3_errc::database_open_failed);
    }
}

TEST_F(ConnectionUnitTest, ExceptionOnClose)
{
    try {
        sqlite3 db = {1};

        InSequence seq;
        EXPECT_CALL(*this, open_v2(_, _, _, _)).WillOnce(DoAll(SetArgPointee<1>(&db), Return(SQLITE_OK)));
        EXPECT_CALL(*this, close_v2(&db)).WillOnce(Return(SQLITE_BUSY));
        EXPECT_CALL(*this, errstr(_)).WillOnce(Return("Busy"));
        EXPECT_CALL(*this, close_v2(&db));

        connection conn = connect("sample.db", SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);
        conn.close();

        FAIL() << "No exception was thrown";
    }
    catch (const std::system_error& ec) {
        EXPECT_EQ(ec.code(), sqlite3_errc::database_busy);
    }
}

TEST_F(ConnectionUnitTest, ExceptionOnMoveAssignment)
{
    try {
        sqlite3 db1 = {1};
        sqlite3 db2 = {2};

        InSequence seq;
        EXPECT_CALL(*this, open_v2(_, _, _, _)).WillOnce(DoAll(SetArgPointee<1>(&db1), Return(SQLITE_OK)));
        EXPECT_CALL(*this, open_v2(_, _, _, _)).WillOnce(DoAll(SetArgPointee<1>(&db2), Return(SQLITE_OK)));
        EXPECT_CALL(*this, close_v2(&db1)).WillOnce(Return(SQLITE_BUSY));
        EXPECT_CALL(*this, errstr(_)).WillOnce(Return("Busy"));
        EXPECT_CALL(*this, close_v2(&db2));
        EXPECT_CALL(*this, close_v2(&db1));

        connection conn = connect(":memory:");
        conn = std::move(connect(":memory:"));

        FAIL() << "No exception was thrown";
    }
    catch (const std::system_error& ec) {
        EXPECT_EQ(ec.code(), sqlite3_errc::database_busy);
    }
}
