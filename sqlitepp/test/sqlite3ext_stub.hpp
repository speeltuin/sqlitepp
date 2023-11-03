// SPDX-License-Identifier: MIT

#ifndef SQLITE3EXT_STUB_HPP
#define SQLITE3EXT_STUB_HPP

#include <sqlitepp/detail/sqlite3.hpp>

#include <gtest/gtest.h>

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic error "-Wmissing-field-initializers"
#endif

class sqlite3ext_ignore
{
public:
    template<typename T>
    static auto handle(const char*) noexcept
    {
        return T();
    }
};

class sqlite3ext_fail
{
public:
    template<typename T>
    static auto handle(const char* name) noexcept
    {
        ADD_FAILURE() << "Unexpected call to function sqlite3_" << name;
        return T();
    }
};

template<typename StubPolicy = sqlite3ext_ignore>
class sqlite3ext_stub
{
public:
    static constexpr const sqlite3_api_routines& get() noexcept
    {
        return stub_;
    }

private:
#define STUB_FUNC(name, params, ret) \
    static ret stub_##name params noexcept \
    { \
        return StubPolicy::template handle<ret>(#name); \
    }

    STUB_FUNC(aggregate_context, (sqlite3_context*, int), void*)
    STUB_FUNC(aggregate_count, (sqlite3_context*), int)
    STUB_FUNC(bind_blob, (sqlite3_stmt*, int, const void*, int, void (*)(void*)), int)
    STUB_FUNC(bind_double, (sqlite3_stmt*, int, double), int)
    STUB_FUNC(bind_int, (sqlite3_stmt*, int, int), int)
    STUB_FUNC(bind_int64, (sqlite3_stmt*, int, sqlite_int64), int)
    STUB_FUNC(bind_null, (sqlite3_stmt*, int), int)
    STUB_FUNC(bind_parameter_count, (sqlite3_stmt*), int)
    STUB_FUNC(bind_parameter_index, (sqlite3_stmt*, const char*), int)
    STUB_FUNC(bind_parameter_name, (sqlite3_stmt*, int), const char*)
    STUB_FUNC(bind_text, (sqlite3_stmt*, int, const char*, int, void (*)(void*)), int)
    STUB_FUNC(bind_text16, (sqlite3_stmt*, int, const void*, int, void (*)(void*)), int)
    STUB_FUNC(bind_value, (sqlite3_stmt*, int, const sqlite3_value*), int)
    STUB_FUNC(busy_handler, (sqlite3*, int (*)(void*, int), void*), int)
    STUB_FUNC(busy_timeout, (sqlite3*, int), int)
    STUB_FUNC(changes, (sqlite3*), int)
    STUB_FUNC(close, (sqlite3*), int)
    STUB_FUNC(collation_needed, (sqlite3*, void*, void (*)(void*, sqlite3*, int, const char*)), int)
    STUB_FUNC(collation_needed16, (sqlite3*, void*, void (*)(void*, sqlite3*, int, const void*)), int)
    STUB_FUNC(column_blob, (sqlite3_stmt*, int), const void*)
    STUB_FUNC(column_bytes, (sqlite3_stmt*, int), int)
    STUB_FUNC(column_bytes16, (sqlite3_stmt*, int), int)
    STUB_FUNC(column_count, (sqlite3_stmt*), int)
    STUB_FUNC(column_database_name, (sqlite3_stmt*, int), const char*)
    STUB_FUNC(column_database_name16, (sqlite3_stmt*, int), const void*)
    STUB_FUNC(column_decltype, (sqlite3_stmt*, int), const char*)
    STUB_FUNC(column_decltype16, (sqlite3_stmt*, int), const void*)
    STUB_FUNC(column_double, (sqlite3_stmt*, int), double)
    STUB_FUNC(column_int, (sqlite3_stmt*, int), int)
    STUB_FUNC(column_int64, (sqlite3_stmt*, int), sqlite_int64)
    STUB_FUNC(column_name, (sqlite3_stmt*, int), const char*)
    STUB_FUNC(column_name16, (sqlite3_stmt*, int), const void*)
    STUB_FUNC(column_origin_name, (sqlite3_stmt*, int), const char*)
    STUB_FUNC(column_origin_name16, (sqlite3_stmt*, int), const void*)
    STUB_FUNC(column_table_name, (sqlite3_stmt*, int), const char*)
    STUB_FUNC(column_table_name16, (sqlite3_stmt*, int), const void*)
    STUB_FUNC(column_text, (sqlite3_stmt*, int), const unsigned char*)
    STUB_FUNC(column_text16, (sqlite3_stmt*, int), const void*)
    STUB_FUNC(column_type, (sqlite3_stmt*, int), int)
    STUB_FUNC(column_value, (sqlite3_stmt*, int), sqlite3_value*)
    STUB_FUNC(commit_hook, (sqlite3*, int (*)(void*), void*), void*)
    STUB_FUNC(complete, (const char*), int)
    STUB_FUNC(complete16, (const void*), int)
    STUB_FUNC(create_collation, (sqlite3*, const char*, int, void*, int (*)(void*, int, const void*, int, const void*)), int)
    STUB_FUNC(create_collation16, (sqlite3*, const void*, int, void*, int (*)(void*, int, const void*, int, const void*)), int)
    STUB_FUNC(create_function,
              (sqlite3*, const char*, int, int, void*, void (*)(sqlite3_context*, int, sqlite3_value**), void (*)(sqlite3_context*, int, sqlite3_value**),
               void (*)(sqlite3_context*)),
              int)
    STUB_FUNC(create_function16,
              (sqlite3*, const void*, int, int, void*, void (*)(sqlite3_context*, int, sqlite3_value**), void (*)(sqlite3_context*, int, sqlite3_value**),
               void (*)(sqlite3_context*)),
              int)
    STUB_FUNC(create_module, (sqlite3*, const char*, const sqlite3_module*, void*), int)
    STUB_FUNC(data_count, (sqlite3_stmt*), int)
    STUB_FUNC(db_handle, (sqlite3_stmt*), sqlite3*)
    STUB_FUNC(declare_vtab, (sqlite3*, const char*), int)
    STUB_FUNC(enable_shared_cache, (int), int)
    STUB_FUNC(errcode, (sqlite3*), int)
    STUB_FUNC(errmsg, (sqlite3*), const char*)
    STUB_FUNC(errmsg16, (sqlite3*), const void*)
    STUB_FUNC(exec, (sqlite3*, const char*, sqlite3_callback, void*, char**), int)
    STUB_FUNC(expired, (sqlite3_stmt*), int)
    STUB_FUNC(finalize, (sqlite3_stmt*), int)
    STUB_FUNC(free, (void*), void)
    STUB_FUNC(free_table, (char**), void)
    STUB_FUNC(get_autocommit, (sqlite3*), int)
    STUB_FUNC(get_auxdata, (sqlite3_context*, int), void*)
    STUB_FUNC(get_table, (sqlite3*, const char*, char***, int*, int*, char**), int)
    STUB_FUNC(global_recover, (void), int)
    STUB_FUNC(interruptx, (sqlite3*), void)
    STUB_FUNC(last_insert_rowid, (sqlite3*), sqlite_int64)
    STUB_FUNC(libversion, (void), const char*)
    STUB_FUNC(libversion_number, (void), int)
    STUB_FUNC(malloc, (int), void*)
    STUB_FUNC(mprintf, (const char*, ...), char*)
    STUB_FUNC(open, (const char*, sqlite3**), int)
    STUB_FUNC(open16, (const void*, sqlite3**), int)
    STUB_FUNC(prepare, (sqlite3*, const char*, int, sqlite3_stmt**, const char**), int)
    STUB_FUNC(prepare16, (sqlite3*, const void*, int, sqlite3_stmt**, const void**), int)
    STUB_FUNC(profile, (sqlite3*, void (*)(void*, const char*, sqlite_uint64), void*), void*)
    STUB_FUNC(progress_handler, (sqlite3*, int, int (*)(void*), void*), void)
    STUB_FUNC(realloc, (void*, int), void*)
    STUB_FUNC(reset, (sqlite3_stmt*), int)
    STUB_FUNC(result_blob, (sqlite3_context*, const void*, int, void (*)(void*)), void)
    STUB_FUNC(result_double, (sqlite3_context*, double), void)
    STUB_FUNC(result_error, (sqlite3_context*, const char*, int), void)
    STUB_FUNC(result_error16, (sqlite3_context*, const void*, int), void)
    STUB_FUNC(result_int, (sqlite3_context*, int), void)
    STUB_FUNC(result_int64, (sqlite3_context*, sqlite_int64), void)
    STUB_FUNC(result_null, (sqlite3_context*), void)
    STUB_FUNC(result_text, (sqlite3_context*, const char*, int, void (*)(void*)), void)
    STUB_FUNC(result_text16, (sqlite3_context*, const void*, int, void (*)(void*)), void)
    STUB_FUNC(result_text16be, (sqlite3_context*, const void*, int, void (*)(void*)), void)
    STUB_FUNC(result_text16le, (sqlite3_context*, const void*, int, void (*)(void*)), void)
    STUB_FUNC(result_value, (sqlite3_context*, sqlite3_value*), void)
    STUB_FUNC(rollback_hook, (sqlite3*, void (*)(void*), void*), void*)
    STUB_FUNC(set_authorizer, (sqlite3*, int (*)(void*, int, const char*, const char*, const char*, const char*), void*), int)
    STUB_FUNC(set_auxdata, (sqlite3_context*, int, void*, void (*)(void*)), void)
    STUB_FUNC(xsnprintf, (int, char*, const char*, ...), char*)
    STUB_FUNC(step, (sqlite3_stmt*), int)
    STUB_FUNC(table_column_metadata, (sqlite3*, const char*, const char*, const char*, char const**, char const**, int*, int*, int*), int)
    STUB_FUNC(thread_cleanup, (void), void)
    STUB_FUNC(total_changes, (sqlite3*), int)
    STUB_FUNC(trace, (sqlite3*, void (*)(void*, const char*), void*), void*)
    STUB_FUNC(transfer_bindings, (sqlite3_stmt*, sqlite3_stmt*), int)
    STUB_FUNC(update_hook, (sqlite3*, void (*)(void*, int, char const*, char const*, sqlite_int64), void*), void*)
    STUB_FUNC(user_data, (sqlite3_context*), void*)
    STUB_FUNC(value_blob, (sqlite3_value*), const void*)
    STUB_FUNC(value_bytes, (sqlite3_value*), int)
    STUB_FUNC(value_bytes16, (sqlite3_value*), int)
    STUB_FUNC(value_double, (sqlite3_value*), double)
    STUB_FUNC(value_int, (sqlite3_value*), int)
    STUB_FUNC(value_int64, (sqlite3_value*), sqlite_int64)
    STUB_FUNC(value_numeric_type, (sqlite3_value*), int)
    STUB_FUNC(value_text, (sqlite3_value*), const unsigned char*)
    STUB_FUNC(value_text16, (sqlite3_value*), const void*)
    STUB_FUNC(value_text16be, (sqlite3_value*), const void*)
    STUB_FUNC(value_text16le, (sqlite3_value*), const void*)
    STUB_FUNC(value_type, (sqlite3_value*), int)
    STUB_FUNC(vmprintf, (const char*, va_list), char*)
    STUB_FUNC(overload_function, (sqlite3*, const char*, int), int)
#if SQLITE_VERSION_NUMBER >= 3003013
    STUB_FUNC(prepare_v2, (sqlite3*, const char*, int, sqlite3_stmt**, const char**), int)
    STUB_FUNC(prepare16_v2, (sqlite3*, const void*, int, sqlite3_stmt**, const void**), int)
    STUB_FUNC(clear_bindings, (sqlite3_stmt*), int)
#endif
#if SQLITE_VERSION_NUMBER >= 3004001
    STUB_FUNC(create_module_v2, (sqlite3*, const char*, const sqlite3_module*, void*, void (*)(void*)), int)
#endif
#if SQLITE_VERSION_NUMBER >= 3005000
    STUB_FUNC(bind_zeroblob, (sqlite3_stmt*, int, int), int)
    STUB_FUNC(blob_bytes, (sqlite3_blob*), int)
    STUB_FUNC(blob_close, (sqlite3_blob*), int)
    STUB_FUNC(blob_open, (sqlite3*, const char*, const char*, const char*, sqlite3_int64, int, sqlite3_blob**), int)
    STUB_FUNC(blob_read, (sqlite3_blob*, void*, int, int), int)
    STUB_FUNC(blob_write, (sqlite3_blob*, const void*, int, int), int)
    STUB_FUNC(create_collation_v2, (sqlite3*, const char*, int, void*, int (*)(void*, int, const void*, int, const void*), void (*)(void*)), int)
    STUB_FUNC(file_control, (sqlite3*, const char*, int, void*), int)
    STUB_FUNC(memory_highwater, (int), sqlite3_int64)
    STUB_FUNC(memory_used, (void), sqlite3_int64)
    STUB_FUNC(mutex_alloc, (int), sqlite3_mutex*)
    STUB_FUNC(mutex_enter, (sqlite3_mutex*), void)
    STUB_FUNC(mutex_free, (sqlite3_mutex*), void)
    STUB_FUNC(mutex_leave, (sqlite3_mutex*), void)
    STUB_FUNC(mutex_try, (sqlite3_mutex*), int)
    STUB_FUNC(open_v2, (const char*, sqlite3**, int, const char*), int)
    STUB_FUNC(release_memory, (int), int)
    STUB_FUNC(result_error_nomem, (sqlite3_context*), void)
    STUB_FUNC(result_error_toobig, (sqlite3_context*), void)
    STUB_FUNC(sleep, (int), int)
    STUB_FUNC(soft_heap_limit, (int), void)
    STUB_FUNC(vfs_find, (const char*), sqlite3_vfs*)
    STUB_FUNC(vfs_register, (sqlite3_vfs*, int), int)
    STUB_FUNC(vfs_unregister, (sqlite3_vfs*), int)
    STUB_FUNC(xthreadsafe, (void), int)
    STUB_FUNC(result_zeroblob, (sqlite3_context*, int), void)
    STUB_FUNC(result_error_code, (sqlite3_context*, int), void)
    STUB_FUNC(test_control, (int, ...), int)
    STUB_FUNC(randomness, (int, void*), void)
    STUB_FUNC(context_db_handle, (sqlite3_context*), sqlite3*)
    STUB_FUNC(extended_result_codes, (sqlite3*, int), int)
    STUB_FUNC(limit, (sqlite3*, int, int), int)
    STUB_FUNC(next_stmt, (sqlite3*, sqlite3_stmt*), sqlite3_stmt*)
    STUB_FUNC(sql, (sqlite3_stmt*), const char*)
    STUB_FUNC(status, (int, int*, int*, int), int)
    STUB_FUNC(backup_finish, (sqlite3_backup*), int)
    STUB_FUNC(backup_init, (sqlite3*, const char*, sqlite3*, const char*), sqlite3_backup*)
    STUB_FUNC(backup_pagecount, (sqlite3_backup*), int)
    STUB_FUNC(backup_remaining, (sqlite3_backup*), int)
    STUB_FUNC(backup_step, (sqlite3_backup*, int), int)
    STUB_FUNC(compileoption_get, (int), const char*)
    STUB_FUNC(compileoption_used, (const char*), int)
    STUB_FUNC(create_function_v2,
              (sqlite3*, const char*, int, int, void*, void (*)(sqlite3_context*, int, sqlite3_value**), void (*)(sqlite3_context*, int, sqlite3_value**),
               void (*)(sqlite3_context*), void (*)(void*)),
              int)
    STUB_FUNC(db_config, (sqlite3*, int, ...), int)
    STUB_FUNC(db_mutex, (sqlite3*), sqlite3_mutex*)
    STUB_FUNC(db_status, (sqlite3*, int, int*, int*, int), int)
    STUB_FUNC(extended_errcode, (sqlite3*), int)
    STUB_FUNC(log, (int, const char*, ...), void)
    STUB_FUNC(soft_heap_limit64, (sqlite3_int64), sqlite3_int64)
    STUB_FUNC(sourceid, (void), const char*)
    STUB_FUNC(stmt_status, (sqlite3_stmt*, int, int), int)
    STUB_FUNC(strnicmp, (const char*, const char*, int), int)
    STUB_FUNC(unlock_notify, (sqlite3*, void (*)(void**, int), void*), int)
    STUB_FUNC(wal_autocheckpoint, (sqlite3*, int), int)
    STUB_FUNC(wal_checkpoint, (sqlite3*, const char*), int)
    STUB_FUNC(wal_hook, (sqlite3*, int (*)(void*, sqlite3*, const char*, int), void*), void*)
    STUB_FUNC(blob_reopen, (sqlite3_blob*, sqlite3_int64), int)
    STUB_FUNC(vtab_config, (sqlite3*, int, ...), int)
    STUB_FUNC(vtab_on_conflict, (sqlite3*), int)
#endif
#if SQLITE_VERSION_NUMBER >= 3007016
    STUB_FUNC(close_v2, (sqlite3*), int)
    STUB_FUNC(db_filename, (sqlite3*, const char*), const char*)
    STUB_FUNC(db_readonly, (sqlite3*, const char*), int)
    STUB_FUNC(db_release_memory, (sqlite3*), int)
    STUB_FUNC(errstr, (int), const char*)
    STUB_FUNC(stmt_busy, (sqlite3_stmt*), int)
    STUB_FUNC(stmt_readonly, (sqlite3_stmt*), int)
    STUB_FUNC(stricmp, (const char*, const char*), int)
    STUB_FUNC(uri_boolean, (const char*, const char*, int), int)
    STUB_FUNC(uri_int64, (const char*, const char*, sqlite3_int64), sqlite3_int64)
    STUB_FUNC(uri_parameter, (const char*, const char*), const char*)
    STUB_FUNC(xvsnprintf, (int, char*, const char*, va_list), char*)
    STUB_FUNC(wal_checkpoint_v2, (sqlite3*, const char*, int, int*, int*), int)
#endif
#if SQLITE_VERSION_NUMBER >= 3008007
    STUB_FUNC(auto_extension, (void (*)(void)), int)
    STUB_FUNC(bind_blob64, (sqlite3_stmt*, int, const void*, sqlite3_uint64, void (*)(void*)), int)
    STUB_FUNC(bind_text64, (sqlite3_stmt*, int, const char*, sqlite3_uint64, void (*)(void*), unsigned char), int)
    STUB_FUNC(cancel_auto_extension, (void (*)(void)), int)
    STUB_FUNC(load_extension, (sqlite3*, const char*, const char*, char**), int)
    STUB_FUNC(malloc64, (sqlite3_uint64), void*)
    STUB_FUNC(msize, (void*), sqlite3_uint64)
    STUB_FUNC(realloc64, (void*, sqlite3_uint64), void*)
    STUB_FUNC(reset_auto_extension, (void), void)
    STUB_FUNC(result_blob64, (sqlite3_context*, const void*, sqlite3_uint64, void (*)(void*)), void)
    STUB_FUNC(result_text64, (sqlite3_context*, const char*, sqlite3_uint64, void (*)(void*), unsigned char), void)
    STUB_FUNC(strglob, (const char*, const char*), int)
#endif
#if SQLITE_VERSION_NUMBER >= 3008011
    STUB_FUNC(value_dup, (const sqlite3_value*), sqlite3_value*)
    STUB_FUNC(value_free, (sqlite3_value*), void)
    STUB_FUNC(result_zeroblob64, (sqlite3_context*, sqlite3_uint64), int)
    STUB_FUNC(bind_zeroblob64, (sqlite3_stmt*, int, sqlite3_uint64), int)
#endif
#if SQLITE_VERSION_NUMBER >= 3009000
    STUB_FUNC(value_subtype, (sqlite3_value*), unsigned int)
    STUB_FUNC(result_subtype, (sqlite3_context*, unsigned int), void)
#endif
#if SQLITE_VERSION_NUMBER >= 3010000
    STUB_FUNC(status64, (int, sqlite3_int64*, sqlite3_int64*, int), int)
    STUB_FUNC(strlike, (const char*, const char*, unsigned int), int)
    STUB_FUNC(db_cacheflush, (sqlite3*), int)
#endif
#if SQLITE_VERSION_NUMBER >= 3012000
    STUB_FUNC(system_errno, (sqlite3*), int)
#endif
#if SQLITE_VERSION_NUMBER >= 3014000
    STUB_FUNC(trace_v2, (sqlite3*, unsigned, int (*)(unsigned, void*, void*, void*), void*), int)
    STUB_FUNC(expanded_sql, (sqlite3_stmt*), char*)
#endif
#if SQLITE_VERSION_NUMBER >= 3018000
    STUB_FUNC(set_last_insert_rowid, (sqlite3*, sqlite3_int64), void)
#endif
#if SQLITE_VERSION_NUMBER >= 3020000
    STUB_FUNC(prepare_v3, (sqlite3*, const char*, int, unsigned int, sqlite3_stmt**, const char**), int)
    STUB_FUNC(prepare16_v3, (sqlite3*, const void*, int, unsigned int, sqlite3_stmt**, const void**), int)
    STUB_FUNC(bind_pointer, (sqlite3_stmt*, int, void*, const char*, void (*)(void*)), int)
    STUB_FUNC(result_pointer, (sqlite3_context*, void*, const char*, void (*)(void*)), void)
    STUB_FUNC(value_pointer, (sqlite3_value*, const char*), void*)
    STUB_FUNC(vtab_nochange, (sqlite3_context*), int)
    STUB_FUNC(value_nochange, (sqlite3_value*), int)
    STUB_FUNC(vtab_collation, (sqlite3_index_info*, int), const char*)
#endif
#if SQLITE_VERSION_NUMBER >= 3024000
    STUB_FUNC(keyword_count, (void), int)
    STUB_FUNC(keyword_name, (int, const char**, int*), int)
    STUB_FUNC(keyword_check, (const char*, int), int)
    STUB_FUNC(str_new, (sqlite3*), sqlite3_str*)
    STUB_FUNC(str_finish, (sqlite3_str*), char*)
    STUB_FUNC(str_appendf, (sqlite3_str*, const char*, ...), void)
    STUB_FUNC(str_vappendf, (sqlite3_str*, const char*, va_list), void)
    STUB_FUNC(str_append, (sqlite3_str*, const char*, int), void)
    STUB_FUNC(str_appendall, (sqlite3_str*, const char*), void)
    STUB_FUNC(str_appendchar, (sqlite3_str*, int, char), void)
    STUB_FUNC(str_reset, (sqlite3_str*), void)
    STUB_FUNC(str_errcode, (sqlite3_str*), int)
    STUB_FUNC(str_length, (sqlite3_str*), int)
    STUB_FUNC(str_value, (sqlite3_str*), char*)
#endif
#if SQLITE_VERSION_NUMBER >= 3025000
    STUB_FUNC(create_window_function,
              (sqlite3*, const char*, int, int, void*, void (*)(sqlite3_context*, int, sqlite3_value**), void (*)(sqlite3_context*), void (*)(sqlite3_context*),
               void (*)(sqlite3_context*, int, sqlite3_value**), void (*)(void*)),
              int)
#endif
#if SQLITE_VERSION_NUMBER >= 3026000
    STUB_FUNC(normalized_sql, (sqlite3_stmt*), const char*)
#endif
#if SQLITE_VERSION_NUMBER >= 3028000
    STUB_FUNC(stmt_isexplain, (sqlite3_stmt*), int)
    STUB_FUNC(value_frombind, (sqlite3_value*), int)
#endif
#if SQLITE_VERSION_NUMBER >= 3030000
    STUB_FUNC(drop_modules, (sqlite3*, const char**), int)
#endif
#if SQLITE_VERSION_NUMBER >= 3031000
    STUB_FUNC(hard_heap_limit64, (sqlite3_int64), sqlite3_int64)
    STUB_FUNC(uri_key, (const char*, int), const char*)
    STUB_FUNC(filename_database, (const char*), const char*)
    STUB_FUNC(filename_journal, (const char*), const char*)
    STUB_FUNC(filename_wal, (const char*), const char*)
#endif
#if SQLITE_VERSION_NUMBER >= 3032000
    STUB_FUNC(create_filename, (const char*, const char*, const char*, int, const char**), const char*)
    STUB_FUNC(free_filename, (const char*), void)
    STUB_FUNC(database_file_object, (const char*), sqlite3_file*)
#endif
#if SQLITE_VERSION_NUMBER >= 3034000
    STUB_FUNC(txn_state, (sqlite3*, const char*), int)
#endif
#if SQLITE_VERSION_NUMBER >= 3036001
    STUB_FUNC(changes64, (sqlite3*), sqlite3_int64)
    STUB_FUNC(total_changes64, (sqlite3*), sqlite3_int64)
#endif
#if SQLITE_VERSION_NUMBER >= 3037000
    STUB_FUNC(autovacuum_pages, (sqlite3*, unsigned int (*)(void*, const char*, unsigned int, unsigned int, unsigned int), void*, void (*)(void*)), int)
#endif
#if SQLITE_VERSION_NUMBER >= 3038000
    STUB_FUNC(error_offset, (sqlite3*), int)
    STUB_FUNC(vtab_rhs_value, (sqlite3_index_info*, int, sqlite3_value**), int)
    STUB_FUNC(vtab_distinct, (sqlite3_index_info*), int)
    STUB_FUNC(vtab_in, (sqlite3_index_info*, int, int), int)
    STUB_FUNC(vtab_in_first, (sqlite3_value*, sqlite3_value**), int)
    STUB_FUNC(vtab_in_next, (sqlite3_value*, sqlite3_value**), int)
#endif
#if SQLITE_VERSION_NUMBER >= 3039000
    STUB_FUNC(deserialize, (sqlite3*, const char*, unsigned char*, sqlite3_int64, sqlite3_int64, unsigned), int)
    STUB_FUNC(serialize, (sqlite3*, const char*, sqlite3_int64*, unsigned int), unsigned char*)
    STUB_FUNC(db_name, (sqlite3*, int), const char*)
#endif
#if SQLITE_VERSION_NUMBER >= 3040000
    STUB_FUNC(value_encoding, (sqlite3_value*), int)
#endif
#if SQLITE_VERSION_NUMBER >= 3041000
    STUB_FUNC(is_interrupted, (sqlite3*), int)
#endif
#if SQLITE_VERSION_NUMBER >= 3043000
    STUB_FUNC(stmt_explain, (sqlite3_stmt*, int), int)
#endif

#undef STUB_FUNC

    static constexpr const sqlite3_api_routines stub_ = {
        stub_aggregate_context,
        stub_aggregate_count,
        stub_bind_blob,
        stub_bind_double,
        stub_bind_int,
        stub_bind_int64,
        stub_bind_null,
        stub_bind_parameter_count,
        stub_bind_parameter_index,
        stub_bind_parameter_name,
        stub_bind_text,
        stub_bind_text16,
        stub_bind_value,
        stub_busy_handler,
        stub_busy_timeout,
        stub_changes,
        stub_close,
        stub_collation_needed,
        stub_collation_needed16,
        stub_column_blob,
        stub_column_bytes,
        stub_column_bytes16,
        stub_column_count,
        stub_column_database_name,
        stub_column_database_name16,
        stub_column_decltype,
        stub_column_decltype16,
        stub_column_double,
        stub_column_int,
        stub_column_int64,
        stub_column_name,
        stub_column_name16,
        stub_column_origin_name,
        stub_column_origin_name16,
        stub_column_table_name,
        stub_column_table_name16,
        stub_column_text,
        stub_column_text16,
        stub_column_type,
        stub_column_value,
        stub_commit_hook,
        stub_complete,
        stub_complete16,
        stub_create_collation,
        stub_create_collation16,
        stub_create_function,
        stub_create_function16,
        stub_create_module,
        stub_data_count,
        stub_db_handle,
        stub_declare_vtab,
        stub_enable_shared_cache,
        stub_errcode,
        stub_errmsg,
        stub_errmsg16,
        stub_exec,
        stub_expired,
        stub_finalize,
        stub_free,
        stub_free_table,
        stub_get_autocommit,
        stub_get_auxdata,
        stub_get_table,
        stub_global_recover,
        stub_interruptx,
        stub_last_insert_rowid,
        stub_libversion,
        stub_libversion_number,
        stub_malloc,
        stub_mprintf,
        stub_open,
        stub_open16,
        stub_prepare,
        stub_prepare16,
        stub_profile,
        stub_progress_handler,
        stub_realloc,
        stub_reset,
        stub_result_blob,
        stub_result_double,
        stub_result_error,
        stub_result_error16,
        stub_result_int,
        stub_result_int64,
        stub_result_null,
        stub_result_text,
        stub_result_text16,
        stub_result_text16be,
        stub_result_text16le,
        stub_result_value,
        stub_rollback_hook,
        stub_set_authorizer,
        stub_set_auxdata,
        stub_xsnprintf,
        stub_step,
        stub_table_column_metadata,
        stub_thread_cleanup,
        stub_total_changes,
        stub_trace,
        stub_transfer_bindings,
        stub_update_hook,
        stub_user_data,
        stub_value_blob,
        stub_value_bytes,
        stub_value_bytes16,
        stub_value_double,
        stub_value_int,
        stub_value_int64,
        stub_value_numeric_type,
        stub_value_text,
        stub_value_text16,
        stub_value_text16be,
        stub_value_text16le,
        stub_value_type,
        stub_vmprintf,
        stub_overload_function,
#if SQLITE_VERSION_NUMBER >= 3003013
        stub_prepare_v2,
        stub_prepare16_v2,
        stub_clear_bindings,
#endif
#if SQLITE_VERSION_NUMBER >= 3004001
        stub_create_module_v2,
#endif
#if SQLITE_VERSION_NUMBER >= 3005000
        stub_bind_zeroblob,
        stub_blob_bytes,
        stub_blob_close,
        stub_blob_open,
        stub_blob_read,
        stub_blob_write,
        stub_create_collation_v2,
        stub_file_control,
        stub_memory_highwater,
        stub_memory_used,
        stub_mutex_alloc,
        stub_mutex_enter,
        stub_mutex_free,
        stub_mutex_leave,
        stub_mutex_try,
        stub_open_v2,
        stub_release_memory,
        stub_result_error_nomem,
        stub_result_error_toobig,
        stub_sleep,
        stub_soft_heap_limit,
        stub_vfs_find,
        stub_vfs_register,
        stub_vfs_unregister,
        stub_xthreadsafe,
        stub_result_zeroblob,
        stub_result_error_code,
        stub_test_control,
        stub_randomness,
        stub_context_db_handle,
        stub_extended_result_codes,
        stub_limit,
        stub_next_stmt,
        stub_sql,
        stub_status,
        stub_backup_finish,
        stub_backup_init,
        stub_backup_pagecount,
        stub_backup_remaining,
        stub_backup_step,
        stub_compileoption_get,
        stub_compileoption_used,
        stub_create_function_v2,
        stub_db_config,
        stub_db_mutex,
        stub_db_status,
        stub_extended_errcode,
        stub_log,
        stub_soft_heap_limit64,
        stub_sourceid,
        stub_stmt_status,
        stub_strnicmp,
        stub_unlock_notify,
        stub_wal_autocheckpoint,
        stub_wal_checkpoint,
        stub_wal_hook,
        stub_blob_reopen,
        stub_vtab_config,
        stub_vtab_on_conflict,
#endif
#if SQLITE_VERSION_NUMBER >= 3007016
        stub_close_v2,
        stub_db_filename,
        stub_db_readonly,
        stub_db_release_memory,
        stub_errstr,
        stub_stmt_busy,
        stub_stmt_readonly,
        stub_stricmp,
        stub_uri_boolean,
        stub_uri_int64,
        stub_uri_parameter,
        stub_xvsnprintf,
        stub_wal_checkpoint_v2,
#endif
#if SQLITE_VERSION_NUMBER >= 3008007
        stub_auto_extension,
        stub_bind_blob64,
        stub_bind_text64,
        stub_cancel_auto_extension,
        stub_load_extension,
        stub_malloc64,
        stub_msize,
        stub_realloc64,
        stub_reset_auto_extension,
        stub_result_blob64,
        stub_result_text64,
        stub_strglob,
#endif
#if SQLITE_VERSION_NUMBER >= 3008011
        stub_value_dup,
        stub_value_free,
        stub_result_zeroblob64,
        stub_bind_zeroblob64,
#endif
#if SQLITE_VERSION_NUMBER >= 3009000
        stub_value_subtype,
        stub_result_subtype,
#endif
#if SQLITE_VERSION_NUMBER >= 3010000
        stub_status64,
        stub_strlike,
        stub_db_cacheflush,
#endif
#if SQLITE_VERSION_NUMBER >= 3012000
        stub_system_errno,
#endif
#if SQLITE_VERSION_NUMBER >= 3014000
        stub_trace_v2,
        stub_expanded_sql,
#endif
#if SQLITE_VERSION_NUMBER >= 3018000
        stub_set_last_insert_rowid,
#endif
#if SQLITE_VERSION_NUMBER >= 3020000
        stub_prepare_v3,
        stub_prepare16_v3,
        stub_bind_pointer,
        stub_result_pointer,
        stub_value_pointer,
        stub_vtab_nochange,
        stub_value_nochange,
        stub_vtab_collation,
#endif
#if SQLITE_VERSION_NUMBER >= 3024000
        stub_keyword_count,
        stub_keyword_name,
        stub_keyword_check,
        stub_str_new,
        stub_str_finish,
        stub_str_appendf,
        stub_str_vappendf,
        stub_str_append,
        stub_str_appendall,
        stub_str_appendchar,
        stub_str_reset,
        stub_str_errcode,
        stub_str_length,
        stub_str_value,
#endif
#if SQLITE_VERSION_NUMBER >= 3025000
        stub_create_window_function,
#endif
#if SQLITE_VERSION_NUMBER >= 3026000
        stub_normalized_sql,
#endif
#if SQLITE_VERSION_NUMBER >= 3028000
        stub_stmt_isexplain,
        stub_value_frombind,
#endif
#if SQLITE_VERSION_NUMBER >= 3030000
        stub_drop_modules,
#endif
#if SQLITE_VERSION_NUMBER >= 3031000
        stub_hard_heap_limit64,
        stub_uri_key,
        stub_filename_database,
        stub_filename_journal,
        stub_filename_wal,
#endif
#if SQLITE_VERSION_NUMBER >= 3032000
        stub_create_filename,
        stub_free_filename,
        stub_database_file_object,
#endif
#if SQLITE_VERSION_NUMBER >= 3034000
        stub_txn_state,
#endif
#if SQLITE_VERSION_NUMBER >= 3036001
        stub_changes64,
        stub_total_changes64,
#endif
#if SQLITE_VERSION_NUMBER >= 3037000
        stub_autovacuum_pages,
#endif
#if SQLITE_VERSION_NUMBER >= 3038000
        stub_error_offset,
        stub_vtab_rhs_value,
        stub_vtab_distinct,
        stub_vtab_in,
        stub_vtab_in_first,
        stub_vtab_in_next,
#endif
#if SQLITE_VERSION_NUMBER >= 3039000
        stub_deserialize,
        stub_serialize,
        stub_db_name,
#endif
#if SQLITE_VERSION_NUMBER >= 3040000
        stub_value_encoding,
#endif
#if SQLITE_VERSION_NUMBER >= 3041000
        stub_is_interrupted,
#endif
#if SQLITE_VERSION_NUMBER >= 3043000
        stub_stmt_explain,
#endif
    };
};

using sqlite3ext_nice_stub = sqlite3ext_stub<sqlite3ext_ignore>;
using sqlite3ext_strict_stub = sqlite3ext_stub<sqlite3ext_fail>;

#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

#endif // SQLITE3EXT_STUB_HPP
