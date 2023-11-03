// SPDX-License-Identifier: MIT

#ifndef SQLITEPP_SQLITE3_ERROR_HPP
#define SQLITEPP_SQLITE3_ERROR_HPP

#include <sqlitepp/detail/sqlite3_error_category.hpp>
#include <sqlitepp/sqlite3_errc.hpp>

#include <system_error>

namespace sqlitepp
{

inline const std::error_category& sqlite3_category() noexcept
{
    static const detail::sqlite3_error_category category;
    return category;
}

inline std::error_condition make_error_condition(sqlite3_errc errc) noexcept
{
    return std::error_condition{static_cast<int>(errc), sqlite3_category()};
}

} // namespace sqlitepp

template<>
struct std::is_error_condition_enum<sqlitepp::sqlite3_errc> : std::true_type
{
};

#endif // SQLITEPP_SQLITE3_ERROR_HPP
