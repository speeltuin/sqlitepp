// SPDX-License-Identifier: MIT

#ifndef SQLITEPP_DETAIL_SQLITE3_ERROR_CATEGORY_HPP
#define SQLITEPP_DETAIL_SQLITE3_ERROR_CATEGORY_HPP

#include <sqlitepp/detail/sqlite3.hpp>

#include <string>
#include <system_error>

namespace sqlitepp::detail
{

class sqlite3_error_category : public std::error_category
{
public:
    const char* name() const noexcept override
    {
        return "sqlite3";
    }

    std::string message(int code) const override
    {
        return sqlite3_errstr(code);
    }

    std::error_condition default_error_condition(int code) const noexcept override
    {
        return std::error_condition{code & 0xff, *this};
    }
};

} // namespace sqlitepp::detail

#endif // SQLITEPP_DETAIL_SQLITE3_ERROR_CATEGORY_HPP
