/*
 * Copyright (C) 2026 by Thun Lu. All rights reserved.
 * Author: Thun Lu <thun.lu@zohomail.cn>
 */

#pragma once

#include "../macros.h"

namespace vmsg::interface::localization {

// =========================================================================
//  Ego-motion outputs
// =========================================================================
VMSGS_MACRO(odometry, "dds://localization/odometry?qos=sensor", Odometry)
VMSGS_MACRO(kinematic_state, "dds://localization/kinematic_state?qos=sensor", KinematicState)
VMSGS_MACRO(ekf_state, "dds://localization/ekf_state?qos=sensor", EkfState)

// =========================================================================
//  Initialization
// =========================================================================
VMSGS_MACRO(initial_pose, "dds://localization/initial_pose?qos=sensor", InitialPose)
VMSGS_MACRO(initialization_state, "dds://localization/initialization_state?qos=sensor", LocalizationInitializationState)

// =========================================================================
//  Quality / health
// =========================================================================
VMSGS_MACRO(localization_quality, "dds://localization/quality?qos=sensor", LocalizationQuality)
VMSGS_MACRO(lidar_pose_accuracy, "dds://localization/lidar_pose_accuracy?qos=sensor", LidarPoseAccuracy)

}  // namespace vmsg::interface::localization
