// SPDX-License-Identifier: MIT

#ifndef SQLITEPP_DETAIL_SQLITEPP_ERROR_CATEGORY_HPP
#define SQLITEPP_DETAIL_SQLITEPP_ERROR_CATEGORY_HPP

#include <sqlitepp/sqlitepp_errc.hpp>

#include <string>
#include <system_error>

namespace sqlitepp::detail
{

class sqlitepp_error_category : public std::error_category
{
public:
    const char* name() const noexcept override
    {
        return "sqlitepp";
    }

    std::string message(int code) const override
    {
        switch (static_cast<sqlitepp_errc>(code)) {
        case sqlitepp_errc::invalid_handle:
            return "Invalid handle";
        case sqlitepp_errc::invalid_argument:
            return "Invalid argument";
        }
        return "Unknown error";
    }
};

} // namespace sqlitepp::detail

#endif // SQLITEPP_DETAIL_SQLITEPP_ERROR_CATEGORY_HPP
