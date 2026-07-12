# 更新日志

## v2.0.0（2026/07/12）

> 注意：v1.x 数据与 v2.x schema 不互通，历史数据需先离线迁移，节点不可 1.x/2.x 混部。

### 类型与语义

- 绝对时间戳统一为 `uint64` 纳秒；相对时间量（间隔、超时、生命周期、偏移、步长）统一用
  `common/duration.proto`（FlatBuffers 用 `_ns`），删除 `time.proto`、`published_time.proto`。
- 服务与结果响应统一用 `common.Status`；合并 `ResponseStatus`、空 Trigger 请求，删除与
  `Twist` 重复的 `Velocity`。
- 重命名与收敛：`AutowareState`→`AutonomyLifecycleState`（补 mission/暂停/空闲/错误态）、
  `LidarPoseAccuracy`→`ScanMatchingStatus`、`EkfState`→`KinematicState`、`VehicleStatus`→`ChassisInfo`，
  V2X operator API 迁至 system 域。
- 枚举规范化：零值表示未知/未选择并避免跨域同名；合并 `NavSatStatus`、`CameraInfo` 同义枚举；
  `GateMode`、雷达运动状态、深度/音频格式补零值哨兵。
- 逐文件明确字段单位、范围、数组对齐与枚举语义；公共 schema 不含具体框架、算法或厂商实现名称。

### 消息扩展

- 新增 navigation、shape、visualization 域；补充通用几何、标定、图像、PointCloud2、停车位、
  多维数组、service/action 与综合 GNSS solution。
- 具身：运动规划、规划场景、IK/FK、硬件与控制器状态、Action/Task 生命周期、VLA policy/episode、
  多机器人协调；资源统一用 `*_id` 寻址并移除写死拓扑，补齐 MoveIt/ros2_control 核心契约。
- 建图定位：OccupancyGrid 全量/增量、地图查询、SLAM/位姿图/闭环、重定位闭环。
- 为 54 个热路径消息新增 FlatBuffers 表示与 canonical `shm://` 接口；有损投影用独立类型名
  （`CompactDetectedObjects`、`CompactRadarObjects`）。
- InteractiveMarker 位姿更新改为结构化记录，移除远程命令执行语义。

### 接口与 QoS

- 扩展各域 `include/interface/`；按连续流、最新状态、静态数据、RPC、命令、告警、事件、日志
  校正 scheme 与 QoS profile，Interface descriptor 同时暴露 URL 与 schema 名。

### 构建与发布

- 修复 install 配置 CMake 条件语法（可 `find_package(vmsgs)` 消费）；递归收集加
  `CONFIGURE_DEPENDS`；导出 `vmsgs::vmsgs` 与兼容 `vlink::vmsgs`。
- 新增 GitHub Actions `schema-validation.yml`：protoc/flatc 全量编译 + package/namespace
  校验，独立于 vlink。

## v1.0.0（2025/07/01）

- 首次发布。
