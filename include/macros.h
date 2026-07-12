/*
 * Copyright (c) 2026 VMsgs Contributors.
 * SPDX-License-Identifier: MIT
 *
 * Author: Thun Lu <thun.lu@zohomail.cn>
 */

#pragma once

#include <string>
#include <string_view>

namespace vmsg::interface {

/** Transport selected by the canonical URL scheme. */
enum class TransportKind { kDds, kSharedMemory, kUnknown };

/** Named QoS contract understood by the VLink transport adapter. */
enum class QosProfile {
  kEvent,
  kLatestSensor,
  kLatestState,
  kPersistentState,
  kMethod,
  kCommand,
  kAlarm,
  kLog,
};

/** Compile-time topic metadata shared by every interface declaration. */
struct TopicDescriptor {
  std::string_view url;
  std::string_view schema;
  TransportKind transport;
  QosProfile qos;
};

constexpr bool starts_with(std::string_view value, std::string_view prefix) { return value.size() >= prefix.size() && value.substr(0, prefix.size()) == prefix; }

constexpr TransportKind transport_from_url(std::string_view url) {
  return starts_with(url, "dds://") ? TransportKind::kDds : starts_with(url, "shm://") ? TransportKind::kSharedMemory : TransportKind::kUnknown;
}

constexpr QosProfile qos_from_url(std::string_view url) {
  return url.find("qos=event") != std::string_view::npos     ? QosProfile::kEvent
         : url.find("qos=sensor") != std::string_view::npos  ? QosProfile::kLatestSensor
         : url.find("qos=field") != std::string_view::npos   ? QosProfile::kLatestState
         : url.find("qos=static") != std::string_view::npos  ? QosProfile::kPersistentState
         : url.find("qos=method") != std::string_view::npos  ? QosProfile::kMethod
         : url.find("qos=command") != std::string_view::npos ? QosProfile::kCommand
         : url.find("qos=alarm") != std::string_view::npos   ? QosProfile::kAlarm
         : url.find("qos=log") != std::string_view::npos     ? QosProfile::kLog
                                                             : QosProfile::kEvent;
}

}  // namespace vmsg::interface

/**
 * @def VMSGS_MACRO(vmsgs_name, vmsgs_url, vmsgs_schema)
 * @brief Declare constexpr accessors for a topic URL and schema name.
 *
 * @details
 * Expands to a function definition in the enclosing namespace:
 * - `<name>()` returns the URL for backward compatibility.
 * - `<name>_descriptor()` returns the URL and stringified schema token.
 *
 * This is a lightweight, allocation-free accessor suitable for call sites that
 * accept `std::string_view`.
 *
 * @param vmsgs_name C++ identifier used as the accessor name.
 * @param vmsgs_url  Topic URL string literal (e.g. "dds://...").
 * @param vmsgs_schema Canonical registry key string, for example
 *                     "vmsgs.proto.sensor.Imu".
 */
#define VMSGS_MACRO(vmsgs_name, vmsgs_url, vmsgs_schema)                                                                                                              \
  constexpr std::string_view vmsgs_name() { return std::string_view{vmsgs_url}; }                                                                                     \
  constexpr ::vmsg::interface::TopicDescriptor vmsgs_name##_descriptor() {                                                                                            \
    constexpr std::string_view url{vmsgs_url};                                                                                                                        \
    return ::vmsg::interface::TopicDescriptor{url, std::string_view{vmsgs_schema}, ::vmsg::interface::transport_from_url(url), ::vmsg::interface::qos_from_url(url)}; \
  }

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
  const std::string& vmsgs_name() {                  \
    static std::string target_url{vmsgs_url};        \
    return target_url;                               \
  }
