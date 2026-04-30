/*
 * Copyright (C) 2026 by Thun Lu. All rights reserved.
 * Author: Thun Lu <thun.lu@zohomail.cn>
 */

#pragma once

#include "../macros.h"

namespace vmsg::interface::tf2 {

// Dynamic transform tree, broadcast at high rate — drop-OK.
VMSGS_MACRO(tf, "dds://tf?qos=sensor", TFMessage)

// Static transforms — published once at startup, must-deliver.
VMSGS_MACRO(tf_static, "dds://tf_static", TFMessage)

}  // namespace vmsg::interface::tf2
