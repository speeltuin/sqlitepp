// SPDX-License-Identifier: MIT

#ifndef SQLITEPP_SQLITE3_ERRC_HPP
#define SQLITEPP_SQLITE3_ERRC_HPP

#include <sqlitepp/detail/sqlite3.hpp>

namespace sqlitepp
{

enum class sqlite3_errc
{
    authorization_denied = SQLITE_AUTH,
    constraint_violation = SQLITE_CONSTRAINT,
    data_type_mismatch = SQLITE_MISMATCH,
    database_busy = SQLITE_BUSY,
    database_corrupt = SQLITE_CORRUPT,
    database_open_failed = SQLITE_CANTOPEN,
    database_schema_changed = SQLITE_SCHEMA,
    generic_error = SQLITE_ERROR,
    inappropriate_use = SQLITE_MISUSE,
    internal_malfunction = SQLITE_INTERNAL,
    interrupted = SQLITE_INTERRUPT,
    io_error = SQLITE_IOERR,
    log_notice = SQLITE_NOTICE,
    log_warning = SQLITE_WARNING,
    no_large_file_support = SQLITE_NOLFS,
    no_space_on_device = SQLITE_FULL,
    not_a_database = SQLITE_NOTADB,
    not_enough_memory = SQLITE_NOMEM,
    operation_canceled = SQLITE_ABORT,
    operation_completed = SQLITE_DONE,
    operation_in_progress = SQLITE_LOCKED,
    operation_not_supported = SQLITE_NOTFOUND,
    permission_denied = SQLITE_PERM,
    position_out_of_range = SQLITE_RANGE,
    protocol_error = SQLITE_PROTOCOL,
    read_only_database = SQLITE_READONLY,
    string_or_blob_too_large = SQLITE_TOOBIG
};

} // namespace sqlitepp

#endif // SQLITEPP_SQLITE3_ERRC_HPP
