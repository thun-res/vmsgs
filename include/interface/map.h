/*
 * Copyright (C) 2026 by Thun Lu. All rights reserved.
 * Author: Thun Lu <thun.lu@zohomail.cn>
 */

#pragma once

#include "../macros.h"

namespace vmsg::interface::map {

// =========================================================================
//  Bulk map blobs (zero-copy)
// =========================================================================
VMSGS_MACRO(lanelet_map_bin, "shm://map/lanelet_map_bin", LaneletMapBin)
VMSGS_MACRO(point_cloud_map, "shm://map/point_cloud_map", PointCloudMap)
VMSGS_MACRO(occupancy_grid_map, "shm://map/occupancy_grid_map", OccupancyGridMap)
VMSGS_MACRO(elevation_map, "shm://map/elevation_map", ElevationMap)

// =========================================================================
//  Map metadata / structure — published once, must-deliver
// =========================================================================
VMSGS_MACRO(meta_data, "dds://map/meta_data", MapMetaData)
VMSGS_MACRO(projector_info, "dds://map/projector_info", MapProjectorInfo)
VMSGS_MACRO(hd_map_primitives, "dds://map/hd_map_primitives", HDMapPrimitives)
VMSGS_MACRO(lanelet_map_meta, "dds://map/lanelet_map_meta", LaneletMapMetaData)
VMSGS_MACRO(point_cloud_map_meta, "dds://map/point_cloud_map_meta", PointCloudMapMetaData)

}  // namespace vmsg::interface::map
