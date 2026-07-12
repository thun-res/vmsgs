/*
 * Copyright (c) 2026 VMsgs Contributors.
 * SPDX-License-Identifier: MIT
 *
 * Author: Thun Lu <thun.lu@zohomail.cn>
 */

#pragma once

#include "../macros.h"

namespace vmsg::interface::visualization {

// Marker arrays carry incremental add/delete operations, so loss may leave stale
// persistent geometry. Reliable event QoS preserves lifecycle ordering.
VMSGS_MACRO(markers, "dds://visualization/markers?qos=event", "vmsgs.proto.visualization.MarkerArray")
VMSGS_MACRO(image_markers, "dds://visualization/image_markers?qos=event", "vmsgs.proto.visualization.ImageMarker")

// Initialization is latched latest-state data; updates and feedback are reliable events.
VMSGS_MACRO(interactive_marker_init, "dds://visualization/interactive/init?qos=field", "vmsgs.proto.visualization.InteractiveMarkerInit")
VMSGS_MACRO(interactive_marker_update, "dds://visualization/interactive/update?qos=event", "vmsgs.proto.visualization.InteractiveMarkerUpdate")
VMSGS_MACRO(interactive_marker_feedback, "dds://visualization/interactive/feedback?qos=event", "vmsgs.proto.visualization.InteractiveMarkerFeedback")

}  // namespace vmsg::interface::visualization
