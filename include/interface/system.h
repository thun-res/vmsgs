/*
 * Copyright (C) 2026 by Thun Lu. All rights reserved.
 * Author: Thun Lu <thun.lu@zohomail.cn>
 */

#pragma once

#include "../macros.h"

namespace vmsg::interface::system {

// =========================================================================
//  Top-level state machines — must-deliver
// =========================================================================
VMSGS_MACRO(system_state, "dds://system/state", AutowareStateStamped)
VMSGS_MACRO(emergency_state, "dds://system/emergency_state", EmergencyStateStamped)

// =========================================================================
//  Minimum-Risk-Maneuver — safety-critical, must-deliver
// =========================================================================
VMSGS_MACRO(mrm_state, "dds://system/mrm/state", MrmState)
VMSGS_MACRO(mrm_behavior_status, "dds://system/mrm/behavior_status", MrmBehaviorStatus)
VMSGS_MACRO(mrm_request_list, "dds://system/mrm/request_list", MrmRequestList)

// =========================================================================
//  Hazard / diagnostics
// =========================================================================
// hazard_status streams at high rate: drop-OK, latest wins.
VMSGS_MACRO(hazard_status, "dds://system/hazard_status?qos=sensor", HazardStatusStamped)
VMSGS_MACRO(diagnostics, "dds://system/diagnostics?qos=sensor", DiagnosticArray)
// diag_graph_struct is published once at startup → must-deliver.
VMSGS_MACRO(diag_graph_struct, "dds://system/diag_graph/struct", DiagGraphStruct)
VMSGS_MACRO(diag_graph_status, "dds://system/diag_graph/status?qos=sensor", DiagGraphStatus)

// =========================================================================
//  Liveness / observability — periodic streams (drop-OK)
// =========================================================================
VMSGS_MACRO(log, "dds://system/log?qos=sensor", Log)
VMSGS_MACRO(heartbeat, "dds://system/heartbeat?qos=sensor", Heartbeat)
VMSGS_MACRO(process_info, "dds://system/process_info?qos=sensor", ProcessInfoArray)
VMSGS_MACRO(published_time, "dds://system/published_time?qos=sensor", PublishedTime)

// service_log records each RPC's lifecycle — must-deliver for audit trace.
VMSGS_MACRO(service_log, "dds://system/service_log", ServiceLog)

// =========================================================================
//  Command-source switching / availability — must-deliver
// =========================================================================
VMSGS_MACRO(command_mode_availability, "dds://system/command_mode/availability", CommandModeAvailability)
VMSGS_MACRO(command_mode_status, "dds://system/command_mode/status", CommandModeStatus)
VMSGS_MACRO(command_mode_request, "dds://system/command_mode/request", CommandModeRequest)
VMSGS_MACRO(command_source_status, "dds://system/command_source_status", CommandSourceStatus)
VMSGS_MACRO(operation_mode_availability, "dds://system/operation_mode_availability", OperationModeAvailability)

// =========================================================================
//  Metrics / resource usage — periodic streams
// =========================================================================
VMSGS_MACRO(metrics, "dds://system/metrics?qos=sensor", MetricArray)
VMSGS_MACRO(resource_usage, "dds://system/resource_usage?qos=sensor", ResourceUsageReport)
VMSGS_MACRO(system_usage, "dds://system/system_usage?qos=sensor", SystemUsageArray)
VMSGS_MACRO(mission_remaining, "dds://system/mission_remaining?qos=sensor", MissionRemainingDistanceTime)

}  // namespace vmsg::interface::system
