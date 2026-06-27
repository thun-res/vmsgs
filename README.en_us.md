# VMsgs

![](https://img.shields.io/badge/version-v1.0.0-informational.svg) ![](https://img.shields.io/badge/language-C++17-informational.svg) ![](https://img.shields.io/badge/license-MIT-informational.svg)

English | [中文](README.md)

**VMsgs** is the standard message-definition repository that accompanies the [VLink](https://github.com/thun-res/vlink) communication middleware. Targeting autonomous driving and embodied intelligence, it provides a set of type-safe message models spanning perception, planning, localization, control, map, vehicle, system, V2X and more — together with the standard topic (Topic / URL) conventions that go with them — so that upstream and downstream modules communicate through a single shared contract instead of each redefining its own data structures.

The current release ships **13 domains** and **174 schema files** (151 Protobuf, 23 FlatBuffers), built as the C++ library `vlink::vmsgs` that business projects can link directly.

---

## 🧩 Design Philosophy: Messages Are Contracts

VLink's central abstraction is "communication model + URL + core method", and the **message type** together with the **topic URL** form the contract between modules. VMsgs consolidates both into a single repository:

- **Data structures** — Protobuf / FlatBuffers define cross-language, backward-compatible message models;
- **Topic conventions** — a set of `VMSGS_MACRO` declarations expose each standard topic's URL (backend prefix + QoS), so both ends reference one shared constant rather than scattered string literals.

A module simply `#include`s the interface header for its domain to obtain strongly-typed messages and the authoritative topic addresses, eliminating type drift and topic typos.

---

## 📦 Message Domains

Schemas live under `schemas/`, organized by domain, in the namespaces `vmsgs.proto.<domain>` / `vmsgs.fbs.<domain>`:

| Domain | Directory | Overview |
| --- | --- | --- |
| common | `schemas/common/` | Header, timestamps, UUID, status codes, version, key-value, metrics |
| geometry | `schemas/geometry/` | Point / Pose / Twist / Accel / Quaternion / Transform / Polygon, etc. |
| tf2 | `schemas/tf2/` | TF transform messages and error codes |
| sensor | `schemas/sensor/` | Image / point cloud / IMU / GNSS / radar / lidar / audio-video raw data |
| perception | `schemas/perception/` | Detected/tracked/predicted objects, traffic lights, lanes, free space, occupancy grid |
| localization | `schemas/localization/` | Odometry, kinematic state, EKF state, initialization and quality |
| map | `schemas/map/` | Lanelet map, point-cloud map, elevation map, occupancy-grid map and metadata |
| planning | `schemas/planning/` | Route, path, trajectory, behavior state, mission, avoidance, velocity limits, etc. |
| control | `schemas/control/` | Ackermann command, lateral/longitudinal control, control horizon, operation mode |
| vehicle | `schemas/vehicle/` | Velocity/steering/gear/brake reports, lights, doors, kinematics, etc. |
| system | `schemas/system/` | Diagnostics, heartbeat, MRM, emergency state, resource usage, logs |
| v2x | `schemas/v2x/` | V2X messages, cooperative status, virtual traffic light, infrastructure command |
| embodied | `schemas/embodied/` | Joint trajectory, manipulator/end-effector, skill, VLA action, tactile, RGBD/observation frame |

**Choosing a Serialization Format:**

- **Protobuf** — for structured, frequently-evolving control and semantic messages, balancing cross-language ecosystem support and backward compatibility;
- **FlatBuffers** — for large, zero-copy data streams such as images, point clouds, grids and voxels (`image.fbs`, `point_cloud2.fbs`, `occupancy_grid.fbs`, `cost_map.fbs`), pairing with VLink's `shm://` backend for same-host zero-copy transport.

> For large data streams, **prefer FlatBuffers** to take full advantage of VLink's `shm://` zero-copy backend and avoid serialization and memory-copy overhead.

---

## 🔗 Standard Topic Interface

Each domain under `include/interface/` provides a header that declares URL accessors for all of that domain's standard topics via `VMSGS_MACRO`. The accessors live in the `vmsg::interface::<domain>` namespace and return a `constexpr std::string_view` — zero-overhead and directly usable when constructing VLink primitives.

```cpp
#include <vmsgs/interface/perception.h>
#include <vmsgs/perception/tracked_object.pb.h>

using namespace vmsg::interface;

// The topic URL (backend prefix + path + QoS) is defined once, by VMsgs
vlink::Publisher<vmsgs::proto::perception::TrackedObjects> pub(perception::tracked_objects());
//  => "dds://perception/objects/tracked?qos=sensor"

vlink::Subscriber<vmsgs::proto::perception::TrackedObjects> sub(perception::tracked_objects());
sub.listen([](const auto& msg) { process(msg); });
```

Topics follow the `<scheme>://<domain>/<path>[?qos=...]` convention: high-rate perception/state data uses `dds://`, while grids, voxels and images use `shm://` for zero-copy.

Macro definitions are in `include/macros.h`: `VMSGS_MACRO` generates the `constexpr` accessor, while `VMSGS_MACRO_STR` / `VMSGS_MACRO_IMPL` provide a stable `const std::string&` reference variant.

---

## 🚀 Quick Start

The recommended path is a one-command build with [VKit](https://github.com/thun-res/vkit), which fetches both `vmsgs` and `vlink` and performs cross-platform build and packaging:

```bash
git clone https://github.com/thun-res/vkit.git && cd vkit
make import_full      # fetch middleware sources: vmsgs and vlink
make                  # build, deploy and produce the runtime package
```

You can also integrate it standalone into an existing CMake project. VMsgs depends on vlink, Protobuf and FlatBuffers, and produces the `vlink::vmsgs` target:

```cmake
find_package(vmsgs REQUIRED)
target_link_libraries(my_app PRIVATE vlink::vmsgs)
```

At build time VMsgs uses `vlink_generate_cpp` to automatically compile the `.proto` / `.fbs` files under `schemas/` into C++ headers, which are installed alongside the library.

| Build Option | Default | Description |
| --- | :---: | --- |
| `ENABLE_PROTOBUF` | ON | Compile and link Protobuf schemas |
| `ENABLE_FLATBUFFERS` | ON | Compile and link FlatBuffers schemas and their registry |
| `BUILD_SHARED_LIBS` | ON | Build shared libraries |

> `ENABLE_PROTOBUF` and `ENABLE_FLATBUFFERS` cannot both be disabled.

---

## 🔌 Integration with VLink

VMsgs implements `vlink::SchemaPluginBase` in `src/schema_plugin_impl.cc`, registering itself as a **schema plugin** with VLink. This lets VLink's CLI tools, Viewer, and record/replay components recognize VMsgs' version information and message types. FlatBuffers schemas additionally generate a type registry (`fbs_registry.cc`) for resolving messages by name at runtime.

---

## 📁 Project Structure

```
vmsgs/
├── schemas/          message definitions for 13 domains (.proto / .fbs)
│   ├── common/       base types (Header, time, UUID, status…)
│   ├── geometry/     geometric primitives
│   ├── sensor/       raw sensor data
│   ├── perception/   perception results
│   ├── localization/ localization and odometry
│   ├── map/          maps and metadata
│   ├── planning/     planning and trajectories
│   ├── control/      control commands
│   ├── vehicle/      vehicle status and actuation
│   ├── system/       system / diagnostics / MRM
│   ├── v2x/          vehicle-to-everything
│   ├── embodied/     embodied intelligence
│   └── tf2/          coordinate transforms
├── include/
│   ├── macros.h      topic-URL accessor macros
│   └── interface/    standard topic declarations per domain
├── src/              source (VLink schema plugin implementation)
├── tools/            formatting and checking scripts
├── cmake/            build helpers (version.h.in, etc.)
├── CMakeLists.txt    top-level CMake entry
└── version.txt       version number
```

---

## 🤝 Contributing

VMsgs is maintained by Thun Lu. When adding or changing messages, please follow these conventions:

- Place schemas in the matching domain directory, keeping the package name aligned with the directory (`vmsgs.proto.<domain>`);
- Only append field numbers — never reuse them — to preserve backward compatibility;
- Prefer FlatBuffers over `shm://` for large data streams;
- When adding a standard topic, add a `VMSGS_MACRO` declaration to the corresponding `include/interface/<domain>.h`;
- Run `tools/format.sh` and `tools/check.sh` before submitting for formatting and static checks.

## 📜 License

[MIT License](LICENSE) — free for commercial use.

Copyright (c) 2026 VMsgs Contributors.
