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

class statement : private detail::statement_impl<statement>
{
private:
    using Impl = detail::statement_impl<statement>;

public:
    statement() = delete;
    virtual ~statement() noexcept = default;

    template<typename... Args, std::enable_if_t<std::disjunction_v<std::is_same<Args, std::error_code&>...>, bool> = true>
    explicit statement(Args&&... args) noexcept
    {
        Impl::construct(std::forward<Args>(args)...);
    }

    template<typename... Args, std::enable_if_t<std::negation_v<std::disjunction<std::is_same<Args, std::error_code&>...>>, bool> = true>
    explicit statement(Args&&... args)
    {
        std::error_code ec;
        Impl::construct(std::forward<Args>(args)..., ec);
        throw_on_error(ec);
    }

    statement(const statement&) = delete;
    statement& operator=(const statement&) = delete;

    statement(statement&& other) noexcept
    {
        std::swap<Impl>(*this, other);
    }

    statement& operator=(statement&& other)
    {
        if (this != &other) {
            std::error_code ec;
            Impl::finalize(ec);
            throw_on_error(ec);
            std::swap<Impl>(*this, other);
        }
        return *this;
    }

    template<typename... Args, std::enable_if_t<std::disjunction_v<std::is_same<Args, std::error_code&>...>, bool> = true>
    bool prepare(Args&&... args) noexcept
    {
        return Impl::prepare(std::forward<Args>(args)...);
    }

    template<typename... Args, std::enable_if_t<std::negation_v<std::disjunction<std::is_same<Args, std::error_code&>...>>, bool> = true>
    bool prepare(Args&&... args)
    {
        std::error_code ec;
        bool opened = Impl::prepare(std::forward<Args>(args)..., ec);
        throw_on_error(ec);
        return opened;
    }

    void finalize(std::error_code& ec) noexcept
    {
        Impl::finalize(ec);
    }

    void finalize()
    {
        std::error_code ec;
        Impl::finalize(ec);
        throw_on_error(ec);
    }

    conn_handle_t conn_handle() const noexcept
    {
        return Impl::conn_handle();
    }

    stmt_handle_t stmt_handle() const noexcept
    {
        return Impl::stmt_handle();
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
statement prepare(Args&&... args) noexcept(noexcept(statement{std::forward<Args>(args)...}))
{
    return statement{std::forward<Args>(args)...};
}

} // namespace sqlitepp

#endif // SQLITEPP_STATEMENT_HPP
