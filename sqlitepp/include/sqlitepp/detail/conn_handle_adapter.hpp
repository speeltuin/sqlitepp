// SPDX-License-Identifier: MIT

#ifndef SQLITEPP_DETAIL_CONN_HANDLE_ADAPTER_HPP
#define SQLITEPP_DETAIL_CONN_HANDLE_ADAPTER_HPP

#include <sqlitepp/connection.hpp>
#include <sqlitepp/types.hpp>

#include <cstddef>

namespace sqlitepp::detail
{

class conn_handle_adapter
{
public:
    conn_handle_adapter() = delete;

    conn_handle_adapter(connection& conn) noexcept : conn_handle_(conn.conn_handle())
    {
    }

    conn_handle_adapter(conn_handle_t conn_handle) noexcept : conn_handle_(conn_handle)
    {
    }

    conn_handle_adapter(std::nullptr_t) = delete;

    conn_handle_t conn_handle() const noexcept
    {
        return conn_handle_;
    }

private:
    conn_handle_t conn_handle_;
};

} // namespace sqlitepp::detail

#endif // SQLITEPP_DETAIL_CONN_HANDLE_ADAPTER_HPP
