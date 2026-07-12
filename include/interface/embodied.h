/*
 * Copyright (c) 2026 VMsgs Contributors.
 * SPDX-License-Identifier: MIT
 *
 * Author: Thun Lu <thun.lu@zohomail.cn>
 */

#pragma once

#include "../macros.h"

// Topics used by the embodied-AI / robotics stack.
//
// Where a humanoid / dual-arm setup is expected, both a generic
// (single-arm) topic and left/right variants are provided.

namespace vmsg::interface::embodied {

// =========================================================================
//  Joint-space — trajectory must-deliver, command/state high-rate
// =========================================================================
VMSGS_MACRO(joint_trajectory, "dds://embodied/joint/trajectory", "vmsgs.proto.embodied.JointTrajectory")
VMSGS_MACRO(joint_trajectory_zero_copy, "shm://embodied/joint/trajectory", "vmsgs.fbs.embodied.JointTrajectory")
VMSGS_MACRO(joint_command, "dds://embodied/joint/command?qos=command", "vmsgs.proto.embodied.JointCommand")
VMSGS_MACRO(joint_command_zero_copy, "shm://embodied/joint/command", "vmsgs.fbs.embodied.JointCommand")
VMSGS_MACRO(multi_dof_joint_trajectory, "dds://embodied/joint/multi_dof_trajectory", "vmsgs.proto.embodied.MultiDOFJointTrajectory")
VMSGS_MACRO(joint_controller_state, "dds://embodied/joint/controller_state?qos=sensor", "vmsgs.proto.embodied.JointTrajectoryControllerState")
VMSGS_MACRO(joint_controller_state_fbs, "shm://embodied/joint/controller_state", "vmsgs.fbs.embodied.JointTrajectoryControllerState")
VMSGS_MACRO(pid_state, "dds://embodied/controller/pid_state?qos=sensor", "vmsgs.proto.embodied.PidState")
VMSGS_MACRO(hardware_state, "dds://embodied/hardware/state?qos=sensor", "vmsgs.proto.embodied.HardwareState")

// =========================================================================
//  Manipulator state (TCP pose / twist / wrench) — high-rate stream
// =========================================================================
VMSGS_MACRO(manipulator_state, "dds://embodied/manipulator/state?qos=sensor", "vmsgs.proto.embodied.ManipulatorState")
VMSGS_MACRO(manipulator_state_fbs, "shm://embodied/manipulator/state", "vmsgs.fbs.embodied.ManipulatorState")

// =========================================================================
//  End-effector (Cartesian command / state) — high-rate stream
// =========================================================================
VMSGS_MACRO(end_effector_command, "dds://embodied/end_effector/command?qos=command", "vmsgs.proto.embodied.EndEffectorCommand")
VMSGS_MACRO(end_effector_state, "dds://embodied/end_effector/state?qos=sensor", "vmsgs.proto.embodied.EndEffectorState")
VMSGS_MACRO(end_effector_command_fbs, "shm://embodied/end_effector/command", "vmsgs.fbs.embodied.EndEffectorCommand")
VMSGS_MACRO(end_effector_state_fbs, "shm://embodied/end_effector/state", "vmsgs.fbs.embodied.EndEffectorState")

// =========================================================================
//  Gripper — command must-deliver, state high-rate
// =========================================================================
VMSGS_MACRO(gripper_command, "dds://embodied/gripper/command?qos=command", "vmsgs.proto.embodied.GripperCommand")
VMSGS_MACRO(gripper_state, "dds://embodied/gripper/state?qos=sensor", "vmsgs.proto.embodied.GripperState")
VMSGS_MACRO(gripper_state_fbs, "shm://embodied/gripper/state", "vmsgs.fbs.embodied.GripperState")

// =========================================================================
//  Whole-body / mobile base — high-rate stream
// =========================================================================
VMSGS_MACRO(robot_state, "dds://embodied/robot_state?qos=sensor", "vmsgs.proto.embodied.RobotState")
VMSGS_MACRO(robot_state_fbs, "shm://embodied/robot_state", "vmsgs.fbs.embodied.RobotState")
VMSGS_MACRO(locomotion_command, "dds://embodied/locomotion/command?qos=command", "vmsgs.proto.embodied.LocomotionCommand")
VMSGS_MACRO(locomotion_state, "dds://embodied/locomotion/state?qos=sensor", "vmsgs.proto.embodied.LocomotionState")
VMSGS_MACRO(locomotion_command_fbs, "shm://embodied/locomotion/command", "vmsgs.fbs.embodied.LocomotionCommand")
VMSGS_MACRO(locomotion_state_fbs, "shm://embodied/locomotion/state", "vmsgs.fbs.embodied.LocomotionState")

// =========================================================================
//  Skill / task orchestration — request/result must-deliver, feedback high-rate
// =========================================================================
VMSGS_MACRO(skill_request, "dds://embodied/skill/request?qos=method", "vmsgs.proto.embodied.SkillRequest")
VMSGS_MACRO(skill_descriptor, "dds://embodied/skill/descriptor?qos=static", "vmsgs.proto.embodied.SkillDescriptor")
VMSGS_MACRO(skill_feedback, "dds://embodied/skill/feedback?qos=sensor", "vmsgs.proto.embodied.SkillFeedback")
VMSGS_MACRO(skill_result, "dds://embodied/skill/result?qos=method", "vmsgs.proto.embodied.SkillResult")
VMSGS_MACRO(task_request, "dds://embodied/task/request?qos=method", "vmsgs.proto.embodied.Task")
VMSGS_MACRO(task_feedback, "dds://embodied/task/feedback?qos=sensor", "vmsgs.proto.embodied.TaskFeedback")
VMSGS_MACRO(task_result, "dds://embodied/task/result?qos=method", "vmsgs.proto.embodied.TaskResult")
VMSGS_MACRO(task_cancel_request, "dds://embodied/task/cancel/request?qos=method", "vmsgs.proto.embodied.TaskCancelRequest")
VMSGS_MACRO(task_cancel_response, "dds://embodied/task/cancel/response?qos=method", "vmsgs.proto.embodied.TaskCancelResponse")
VMSGS_MACRO(fleet_state, "dds://coordination/fleet/state?qos=field", "vmsgs.proto.embodied.FleetState")
VMSGS_MACRO(fleet_path_request, "dds://coordination/fleet/path_request?qos=method", "vmsgs.proto.embodied.FleetPathRequest")
VMSGS_MACRO(fleet_path_response, "dds://coordination/fleet/path_response?qos=method", "vmsgs.proto.embodied.FleetPathResponse")
VMSGS_MACRO(bid_notice, "dds://coordination/bid/notice", "vmsgs.proto.embodied.BidNotice")
VMSGS_MACRO(bid_proposal, "dds://coordination/bid/proposal", "vmsgs.proto.embodied.BidProposal")
VMSGS_MACRO(bid_award, "dds://coordination/bid/award", "vmsgs.proto.embodied.BidAward")
VMSGS_MACRO(dispatch_request, "dds://coordination/dispatch/request?qos=method", "vmsgs.proto.embodied.DispatchRequest")
VMSGS_MACRO(dispatch_ack, "dds://coordination/dispatch/ack?qos=method", "vmsgs.proto.embodied.DispatchAck")
VMSGS_MACRO(dispatch_status, "dds://coordination/dispatch/status?qos=field", "vmsgs.proto.embodied.DispatchStatus")
VMSGS_MACRO(path_cancel_request, "dds://coordination/path/cancel?qos=method", "vmsgs.proto.embodied.PathCancelRequest")
VMSGS_MACRO(path_result, "dds://coordination/path/result?qos=method", "vmsgs.proto.embodied.PathResult")
VMSGS_MACRO(traffic_participant, "dds://coordination/traffic/participant?qos=static", "vmsgs.proto.embodied.TrafficParticipant")
VMSGS_MACRO(traffic_itinerary, "dds://coordination/traffic/itinerary?qos=field", "vmsgs.proto.embodied.TrafficItinerary")
VMSGS_MACRO(traffic_negotiation, "dds://coordination/traffic/negotiation", "vmsgs.proto.embodied.TrafficNegotiation")
VMSGS_MACRO(building_nav_graph, "dds://coordination/building/nav_graph?qos=static", "vmsgs.proto.embodied.BuildingNavGraph")
VMSGS_MACRO(facility_emergency, "dds://coordination/facility/emergency?qos=alarm", "vmsgs.proto.embodied.FacilityEmergency")
VMSGS_MACRO(dispenser_request, "dds://coordination/dispenser/request?qos=method", "vmsgs.proto.embodied.WorkcellRequest")
VMSGS_MACRO(dispenser_status, "dds://coordination/dispenser/status?qos=field", "vmsgs.proto.embodied.WorkcellStatus")
VMSGS_MACRO(ingestor_request, "dds://coordination/ingestor/request?qos=method", "vmsgs.proto.embodied.WorkcellRequest")
VMSGS_MACRO(ingestor_status, "dds://coordination/ingestor/status?qos=field", "vmsgs.proto.embodied.WorkcellStatus")
VMSGS_MACRO(charger_reservation_request, "dds://coordination/charger/reservation/request?qos=method", "vmsgs.proto.embodied.ChargerReservationRequest")
VMSGS_MACRO(charger_reservation_response, "dds://coordination/charger/reservation/response?qos=method", "vmsgs.proto.embodied.ChargerReservationResponse")
VMSGS_MACRO(facility_door_command, "dds://coordination/facility/door/command?qos=command", "vmsgs.proto.embodied.FacilityDoorCommand")
VMSGS_MACRO(facility_door_state, "dds://coordination/facility/door/state?qos=field", "vmsgs.proto.embodied.FacilityDoorState")
VMSGS_MACRO(facility_lift_command, "dds://coordination/facility/lift/command?qos=command", "vmsgs.proto.embodied.FacilityLiftCommand")
VMSGS_MACRO(facility_lift_state, "dds://coordination/facility/lift/state?qos=field", "vmsgs.proto.embodied.FacilityLiftState")
VMSGS_MACRO(motion_plan_request, "dds://embodied/motion_plan/request?qos=method", "vmsgs.proto.embodied.MotionPlanRequest")
VMSGS_MACRO(motion_plan_response, "dds://embodied/motion_plan/response?qos=method", "vmsgs.proto.embodied.MotionPlanResponse")
VMSGS_MACRO(cartesian_path_request, "dds://embodied/cartesian_path/request?qos=method", "vmsgs.proto.embodied.CartesianPathRequest")
VMSGS_MACRO(cartesian_path_response, "dds://embodied/cartesian_path/response?qos=method", "vmsgs.proto.embodied.CartesianPathResponse")
VMSGS_MACRO(motion_sequence_request, "dds://embodied/motion_sequence/request?qos=method", "vmsgs.proto.embodied.MotionSequenceRequest")
VMSGS_MACRO(motion_sequence_response, "dds://embodied/motion_sequence/response?qos=method", "vmsgs.proto.embodied.MotionSequenceResponse")
VMSGS_MACRO(planning_scene, "dds://embodied/planning_scene?qos=field", "vmsgs.proto.embodied.PlanningScene")
VMSGS_MACRO(get_planning_scene_request, "dds://embodied/planning_scene/query?qos=method", "vmsgs.proto.embodied.GetPlanningSceneRequest")
VMSGS_MACRO(get_planning_scene_response, "dds://embodied/planning_scene/query/response?qos=method", "vmsgs.proto.embodied.GetPlanningSceneResponse")
VMSGS_MACRO(inverse_kinematics_request, "dds://embodied/kinematics/ik/request?qos=method", "vmsgs.proto.embodied.InverseKinematicsRequest")
VMSGS_MACRO(inverse_kinematics_response, "dds://embodied/kinematics/ik/response?qos=method", "vmsgs.proto.embodied.InverseKinematicsResponse")
VMSGS_MACRO(forward_kinematics_request, "dds://embodied/kinematics/fk/request?qos=method", "vmsgs.proto.embodied.ForwardKinematicsRequest")
VMSGS_MACRO(forward_kinematics_response, "dds://embodied/kinematics/fk/response?qos=method", "vmsgs.proto.embodied.ForwardKinematicsResponse")
VMSGS_MACRO(pickup_request, "dds://embodied/manipulation/pickup?qos=method", "vmsgs.proto.embodied.PickupRequest")
VMSGS_MACRO(pickup_feedback, "dds://embodied/manipulation/pickup/feedback?qos=sensor", "vmsgs.proto.embodied.ManipulationFeedback")
VMSGS_MACRO(pickup_result, "dds://embodied/manipulation/pickup/result?qos=method", "vmsgs.proto.embodied.PickupResult")
VMSGS_MACRO(place_request, "dds://embodied/manipulation/place?qos=method", "vmsgs.proto.embodied.PlaceRequest")
VMSGS_MACRO(place_feedback, "dds://embodied/manipulation/place/feedback?qos=sensor", "vmsgs.proto.embodied.ManipulationFeedback")
VMSGS_MACRO(place_result, "dds://embodied/manipulation/place/result?qos=method", "vmsgs.proto.embodied.PlaceResult")
VMSGS_MACRO(follow_joint_trajectory_goal, "dds://embodied/action/follow_joint_trajectory/goal?qos=method", "vmsgs.proto.embodied.FollowJointTrajectoryGoal")
VMSGS_MACRO(follow_joint_trajectory_goal_response, "dds://embodied/action/follow_joint_trajectory/goal/response?qos=method", "vmsgs.proto.embodied.ActionGoalResponse")
VMSGS_MACRO(follow_joint_trajectory_feedback, "dds://embodied/action/follow_joint_trajectory/feedback?qos=sensor", "vmsgs.proto.embodied.FollowJointTrajectoryFeedback")
VMSGS_MACRO(follow_joint_trajectory_result, "dds://embodied/action/follow_joint_trajectory/result?qos=method", "vmsgs.proto.embodied.FollowJointTrajectoryResult")
VMSGS_MACRO(gripper_goal, "dds://embodied/action/gripper/goal?qos=method", "vmsgs.proto.embodied.GripperGoal")
VMSGS_MACRO(gripper_goal_response, "dds://embodied/action/gripper/goal/response?qos=method", "vmsgs.proto.embodied.ActionGoalResponse")
VMSGS_MACRO(gripper_feedback, "dds://embodied/action/gripper/feedback?qos=sensor", "vmsgs.proto.embodied.GripperFeedback")
VMSGS_MACRO(gripper_result, "dds://embodied/action/gripper/result?qos=method", "vmsgs.proto.embodied.GripperResult")
VMSGS_MACRO(execute_trajectory_goal, "dds://embodied/action/execute_trajectory/goal?qos=method", "vmsgs.proto.embodied.ExecuteTrajectoryGoal")
VMSGS_MACRO(execute_trajectory_goal_response, "dds://embodied/action/execute_trajectory/goal/response?qos=method", "vmsgs.proto.embodied.ActionGoalResponse")
VMSGS_MACRO(execute_trajectory_feedback, "dds://embodied/action/execute_trajectory/feedback?qos=sensor", "vmsgs.proto.embodied.ExecuteTrajectoryFeedback")
VMSGS_MACRO(execute_trajectory_result, "dds://embodied/action/execute_trajectory/result?qos=method", "vmsgs.proto.embodied.ExecuteTrajectoryResult")
VMSGS_MACRO(dynamic_joint_state, "dds://embodied/joint/dynamic_state?qos=sensor", "vmsgs.proto.embodied.DynamicJointState")
VMSGS_MACRO(dynamic_joint_state_fbs, "shm://embodied/joint/dynamic_state", "vmsgs.fbs.embodied.DynamicJointState")
VMSGS_MACRO(joint_jog, "dds://embodied/joint/jog?qos=command", "vmsgs.proto.embodied.JointJog")
VMSGS_MACRO(joint_jog_fbs, "shm://embodied/joint/jog", "vmsgs.fbs.embodied.JointJog")
VMSGS_MACRO(controller_manager_state, "dds://embodied/controller_manager/state?qos=field", "vmsgs.proto.embodied.ControllerManagerState")
VMSGS_MACRO(controller_statistics, "dds://embodied/controller/statistics?qos=sensor", "vmsgs.proto.embodied.ControllerStatistics")

// =========================================================================
//  Natural-language interaction — must-deliver
// =========================================================================
VMSGS_MACRO(nl_instruction, "dds://embodied/nl/instruction", "vmsgs.proto.embodied.NLInstruction")
VMSGS_MACRO(nl_response, "dds://embodied/nl/response?qos=method", "vmsgs.proto.embodied.NLResponse")

// =========================================================================
//  Vision-Language-Action policy I/O — high-rate
// =========================================================================
VMSGS_MACRO(vla_action, "dds://embodied/vla/action?qos=sensor", "vmsgs.proto.embodied.VLAAction")
VMSGS_MACRO(vla_action_zero_copy, "shm://embodied/vla/action", "vmsgs.fbs.embodied.VLAAction")
VMSGS_MACRO(vla_feedback, "dds://embodied/vla/feedback?qos=sensor", "vmsgs.proto.embodied.VLAFeedback")
VMSGS_MACRO(vla_policy_descriptor, "dds://embodied/vla/policy/descriptor?qos=static", "vmsgs.proto.embodied.VLAPolicyDescriptor")
VMSGS_MACRO(vla_inference_request, "dds://embodied/vla/inference/request?qos=method", "vmsgs.proto.embodied.VLAInferenceRequest")
VMSGS_MACRO(vla_inference_result, "dds://embodied/vla/inference/result?qos=method", "vmsgs.proto.embodied.VLAInferenceResult")
VMSGS_MACRO(vla_policy_reset_request, "dds://embodied/vla/policy/reset/request?qos=method", "vmsgs.proto.embodied.VLAPolicyResetRequest")
VMSGS_MACRO(vla_policy_reset_response, "dds://embodied/vla/policy/reset/response?qos=method", "vmsgs.proto.embodied.VLAPolicyResetResponse")
VMSGS_MACRO(episode_step, "shm://embodied/episode/step", "vmsgs.fbs.embodied.EpisodeStep")
VMSGS_MACRO(episode_metadata, "dds://embodied/episode/metadata", "vmsgs.proto.embodied.EpisodeMetadata")
VMSGS_MACRO(robot_embodiment_descriptor, "dds://embodied/robot/descriptor?qos=static", "vmsgs.proto.embodied.RobotEmbodimentDescriptor")

// =========================================================================
//  Teleoperation / haptic — high-rate
// =========================================================================
VMSGS_MACRO(teleop_frame, "dds://embodied/teleop/frame?qos=sensor", "vmsgs.proto.embodied.TeleopFrame")
VMSGS_MACRO(haptic_feedback, "dds://embodied/teleop/haptic?qos=sensor", "vmsgs.proto.embodied.HapticFeedback")

// =========================================================================
//  Bulk multimodal payloads (zero-copy)
// =========================================================================
VMSGS_MACRO(observation_frame, "shm://embodied/observation_frame", "vmsgs.fbs.embodied.ObservationFrame")
VMSGS_MACRO(rgbd_frame, "shm://embodied/rgbd_frame", "vmsgs.fbs.embodied.RGBDFrame")

// Tactile arrays (per-skin-region).
VMSGS_MACRO(tactile_array, "shm://embodied/tactile_array", "vmsgs.fbs.embodied.TactileArray")

}  // namespace vmsg::interface::embodied
