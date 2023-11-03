// SPDX-License-Identifier: MIT

#include <sqlitepp/connection.hpp>
#include <sqlitepp/sqlite3_error.hpp>

#include <cstdio>
#include <cstring>
#include <filesystem>
#include <gtest/gtest.h>

using namespace sqlitepp;

class ConnectionSystemTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

TEST_F(ConnectionSystemTest, ConstructDatabaseInMemoryFromFileName)
{
    try {
        auto conn = connect(":memory:");

        EXPECT_NE(conn.conn_handle(), nullptr);
        EXPECT_TRUE(conn.is_open());

        auto filename = sqlite3_db_filename(conn.conn_handle(), "main");
        EXPECT_TRUE(filename == nullptr || filename[0] == '\0');

        conn.close();

        EXPECT_EQ(conn.conn_handle(), nullptr);
        EXPECT_FALSE(conn.is_open());
    }
    catch (const std::system_error& ec) {
        FAIL() << ec.what();
    }
}

TEST_F(ConnectionSystemTest, ConstructDatabaseInMemoryFromOpenMode)
{
    try {
        auto conn = connect("sample.db", connection::openmode::mem);

        EXPECT_NE(conn.conn_handle(), nullptr);
        EXPECT_TRUE(conn.is_open());

        auto filename = sqlite3_db_filename(conn.conn_handle(), "main");
        EXPECT_TRUE(filename == nullptr || filename[0] == '\0');

        conn.close();

        EXPECT_EQ(conn.conn_handle(), nullptr);
        EXPECT_FALSE(conn.is_open());
    }
    catch (const std::system_error& ec) {
        FAIL() << ec.what();
    }
}

TEST_F(ConnectionSystemTest, ConstructDatabaseInMemoryFromVfsName)
{
    try {
        auto conn = connect("sample.db", connection::openmode::rwc, "memdb");

        EXPECT_NE(conn.conn_handle(), nullptr);
        EXPECT_TRUE(conn.is_open());

#if SQLITE_VERSION_NUMBER >= 3041000
        // Ubuntu 23.04 provides package libsqlite3-0 which contains a shared
        // library for SQLite3 version 3.40.1 that fails on this expectation.
        // SQLite3 version 3.41.0 fixes private function sqlite3PagerFilename.
        auto filename = sqlite3_db_filename(conn.conn_handle(), "main");
        EXPECT_TRUE(filename == nullptr || filename[0] == '\0');
#endif

        conn.close();

        EXPECT_EQ(conn.conn_handle(), nullptr);
        EXPECT_FALSE(conn.is_open());
    }
    catch (const std::system_error& ec) {
        FAIL() << ec.what();
    }
}

TEST_F(ConnectionSystemTest, ConstructDatabaseInMemoryFromUri)
{
    try {
        auto conn = connect("file:sample.db?mode=memory", connection::openmode::uri);

        EXPECT_NE(conn.conn_handle(), nullptr);
        EXPECT_TRUE(conn.is_open());

        auto filename = sqlite3_db_filename(conn.conn_handle(), "main");
        EXPECT_TRUE(filename == nullptr || filename[0] == '\0');

        conn.close();

        EXPECT_EQ(conn.conn_handle(), nullptr);
        EXPECT_FALSE(conn.is_open());
    }
    catch (const std::system_error& ec) {
        FAIL() << ec.what();
    }
}

TEST_F(ConnectionSystemTest, ConstructSampleDatabase)
{
    try {
        auto conn = connect("sample.db");

        EXPECT_NE(conn.conn_handle(), nullptr);
        EXPECT_TRUE(conn.is_open());

        auto filename = sqlite3_db_filename(conn.conn_handle(), "main");
        ASSERT_FALSE(filename == nullptr || filename[0] == '\0');
        EXPECT_NE(std::strstr(filename, "sample.db"), nullptr);

        conn.close();

        EXPECT_EQ(conn.conn_handle(), nullptr);
        EXPECT_FALSE(conn.is_open());

        auto result = std::remove("sample.db");
        EXPECT_EQ(result, 0);
    }
    catch (const std::system_error& ec) {
        FAIL() << ec.what();
    }
}

#if !defined(_WIN32)
TEST_F(ConnectionSystemTest, ConstructSampleDatabaseByPath)
{
    try {
        auto path = std::filesystem::path{"sample.db"};
        auto conn = connect(path);

        EXPECT_NE(conn.conn_handle(), nullptr);
        EXPECT_TRUE(conn.is_open());

        auto filename = sqlite3_db_filename(conn.conn_handle(), "main");
        ASSERT_FALSE(filename == nullptr || filename[0] == '\0');
        EXPECT_NE(std::strstr(filename, path.c_str()), nullptr);

        conn.close();

        EXPECT_EQ(conn.conn_handle(), nullptr);
        EXPECT_FALSE(conn.is_open());

        auto removed = std::filesystem::remove(path);
        EXPECT_TRUE(removed);
    }
    catch (const std::system_error& ec) {
        FAIL() << ec.what();
    }
}
#endif

TEST_F(ConnectionSystemTest, ExceptionOnReadOnly)
{
    try {
        auto conn = connect("sample.db", connection::openmode::ro);

        FAIL() << "No exception was thrown";
    }
    catch (const std::system_error& ec) {
        EXPECT_EQ(ec.code(), sqlite3_errc::database_open_failed);
    }
}
