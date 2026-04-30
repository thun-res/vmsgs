/*
 * Copyright (C) 2026 by Thun Lu. All rights reserved.
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
VMSGS_MACRO(joint_trajectory, "dds://embodied/joint/trajectory", JointTrajectory)
VMSGS_MACRO(joint_command, "dds://embodied/joint/command?qos=sensor", JointCommand)
VMSGS_MACRO(multi_dof_joint_trajectory, "dds://embodied/joint/multi_dof_trajectory", MultiDOFJointTrajectory)

// =========================================================================
//  Manipulator state (TCP pose / twist / wrench) — high-rate stream
// =========================================================================
VMSGS_MACRO(manipulator_state, "dds://embodied/manipulator/state?qos=sensor", ManipulatorState)
VMSGS_MACRO(left_manipulator_state, "dds://embodied/manipulator/left/state?qos=sensor", ManipulatorState)
VMSGS_MACRO(right_manipulator_state, "dds://embodied/manipulator/right/state?qos=sensor", ManipulatorState)

// =========================================================================
//  End-effector (Cartesian command / state) — high-rate stream
// =========================================================================
VMSGS_MACRO(end_effector_command, "dds://embodied/end_effector/command?qos=sensor", EndEffectorCommand)
VMSGS_MACRO(end_effector_state, "dds://embodied/end_effector/state?qos=sensor", EndEffectorState)
VMSGS_MACRO(left_end_effector_command, "dds://embodied/end_effector/left/command?qos=sensor", EndEffectorCommand)
VMSGS_MACRO(left_end_effector_state, "dds://embodied/end_effector/left/state?qos=sensor", EndEffectorState)
VMSGS_MACRO(right_end_effector_command, "dds://embodied/end_effector/right/command?qos=sensor", EndEffectorCommand)
VMSGS_MACRO(right_end_effector_state, "dds://embodied/end_effector/right/state?qos=sensor", EndEffectorState)

// =========================================================================
//  Gripper — command must-deliver, state high-rate
// =========================================================================
VMSGS_MACRO(gripper_command, "dds://embodied/gripper/command", GripperCommand)
VMSGS_MACRO(gripper_state, "dds://embodied/gripper/state?qos=sensor", GripperState)
VMSGS_MACRO(left_gripper_command, "dds://embodied/gripper/left/command", GripperCommand)
VMSGS_MACRO(left_gripper_state, "dds://embodied/gripper/left/state?qos=sensor", GripperState)
VMSGS_MACRO(right_gripper_command, "dds://embodied/gripper/right/command", GripperCommand)
VMSGS_MACRO(right_gripper_state, "dds://embodied/gripper/right/state?qos=sensor", GripperState)

// =========================================================================
//  Whole-body / mobile base — high-rate stream
// =========================================================================
VMSGS_MACRO(robot_state, "dds://embodied/robot_state?qos=sensor", RobotState)
VMSGS_MACRO(locomotion_command, "dds://embodied/locomotion/command?qos=sensor", LocomotionCommand)
VMSGS_MACRO(locomotion_state, "dds://embodied/locomotion/state?qos=sensor", LocomotionState)

// =========================================================================
//  Skill / task orchestration — request/result must-deliver, feedback high-rate
// =========================================================================
VMSGS_MACRO(skill_request, "dds://embodied/skill/request", SkillRequest)
VMSGS_MACRO(skill_feedback, "dds://embodied/skill/feedback?qos=sensor", SkillFeedback)
VMSGS_MACRO(skill_result, "dds://embodied/skill/result", SkillResult)
VMSGS_MACRO(task_request, "dds://embodied/task/request", Task)
VMSGS_MACRO(task_feedback, "dds://embodied/task/feedback?qos=sensor", TaskFeedback)

// =========================================================================
//  Natural-language interaction — must-deliver
// =========================================================================
VMSGS_MACRO(nl_instruction, "dds://embodied/nl/instruction", NLInstruction)
VMSGS_MACRO(nl_response, "dds://embodied/nl/response", NLResponse)

// =========================================================================
//  Vision-Language-Action policy I/O — high-rate
// =========================================================================
VMSGS_MACRO(vla_action, "dds://embodied/vla/action?qos=sensor", VLAAction)
VMSGS_MACRO(vla_feedback, "dds://embodied/vla/feedback?qos=sensor", VLAFeedback)

// =========================================================================
//  Teleoperation / haptic — high-rate
// =========================================================================
VMSGS_MACRO(teleop_frame, "dds://embodied/teleop/frame?qos=sensor", TeleopFrame)
VMSGS_MACRO(haptic_feedback, "dds://embodied/teleop/haptic?qos=sensor", HapticFeedback)

// =========================================================================
//  Bulk multimodal payloads (zero-copy)
// =========================================================================
VMSGS_MACRO(observation_frame, "shm://embodied/observation_frame", ObservationFrame)
VMSGS_MACRO(rgbd_frame, "shm://embodied/rgbd_frame", RGBDFrame)
VMSGS_MACRO(rgbd_frame_head, "shm://embodied/rgbd_frame/head", RGBDFrame)
VMSGS_MACRO(rgbd_frame_left_wrist, "shm://embodied/rgbd_frame/left_wrist", RGBDFrame)
VMSGS_MACRO(rgbd_frame_right_wrist, "shm://embodied/rgbd_frame/right_wrist", RGBDFrame)

// Tactile arrays (per-skin-region).
VMSGS_MACRO(tactile_array, "shm://embodied/tactile_array", TactileArray)
VMSGS_MACRO(left_tactile_array, "shm://embodied/tactile_array/left", TactileArray)
VMSGS_MACRO(right_tactile_array, "shm://embodied/tactile_array/right", TactileArray)

}  // namespace vmsg::interface::embodied
