/*
 * Copyright (c) 2026 VMsgs Contributors.
 * SPDX-License-Identifier: MIT
 *
 * Author: Thun Lu <thun.lu@zohomail.cn>
 */

#pragma once

#include "../macros.h"

namespace vmsg::interface::v2x {

// =========================================================================
//  Generic V2X envelope — each network packet must be delivered
// =========================================================================
VMSGS_MACRO(v2x_message, "dds://v2x/message", "vmsgs.proto.v2x.V2XMessage")

// =========================================================================
//  Virtual traffic light
// =========================================================================
// Right-of-way state and requests are reliable state-machine traffic.
VMSGS_MACRO(virtual_traffic_light_status, "dds://v2x/virtual_traffic_light/status", "vmsgs.proto.v2x.VirtualTrafficLightStatusArray")
VMSGS_MACRO(virtual_traffic_light_state_request, "dds://v2x/virtual_traffic_light/state_request?qos=method", "vmsgs.proto.v2x.VirtualTrafficLightStateRequest")

// =========================================================================
//  Cooperative driving — reliable negotiated state
// =========================================================================
VMSGS_MACRO(cooperative_status, "dds://v2x/cooperative_status", "vmsgs.proto.v2x.CooperativeStatus")

// =========================================================================
//  Virtual gate — commands and latest state must be delivered
// =========================================================================
VMSGS_MACRO(virtual_gate_command, "dds://v2x/virtual_gate/command?qos=command", "vmsgs.proto.v2x.VirtualGateCommand")
VMSGS_MACRO(virtual_gate_status, "dds://v2x/virtual_gate/status", "vmsgs.proto.v2x.VirtualGateStatus")
VMSGS_MACRO(virtual_gate_area_command, "dds://v2x/virtual_gate/area_command?qos=command", "vmsgs.proto.v2x.VirtualGateAreaCommand")
VMSGS_MACRO(virtual_gate_area_status, "dds://v2x/virtual_gate/area_status", "vmsgs.proto.v2x.VirtualGateAreaStatus")

// =========================================================================
//  Roadside infrastructure command — must-deliver
// =========================================================================
VMSGS_MACRO(infrastructure_commands, "dds://v2x/infrastructure_commands", "vmsgs.proto.v2x.InfrastructureCommandArray")

}  // namespace vmsg::interface::v2x
