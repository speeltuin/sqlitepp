// SPDX-License-Identifier: MIT

#ifndef SQLITEPP_DETAIL_STATEMENT_IMPL_HPP
#define SQLITEPP_DETAIL_STATEMENT_IMPL_HPP

#include <sqlitepp/connection.hpp>
#include <sqlitepp/detail/conn_handle_adapter.hpp>
#include <sqlitepp/detail/sqlite3.hpp>
#include <sqlitepp/types.hpp>

#include <cstdlib>
#include <string>
#include <string_view>

namespace sqlitepp::detail
{

template<typename Statement>
class statement_impl
{
public:
    class text_adapter
    {
    public:
        text_adapter() = delete;

        template<typename CharT = char*>
        text_adapter(const CharT text) noexcept : text_(text), bytes_(-1)
        {
        }

        template<typename CharT = char, int N>
        text_adapter(const CharT (&text)[N]) noexcept : text_(text), bytes_(N)
        {
        }

        text_adapter(const std::string& text) noexcept : text_(text.c_str()), bytes_(text.length() + 1)
        {
        }

        text_adapter(const std::string_view& text) noexcept : text_(text.data()), bytes_(text.size())
        {
        }

        text_adapter(std::nullptr_t) = delete;

        const char* data() const noexcept
        {
            return text_;
        }

        int size() const noexcept
        {
            return bytes_;
        }

    private:
        const char* text_;
        int bytes_;
    };

    statement_impl() = default;

    ~statement_impl() noexcept
    {
        std::error_code ec;
        do_finalize(ec);
    }

    void construct(conn_handle_adapter conn, std::error_code& ec) noexcept
    {
        do_construct(conn, ec);
    }

    void construct(conn_handle_adapter conn, text_adapter sql, std::error_code& ec) noexcept
    {
        do_construct(conn, sql.data(), sql.size(), 0, ec);
    }

    bool prepare(conn_handle_adapter conn, text_adapter sql, std::error_code& ec) noexcept
    {
        return do_prepare(conn, sql.data(), sql.size(), ec);
    }

    bool prepare(text_adapter sql, std::error_code& ec) noexcept
    {
        return do_prepare(conn_handle_, sql.data(), sql.size(), ec);
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

    void do_construct(conn_handle_t conn_handle, std::error_code& ec) noexcept
    {
        ec.clear();
        conn_handle_ = conn_handle;
    }

    void do_construct(conn_handle_t conn_handle, const char* sql, int bytes, unsigned int flags, std::error_code& ec) noexcept
    {
        int rc = sqlite3_prepare_v3(conn_handle, sql, bytes, flags, &stmt_handle_, &tail_);
        if (rc != SQLITE_OK) {
            ec.assign(rc, sqlite3_category());
        }
        else {
            ec.clear();
            conn_handle_ = conn_handle;
        }
    }

    bool do_prepare(conn_handle_t conn_handle, const char* sql, int bytes, std::error_code& ec) noexcept
    {
        if (stmt_handle_ != nullptr) {
            ec.clear();
            return false;
        }
        do_construct(conn_handle, sql, bytes, 0, ec);
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
