// SPDX-License-Identifier: MIT

#ifndef SQLITEPP_CONNECTION_HPP
#define SQLITEPP_CONNECTION_HPP

#include <sqlitepp/detail/connection_impl.hpp>
#include <sqlitepp/detail/sqlite3.hpp>
#include <sqlitepp/types.hpp>

#include <system_error>
#include <type_traits>
#include <utility>

namespace sqlitepp
{

class connection : private detail::connection_impl<connection>
{
private:
    using Impl = detail::connection_impl<connection>;

public:
    enum class openmode : int
    {
        ro = SQLITE_OPEN_READONLY,
        rw = SQLITE_OPEN_READWRITE,
        rwc = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE,
        mem = rwc | SQLITE_OPEN_MEMORY,
        uri = rwc | SQLITE_OPEN_URI
    };

    connection() noexcept = default;
    virtual ~connection() noexcept = default;

    template<typename... Args, std::enable_if_t<std::disjunction_v<std::is_same<Args, std::error_code&>...>, bool> = true>
    explicit connection(Args&&... args) noexcept
    {
        impl_construct(std::forward<Args>(args)...);
    }

    template<typename... Args, std::enable_if_t<std::negation_v<std::disjunction<std::is_same<Args, std::error_code&>...>>, bool> = true>
    explicit connection(Args&&... args)
    {
        std::error_code ec;
        impl_construct(std::forward<Args>(args)..., ec);
        throw_on_error(ec);
    }

    connection(const connection&) = delete;
    connection& operator=(const connection&) = delete;

    connection(connection&& other) noexcept
    {
        std::swap<Impl>(*this, other);
    }

    connection& operator=(connection&& other)
    {
        if (this != &other) {
            std::error_code ec;
            impl_close(ec);
            throw_on_error(ec);
            std::swap<Impl>(*this, other);
        }
        return *this;
    }

    template<typename... Args, std::enable_if_t<std::disjunction_v<std::is_same<Args, std::error_code&>...>, bool> = true>
    bool open(Args&&... args) noexcept
    {
        return impl_open(std::forward<Args>(args)...);
    }

    template<typename... Args, std::enable_if_t<std::negation_v<std::disjunction<std::is_same<Args, std::error_code&>...>>, bool> = true>
    bool open(Args&&... args)
    {
        std::error_code ec;
        bool opened = impl_open(std::forward<Args>(args)..., ec);
        throw_on_error(ec);
        return opened;
    }

    void close(std::error_code& ec) noexcept
    {
        impl_close(ec);
    }

    void close()
    {
        std::error_code ec;
        impl_close(ec);
        throw_on_error(ec);
    }

    bool is_open() const noexcept
    {
        return Impl::is_open();
    }

    conn_handle_t conn_handle() const noexcept
    {
        return Impl::conn_handle();
    }

private:
    static void throw_on_error(const std::error_code& ec)
    {
        if (ec) {
            throw std::system_error(ec);
        }
    }
};

template<typename... Args>
connection connect(Args&&... args) noexcept(noexcept(connection{std::forward<Args>(args)...}))
{
    return connection{std::forward<Args>(args)...};
}

} // namespace sqlitepp

#endif // SQLITEPP_CONNECTION_HPP
