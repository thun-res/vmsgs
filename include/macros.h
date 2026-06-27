/*
 * Copyright (c) 2026 VMsgs Contributors.
 * SPDX-License-Identifier: MIT
 *
 * Author: Thun Lu <thun.lu@zohomail.cn>
 */

#pragma once

#include <string>
#include <string_view>

/**
 * @def VMSGS_MACRO(vmsgs_name, vmsgs_url, ...)
 * @brief Declare a constexpr accessor that returns the topic URL.
 *
 * @details
 * Expands to a function definition in the enclosing namespace:
 * - `constexpr std::string_view <name>()` returning the provided URL.
 *
 * This is a lightweight, allocation-free accessor suitable for call sites that
 * accept `std::string_view`.
 *
 * The variadic parameter list (`...`) allows optional extra arguments for
 * backward compatibility and/or future extensions; any additional arguments are
 * ignored by this macro.
 *
 * @param vmsgs_name C++ identifier used as the accessor name.
 * @param vmsgs_url  Topic URL string literal (e.g. "dds://...").
 * @param ...       Optional extra arguments (currently unused/ignored).
 *
 * @note
 * This macro defines a non-member function. If used in a header that is included
 * by multiple translation units, multiple definitions may occur unless the
 * function is given internal linkage or otherwise arranged to be ODR-safe.
 */
#define VMSGS_MACRO(vmsgs_name, vmsgs_url, ...) \
  constexpr std::string_view vmsgs_name() { return std::string_view{vmsgs_url}; }

/**
 * @def VMSGS_MACRO_STR(vmsgs_name, ...)
 * @brief Declare an out-of-line accessor returning a stable std::string reference.
 *
 * @details
 * Expands to a function declaration in the enclosing namespace:
 * - `const std::string& <name>();`
 *
 * The corresponding definition is expected to be provided by
 * @ref VMSGS_MACRO_IMPL in exactly one translation unit.
 *
 * The variadic parameter list (`...`) allows optional extra arguments for
 * backward compatibility and/or future extensions; any additional arguments are
 * ignored by this macro.
 *
 * @param vmsgs_name C++ identifier used as the accessor name.
 * @param ...       Optional extra arguments (currently unused/ignored).
 */
#define VMSGS_MACRO_STR(vmsgs_name, ...) const std::string& vmsgs_name();

/**
 * @def VMSGS_MACRO_IMPL(vmsgs_name, vmsgs_url, ...)
 * @brief Define the out-of-line accessor declared by @ref VMSGS_MACRO_STR.
 *
 * @details
 * Expands to a function definition in the enclosing namespace:
 * - `const std::string& <name>()`
 *
 * The returned reference is bound to a function-local static `std::string`
 * initialized from `vmsgs_url`. The reference remains valid for the lifetime of
 * the program.
 *
 * The variadic parameter list (`...`) allows optional extra arguments for
 * backward compatibility and/or future extensions; any additional arguments are
 * ignored by this macro.
 *
 * @param vmsgs_name C++ identifier used as the accessor name.
 * @param vmsgs_url  Topic URL string literal (e.g. "dds://...").
 * @param ...       Optional extra arguments (currently unused/ignored).
 *
 * @warning
 * Place the expansion of this macro in exactly one translation unit to avoid
 * multiple-definition linker errors.
 */
#define VMSGS_MACRO_IMPL(vmsgs_name, vmsgs_url, ...) \
  const std::string& vmsgs_name() {                 \
    static std::string target_url{vmsgs_url};       \
    return target_url;                             \
  }
