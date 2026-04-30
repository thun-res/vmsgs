/*
 * Copyright (C) 2026 by Thun Lu. All rights reserved.
 * Author: Thun Lu <thun.lu@zohomail.cn>
 */

#include <vlink/extension/schema_plugin_base.h>
#include <vlink/version.h>

#if __has_include("config/version.h")
#include "config/version.h"
#endif

namespace vmsgs {

class SchemaPluginImpl final : public vlink::SchemaPluginBase {
 protected:
  VersionInfo get_version_info() const override {
    VersionInfo info;

    info.name = "vmsgs";

#ifdef VMSGS_VERSION
    info.version = VMSGS_VERSION;
    info.timestamp = VMSGS_VERSION_TIMESTAMP;
    info.tag = VMSGS_VERSION_TAG;
    info.commit_id = VMSGS_VERSION_COMMIT_ID;
#endif

    return info;
  }
};

}  // namespace vmsgs

VLINK_PLUGIN_DECLARE(vmsgs::SchemaPluginImpl, 1, 0);
