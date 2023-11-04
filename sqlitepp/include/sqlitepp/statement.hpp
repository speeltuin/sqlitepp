// SPDX-License-Identifier: MIT

#ifndef SQLITEPP_STATEMENT_HPP
#define SQLITEPP_STATEMENT_HPP

#include <sqlitepp/connection.hpp>
#include <sqlitepp/detail/statement_impl.hpp>
#include <sqlitepp/types.hpp>

#include <type_traits>
#include <utility>

namespace sqlitepp
{

class statement
{
public:
    statement() = delete;
    virtual ~statement() noexcept = default;

    template<typename... Args, std::enable_if_t<std::disjunction_v<std::is_same<Args, std::error_code&>...>, bool> = true>
    explicit statement(Args&&... args) noexcept
    {
        impl_.construct(std::forward<Args>(args)...);
    }

    template<typename... Args, std::enable_if_t<std::negation_v<std::disjunction<std::is_same<Args, std::error_code&>...>>, bool> = true>
    explicit statement(Args&&... args)
    {
        std::error_code ec;
        impl_.construct(std::forward<Args>(args)..., ec);
        throw_on_error(ec);
    }

    statement(const statement&) = delete;
    statement& operator=(const statement&) = delete;

    statement(statement&& other) noexcept
    {
        statement temp{other.impl_.conn_handle()};
        std::swap(impl_, temp.impl_);
        std::swap(impl_, other.impl_);
    }

    statement& operator=(statement&& other)
    {
        if (this != &other) {
            std::error_code ec;
            impl_.finalize(ec);
            throw_on_error(ec);
            statement temp{other.impl_.conn_handle()};
            std::swap(impl_, temp.impl_);
            std::swap(impl_, other.impl_);
        }
        return *this;
    }

    template<typename... Args, std::enable_if_t<std::disjunction_v<std::is_same<Args, std::error_code&>...>, bool> = true>
    bool prepare(Args&&... args) noexcept
    {
        return impl_.prepare(std::forward<Args>(args)...);
    }

    template<typename... Args, std::enable_if_t<std::negation_v<std::disjunction<std::is_same<Args, std::error_code&>...>>, bool> = true>
    bool prepare(Args&&... args)
    {
        std::error_code ec;
        bool opened = impl_.prepare(std::forward<Args>(args)..., ec);
        throw_on_error(ec);
        return opened;
    }

    void finalize(std::error_code& ec) noexcept
    {
        impl_.finalize(ec);
    }

    void finalize()
    {
        std::error_code ec;
        impl_.finalize(ec);
        throw_on_error(ec);
    }

    conn_handle_t conn_handle() const noexcept
    {
        return impl_.conn_handle();
    }

    stmt_handle_t stmt_handle() const noexcept
    {
        return impl_.stmt_handle();
    }

private:
    detail::statement_impl impl_;

    static void throw_on_error(const std::error_code& ec)
    {
        if (ec) {
            throw std::system_error(ec);
        }
    }
};

template<typename... Args>
statement prepare(Args&&... args) noexcept(noexcept(statement{std::forward<Args>(args)...}))
{
    return statement{std::forward<Args>(args)...};
}

} // namespace sqlitepp

#endif // SQLITEPP_STATEMENT_HPP
