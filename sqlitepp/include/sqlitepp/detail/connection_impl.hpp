// SPDX-License-Identifier: MIT

#ifndef SQLITEPP_DETAIL_CONNECTION_IMPL_HPP
#define SQLITEPP_DETAIL_CONNECTION_IMPL_HPP

#include <sqlitepp/detail/sqlite3.hpp>
#include <sqlitepp/sqlite3_error.hpp>
#include <sqlitepp/types.hpp>

#include <filesystem>
#include <type_traits>

namespace sqlitepp::detail
{

template<typename Connection>
class connection_impl
{
public:
    class filename_adapter
    {
    public:
        filename_adapter() = delete;

        filename_adapter(const char* filename) noexcept : filename_(filename)
        {
        }

        filename_adapter(const std::string& filename) noexcept : filename_(filename.c_str())
        {
        }

        template<typename CharT = char, std::enable_if_t<std::is_same_v<std::filesystem::path::value_type, CharT>, bool> = true>
        filename_adapter(const std::filesystem::path& filename) noexcept : filename_(filename.c_str())
        {
        }

        filename_adapter(std::nullptr_t) = delete;

        operator const char*() const noexcept
        {
            return filename_;
        }

    private:
        const char* filename_;
    };

    class flags_adapter
    {
    public:
        flags_adapter() = delete;

        flags_adapter(int flags) noexcept : flags_(flags)
        {
        }

        flags_adapter(typename Connection::openmode flags) noexcept : flags_(static_cast<int>(flags))
        {
        }

        operator int() const noexcept
        {
            return flags_;
        }

    private:
        int flags_;
    };

    class vfsname_adapter
    {
    public:
        vfsname_adapter() = delete;

        vfsname_adapter(const char* vfsname) noexcept : vfsname_(vfsname)
        {
        }

        vfsname_adapter(const std::string& vfsname) noexcept : vfsname_(vfsname.c_str())
        {
        }

        vfsname_adapter(const std::filesystem::path& vfsname) = delete;

        vfsname_adapter(std::nullptr_t) noexcept : vfsname_(nullptr)
        {
        }

        operator const char*() const noexcept
        {
            return vfsname_;
        }

    private:
        const char* vfsname_;
    };

    connection_impl() = default;

    ~connection_impl() noexcept
    {
        std::error_code ec;
        do_close(ec);
    }

    void impl_construct(filename_adapter filename, std::error_code& ec) noexcept
    {
        do_construct(filename, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, nullptr, ec);
    }

    void impl_construct(filename_adapter filename, flags_adapter flags, std::error_code& ec) noexcept
    {
        do_construct(filename, flags, nullptr, ec);
    }

    void impl_construct(filename_adapter filename, flags_adapter flags, vfsname_adapter vfsname, std::error_code& ec) noexcept
    {
        do_construct(filename, flags, vfsname, ec);
    }

    bool impl_open(filename_adapter filename, std::error_code& ec) noexcept
    {
        return do_open(filename, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, nullptr, ec);
    }

    bool impl_open(filename_adapter filename, flags_adapter flags, std::error_code& ec) noexcept
    {
        return do_open(filename, flags, nullptr, ec);
    }

    bool impl_open(filename_adapter filename, flags_adapter flags, vfsname_adapter vfsname, std::error_code& ec) noexcept
    {
        return do_open(filename, flags, vfsname, ec);
    }

    void impl_close(std::error_code& ec) noexcept
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
