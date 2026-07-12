/*
 * Copyright (c) 2026 VMsgs Contributors.
 * SPDX-License-Identifier: MIT
 *
 * Author: Thun Lu <thun.lu@zohomail.cn>
 */

#pragma once

#include "../macros.h"

namespace vmsg::interface::navigation {

// High-rate local navigation output.
VMSGS_MACRO(path, "dds://navigation/path?qos=sensor", "vmsgs.proto.navigation.NavigationPath")

// Goal updates are discrete and must be delivered reliably.
VMSGS_MACRO(goals, "dds://navigation/goals?qos=command", "vmsgs.proto.navigation.Goals")

// Local planner/debug grid, where newest data wins.
VMSGS_MACRO(grid_cells, "dds://navigation/grid_cells?qos=sensor", "vmsgs.proto.navigation.GridCells")

}  // namespace vmsg::interface::navigation
