# VMsgs

![](https://img.shields.io/badge/version-v2.0.0-informational.svg) ![](https://img.shields.io/badge/language-C++17-informational.svg) ![](https://img.shields.io/badge/license-MIT-informational.svg)

[English](README.en_us.md) | 中文

**VMsgs** 是 [VLink](https://github.com/thun-res/vlink) 通信中间件配套的标准消息定义中心仓库。它面向自动驾驶与具身智能，提供一套覆盖感知、规划、定位、控制、地图、车辆、系统、车联网等领域的类型安全消息模型，以及与之配套的标准话题（Topic / URL）约定，使上下游模块以统一的契约通信，无需各自重复定义数据结构。

当前版本提供 16 个领域、237 个 schema 文件（178 个 Protobuf、59 个 FlatBuffers），并以 C++ 库 `vlink::vmsgs` 的形式产出，可直接被业务工程链接使用。

---

## 🧩 设计理念：消息即契约

VLink 的核心抽象是"通信模型 + URL + 核心方法"，而 **消息类型** 与 **话题 URL** 共同构成了模块间的通信契约。VMsgs 将这两部分统一收敛到一个仓库中：

- **数据结构**：用 Protobuf / FlatBuffers 定义跨语言、向后兼容的消息模型；
- **话题约定**：用一组 `VMSGS_MACRO` 声明每个标准话题的 URL（含后端前缀与 QoS），让收发两端引用同一份常量而非散落的字符串字面量。

由此，模块只需 `#include` 对应领域的接口头，即可拿到强类型消息与权威话题地址，避免类型漂移与话题拼写错误。

---

## 📦 消息领域

schema 按领域分目录组织于 `schemas/`，命名空间为 `vmsgs.proto.<domain>` / `vmsgs.fbs.<domain>`：

| 领域 | 目录 | 内容概要 |
| --- | --- | --- |
| 基础 common | `schemas/common/` | Header、时间戳、UUID、状态码、版本、键值对、度量 |
| 几何 geometry | `schemas/geometry/` | Point / Pose / Twist / Accel / Quaternion / Transform / Polygon 等 |
| 坐标 tf2 | `schemas/tf2/` | TF 变换消息与错误码 |
| 传感 sensor | `schemas/sensor/` | 图像/点云/IMU/GNSS/雷达/激光/音视频等原始传感数据 |
| 感知 perception | `schemas/perception/` | 检测/跟踪/预测目标、交通灯、车道、可行驶区域、占据栅格 |
| 定位 localization | `schemas/localization/` | 里程计、运动状态、初始化、定位质量、扫描匹配与重定位 |
| 地图 map | `schemas/map/` | Lanelet 地图、点云地图、高程图、占据栅格地图与元数据 |
| 规划 planning | `schemas/planning/` | 路由、路径、轨迹、行为状态、任务、避让、限速等 |
| 控制 control | `schemas/control/` | Ackermann 指令、横/纵向控制、控制时域、运行模式 |
| 车辆 vehicle | `schemas/vehicle/` | 速度/转向/挡位/制动报告与灯光、车门、运动学等 |
| 系统 system | `schemas/system/` | 诊断、心跳、MRM、紧急状态、资源占用、日志 |
| 车联网 v2x | `schemas/v2x/` | V2X 消息、协同状态、虚拟交通灯、基础设施指令 |
| 具身 embodied | `schemas/embodied/` | 关节轨迹、机械臂/末端执行器、技能、VLA 动作、触觉、RGBD/观测帧 |
| 导航 navigation | `schemas/navigation/` | 几何路径、导航目标与稀疏栅格单元 |
| 形状 shape | `schemas/shape/` | 碰撞体、三角网格、平面与实体基元 |
| 可视化 visualization | `schemas/visualization/` | Marker 与批量可视化图元 |

**序列化格式选型：**

- **Protobuf**：用于结构化、字段演进频繁的控制流与语义消息，兼顾跨语言生态与向后兼容；
- **FlatBuffers**：用于图像、点云、栅格、体素等大体量、零拷贝场景的数据流（如 `image.fbs`、`point_cloud2.fbs`、`occupancy_grid.fbs`、`cost_map.fbs`），配合 VLink 的 `shm://` 后端实现同机零拷贝传输。

> 对于大体量数据流，**优先使用 FlatBuffers**，以充分发挥 VLink `shm://` 后端的零拷贝能力，避免序列化与内存拷贝开销。

---

## 🔗 标准话题接口

`include/interface/` 下每个领域提供一个头文件，通过 `VMSGS_MACRO` 声明该领域所有标准话题的 URL 访问器。访问器位于 `vmsg::interface::<domain>` 命名空间，返回 `constexpr std::string_view`，零开销、可直接用于 VLink 的原语构造。

```cpp
#include <vmsgs/interface/perception.h>
#include <vmsgs/perception/tracked_object.pb.h>

using namespace vmsg::interface;

// 话题 URL（后端前缀 + 路径 + QoS）由 VMsgs 统一约定
vlink::Publisher<vmsgs::proto::perception::TrackedObjects> pub(perception::tracked_objects());
//  => "dds://perception/objects/tracked?qos=sensor"

vlink::Subscriber<vmsgs::proto::perception::TrackedObjects> sub(perception::tracked_objects());
sub.listen([](const auto& msg) { process(msg); });
```

话题约定遵循 `<scheme>://<domain>/<path>[?qos=...]` 规范：高频感知/状态数据使用 `dds://`，栅格/体素/图像等大块数据使用 `shm://` 零拷贝。

宏定义见 `include/macros.h`：`VMSGS_MACRO` 生成 `constexpr` 访问器，`VMSGS_MACRO_STR` / `VMSGS_MACRO_IMPL` 提供返回 `const std::string&` 的稳定引用变体。

---

## 🚀 快速开始

推荐使用 [VKit](https://github.com/thun-res/vkit) 一键构建，VKit 会自动拉取 `vmsgs` 与 `vlink` 并完成跨平台编译与打包：

```bash
git clone https://github.com/thun-res/vkit.git && cd vkit
make import_full      # 拉取 middleware 源码：vmsgs 与 vlink
make                  # 编译、部署并生成 runtime 包
```

亦可在已有 CMake 工程中单独集成。VMsgs 依赖 vlink、Protobuf 与 FlatBuffers，构建产物为 `vlink::vmsgs`：

```cmake
find_package(vmsgs REQUIRED)
target_link_libraries(my_app PRIVATE vlink::vmsgs)
```

构建时 VMsgs 会通过 `vlink_generate_cpp` 自动将 `schemas/` 下的 `.proto` / `.fbs` 编译为 C++ 头文件，并随库一同安装。

| 构建选项 | 默认 | 说明 |
| --- | :---: | --- |
| `ENABLE_PROTOBUF` | ON | 编译并链接 Protobuf schema |
| `ENABLE_FLATBUFFERS` | ON | 编译并链接 FlatBuffers schema 及其注册表 |
| `ENABLE_BAG_PLUGIN` | ON | 构建 bag 消息时间重排插件 |
| `BUILD_SHARED_LIBS` | ON | 构建动态库 |

> `ENABLE_PROTOBUF` 与 `ENABLE_FLATBUFFERS` 不可同时关闭。

Windows 共享构建应通过 `vmsgs::vmsgs` 或 `vlink::vmsgs` 目标链接，以传递生成 Protobuf 类型所需的 DLL 导入定义。

---

## 🔌 与 VLink 的集成

VMsgs 通过 `src/schema_plugin_impl.cc` 实现 `vlink::SchemaPluginBase`，向 VLink 注册为 **schema 插件**，使 VLink 的 CLI 工具、Viewer 与录制回放等组件能够识别 VMsgs 的版本信息与消息类型。FlatBuffers schema 额外生成类型注册表（`fbs_registry.cc`），供运行时按名解析消息。

`plugins/bag/` 提供可选的 bag 消息时间重排插件，动态读取已加载的 VMsgs schema，并支持 VLink ZeroCopy PointCloud 消息。

---

## 📁 项目结构

```
vmsgs/
├── schemas/          16 个领域的消息定义（.proto / .fbs）
│   ├── common/       基础类型（Header、时间、UUID、状态…）
│   ├── geometry/     几何基元
│   ├── sensor/       原始传感数据
│   ├── perception/   感知结果
│   ├── localization/ 定位与里程计
│   ├── map/          地图与元数据
│   ├── planning/     规划与轨迹
│   ├── control/      控制指令
│   ├── vehicle/      车辆状态与执行
│   ├── system/       系统/诊断/MRM
│   ├── v2x/          车联网
│   ├── embodied/     具身智能
│   ├── navigation/   导航路径与目标
│   ├── shape/        通用形状与碰撞几何
│   ├── visualization/ 可视化图元
│   └── tf2/          坐标变换
├── include/
│   ├── macros.h      话题 URL 访问器宏
│   └── interface/    各领域标准话题声明
├── src/              源码（VLink schema 插件实现）
├── plugins/bag/      bag 消息时间重排插件
├── tools/            格式化与检查脚本
├── cmake/            构建辅助（version.h.in 等）
├── CMakeLists.txt    顶层 CMake 入口
└── version.txt       版本号
```

---

## 🤝 贡献

VMsgs 由 Thun Lu 维护。新增或修改消息时请遵循以下约定：

- schema 置于对应领域目录，包名与目录保持一致（`vmsgs.proto.<domain>`）；
- 字段编号仅追加、不复用，保证向后兼容；
- 大体量数据流优先使用 FlatBuffers 并走 `shm://`；
- 新增标准话题时，在对应 `include/interface/<domain>.h` 中补充 `VMSGS_MACRO` 声明；
- 提交前运行 `tools/format.sh` 与 `tools/check.sh` 进行格式化与静态检查。

## 📜 许可证

[MIT License](LICENSE) —— 可自由用于商业项目。

Copyright (c) 2026 VMsgs Contributors.
