// SPDX-License-Identifier: MIT

#ifndef SQLITEPP_DETAIL_CONVERTER_HPP
#define SQLITEPP_DETAIL_CONVERTER_HPP

#include <cstddef>
#include <string>

namespace sqlitepp::detail
{

struct string_converter
{
    static const char* to_czstring(const char* s) noexcept
    {
        return s;
    }

    static const char* to_czstring(const std::string& s) noexcept
    {
        return s.c_str();
    }

    static const char* to_czstring(std::nullptr_t) noexcept
    {
        return nullptr;
    }
};

} // namespace sqlitepp::detail

#endif // SQLITEPP_DETAIL_CONVERTER_HPP
