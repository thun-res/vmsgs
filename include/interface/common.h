/*
 * Copyright (c) 2026 VMsgs Contributors.
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "../macros.h"

namespace vmsg::interface::common {

// Generic service and action control traffic is reliable.
VMSGS_MACRO(trigger_request, "dds://common/service/trigger/request?qos=method", "vmsgs.proto.common.Empty")
VMSGS_MACRO(trigger_response, "dds://common/service/trigger/response?qos=method", "vmsgs.proto.common.TriggerResponse")
VMSGS_MACRO(set_bool_request, "dds://common/service/set_bool/request?qos=method", "vmsgs.proto.common.SetBoolRequest")
VMSGS_MACRO(set_bool_response, "dds://common/service/set_bool/response?qos=method", "vmsgs.proto.common.SetBoolResponse")
VMSGS_MACRO(goal_status, "dds://common/action/status?qos=field", "vmsgs.proto.common.GoalStatusArray")
VMSGS_MACRO(cancel_goal_request, "dds://common/action/cancel/request?qos=method", "vmsgs.proto.common.CancelGoalRequest")
VMSGS_MACRO(cancel_goal_response, "dds://common/action/cancel/response?qos=method", "vmsgs.proto.common.CancelGoalResponse")

}  // namespace vmsg::interface::common
