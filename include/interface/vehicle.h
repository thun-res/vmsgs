/*
 * Copyright (C) 2026 by Thun Lu. All rights reserved.
 * Author: Thun Lu <thun.lu@zohomail.cn>
 */

#pragma once

#include "../macros.h"

namespace vmsg::interface::vehicle {

// =========================================================================
//  Status reports (high-rate, sensor-class)
// =========================================================================
VMSGS_MACRO(velocity_report, "dds://vehicle/status/velocity?qos=sensor", VelocityReport)
VMSGS_MACRO(steering_report, "dds://vehicle/status/steering?qos=sensor", SteeringReport)
VMSGS_MACRO(steering_wheel_status, "dds://vehicle/status/steering_wheel?qos=sensor", SteeringWheelStatusStamped)
VMSGS_MACRO(actuation_status, "dds://vehicle/status/actuation?qos=sensor", ActuationStatus)
VMSGS_MACRO(wheel_speeds, "dds://vehicle/status/wheel_speeds?qos=sensor", WheelSpeeds)
VMSGS_MACRO(wheel_linear_speed, "dds://vehicle/status/wheel_linear_speed?qos=sensor", WheelLinearSpeedReport)
VMSGS_MACRO(vehicle_status, "dds://vehicle/status/summary?qos=sensor", VehicleStatus)
VMSGS_MACRO(vehicle_metrics, "dds://vehicle/status/metrics?qos=sensor", VehicleMetrics)

// =========================================================================
//  Light / signaling commands & reports (event-class)
// =========================================================================
VMSGS_MACRO(turn_indicators_command, "dds://vehicle/command/turn_indicators?qos=sensor", TurnIndicatorsCommand)
VMSGS_MACRO(turn_indicators_report, "dds://vehicle/status/turn_indicators?qos=sensor", TurnIndicatorsReport)
VMSGS_MACRO(hazard_lights_command, "dds://vehicle/command/hazard_lights?qos=sensor", HazardLightsCommand)
VMSGS_MACRO(hazard_lights_report, "dds://vehicle/status/hazard_lights?qos=sensor", HazardLightsReport)
VMSGS_MACRO(headlights_command, "dds://vehicle/command/headlights?qos=sensor", HeadlightsCommand)
VMSGS_MACRO(headlights_report, "dds://vehicle/status/headlights?qos=sensor", HeadlightsReport)
VMSGS_MACRO(wipers_command, "dds://vehicle/command/wipers?qos=sensor", WipersCommand)
VMSGS_MACRO(wipers_report, "dds://vehicle/status/wipers?qos=sensor", WipersReport)
VMSGS_MACRO(horn_command, "dds://vehicle/command/horn?qos=sensor", HornCommand)
VMSGS_MACRO(horn_report, "dds://vehicle/status/horn?qos=sensor", HornReport)

// =========================================================================
//  Powertrain / brakes
// =========================================================================
VMSGS_MACRO(gear_command, "dds://vehicle/command/gear?qos=sensor", GearCommand)
VMSGS_MACRO(gear_report, "dds://vehicle/status/gear?qos=sensor", GearReport)
VMSGS_MACRO(hand_brake_command, "dds://vehicle/command/hand_brake?qos=sensor", HandBrakeCommand)
VMSGS_MACRO(hand_brake_report, "dds://vehicle/status/hand_brake?qos=sensor", HandBrakeReport)
VMSGS_MACRO(actuation_command, "dds://vehicle/command/actuation?qos=sensor", ActuationCommand)

// =========================================================================
//  Engagement / control mode
// =========================================================================
VMSGS_MACRO(engage, "dds://vehicle/engage?qos=sensor", Engage)
VMSGS_MACRO(control_mode_command, "dds://vehicle/command/control_mode?qos=sensor", ControlModeCommand)
VMSGS_MACRO(control_mode_report, "dds://vehicle/status/control_mode?qos=sensor", ControlModeReport)

// =========================================================================
//  Doors
// =========================================================================
VMSGS_MACRO(door_command, "dds://vehicle/command/door?qos=sensor", DoorCommand)
VMSGS_MACRO(door_status, "dds://vehicle/status/door?qos=sensor", DoorStatus)
VMSGS_MACRO(door_status_array, "dds://vehicle/status/door_array?qos=sensor", DoorStatusArray)
VMSGS_MACRO(door_layout, "dds://vehicle/status/door_layout?qos=sensor", DoorLayout)

// =========================================================================
//  Static spec / capability (event-class, slow-changing)
// =========================================================================
VMSGS_MACRO(vehicle_kinematics, "dds://vehicle/spec/kinematics?qos=sensor", VehicleKinematics)
VMSGS_MACRO(vehicle_dimensions, "dds://vehicle/spec/dimensions?qos=sensor", VehicleDimensions)
VMSGS_MACRO(vehicle_specs, "dds://vehicle/spec/specs?qos=sensor", VehicleSpecs)

// =========================================================================
//  Emergency
// =========================================================================
VMSGS_MACRO(vehicle_emergency, "dds://vehicle/emergency?qos=sensor", VehicleEmergencyStamped)

}  // namespace vmsg::interface::vehicle
