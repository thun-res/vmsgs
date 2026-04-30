/*
 * Copyright (C) 2026 by Thun Lu. All rights reserved.
 * Author: Thun Lu <thun.lu@zohomail.cn>
 */

#pragma once

#include "../macros.h"

namespace vmsg::interface::v2x {

// =========================================================================
//  Generic V2X envelope — each network packet must be delivered
// =========================================================================
VMSGS_MACRO(v2x_message, "dds://v2x/message", V2XMessage)

// =========================================================================
//  Virtual traffic light
// =========================================================================
// Status streams at sensor rate; the request is a one-shot command.
VMSGS_MACRO(virtual_traffic_light_status, "dds://v2x/virtual_traffic_light/status?qos=sensor", VirtualTrafficLightStatusArray)
VMSGS_MACRO(virtual_traffic_light_state_request, "dds://v2x/virtual_traffic_light/state_request", VirtualTrafficLightStateRequest)

// =========================================================================
//  Cooperative driving — sensor stream
// =========================================================================
VMSGS_MACRO(cooperative_status, "dds://v2x/cooperative_status?qos=sensor", CooperativeStatus)

// =========================================================================
//  Virtual gate — commands must-deliver, status is high-rate
// =========================================================================
VMSGS_MACRO(virtual_gate_command, "dds://v2x/virtual_gate/command", VirtualGateCommand)
VMSGS_MACRO(virtual_gate_status, "dds://v2x/virtual_gate/status?qos=sensor", VirtualGateStatus)
VMSGS_MACRO(virtual_gate_area_command, "dds://v2x/virtual_gate/area_command", VirtualGateAreaCommand)
VMSGS_MACRO(virtual_gate_area_status, "dds://v2x/virtual_gate/area_status?qos=sensor", VirtualGateAreaStatus)

// =========================================================================
//  Roadside infrastructure command — must-deliver
// =========================================================================
VMSGS_MACRO(infrastructure_commands, "dds://v2x/infrastructure_commands", InfrastructureCommandArray)

}  // namespace vmsg::interface::v2x
