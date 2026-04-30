/*
 * Copyright (C) 2026 by Thun Lu. All rights reserved.
 * Author: Thun Lu <thun.lu@zohomail.cn>
 */

#pragma once

#include "../macros.h"

namespace vmsg::interface::control {

// =========================================================================
//  Tracking commands (high-rate, sensor-class)
// =========================================================================
VMSGS_MACRO(lateral_command, "dds://control/command/lateral?qos=sensor", LateralCommand)
VMSGS_MACRO(longitudinal_command, "dds://control/command/longitudinal?qos=sensor", LongitudinalCommand)
VMSGS_MACRO(control_command, "dds://control/command/control?qos=sensor", AckermannControlCommand)
VMSGS_MACRO(external_control_command, "dds://control/command/external?qos=sensor", ExternalControlCommand)
VMSGS_MACRO(control_horizon, "dds://control/horizon?qos=sensor", ControlHorizon)

// =========================================================================
//  Mode / gating (event-class)
// =========================================================================
VMSGS_MACRO(operation_mode_state, "dds://control/operation_mode_state?qos=sensor", OperationModeState)
VMSGS_MACRO(gate_mode, "dds://control/gate_mode?qos=sensor", GateModeStamped)
VMSGS_MACRO(external_command_selector, "dds://control/external_command_selector?qos=sensor", ExternalCommandSelectorModeStamped)

// =========================================================================
//  Pause-state machine
// =========================================================================
VMSGS_MACRO(is_paused, "dds://control/is_paused?qos=sensor", IsPaused)
VMSGS_MACRO(is_start_requested, "dds://control/is_start_requested?qos=sensor", IsStartRequested)
VMSGS_MACRO(is_stopped, "dds://control/is_stopped?qos=sensor", IsStopped)

}  // namespace vmsg::interface::control
