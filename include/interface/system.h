/*
 * Copyright (c) 2026 VMsgs Contributors.
 * SPDX-License-Identifier: MIT
 *
 * Author: Thun Lu <thun.lu@zohomail.cn>
 */

#pragma once

#include "../macros.h"

namespace vmsg::interface::system {

// External operator/cloud methods use reliable request/response QoS.
VMSGS_MACRO(set_route_request, "dds://system/operator/set_route/request?qos=method", "vmsgs.proto.system.SetRouteRequest")
VMSGS_MACRO(set_route_response, "dds://system/operator/set_route/response?qos=method", "vmsgs.proto.system.SetRouteResponse")
VMSGS_MACRO(clear_route_request, "dds://system/operator/clear_route/request?qos=method", "vmsgs.proto.system.ClearRouteRequest")
VMSGS_MACRO(clear_route_response, "dds://system/operator/clear_route/response?qos=method", "vmsgs.proto.system.ClearRouteResponse")
VMSGS_MACRO(engage_control_request, "dds://system/operator/engage/request?qos=method", "vmsgs.proto.system.EngageControlRequest")
VMSGS_MACRO(engage_control_response, "dds://system/operator/engage/response?qos=method", "vmsgs.proto.system.EngageControlResponse")
VMSGS_MACRO(set_control_override_request, "dds://system/operator/override/request?qos=method", "vmsgs.proto.system.SetControlOverrideRequest")
VMSGS_MACRO(set_control_override_response, "dds://system/operator/override/response?qos=method", "vmsgs.proto.system.SetControlOverrideResponse")

// =========================================================================
//  Top-level state machines — must-deliver
// =========================================================================
VMSGS_MACRO(autonomy_lifecycle_state, "dds://system/autonomy/lifecycle_state?qos=field", "vmsgs.proto.system.AutonomyLifecycleStateStamped")
VMSGS_MACRO(emergency_state, "dds://system/emergency_state?qos=field", "vmsgs.proto.system.EmergencyStateStamped")

// =========================================================================
//  Minimum-Risk-Maneuver — safety-critical, must-deliver
// =========================================================================
VMSGS_MACRO(mrm_state, "dds://system/mrm/state?qos=field", "vmsgs.proto.system.MrmState")
VMSGS_MACRO(mrm_behavior_status, "dds://system/mrm/behavior_status?qos=field", "vmsgs.proto.system.MrmBehaviorStatus")
VMSGS_MACRO(mrm_description, "dds://system/mrm/description?qos=static", "vmsgs.proto.system.MrmDescription")
VMSGS_MACRO(mrm_request_list, "dds://system/mrm/request_list?qos=alarm", "vmsgs.proto.system.MrmRequestList")

// =========================================================================
//  Hazard / diagnostics
// =========================================================================
// Hazard and fault transitions are safety relevant and must be delivered.
VMSGS_MACRO(hazard_status, "dds://system/hazard_status?qos=alarm", "vmsgs.proto.system.HazardStatusStamped")
VMSGS_MACRO(diagnostics, "dds://system/diagnostics?qos=alarm", "vmsgs.proto.system.DiagnosticArray")
// diag_graph_struct is published once at startup → must-deliver.
VMSGS_MACRO(diag_graph_struct, "dds://system/diag_graph/struct?qos=static", "vmsgs.proto.system.DiagGraphStruct")
VMSGS_MACRO(diag_graph_status, "dds://system/diag_graph/status?qos=sensor", "vmsgs.proto.system.DiagGraphStatus")

// =========================================================================
//  Liveness / observability — periodic streams (drop-OK)
// =========================================================================
VMSGS_MACRO(log, "dds://system/log?qos=sensor", "vmsgs.proto.system.Log")
VMSGS_MACRO(heartbeat, "dds://system/heartbeat?qos=sensor", "vmsgs.proto.system.Heartbeat")
VMSGS_MACRO(process_info, "dds://system/process_info?qos=sensor", "vmsgs.proto.system.ProcessInfoArray")

// service_log records each RPC's lifecycle — must-deliver for audit trace.
VMSGS_MACRO(service_log, "dds://system/service_log?qos=log", "vmsgs.proto.system.ServiceLog")

// =========================================================================
//  Command-source switching / availability — must-deliver
// =========================================================================
VMSGS_MACRO(command_mode_availability, "dds://system/command_mode/availability?qos=field", "vmsgs.proto.system.CommandModeAvailability")
VMSGS_MACRO(command_mode_status, "dds://system/command_mode/status?qos=field", "vmsgs.proto.system.CommandModeStatus")
VMSGS_MACRO(command_mode_request, "dds://system/command_mode/request?qos=method", "vmsgs.proto.system.CommandModeRequest")
VMSGS_MACRO(command_source_status, "dds://system/command_source_status?qos=field", "vmsgs.proto.system.CommandSourceStatus")
VMSGS_MACRO(operation_mode_availability, "dds://system/operation_mode_availability?qos=field", "vmsgs.proto.system.OperationModeAvailability")
VMSGS_MACRO(mode_change_request, "dds://system/mode_change/request?qos=method", "vmsgs.proto.system.ModeChangeRequest")
VMSGS_MACRO(mode_change_response, "dds://system/mode_change/response?qos=method", "vmsgs.proto.system.ModeChangeResponse")

// =========================================================================
//  Metrics / resource usage — periodic streams
// =========================================================================
VMSGS_MACRO(metrics, "dds://system/metrics?qos=sensor", "vmsgs.proto.common.MetricArray")
VMSGS_MACRO(resource_usage, "dds://system/resource_usage?qos=sensor", "vmsgs.proto.system.ResourceUsageReport")
VMSGS_MACRO(system_usage, "dds://system/system_usage?qos=sensor", "vmsgs.proto.system.SystemUsageArray")
VMSGS_MACRO(mission_remaining, "dds://system/mission_remaining?qos=sensor", "vmsgs.proto.system.MissionRemainingDistanceTime")

}  // namespace vmsg::interface::system
