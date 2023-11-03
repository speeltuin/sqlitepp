// SPDX-License-Identifier: MIT

#ifndef SQLITEPP_VERSION_HPP
#define SQLITEPP_VERSION_HPP

#define SQLITEPP_VERSION "0.1.0"
#define SQLITEPP_VERSION_MAJOR 0
#define SQLITEPP_VERSION_MINOR 1
#define SQLITEPP_VERSION_PATCH 0

namespace sqlitepp
{

constexpr const char version[] = SQLITEPP_VERSION;
constexpr const int version_major = SQLITEPP_VERSION_MAJOR;
constexpr const int version_minor = SQLITEPP_VERSION_MINOR;
constexpr const int version_patch = SQLITEPP_VERSION_PATCH;

} // namespace sqlitepp

#endif // SQLITEPP_VERSION_HPP
