// SPDX-License-Identifier: MIT

#ifndef SQLITEPP_TYPES_HPP
#define SQLITEPP_TYPES_HPP

#include <sqlitepp/detail/sqlite3.hpp>
#include <type_traits>

namespace sqlitepp
{

using conn_handle_t = std::add_pointer_t<sqlite3>;
using stmt_handle_t = std::add_pointer_t<sqlite3_stmt>;

} // namespace sqlitepp

#endif // SQLITEPP_TYPES_HPP
