/*
 * Copyright (c) 2026 VMsgs Contributors.
 * SPDX-License-Identifier: MIT
 *
 * Author: Thun Lu <thun.lu@zohomail.cn>
 */

#pragma once

#include "../macros.h"

namespace vmsg::interface::map {

// =========================================================================
//  Bulk map blobs (zero-copy)
// =========================================================================
VMSGS_MACRO(lanelet_map_bin, "shm://map/lanelet_map_bin?qos=static", "vmsgs.fbs.map.LaneletMapBin")
VMSGS_MACRO(point_cloud_map, "shm://map/point_cloud_map?qos=static", "vmsgs.fbs.map.PointCloudMap")
VMSGS_MACRO(occupancy_grid_map, "shm://map/occupancy_grid_map?qos=static", "vmsgs.fbs.map.OccupancyGridMap")
VMSGS_MACRO(elevation_map, "shm://map/elevation_map?qos=static", "vmsgs.fbs.map.ElevationMap")
VMSGS_MACRO(occupancy_grid, "dds://map/occupancy_grid?qos=static", "vmsgs.proto.map.OccupancyGrid")

// Incremental patches must be reliable and ordered; dropping one patch corrupts
// the consumer's reconstructed map, so this intentionally does not use sensor QoS.
VMSGS_MACRO(occupancy_grid_update, "dds://map/occupancy_grid/update", "vmsgs.proto.map.OccupancyGridUpdate")

// =========================================================================
//  Map metadata / structure — published once, must-deliver
// =========================================================================
VMSGS_MACRO(meta_data, "dds://map/meta_data?qos=static", "vmsgs.proto.map.MapMetaData")
VMSGS_MACRO(projector_info, "dds://map/projector_info?qos=static", "vmsgs.proto.map.MapProjectorInfo")
VMSGS_MACRO(hd_map_primitives, "dds://map/hd_map_primitives?qos=static", "vmsgs.proto.map.HDMapPrimitives")
VMSGS_MACRO(lanelet_map_meta, "dds://map/lanelet_map_meta?qos=static", "vmsgs.proto.map.LaneletMapMetaData")
VMSGS_MACRO(point_cloud_map_meta, "dds://map/point_cloud_map_meta?qos=static", "vmsgs.proto.map.PointCloudMapMetaData")
VMSGS_MACRO(point_cloud_map_cell, "dds://map/point_cloud_map_cell?qos=static", "vmsgs.proto.map.PointCloudMapCellWithID")

// =========================================================================
//  Map server methods — reliable request/response
// =========================================================================
VMSGS_MACRO(get_occupancy_grid_request, "dds://map/service/get_occupancy_grid/request?qos=method", "vmsgs.proto.map.GetOccupancyGridRequest")
VMSGS_MACRO(get_occupancy_grid_response, "dds://map/service/get_occupancy_grid/response?qos=method", "vmsgs.proto.map.GetOccupancyGridResponse")
VMSGS_MACRO(get_point_cloud_tiles_request, "dds://map/service/get_point_cloud_tiles/request?qos=method", "vmsgs.proto.map.GetPointCloudMapTilesRequest")
VMSGS_MACRO(get_point_cloud_tiles_response, "dds://map/service/get_point_cloud_tiles/response?qos=method", "vmsgs.proto.map.GetPointCloudMapTilesResponse")

}  // namespace vmsg::interface::map
