/*
 * Copyright (c) 2026 VMsgs Contributors.
 * SPDX-License-Identifier: MIT
 *
 * Author: Thun Lu <thun.lu@zohomail.cn>
 */

#pragma once

#include "../macros.h"

namespace vmsg::interface::planning {

// =========================================================================
//  Path / trajectory primary outputs
// =========================================================================
VMSGS_MACRO(path, "dds://planning/path?qos=sensor", "vmsgs.proto.planning.Path")
VMSGS_MACRO(path_with_lane_id, "dds://planning/path_with_lane_id?qos=sensor", "vmsgs.proto.planning.PathWithLaneId")
VMSGS_MACRO(trajectory, "dds://planning/trajectory?qos=sensor", "vmsgs.proto.planning.Trajectory")
VMSGS_MACRO(trajectory_zero_copy, "shm://planning/trajectory", "vmsgs.fbs.planning.Trajectory")

// Multi-hypothesis candidates from candidate-trajectory generators.
VMSGS_MACRO(candidate_trajectories, "dds://planning/candidate_trajectories?qos=sensor", "vmsgs.proto.planning.CandidateTrajectories")
VMSGS_MACRO(scored_candidate_trajectories, "dds://planning/scored_candidate_trajectories?qos=sensor", "vmsgs.proto.planning.ScoredCandidateTrajectories")

// =========================================================================
//  Mission / route / scenario state
// =========================================================================
VMSGS_MACRO(route, "dds://planning/route", "vmsgs.proto.planning.LaneletRoute")
VMSGS_MACRO(route_state, "dds://planning/route_state", "vmsgs.proto.planning.RouteStateStamped")
VMSGS_MACRO(mission_state, "dds://planning/mission_state", "vmsgs.proto.planning.MissionStateStamped")
VMSGS_MACRO(mission_goal, "dds://planning/mission_goal?qos=method", "vmsgs.proto.planning.MissionGoal")
VMSGS_MACRO(scenario, "dds://planning/scenario", "vmsgs.proto.planning.ScenarioStamped")
VMSGS_MACRO(behavior_state, "dds://planning/behavior_state", "vmsgs.proto.planning.BehaviorStateStamped")
VMSGS_MACRO(avoidance_state, "dds://planning/avoidance_state", "vmsgs.proto.planning.AvoidanceState")

// =========================================================================
//  Velocity / lateral / cooperate
// =========================================================================
VMSGS_MACRO(velocity_limit, "dds://planning/velocity_limit", "vmsgs.proto.planning.VelocityLimit")
VMSGS_MACRO(velocity_limit_clear, "dds://planning/velocity_limit_clear", "vmsgs.proto.planning.VelocityLimitClearCommand")
VMSGS_MACRO(lateral_offset, "dds://planning/lateral_offset?qos=sensor", "vmsgs.proto.planning.LateralOffset")
VMSGS_MACRO(reroute_availability, "dds://planning/reroute_availability", "vmsgs.proto.planning.RerouteAvailability")
VMSGS_MACRO(cooperate_status, "dds://planning/cooperate_status", "vmsgs.proto.planning.CooperateStatusArray")
VMSGS_MACRO(pose_with_uuid, "dds://planning/pose_with_uuid?qos=sensor", "vmsgs.proto.planning.PoseWithUuidStamped")

// =========================================================================
//  Decision factors / explanations
// =========================================================================
VMSGS_MACRO(stop_reasons, "dds://planning/stop_reasons?qos=sensor", "vmsgs.proto.planning.StopReasonArray")
VMSGS_MACRO(planning_factors, "dds://planning/planning_factors?qos=sensor", "vmsgs.proto.planning.PlanningFactorArray")
VMSGS_MACRO(safety_factors, "dds://planning/safety_factors?qos=sensor", "vmsgs.proto.planning.SafetyFactorArray")
VMSGS_MACRO(velocity_factors, "dds://planning/velocity_factors?qos=sensor", "vmsgs.proto.planning.VelocityFactorArray")
VMSGS_MACRO(steering_factors, "dds://planning/steering_factors?qos=sensor", "vmsgs.proto.planning.SteeringFactorArray")

}  // namespace vmsg::interface::planning
