// SPDX-License-Identifier: MIT

#ifndef SQLITEPP_DETAIL_STATEMENT_IMPL_HPP
#define SQLITEPP_DETAIL_STATEMENT_IMPL_HPP

#include <sqlitepp/connection.hpp>
#include <sqlitepp/detail/conn_handle_adapter.hpp>
#include <sqlitepp/detail/sqlite3.hpp>
#include <sqlitepp/types.hpp>

namespace sqlitepp::detail
{

class statement_impl
{
public:
    statement_impl() = default;

    ~statement_impl() noexcept
    {
        std::error_code ec;
        do_finalize(ec);
    }

    void construct(conn_handle_adapter conn, std::error_code& ec) noexcept
    {
        conn_handle_ = conn.conn_handle();
        do_construct(ec);
    }

    void construct(conn_handle_adapter conn, const char* sql, std::error_code& ec) noexcept
    {
        conn_handle_ = conn.conn_handle();
        do_construct(sql, -1, 0, ec);
    }

    bool prepare(const char* sql, std::error_code& ec) noexcept
    {
        return do_prepare(sql, ec);
    }

    void finalize(std::error_code& ec) noexcept
    {
        do_finalize(ec);
    }

    conn_handle_t conn_handle() const noexcept
    {
        return conn_handle_;
    }

    stmt_handle_t stmt_handle() const noexcept
    {
        return stmt_handle_;
    }

private:
    conn_handle_t conn_handle_{nullptr};
    stmt_handle_t stmt_handle_{nullptr};
    const char* tail_;

    void do_construct(std::error_code& ec) noexcept
    {
        ec.clear();
    }

    void do_construct(const char* sql, int bytes, unsigned int flags, std::error_code& ec) noexcept
    {
        ec.clear();
        int rc = sqlite3_prepare_v3(conn_handle_, sql, bytes, flags, &stmt_handle_, &tail_);
        if (rc != SQLITE_OK) {
            ec.assign(rc, sqlite3_category());
        }
    }

    bool do_prepare(const char* sql, std::error_code& ec) noexcept
    {
        if (stmt_handle_ != nullptr) {
            ec.clear();
            return false;
        }
        do_construct(sql, -1, 0, ec);
        return (stmt_handle_ != nullptr);
    }

    void do_finalize(std::error_code& ec) noexcept
    {
        ec.clear();
        if (stmt_handle_ != nullptr) {
            (void) sqlite3_finalize(stmt_handle_);
            stmt_handle_ = nullptr;
            tail_ = nullptr;
        }
    }
};

} // namespace sqlitepp::detail

#endif // SQLITEPP_DETAIL_STATEMENT_IMPL_HPP
