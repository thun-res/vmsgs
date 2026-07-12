/*
 * Copyright (c) 2026 VMsgs Contributors.
 * SPDX-License-Identifier: MIT
 *
 * Author: Thun Lu <thun.lu@zohomail.cn>
 */

#pragma once

#include "../macros.h"

// Topics published by the perception layer.

namespace vmsg::interface::perception {

// =========================================================================
//  Object recognition
// =========================================================================
VMSGS_MACRO(detected_objects, "dds://perception/objects/detected?qos=sensor", "vmsgs.proto.perception.DetectedObjects")
VMSGS_MACRO(compact_detected_objects, "shm://perception/objects/detected_compact", "vmsgs.fbs.perception.CompactDetectedObjects")
VMSGS_MACRO(tracked_objects, "dds://perception/objects/tracked?qos=sensor", "vmsgs.proto.perception.TrackedObjects")
VMSGS_MACRO(tracked_objects_fbs, "shm://perception/objects/tracked", "vmsgs.fbs.perception.TrackedObjects")
VMSGS_MACRO(predicted_objects, "dds://perception/objects/predicted?qos=sensor", "vmsgs.proto.perception.PredictedObjects")
VMSGS_MACRO(predicted_objects_fbs, "shm://perception/objects/predicted", "vmsgs.fbs.perception.PredictedObjects")

// =========================================================================
//  Traffic light recognition
// =========================================================================
VMSGS_MACRO(traffic_light_groups, "dds://perception/traffic_light/groups?qos=sensor", "vmsgs.proto.perception.TrafficLightGroupArray")
VMSGS_MACRO(predicted_traffic_light_groups, "dds://perception/traffic_light/predicted_groups?qos=sensor", "vmsgs.proto.perception.PredictedTrafficLightGroupArray")
VMSGS_MACRO(traffic_light_rois, "dds://perception/traffic_light/rois?qos=sensor", "vmsgs.proto.perception.TrafficLightRoiArray")

// =========================================================================
//  Lane / road
// =========================================================================
VMSGS_MACRO(lane_segments, "dds://perception/lane/segments?qos=sensor", "vmsgs.proto.perception.LaneSegments")
VMSGS_MACRO(road_markings, "dds://perception/road/markings?qos=sensor", "vmsgs.proto.perception.RoadMarkingArray")
VMSGS_MACRO(free_space, "dds://perception/free_space?qos=sensor", "vmsgs.proto.perception.FreeSpace")
VMSGS_MACRO(parking_slots, "dds://perception/parking_slots?qos=sensor", "vmsgs.proto.perception.ParkingSlots")
VMSGS_MACRO(parking_slots_zero_copy, "shm://perception/parking_slots", "vmsgs.fbs.perception.ParkingSlots")

// =========================================================================
//  Grid / volumetric outputs (zero-copy)
// =========================================================================
VMSGS_MACRO(occupancy_grid, "shm://perception/occupancy_grid", "vmsgs.fbs.perception.OccupancyGrid")
VMSGS_MACRO(cost_map, "shm://perception/cost_map", "vmsgs.fbs.perception.CostMap")
VMSGS_MACRO(voxel_grid, "shm://perception/voxel_grid", "vmsgs.fbs.perception.VoxelGrid")
VMSGS_MACRO(semantic_image, "shm://perception/semantic_image", "vmsgs.fbs.perception.SemanticImage")

}  // namespace vmsg::interface::perception
