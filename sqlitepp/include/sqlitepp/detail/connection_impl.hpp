// SPDX-License-Identifier: MIT

#ifndef SQLITEPP_DETAIL_CONNECTION_IMPL_HPP
#define SQLITEPP_DETAIL_CONNECTION_IMPL_HPP

#include <sqlitepp/detail/converter.hpp>
#include <sqlitepp/detail/sqlite3.hpp>
#include <sqlitepp/sqlite3_error.hpp>
#include <sqlitepp/types.hpp>

#include <type_traits>

namespace sqlitepp::detail
{

class connection_impl : private string_converter
{
public:
    connection_impl() = default;

    ~connection_impl() noexcept
    {
        std::error_code ec;
        do_close(ec);
    }

    template<typename String,
             std::enable_if_t<std::conjunction_v<std::is_convertible<String, std::string>, std::negation<std::is_same<String, std::nullptr_t>>>, bool> = true>
    void construct(String filename, std::error_code& ec) noexcept
    {
        do_construct(to_czstring(filename), SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, nullptr, ec);
    }

    template<typename String, typename Flags,
             std::enable_if_t<std::conjunction_v<std::is_convertible<String, std::string>, std::negation<std::is_same<String, std::nullptr_t>>,
                                                 std::disjunction<std::is_integral<Flags>, std::is_enum<Flags>>>,
                              bool> = true>
    void construct(String filename, Flags flags, std::error_code& ec) noexcept
    {
        do_construct(to_czstring(filename), static_cast<int>(flags), nullptr, ec);
    }

    template<typename String, typename Flags, typename StringOrNull,
             std::enable_if_t<std::conjunction_v<std::is_convertible<String, std::string>, std::negation<std::is_same<String, std::nullptr_t>>,
                                                 std::disjunction<std::is_integral<Flags>, std::is_enum<Flags>>,
                                                 std::disjunction<std::is_convertible<StringOrNull, std::string>, std::is_same<StringOrNull, std::nullptr_t>>>,
                              bool> = true>
    void construct(String filename, Flags flags, StringOrNull vfsname, std::error_code& ec) noexcept
    {
        do_construct(to_czstring(filename), static_cast<int>(flags), to_czstring(vfsname), ec);
    }

    template<typename String,
             std::enable_if_t<std::conjunction_v<std::is_convertible<String, std::string>, std::negation<std::is_same<String, std::nullptr_t>>>, bool> = true>
    bool open(String filename, std::error_code& ec) noexcept
    {
        return do_open(to_czstring(filename), SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, nullptr, ec);
    }

    template<typename String, typename Flags,
             std::enable_if_t<std::conjunction_v<std::is_convertible<String, std::string>, std::negation<std::is_same<String, std::nullptr_t>>,
                                                 std::disjunction<std::is_integral<Flags>, std::is_enum<Flags>>>,
                              bool> = true>
    bool open(String filename, Flags flags, std::error_code& ec) noexcept
    {
        return do_open(to_czstring(filename), static_cast<int>(flags), nullptr, ec);
    }

    template<typename String, typename Flags, typename StringOrNull,
             std::enable_if_t<std::conjunction_v<std::is_convertible<String, std::string>, std::negation<std::is_same<String, std::nullptr_t>>,
                                                 std::disjunction<std::is_integral<Flags>, std::is_enum<Flags>>,
                                                 std::disjunction<std::is_convertible<StringOrNull, std::string>, std::is_same<StringOrNull, std::nullptr_t>>>,
                              bool> = true>
    bool open(String filename, Flags flags, StringOrNull vfsname, std::error_code& ec) noexcept
    {
        return do_open(to_czstring(filename), static_cast<int>(flags), to_czstring(vfsname), ec);
    }

    void close(std::error_code& ec) noexcept
    {
        do_close(ec);
    }

    bool is_open() const noexcept
    {
        return is_open_;
    }

    conn_handle_t conn_handle() const noexcept
    {
        return conn_handle_;
    }

private:
    conn_handle_t conn_handle_{nullptr};
    bool is_open_{false};

    void do_construct(const char* filename, int flags, const char* vfsname, std::error_code& ec) noexcept
    {
        flags |= SQLITE_OPEN_EXRESCODE;
        int rc = sqlite3_open_v2(filename, &conn_handle_, flags, vfsname);
        if (rc != SQLITE_OK) {
            ec.assign(rc, sqlite3_category());
        }
        else {
            ec.clear();
            is_open_ = true;
        }
    }

    bool do_open(const char* filename, int flags, const char* vfsname, std::error_code& ec) noexcept
    {
        if (is_open_) {
            ec.clear();
            return false;
        }
        do_close(ec);
        // ignore the error code
        do_construct(filename, flags, vfsname, ec);
        return is_open_;
    }

    void do_close(std::error_code& ec) noexcept
    {
        ec.clear();
        if (conn_handle_ != nullptr) {
            int rc = sqlite3_close_v2(conn_handle_);
            if (rc != SQLITE_OK) {
                ec.assign(rc, sqlite3_category());
            }
            else {
                conn_handle_ = nullptr;
                is_open_ = false;
            }
        }
    }
};

} // namespace sqlitepp::detail

#endif // SQLITEPP_DETAIL_CONNECTION_IMPL_HPP
