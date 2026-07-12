/*
 * Copyright (c) 2026 VMsgs Contributors.
 * SPDX-License-Identifier: MIT
 *
 * Author: Thun Lu <thun.lu@zohomail.cn>
 */

#pragma once

#include "../macros.h"

namespace vmsg::interface::control {

// =========================================================================
//  Tracking commands (high-rate, sensor-class)
// =========================================================================
VMSGS_MACRO(lateral_command, "dds://control/command/lateral?qos=sensor", "vmsgs.proto.control.LateralCommand")
VMSGS_MACRO(longitudinal_command, "dds://control/command/longitudinal?qos=sensor", "vmsgs.proto.control.LongitudinalCommand")
VMSGS_MACRO(control_command, "dds://control/command/control?qos=sensor", "vmsgs.proto.control.AckermannControlCommand")
VMSGS_MACRO(control_command_zero_copy, "shm://control/command/control", "vmsgs.fbs.control.AckermannControlCommand")
VMSGS_MACRO(external_control_command, "dds://control/command/external?qos=sensor", "vmsgs.proto.control.ExternalControlCommand")
VMSGS_MACRO(control_horizon, "dds://control/horizon?qos=sensor", "vmsgs.proto.control.ControlHorizon")
VMSGS_MACRO(control_horizon_fbs, "shm://control/horizon", "vmsgs.fbs.control.ControlHorizon")
VMSGS_MACRO(external_control_command_fbs, "shm://control/command/external", "vmsgs.fbs.control.ExternalControlCommand")

// =========================================================================
//  Mode / gating (event-class)
// =========================================================================
VMSGS_MACRO(operation_mode_state, "dds://control/operation_mode_state", "vmsgs.proto.control.OperationModeState")
VMSGS_MACRO(gate_mode, "dds://control/gate_mode", "vmsgs.proto.control.GateModeStamped")
VMSGS_MACRO(external_command_selector, "dds://control/external_command_selector", "vmsgs.proto.control.ExternalCommandSelectorModeStamped")

// =========================================================================
//  Pause-state machine
// =========================================================================
VMSGS_MACRO(is_paused, "dds://control/is_paused", "vmsgs.proto.control.IsPaused")
VMSGS_MACRO(is_start_requested, "dds://control/is_start_requested", "vmsgs.proto.control.IsStartRequested")
VMSGS_MACRO(is_stopped, "dds://control/is_stopped", "vmsgs.proto.control.IsStopped")

}  // namespace vmsg::interface::control
