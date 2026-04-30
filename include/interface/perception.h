/*
 * Copyright (C) 2026 by Thun Lu. All rights reserved.
 * Author: Thun Lu <thun.lu@zohomail.cn>
 */

#pragma once

#include "../macros.h"

// Topics published by the perception layer.

namespace vmsg::interface::perception {

// =========================================================================
//  Object recognition
// =========================================================================
VMSGS_MACRO(detected_objects, "dds://perception/objects/detected?qos=sensor", DetectedObjects)
VMSGS_MACRO(tracked_objects, "dds://perception/objects/tracked?qos=sensor", TrackedObjects)
VMSGS_MACRO(predicted_objects, "dds://perception/objects/predicted?qos=sensor", PredictedObjects)

// Debug variants carrying upstream feature blobs (clusters, indices, patches).
VMSGS_MACRO(detected_objects_with_feature, "dds://perception/objects/detected_with_feature?qos=sensor", DetectedObjectsWithFeature)
VMSGS_MACRO(tracked_objects_with_feature, "dds://perception/objects/tracked_with_feature?qos=sensor", TrackedObjectsWithFeature)

// =========================================================================
//  Traffic light recognition
// =========================================================================
VMSGS_MACRO(traffic_light_groups, "dds://perception/traffic_light/groups?qos=sensor", TrafficLightGroupArray)
VMSGS_MACRO(predicted_traffic_light_groups, "dds://perception/traffic_light/predicted_groups?qos=sensor", PredictedTrafficLightGroupArray)
VMSGS_MACRO(traffic_light_rois, "dds://perception/traffic_light/rois?qos=sensor", TrafficLightRoiArray)

// =========================================================================
//  Lane / road
// =========================================================================
VMSGS_MACRO(lane_segments, "dds://perception/lane/segments?qos=sensor", LaneSegments)
VMSGS_MACRO(road_markings, "dds://perception/road/markings?qos=sensor", RoadMarkingArray)
VMSGS_MACRO(free_space, "dds://perception/free_space?qos=sensor", FreeSpace)

// =========================================================================
//  Grid / volumetric outputs (zero-copy)
// =========================================================================
VMSGS_MACRO(occupancy_grid, "shm://perception/occupancy_grid", OccupancyGrid)
VMSGS_MACRO(cost_map, "shm://perception/cost_map", CostMap)
VMSGS_MACRO(voxel_grid, "shm://perception/voxel_grid", VoxelGrid)
VMSGS_MACRO(semantic_image, "shm://perception/semantic_image", SemanticImage)

}  // namespace vmsg::interface::perception
