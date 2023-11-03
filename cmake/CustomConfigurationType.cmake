# SPDX-License-Identifier: MIT

function(add_custom_configuration_type CCT_BUILD_TYPE)
    set(options "")
    set(oneValueArgs BASED_ON POSTFIX)
    set(multiValueArgs C_FLAGS CXX_FLAGS LINKER_FLAGS EXE_LINKER_FLAGS MODULE_LINKER_FLAGS SHARED_LINKER_FLAGS STATIC_LINKER_FLAGS)
    cmake_parse_arguments(CCT "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    get_property(generator_is_multi_config GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
    if(generator_is_multi_config)
        # Using a multi-configuration generator:
        # Add the custom configuration type to CACHE variable CMAKE_CONFIGURATION_TYPE
        if(CMAKE_CONFIGURATION_TYPES)
            if(NOT ${CCT_BUILD_TYPE} IN_LIST CMAKE_CONFIGURATION_TYPES)
                list(APPEND CMAKE_CONFIGURATION_TYPES ${CCT_BUILD_TYPE})
                set_property(CACHE CMAKE_CONFIGURATION_TYPES PROPERTY VALUE ${CMAKE_CONFIGURATION_TYPES})
            endif()
        endif()
    else()
        # Using a single configuration generator:
        # Add the custom build type to CACHE variable CMAKE_BUILD_TYPE-STRINGS:INTERNAL
        get_property(build_types CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS)
        if(build_types)
            if(NOT ${CCT_BUILD_TYPE} IN_LIST build_types)
                set_property(CACHE CMAKE_BUILD_TYPE APPEND PROPERTY STRINGS ${CCT_BUILD_TYPE})
            endif()
        else()
            set(build_types Debug Release ${CCT_BUILD_TYPE})
            set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${build_types})
        endif()
    endif()

    # Set the compiler and linker flags

    string(TOUPPER "${CCT_BUILD_TYPE}" build_type)

    if(DEFINED CCT_BASED_ON)
        string(TOUPPER "${CCT_BASED_ON}" based_on)

        separate_arguments(based_on_c_flags NATIVE_COMMAND "${CMAKE_C_FLAGS_${based_on}}")
        separate_arguments(based_on_cxx_flags NATIVE_COMMAND "${CMAKE_CXX_FLAGS_${based_on}}")
        separate_arguments(based_on_exe_linker_flags NATIVE_COMMAND "${CMAKE_EXE_LINKER_FLAGS_${based_on}}")
        separate_arguments(based_on_module_linker_flags NATIVE_COMMAND "${CMAKE_MODULE_LINKER_FLAGS_${based_on}}")
        separate_arguments(based_on_shared_linker_flags NATIVE_COMMAND "${CMAKE_SHARED_LINKER_FLAGS_${based_on}}")
        separate_arguments(based_on_static_linker_flags NATIVE_COMMAND "${CMAKE_STATIC_LINKER_FLAGS_${based_on}}")
    endif()

    set(CMAKE_${build_type}_POSTFIX ${CCT_POSTFIX} CACHE STRING "" FORCE)
    mark_as_advanced(CMAKE_${build_type}_POSTFIX)

    string(JOIN " " c_flags ${based_on_c_flags} ${CCT_C_FLAGS})
    set(CMAKE_C_FLAGS_${build_type} ${c_flags} CACHE STRING "Flags used by the C compiler during ${build_type} builds." FORCE)
    mark_as_advanced(CMAKE_C_FLAGS_${build_type})

    string(JOIN " " cxx_flags ${based_on_cxx_flags} ${CCT_CXX_FLAGS})
    set(CMAKE_CXX_FLAGS_${build_type} ${cxx_flags} CACHE STRING "Flags used by the CXX compiler during ${build_type} builds." FORCE)
    mark_as_advanced(CMAKE_CXX_FLAGS_${build_type})

    string(JOIN " " exe_linker_flags ${based_on_exe_linker_flags} ${CCT_LINKER_FLAGS} ${CCT_EXE_LINKER_FLAGS})
    set(CMAKE_EXE_LINKER_FLAGS_${build_type} ${exe_linker_flags} CACHE STRING "Flags used by the linker during ${build_type} builds." FORCE)
    mark_as_advanced(CMAKE_EXE_LINKER_FLAGS_${build_type})

    string(JOIN " " module_linker_flags ${based_on_module_linker_flags} ${CCT_LINKER_FLAGS} ${CCT_MODULE_LINKER_FLAGS})
    set(CMAKE_MODULE_LINKER_FLAGS_${build_type} ${module_linker_flags} CACHE STRING "Flags used by the linker during the creation of modules during ${build_type} builds." FORCE)
    mark_as_advanced(CMAKE_MODULE_LINKER_FLAGS_${build_type})

    string(JOIN " " shared_linker_flags ${based_on_shared_linker_flags} ${CCT_LINKER_FLAGS} ${CCT_SHARED_LINKER_FLAGS})
    set(CMAKE_SHARED_LINKER_FLAGS_${build_type} ${shared_linker_flags} CACHE STRING "Flags used by the linker during the creation of shared libraries during ${build_type} builds." FORCE)
    mark_as_advanced(CMAKE_SHARED_LINKER_FLAGS_${build_type})

    string(JOIN " " static_linker_flags ${based_on_static_linker_flags} ${CCT_LINKER_FLAGS} ${CCT_STATIC_LINKER_FLAGS})
    set(CMAKE_STATIC_LINKER_FLAGS_${build_type} ${static_linker_flags} CACHE STRING "Flags used by the linker during the creation of static libraries during ${build_type} builds." FORCE)
    mark_as_advanced(CMAKE_STATIC_LINKER_FLAGS_${build_type})
endfunction()
