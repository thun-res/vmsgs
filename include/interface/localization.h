/*
 * Copyright (c) 2026 VMsgs Contributors.
 * SPDX-License-Identifier: MIT
 *
 * Author: Thun Lu <thun.lu@zohomail.cn>
 */

#pragma once

#include "../macros.h"

namespace vmsg::interface::localization {

VMSGS_MACRO(odometry_zero_copy, "shm://localization/odometry", "vmsgs.fbs.localization.Odometry")

// =========================================================================
//  Ego-motion outputs
// =========================================================================
VMSGS_MACRO(odometry, "dds://localization/odometry?qos=sensor", "vmsgs.proto.localization.Odometry")
VMSGS_MACRO(kinematic_state, "dds://localization/kinematic_state?qos=sensor", "vmsgs.proto.localization.KinematicState")

// =========================================================================
//  Initialization
// =========================================================================
VMSGS_MACRO(initial_pose, "dds://localization/initial_pose", "vmsgs.proto.localization.InitialPose")
VMSGS_MACRO(initialization_state, "dds://localization/initialization_state", "vmsgs.proto.localization.LocalizationInitializationState")
VMSGS_MACRO(relocalization_request, "dds://localization/relocalization/request", "vmsgs.proto.localization.RelocalizationRequest")
VMSGS_MACRO(relocalization_progress, "dds://localization/relocalization/progress?qos=sensor", "vmsgs.proto.localization.RelocalizationProgress")
VMSGS_MACRO(relocalization_result, "dds://localization/relocalization/result", "vmsgs.proto.localization.RelocalizationResult")

// =========================================================================
//  Quality / health
// =========================================================================
VMSGS_MACRO(localization_quality, "dds://localization/quality?qos=sensor", "vmsgs.proto.localization.LocalizationQuality")
VMSGS_MACRO(scan_matching_status, "dds://localization/scan_matching/status?qos=sensor", "vmsgs.proto.localization.ScanMatchingStatus")

// =========================================================================
//  SLAM graph / loop closure — graph snapshot durable, status high-rate
// =========================================================================
VMSGS_MACRO(pose_graph_snapshot, "dds://localization/slam/pose_graph/snapshot?qos=static", "vmsgs.proto.localization.PoseGraph")
VMSGS_MACRO(pose_graph_update, "dds://localization/slam/pose_graph/update", "vmsgs.proto.localization.PoseGraph")
VMSGS_MACRO(loop_closure, "dds://localization/slam/loop_closure", "vmsgs.proto.localization.LoopClosure")
VMSGS_MACRO(slam_status, "dds://localization/slam/status?qos=sensor", "vmsgs.proto.localization.SlamStatus")

}  // namespace vmsg::interface::localization
