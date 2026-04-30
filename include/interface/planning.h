/*
 * Copyright (C) 2026 by Thun Lu. All rights reserved.
 * Author: Thun Lu <thun.lu@zohomail.cn>
 */

#pragma once

#include "../macros.h"

namespace vmsg::interface::planning {

// =========================================================================
//  Path / trajectory primary outputs
// =========================================================================
VMSGS_MACRO(path, "dds://planning/path?qos=sensor", Path)
VMSGS_MACRO(path_with_lane_id, "dds://planning/path_with_lane_id?qos=sensor", PathWithLaneId)
VMSGS_MACRO(trajectory, "dds://planning/trajectory?qos=sensor", Trajectory)

// Multi-hypothesis candidates from candidate-trajectory generators.
VMSGS_MACRO(candidate_trajectories, "dds://planning/candidate_trajectories?qos=sensor", CandidateTrajectories)
VMSGS_MACRO(scored_candidate_trajectories, "dds://planning/scored_candidate_trajectories?qos=sensor", ScoredCandidateTrajectories)

// =========================================================================
//  Mission / route / scenario state
// =========================================================================
VMSGS_MACRO(route, "dds://planning/route?qos=sensor", LaneletRoute)
VMSGS_MACRO(route_state, "dds://planning/route_state?qos=sensor", RouteStateStamped)
VMSGS_MACRO(mission_state, "dds://planning/mission_state?qos=sensor", MissionStateStamped)
VMSGS_MACRO(mission_goal, "dds://planning/mission_goal?qos=sensor", MissionGoal)
VMSGS_MACRO(scenario, "dds://planning/scenario?qos=sensor", ScenarioStamped)
VMSGS_MACRO(behavior_state, "dds://planning/behavior_state?qos=sensor", BehaviorStateStamped)
VMSGS_MACRO(avoidance_state, "dds://planning/avoidance_state?qos=sensor", AvoidanceState)

// =========================================================================
//  Velocity / lateral / cooperate
// =========================================================================
VMSGS_MACRO(velocity_limit, "dds://planning/velocity_limit?qos=sensor", VelocityLimit)
VMSGS_MACRO(velocity_limit_clear, "dds://planning/velocity_limit_clear?qos=sensor", VelocityLimitClearCommand)
VMSGS_MACRO(lateral_offset, "dds://planning/lateral_offset?qos=sensor", LateralOffset)
VMSGS_MACRO(reroute_availability, "dds://planning/reroute_availability?qos=sensor", RerouteAvailability)
VMSGS_MACRO(cooperate_status, "dds://planning/cooperate_status?qos=sensor", CooperateStatusArray)
VMSGS_MACRO(pose_with_uuid, "dds://planning/pose_with_uuid?qos=sensor", PoseWithUuidStamped)

// =========================================================================
//  Decision factors / explanations
// =========================================================================
VMSGS_MACRO(stop_reasons, "dds://planning/stop_reasons?qos=sensor", StopReasonArray)
VMSGS_MACRO(planning_factors, "dds://planning/planning_factors?qos=sensor", PlanningFactorArray)
VMSGS_MACRO(safety_factors, "dds://planning/safety_factors?qos=sensor", SafetyFactorArray)
VMSGS_MACRO(velocity_factors, "dds://planning/velocity_factors?qos=sensor", VelocityFactorArray)
VMSGS_MACRO(steering_factors, "dds://planning/steering_factors?qos=sensor", SteeringFactorArray)

}  // namespace vmsg::interface::planning
