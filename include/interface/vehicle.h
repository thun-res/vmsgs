/*
 * Copyright (c) 2026 VMsgs Contributors.
 * SPDX-License-Identifier: MIT
 *
 * Author: Thun Lu <thun.lu@zohomail.cn>
 */

#pragma once

#include "../macros.h"

namespace vmsg::interface::vehicle {

// =========================================================================
//  Status reports (high-rate, sensor-class)
// =========================================================================
VMSGS_MACRO(velocity_report, "dds://vehicle/status/velocity?qos=sensor", "vmsgs.proto.vehicle.VelocityReport")
VMSGS_MACRO(velocity_report_fbs, "shm://vehicle/status/velocity", "vmsgs.fbs.vehicle.VelocityReport")
VMSGS_MACRO(steering_report, "dds://vehicle/status/steering?qos=sensor", "vmsgs.proto.vehicle.SteeringReport")
VMSGS_MACRO(steering_report_fbs, "shm://vehicle/status/steering", "vmsgs.fbs.vehicle.SteeringReport")
VMSGS_MACRO(steering_wheel_status, "dds://vehicle/status/steering_wheel?qos=sensor", "vmsgs.proto.vehicle.SteeringWheelStatusStamped")
VMSGS_MACRO(actuation_status, "dds://vehicle/status/actuation?qos=sensor", "vmsgs.proto.vehicle.ActuationStatus")
VMSGS_MACRO(actuation_status_fbs, "shm://vehicle/status/actuation", "vmsgs.fbs.vehicle.ActuationStatus")
VMSGS_MACRO(wheel_speeds, "dds://vehicle/status/wheel_speeds?qos=sensor", "vmsgs.proto.vehicle.WheelSpeeds")
VMSGS_MACRO(wheel_linear_speed, "dds://vehicle/status/wheel_linear_speed?qos=sensor", "vmsgs.proto.vehicle.WheelLinearSpeedReport")
VMSGS_MACRO(wheel_linear_speed_fbs, "shm://vehicle/status/wheel_linear_speed", "vmsgs.fbs.vehicle.WheelLinearSpeedReport")
VMSGS_MACRO(chassis_info, "dds://vehicle/status/chassis?qos=sensor", "vmsgs.proto.vehicle.ChassisInfo")
VMSGS_MACRO(chassis_info_zero_copy, "shm://vehicle/status/chassis", "vmsgs.fbs.vehicle.ChassisInfo")
VMSGS_MACRO(vehicle_metrics, "dds://vehicle/status/metrics?qos=sensor", "vmsgs.proto.vehicle.VehicleMetrics")

// =========================================================================
//  Light / signaling commands & reports (event-class)
// =========================================================================
VMSGS_MACRO(turn_indicators_command, "dds://vehicle/command/turn_indicators?qos=command", "vmsgs.proto.vehicle.TurnIndicatorsCommand")
VMSGS_MACRO(turn_indicators_report, "dds://vehicle/status/turn_indicators?qos=sensor", "vmsgs.proto.vehicle.TurnIndicatorsReport")
VMSGS_MACRO(hazard_lights_command, "dds://vehicle/command/hazard_lights?qos=command", "vmsgs.proto.vehicle.HazardLightsCommand")
VMSGS_MACRO(hazard_lights_report, "dds://vehicle/status/hazard_lights?qos=sensor", "vmsgs.proto.vehicle.HazardLightsReport")
VMSGS_MACRO(headlights_command, "dds://vehicle/command/headlights?qos=command", "vmsgs.proto.vehicle.HeadlightsCommand")
VMSGS_MACRO(headlights_report, "dds://vehicle/status/headlights?qos=sensor", "vmsgs.proto.vehicle.HeadlightsReport")
VMSGS_MACRO(wipers_command, "dds://vehicle/command/wipers?qos=command", "vmsgs.proto.vehicle.WipersCommand")
VMSGS_MACRO(wipers_report, "dds://vehicle/status/wipers?qos=sensor", "vmsgs.proto.vehicle.WipersReport")
VMSGS_MACRO(horn_command, "dds://vehicle/command/horn?qos=command", "vmsgs.proto.vehicle.HornCommand")
VMSGS_MACRO(horn_report, "dds://vehicle/status/horn?qos=sensor", "vmsgs.proto.vehicle.HornReport")

// =========================================================================
//  Powertrain / brakes
// =========================================================================
VMSGS_MACRO(gear_command, "dds://vehicle/command/gear?qos=command", "vmsgs.proto.vehicle.GearCommand")
VMSGS_MACRO(gear_report, "dds://vehicle/status/gear?qos=sensor", "vmsgs.proto.vehicle.GearReport")
VMSGS_MACRO(hand_brake_command, "dds://vehicle/command/hand_brake?qos=command", "vmsgs.proto.vehicle.HandBrakeCommand")
VMSGS_MACRO(hand_brake_report, "dds://vehicle/status/hand_brake?qos=sensor", "vmsgs.proto.vehicle.HandBrakeReport")
VMSGS_MACRO(actuation_command, "dds://vehicle/command/actuation?qos=sensor", "vmsgs.proto.vehicle.ActuationCommand")

// =========================================================================
//  Engagement / control mode
// =========================================================================
VMSGS_MACRO(engage, "dds://vehicle/engage", "vmsgs.proto.vehicle.Engage")
VMSGS_MACRO(control_mode_command, "dds://vehicle/command/control_mode?qos=command", "vmsgs.proto.vehicle.ControlModeCommand")
VMSGS_MACRO(control_mode_report, "dds://vehicle/status/control_mode?qos=sensor", "vmsgs.proto.vehicle.ControlModeReport")

// =========================================================================
//  Doors
// =========================================================================
VMSGS_MACRO(door_command, "dds://vehicle/command/door?qos=command", "vmsgs.proto.vehicle.DoorCommand")
VMSGS_MACRO(door_status, "dds://vehicle/status/door?qos=sensor", "vmsgs.proto.vehicle.DoorStatus")
VMSGS_MACRO(door_status_array, "dds://vehicle/status/door_array?qos=sensor", "vmsgs.proto.vehicle.DoorStatusArray")
VMSGS_MACRO(door_layout, "dds://vehicle/status/door_layout?qos=static", "vmsgs.proto.vehicle.DoorLayout")

// =========================================================================
//  Static spec / capability (event-class, slow-changing)
// =========================================================================
VMSGS_MACRO(vehicle_kinematics, "dds://vehicle/spec/kinematics?qos=static", "vmsgs.proto.vehicle.VehicleKinematics")
VMSGS_MACRO(vehicle_dimensions, "dds://vehicle/spec/dimensions?qos=static", "vmsgs.proto.vehicle.VehicleDimensions")
VMSGS_MACRO(vehicle_specs, "dds://vehicle/spec/specs?qos=static", "vmsgs.proto.vehicle.VehicleSpecs")

// =========================================================================
//  Emergency
// =========================================================================
VMSGS_MACRO(vehicle_emergency, "dds://vehicle/emergency?qos=alarm", "vmsgs.proto.vehicle.VehicleEmergencyStamped")

}  // namespace vmsg::interface::vehicle
