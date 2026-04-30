/*
 * Copyright (C) 2026 by Thun Lu. All rights reserved.
 * Author: Thun Lu <thun.lu@zohomail.cn>
 */

#pragma once

#include "../macros.h"

// Topics published by the sensor layer.
//
// - Bulk-payload streams (image / point cloud / depth / radar burst / audio /
//   event camera) use shm:// for zero-copy.
// - High-rate sensor streams use dds:// with ?qos=sensor (drop-OK).
// - Calibration / capability info / state-change topics use dds:// with no
//   qos query (must-deliver default).

namespace vmsg::interface::sensor {

// =========================================================================
//  Camera (raw / compressed / video / depth → shm; camera_info → dds reliable)
// =========================================================================

// --- front_center (wide / main) -------------------------------------------
VMSGS_MACRO(camera_front_center_image_raw, "shm://sensor/camera/front_center/image_raw", CameraFrame)
VMSGS_MACRO(camera_front_center_image_compressed, "shm://sensor/camera/front_center/image_compressed", CameraFrame)
VMSGS_MACRO(camera_front_center_video, "shm://sensor/camera/front_center/video", CameraFrame)
VMSGS_MACRO(camera_front_center_depth_raw, "shm://sensor/camera/front_center/depth_raw", CameraFrame)
VMSGS_MACRO(camera_front_center_camera_info, "dds://sensor/camera/front_center/camera_info", CameraInfo)

// --- front_center_far (telephoto / long-range) ----------------------------
VMSGS_MACRO(camera_front_center_far_image_raw, "shm://sensor/camera/front_center_far/image_raw", CameraFrame)
VMSGS_MACRO(camera_front_center_far_image_compressed, "shm://sensor/camera/front_center_far/image_compressed", CameraFrame)
VMSGS_MACRO(camera_front_center_far_camera_info, "dds://sensor/camera/front_center_far/camera_info", CameraInfo)

// --- front_left -----------------------------------------------------------
VMSGS_MACRO(camera_front_left_image_raw, "shm://sensor/camera/front_left/image_raw", CameraFrame)
VMSGS_MACRO(camera_front_left_image_compressed, "shm://sensor/camera/front_left/image_compressed", CameraFrame)
VMSGS_MACRO(camera_front_left_camera_info, "dds://sensor/camera/front_left/camera_info", CameraInfo)

// --- front_right ----------------------------------------------------------
VMSGS_MACRO(camera_front_right_image_raw, "shm://sensor/camera/front_right/image_raw", CameraFrame)
VMSGS_MACRO(camera_front_right_image_compressed, "shm://sensor/camera/front_right/image_compressed", CameraFrame)
VMSGS_MACRO(camera_front_right_camera_info, "dds://sensor/camera/front_right/camera_info", CameraInfo)

// --- rear_center ----------------------------------------------------------
VMSGS_MACRO(camera_rear_center_image_raw, "shm://sensor/camera/rear_center/image_raw", CameraFrame)
VMSGS_MACRO(camera_rear_center_image_compressed, "shm://sensor/camera/rear_center/image_compressed", CameraFrame)
VMSGS_MACRO(camera_rear_center_camera_info, "dds://sensor/camera/rear_center/camera_info", CameraInfo)

// --- rear_left ------------------------------------------------------------
VMSGS_MACRO(camera_rear_left_image_raw, "shm://sensor/camera/rear_left/image_raw", CameraFrame)
VMSGS_MACRO(camera_rear_left_image_compressed, "shm://sensor/camera/rear_left/image_compressed", CameraFrame)
VMSGS_MACRO(camera_rear_left_camera_info, "dds://sensor/camera/rear_left/camera_info", CameraInfo)

// --- rear_right -----------------------------------------------------------
VMSGS_MACRO(camera_rear_right_image_raw, "shm://sensor/camera/rear_right/image_raw", CameraFrame)
VMSGS_MACRO(camera_rear_right_image_compressed, "shm://sensor/camera/rear_right/image_compressed", CameraFrame)
VMSGS_MACRO(camera_rear_right_camera_info, "dds://sensor/camera/rear_right/camera_info", CameraInfo)

// --- surround / fisheye ---------------------------------------------------
VMSGS_MACRO(camera_fisheye_front_image_raw, "shm://sensor/camera/fisheye_front/image_raw", CameraFrame)
VMSGS_MACRO(camera_fisheye_front_camera_info, "dds://sensor/camera/fisheye_front/camera_info", CameraInfo)
VMSGS_MACRO(camera_fisheye_rear_image_raw, "shm://sensor/camera/fisheye_rear/image_raw", CameraFrame)
VMSGS_MACRO(camera_fisheye_rear_camera_info, "dds://sensor/camera/fisheye_rear/camera_info", CameraInfo)
VMSGS_MACRO(camera_fisheye_left_image_raw, "shm://sensor/camera/fisheye_left/image_raw", CameraFrame)
VMSGS_MACRO(camera_fisheye_left_camera_info, "dds://sensor/camera/fisheye_left/camera_info", CameraInfo)
VMSGS_MACRO(camera_fisheye_right_image_raw, "shm://sensor/camera/fisheye_right/image_raw", CameraFrame)
VMSGS_MACRO(camera_fisheye_right_camera_info, "dds://sensor/camera/fisheye_right/camera_info", CameraInfo)

// --- event camera (DVS) ---------------------------------------------------
VMSGS_MACRO(event_camera_front_center_events, "shm://sensor/event_camera/front_center/events", CameraFrame)

// =========================================================================
//  LiDAR (zero-copy point cloud)
// =========================================================================
VMSGS_MACRO(lidar_top_point_cloud, "shm://sensor/lidar/top/point_cloud", PointCloud)
VMSGS_MACRO(lidar_front_center_point_cloud, "shm://sensor/lidar/front_center/point_cloud", PointCloud)
VMSGS_MACRO(lidar_rear_center_point_cloud, "shm://sensor/lidar/rear_center/point_cloud", PointCloud)
VMSGS_MACRO(lidar_front_left_point_cloud, "shm://sensor/lidar/front_left/point_cloud", PointCloud)
VMSGS_MACRO(lidar_front_right_point_cloud, "shm://sensor/lidar/front_right/point_cloud", PointCloud)
VMSGS_MACRO(lidar_rear_left_point_cloud, "shm://sensor/lidar/rear_left/point_cloud", PointCloud)
VMSGS_MACRO(lidar_rear_right_point_cloud, "shm://sensor/lidar/rear_right/point_cloud", PointCloud)

VMSGS_MACRO(lidar_concatenated_point_cloud, "shm://sensor/lidar/concatenated/point_cloud", PointCloud)
VMSGS_MACRO(lidar_concatenated_info, "dds://sensor/lidar/concatenated/info?qos=sensor", ConcatenatedPointCloudInfo)

// =========================================================================
//  Radar — raw scan via shm; tracks/objects high-rate dds; info reliable
// =========================================================================
VMSGS_MACRO(radar_front_center_scan, "shm://sensor/radar/front_center/scan", PointCloud)
VMSGS_MACRO(radar_front_center_tracks, "dds://sensor/radar/front_center/tracks?qos=sensor", RadarTracks)
VMSGS_MACRO(radar_front_center_objects, "dds://sensor/radar/front_center/objects?qos=sensor", RadarObjects)
VMSGS_MACRO(radar_front_center_info, "dds://sensor/radar/front_center/info", RadarInfo)

VMSGS_MACRO(radar_front_left_scan, "shm://sensor/radar/front_left/scan", PointCloud)
VMSGS_MACRO(radar_front_left_tracks, "dds://sensor/radar/front_left/tracks?qos=sensor", RadarTracks)
VMSGS_MACRO(radar_front_left_objects, "dds://sensor/radar/front_left/objects?qos=sensor", RadarObjects)
VMSGS_MACRO(radar_front_left_info, "dds://sensor/radar/front_left/info", RadarInfo)

VMSGS_MACRO(radar_front_right_scan, "shm://sensor/radar/front_right/scan", PointCloud)
VMSGS_MACRO(radar_front_right_tracks, "dds://sensor/radar/front_right/tracks?qos=sensor", RadarTracks)
VMSGS_MACRO(radar_front_right_objects, "dds://sensor/radar/front_right/objects?qos=sensor", RadarObjects)
VMSGS_MACRO(radar_front_right_info, "dds://sensor/radar/front_right/info", RadarInfo)

VMSGS_MACRO(radar_rear_center_scan, "shm://sensor/radar/rear_center/scan", PointCloud)
VMSGS_MACRO(radar_rear_center_tracks, "dds://sensor/radar/rear_center/tracks?qos=sensor", RadarTracks)
VMSGS_MACRO(radar_rear_center_objects, "dds://sensor/radar/rear_center/objects?qos=sensor", RadarObjects)
VMSGS_MACRO(radar_rear_center_info, "dds://sensor/radar/rear_center/info", RadarInfo)

VMSGS_MACRO(radar_rear_left_scan, "shm://sensor/radar/rear_left/scan", PointCloud)
VMSGS_MACRO(radar_rear_left_tracks, "dds://sensor/radar/rear_left/tracks?qos=sensor", RadarTracks)
VMSGS_MACRO(radar_rear_left_objects, "dds://sensor/radar/rear_left/objects?qos=sensor", RadarObjects)
VMSGS_MACRO(radar_rear_left_info, "dds://sensor/radar/rear_left/info", RadarInfo)

VMSGS_MACRO(radar_rear_right_scan, "shm://sensor/radar/rear_right/scan", PointCloud)
VMSGS_MACRO(radar_rear_right_tracks, "dds://sensor/radar/rear_right/tracks?qos=sensor", RadarTracks)
VMSGS_MACRO(radar_rear_right_objects, "dds://sensor/radar/rear_right/objects?qos=sensor", RadarObjects)
VMSGS_MACRO(radar_rear_right_info, "dds://sensor/radar/rear_right/info", RadarInfo)

// =========================================================================
//  2D laser scan (small payload — proto, sensor stream)
// =========================================================================
VMSGS_MACRO(laser_front_center_scan, "dds://sensor/laser/front_center/scan?qos=sensor", LaserScan)
VMSGS_MACRO(laser_rear_center_scan, "dds://sensor/laser/rear_center/scan?qos=sensor", LaserScan)
VMSGS_MACRO(laser_front_center_multi_echo_scan, "dds://sensor/laser/front_center/multi_echo_scan?qos=sensor", MultiEchoLaserScan)

// =========================================================================
//  Ultrasonic / IR / ToF range — sensor stream
// =========================================================================
VMSGS_MACRO(range_front_center, "dds://sensor/range/front_center?qos=sensor", Range)
VMSGS_MACRO(range_front_left, "dds://sensor/range/front_left?qos=sensor", Range)
VMSGS_MACRO(range_front_right, "dds://sensor/range/front_right?qos=sensor", Range)
VMSGS_MACRO(range_rear_center, "dds://sensor/range/rear_center?qos=sensor", Range)
VMSGS_MACRO(range_rear_left, "dds://sensor/range/rear_left?qos=sensor", Range)
VMSGS_MACRO(range_rear_right, "dds://sensor/range/rear_right?qos=sensor", Range)

// =========================================================================
//  IMU / GNSS — sensor stream
// =========================================================================
VMSGS_MACRO(imu_raw, "dds://sensor/imu/imu_raw?qos=sensor", Imu)
VMSGS_MACRO(magnetic_field, "dds://sensor/imu/magnetic_field?qos=sensor", MagneticField)
VMSGS_MACRO(nav_sat_fix, "dds://sensor/gnss/nav_sat_fix?qos=sensor", NavSatFix)
VMSGS_MACRO(gnss_ins_orientation, "dds://sensor/gnss/orientation?qos=sensor", GnssInsOrientation)
VMSGS_MACRO(time_reference, "dds://sensor/gnss/time_reference?qos=sensor", TimeReference)

// =========================================================================
//  Audio (zero-copy)
// =========================================================================
VMSGS_MACRO(audio_raw, "shm://sensor/audio/raw", RawData)
VMSGS_MACRO(audio_compressed, "shm://sensor/audio/compressed", RawData)

// =========================================================================
//  Environmental — continuous sensor reading
// =========================================================================
VMSGS_MACRO(fluid_pressure, "dds://sensor/environmental/fluid_pressure?qos=sensor", FluidPressure)
VMSGS_MACRO(temperature, "dds://sensor/environmental/temperature?qos=sensor", Temperature)
VMSGS_MACRO(illuminance, "dds://sensor/environmental/illuminance?qos=sensor", Illuminance)
VMSGS_MACRO(relative_humidity, "dds://sensor/environmental/relative_humidity?qos=sensor", RelativeHumidity)

// =========================================================================
//  Health / state — must-deliver
// =========================================================================
VMSGS_MACRO(battery_state, "dds://sensor/battery/state", BatteryState)
VMSGS_MACRO(sensor_status, "dds://sensor/sensor_status", SensorStatus)

// =========================================================================
//  Joint state (sensor-side encoders / chassis joints) — sensor stream
// =========================================================================
VMSGS_MACRO(joint_state, "dds://sensor/joint_state?qos=sensor", JointState)
VMSGS_MACRO(multi_dof_joint_state, "dds://sensor/multi_dof_joint_state?qos=sensor", MultiDOFJointState)

// =========================================================================
//  Joystick / operator HID — must-deliver
// =========================================================================
VMSGS_MACRO(joy, "dds://sensor/joy", Joy)
VMSGS_MACRO(joy_feedback, "dds://sensor/joy_feedback", JoyFeedbackArray)

}  // namespace vmsg::interface::sensor
