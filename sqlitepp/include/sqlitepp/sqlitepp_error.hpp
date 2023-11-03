// SPDX-License-Identifier: MIT

#ifndef SQLITEPP_SQLITEPP_ERROR_HPP
#define SQLITEPP_SQLITEPP_ERROR_HPP

#include <sqlitepp/detail/sqlitepp_error_category.hpp>
#include <sqlitepp/sqlitepp_errc.hpp>

#include <system_error>

namespace sqlitepp
{

inline const std::error_category& sqlitepp_category() noexcept
{
    static const detail::sqlitepp_error_category category;
    return category;
}

inline std::error_code make_error_code(sqlitepp_errc e) noexcept
{
    return std::error_code{static_cast<int>(e), sqlitepp_category()};
}

} // namespace sqlitepp

template<>
struct std::is_error_code_enum<sqlitepp::sqlitepp_errc> : std::true_type
{
};

#endif // SQLITEPP_SQLITEPP_ERROR_HPP
