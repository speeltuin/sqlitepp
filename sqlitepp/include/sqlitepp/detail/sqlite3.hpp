// SPDX-License-Identifier: MIT

#ifndef SQLITEPP_DETAIL_SQLITE3_HPP
#define SQLITEPP_DETAIL_SQLITE3_HPP

#if defined(SQLITEPP_INCLUDE_SQLITE3EXT)
#include <sqlite3ext.h>
SQLITE_EXTENSION_INIT3
#else
#include <sqlite3.h>
#endif

#endif // SQLITEPP_DETAIL_SQLITE3_HPP
