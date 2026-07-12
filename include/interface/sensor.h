/*
 * Copyright (c) 2026 VMsgs Contributors.
 * SPDX-License-Identifier: MIT
 *
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

// Generic representation-level endpoints used by ROS-compatible bridges.
VMSGS_MACRO(image, "shm://sensor/image", "vmsgs.fbs.sensor.Image")
VMSGS_MACRO(compressed_image, "shm://sensor/compressed_image", "vmsgs.fbs.sensor.CompressedImage")
VMSGS_MACRO(depth_image, "shm://sensor/depth_image", "vmsgs.fbs.sensor.DepthImage")
VMSGS_MACRO(point_cloud2, "shm://sensor/point_cloud2", "vmsgs.fbs.sensor.PointCloud2")

// =========================================================================
//  Camera (raw / compressed / video / depth → shm; camera_info → dds reliable)
// =========================================================================

// --- front_center (wide / main) -------------------------------------------
VMSGS_MACRO(camera_front_center_image_raw, "shm://sensor/camera/front_center/image_raw", "vlink.zerocopy.CameraFrame")
VMSGS_MACRO(camera_front_center_image_compressed, "shm://sensor/camera/front_center/image_compressed", "vlink.zerocopy.CameraFrame")
VMSGS_MACRO(camera_front_center_video, "shm://sensor/camera/front_center/video", "vlink.zerocopy.CameraFrame")
VMSGS_MACRO(camera_front_center_compressed_video, "shm://sensor/camera/front_center/compressed_video", "vmsgs.fbs.sensor.CompressedVideo")
VMSGS_MACRO(camera_front_center_depth_raw, "shm://sensor/camera/front_center/depth_raw", "vlink.zerocopy.CameraFrame")
VMSGS_MACRO(camera_front_center_camera_info, "dds://sensor/camera/front_center/camera_info?qos=static", "vmsgs.proto.sensor.CameraInfo")

// --- front_center_far (telephoto / long-range) ----------------------------
VMSGS_MACRO(camera_front_center_far_image_raw, "shm://sensor/camera/front_center_far/image_raw", "vlink.zerocopy.CameraFrame")
VMSGS_MACRO(camera_front_center_far_image_compressed, "shm://sensor/camera/front_center_far/image_compressed", "vlink.zerocopy.CameraFrame")
VMSGS_MACRO(camera_front_center_far_camera_info, "dds://sensor/camera/front_center_far/camera_info?qos=static", "vmsgs.proto.sensor.CameraInfo")

// --- front_left -----------------------------------------------------------
VMSGS_MACRO(camera_front_left_image_raw, "shm://sensor/camera/front_left/image_raw", "vlink.zerocopy.CameraFrame")
VMSGS_MACRO(camera_front_left_image_compressed, "shm://sensor/camera/front_left/image_compressed", "vlink.zerocopy.CameraFrame")
VMSGS_MACRO(camera_front_left_camera_info, "dds://sensor/camera/front_left/camera_info?qos=static", "vmsgs.proto.sensor.CameraInfo")

// --- front_right ----------------------------------------------------------
VMSGS_MACRO(camera_front_right_image_raw, "shm://sensor/camera/front_right/image_raw", "vlink.zerocopy.CameraFrame")
VMSGS_MACRO(camera_front_right_image_compressed, "shm://sensor/camera/front_right/image_compressed", "vlink.zerocopy.CameraFrame")
VMSGS_MACRO(camera_front_right_camera_info, "dds://sensor/camera/front_right/camera_info?qos=static", "vmsgs.proto.sensor.CameraInfo")

// --- rear_center ----------------------------------------------------------
VMSGS_MACRO(camera_rear_center_image_raw, "shm://sensor/camera/rear_center/image_raw", "vlink.zerocopy.CameraFrame")
VMSGS_MACRO(camera_rear_center_image_compressed, "shm://sensor/camera/rear_center/image_compressed", "vlink.zerocopy.CameraFrame")
VMSGS_MACRO(camera_rear_center_camera_info, "dds://sensor/camera/rear_center/camera_info?qos=static", "vmsgs.proto.sensor.CameraInfo")

// --- rear_left ------------------------------------------------------------
VMSGS_MACRO(camera_rear_left_image_raw, "shm://sensor/camera/rear_left/image_raw", "vlink.zerocopy.CameraFrame")
VMSGS_MACRO(camera_rear_left_image_compressed, "shm://sensor/camera/rear_left/image_compressed", "vlink.zerocopy.CameraFrame")
VMSGS_MACRO(camera_rear_left_camera_info, "dds://sensor/camera/rear_left/camera_info?qos=static", "vmsgs.proto.sensor.CameraInfo")

// --- rear_right -----------------------------------------------------------
VMSGS_MACRO(camera_rear_right_image_raw, "shm://sensor/camera/rear_right/image_raw", "vlink.zerocopy.CameraFrame")
VMSGS_MACRO(camera_rear_right_image_compressed, "shm://sensor/camera/rear_right/image_compressed", "vlink.zerocopy.CameraFrame")
VMSGS_MACRO(camera_rear_right_camera_info, "dds://sensor/camera/rear_right/camera_info?qos=static", "vmsgs.proto.sensor.CameraInfo")

// --- surround / fisheye ---------------------------------------------------
VMSGS_MACRO(camera_fisheye_front_image_raw, "shm://sensor/camera/fisheye_front/image_raw", "vlink.zerocopy.CameraFrame")
VMSGS_MACRO(camera_fisheye_front_camera_info, "dds://sensor/camera/fisheye_front/camera_info?qos=static", "vmsgs.proto.sensor.CameraInfo")
VMSGS_MACRO(camera_fisheye_rear_image_raw, "shm://sensor/camera/fisheye_rear/image_raw", "vlink.zerocopy.CameraFrame")
VMSGS_MACRO(camera_fisheye_rear_camera_info, "dds://sensor/camera/fisheye_rear/camera_info?qos=static", "vmsgs.proto.sensor.CameraInfo")
VMSGS_MACRO(camera_fisheye_left_image_raw, "shm://sensor/camera/fisheye_left/image_raw", "vlink.zerocopy.CameraFrame")
VMSGS_MACRO(camera_fisheye_left_camera_info, "dds://sensor/camera/fisheye_left/camera_info?qos=static", "vmsgs.proto.sensor.CameraInfo")
VMSGS_MACRO(camera_fisheye_right_image_raw, "shm://sensor/camera/fisheye_right/image_raw", "vlink.zerocopy.CameraFrame")
VMSGS_MACRO(camera_fisheye_right_camera_info, "dds://sensor/camera/fisheye_right/camera_info?qos=static", "vmsgs.proto.sensor.CameraInfo")

// --- event camera (DVS) ---------------------------------------------------
VMSGS_MACRO(event_camera_front_center_events, "shm://sensor/event_camera/front_center/events", "vmsgs.fbs.sensor.EventArray")
VMSGS_MACRO(event_camera_front_center_accumulated_image, "shm://sensor/event_camera/front_center/accumulated_image", "vlink.zerocopy.CameraFrame")

// =========================================================================
//  LiDAR (zero-copy point cloud)
// =========================================================================
VMSGS_MACRO(lidar_top_point_cloud, "shm://sensor/lidar/top/point_cloud", "vlink.zerocopy.PointCloud")
VMSGS_MACRO(lidar_front_center_point_cloud, "shm://sensor/lidar/front_center/point_cloud", "vlink.zerocopy.PointCloud")
VMSGS_MACRO(lidar_rear_center_point_cloud, "shm://sensor/lidar/rear_center/point_cloud", "vlink.zerocopy.PointCloud")
VMSGS_MACRO(lidar_front_left_point_cloud, "shm://sensor/lidar/front_left/point_cloud", "vlink.zerocopy.PointCloud")
VMSGS_MACRO(lidar_front_right_point_cloud, "shm://sensor/lidar/front_right/point_cloud", "vlink.zerocopy.PointCloud")
VMSGS_MACRO(lidar_rear_left_point_cloud, "shm://sensor/lidar/rear_left/point_cloud", "vlink.zerocopy.PointCloud")
VMSGS_MACRO(lidar_rear_right_point_cloud, "shm://sensor/lidar/rear_right/point_cloud", "vlink.zerocopy.PointCloud")

VMSGS_MACRO(lidar_concatenated_point_cloud, "shm://sensor/lidar/concatenated/point_cloud", "vlink.zerocopy.PointCloud")
VMSGS_MACRO(lidar_concatenated_info, "dds://sensor/lidar/concatenated/info?qos=sensor", "vmsgs.proto.sensor.ConcatenatedPointCloudInfo")

// =========================================================================
//  Radar — raw scan via shm; tracks/objects high-rate dds; info reliable
// =========================================================================
VMSGS_MACRO(radar_front_center_scan, "shm://sensor/radar/front_center/scan", "vmsgs.fbs.sensor.RadarScan")
VMSGS_MACRO(radar_front_center_point_cloud, "shm://sensor/radar/front_center/point_cloud", "vlink.zerocopy.PointCloud")
VMSGS_MACRO(radar_front_center_tracks, "dds://sensor/radar/front_center/tracks?qos=sensor", "vmsgs.proto.sensor.RadarTracks")
VMSGS_MACRO(radar_tracks, "shm://sensor/radar/tracks", "vmsgs.fbs.sensor.RadarTracks")
VMSGS_MACRO(radar_front_center_objects, "dds://sensor/radar/front_center/objects?qos=sensor", "vmsgs.proto.sensor.RadarObjects")
VMSGS_MACRO(radar_compact_objects, "shm://sensor/radar/objects_compact", "vmsgs.fbs.sensor.CompactRadarObjects")
VMSGS_MACRO(radar_front_center_info, "dds://sensor/radar/front_center/info", "vmsgs.proto.sensor.RadarInfo")

VMSGS_MACRO(radar_front_left_scan, "shm://sensor/radar/front_left/scan", "vmsgs.fbs.sensor.RadarScan")
VMSGS_MACRO(radar_front_left_point_cloud, "shm://sensor/radar/front_left/point_cloud", "vlink.zerocopy.PointCloud")
VMSGS_MACRO(radar_front_left_tracks, "dds://sensor/radar/front_left/tracks?qos=sensor", "vmsgs.proto.sensor.RadarTracks")
VMSGS_MACRO(radar_front_left_objects, "dds://sensor/radar/front_left/objects?qos=sensor", "vmsgs.proto.sensor.RadarObjects")
VMSGS_MACRO(radar_front_left_info, "dds://sensor/radar/front_left/info", "vmsgs.proto.sensor.RadarInfo")

VMSGS_MACRO(radar_front_right_scan, "shm://sensor/radar/front_right/scan", "vmsgs.fbs.sensor.RadarScan")
VMSGS_MACRO(radar_front_right_point_cloud, "shm://sensor/radar/front_right/point_cloud", "vlink.zerocopy.PointCloud")
VMSGS_MACRO(radar_front_right_tracks, "dds://sensor/radar/front_right/tracks?qos=sensor", "vmsgs.proto.sensor.RadarTracks")
VMSGS_MACRO(radar_front_right_objects, "dds://sensor/radar/front_right/objects?qos=sensor", "vmsgs.proto.sensor.RadarObjects")
VMSGS_MACRO(radar_front_right_info, "dds://sensor/radar/front_right/info", "vmsgs.proto.sensor.RadarInfo")

VMSGS_MACRO(radar_rear_center_scan, "shm://sensor/radar/rear_center/scan", "vmsgs.fbs.sensor.RadarScan")
VMSGS_MACRO(radar_rear_center_point_cloud, "shm://sensor/radar/rear_center/point_cloud", "vlink.zerocopy.PointCloud")
VMSGS_MACRO(radar_rear_center_tracks, "dds://sensor/radar/rear_center/tracks?qos=sensor", "vmsgs.proto.sensor.RadarTracks")
VMSGS_MACRO(radar_rear_center_objects, "dds://sensor/radar/rear_center/objects?qos=sensor", "vmsgs.proto.sensor.RadarObjects")
VMSGS_MACRO(radar_rear_center_info, "dds://sensor/radar/rear_center/info", "vmsgs.proto.sensor.RadarInfo")

VMSGS_MACRO(radar_rear_left_scan, "shm://sensor/radar/rear_left/scan", "vmsgs.fbs.sensor.RadarScan")
VMSGS_MACRO(radar_rear_left_point_cloud, "shm://sensor/radar/rear_left/point_cloud", "vlink.zerocopy.PointCloud")
VMSGS_MACRO(radar_rear_left_tracks, "dds://sensor/radar/rear_left/tracks?qos=sensor", "vmsgs.proto.sensor.RadarTracks")
VMSGS_MACRO(radar_rear_left_objects, "dds://sensor/radar/rear_left/objects?qos=sensor", "vmsgs.proto.sensor.RadarObjects")
VMSGS_MACRO(radar_rear_left_info, "dds://sensor/radar/rear_left/info", "vmsgs.proto.sensor.RadarInfo")

VMSGS_MACRO(radar_rear_right_scan, "shm://sensor/radar/rear_right/scan", "vmsgs.fbs.sensor.RadarScan")
VMSGS_MACRO(radar_rear_right_point_cloud, "shm://sensor/radar/rear_right/point_cloud", "vlink.zerocopy.PointCloud")
VMSGS_MACRO(radar_rear_right_tracks, "dds://sensor/radar/rear_right/tracks?qos=sensor", "vmsgs.proto.sensor.RadarTracks")
VMSGS_MACRO(radar_rear_right_objects, "dds://sensor/radar/rear_right/objects?qos=sensor", "vmsgs.proto.sensor.RadarObjects")
VMSGS_MACRO(radar_rear_right_info, "dds://sensor/radar/rear_right/info", "vmsgs.proto.sensor.RadarInfo")

// =========================================================================
//  2D laser scan (Proto compatibility and zero-copy FlatBuffers representations)
// =========================================================================
VMSGS_MACRO(laser_front_center_scan, "dds://sensor/laser/front_center/scan?qos=sensor", "vmsgs.proto.sensor.LaserScan")
VMSGS_MACRO(laser_rear_center_scan, "dds://sensor/laser/rear_center/scan?qos=sensor", "vmsgs.proto.sensor.LaserScan")
VMSGS_MACRO(laser_front_center_multi_echo_scan, "dds://sensor/laser/front_center/multi_echo_scan?qos=sensor", "vmsgs.proto.sensor.MultiEchoLaserScan")
VMSGS_MACRO(laser_scan, "shm://sensor/laser/scan", "vmsgs.fbs.sensor.LaserScan")
VMSGS_MACRO(multi_echo_laser_scan, "shm://sensor/laser/multi_echo_scan", "vmsgs.fbs.sensor.MultiEchoLaserScan")

// =========================================================================
//  Ultrasonic / IR / ToF range — sensor stream
// =========================================================================
VMSGS_MACRO(range_front_center, "dds://sensor/range/front_center?qos=sensor", "vmsgs.proto.sensor.Range")
VMSGS_MACRO(range_front_left, "dds://sensor/range/front_left?qos=sensor", "vmsgs.proto.sensor.Range")
VMSGS_MACRO(range_front_right, "dds://sensor/range/front_right?qos=sensor", "vmsgs.proto.sensor.Range")
VMSGS_MACRO(range_rear_center, "dds://sensor/range/rear_center?qos=sensor", "vmsgs.proto.sensor.Range")
VMSGS_MACRO(range_rear_left, "dds://sensor/range/rear_left?qos=sensor", "vmsgs.proto.sensor.Range")
VMSGS_MACRO(range_rear_right, "dds://sensor/range/rear_right?qos=sensor", "vmsgs.proto.sensor.Range")

// =========================================================================
//  IMU / GNSS — sensor stream
// =========================================================================
VMSGS_MACRO(imu_raw, "dds://sensor/imu/imu_raw?qos=sensor", "vmsgs.proto.sensor.Imu")
VMSGS_MACRO(imu_zero_copy, "shm://sensor/imu/imu", "vmsgs.fbs.sensor.Imu")
VMSGS_MACRO(magnetic_field, "dds://sensor/imu/magnetic_field?qos=sensor", "vmsgs.proto.sensor.MagneticField")
VMSGS_MACRO(nav_sat_fix, "dds://sensor/gnss/nav_sat_fix?qos=sensor", "vmsgs.proto.sensor.NavSatFix")
VMSGS_MACRO(gnss_solution, "dds://sensor/gnss/solution?qos=sensor", "vmsgs.proto.sensor.GnssSolution")
VMSGS_MACRO(gnss_ins_orientation, "dds://sensor/gnss/orientation?qos=sensor", "vmsgs.proto.sensor.GnssInsOrientation")
VMSGS_MACRO(time_reference, "dds://sensor/gnss/time_reference?qos=sensor", "vmsgs.proto.sensor.TimeReference")
VMSGS_MACRO(sensor_calibrations, "dds://sensor/calibrations?qos=static", "vmsgs.proto.sensor.SensorCalibrations")

// =========================================================================
//  Audio (zero-copy)
// =========================================================================
VMSGS_MACRO(audio_raw, "shm://sensor/audio/raw", "vmsgs.fbs.sensor.RawAudio")
VMSGS_MACRO(audio_compressed, "shm://sensor/audio/compressed", "vmsgs.fbs.sensor.CompressedAudio")

// =========================================================================
//  Environmental — continuous sensor reading
// =========================================================================
VMSGS_MACRO(fluid_pressure, "dds://sensor/environmental/fluid_pressure?qos=sensor", "vmsgs.proto.sensor.FluidPressure")
VMSGS_MACRO(temperature, "dds://sensor/environmental/temperature?qos=sensor", "vmsgs.proto.sensor.Temperature")
VMSGS_MACRO(illuminance, "dds://sensor/environmental/illuminance?qos=sensor", "vmsgs.proto.sensor.Illuminance")
VMSGS_MACRO(relative_humidity, "dds://sensor/environmental/relative_humidity?qos=sensor", "vmsgs.proto.sensor.RelativeHumidity")

// =========================================================================
//  Health / state — periodic telemetry, latest sample wins
// =========================================================================
VMSGS_MACRO(battery_state, "dds://sensor/battery/state?qos=sensor", "vmsgs.proto.sensor.BatteryState")
VMSGS_MACRO(sensor_status, "dds://sensor/sensor_status", "vmsgs.proto.sensor.SensorStatus")

// =========================================================================
//  Joint state (sensor-side encoders / chassis joints) — sensor stream
// =========================================================================
VMSGS_MACRO(joint_state, "dds://sensor/joint_state?qos=sensor", "vmsgs.proto.sensor.JointState")
VMSGS_MACRO(joint_state_zero_copy, "shm://sensor/joint_state", "vmsgs.fbs.sensor.JointState")
VMSGS_MACRO(multi_dof_joint_state, "dds://sensor/multi_dof_joint_state?qos=sensor", "vmsgs.proto.sensor.MultiDOFJointState")

// =========================================================================
//  Joystick / operator HID — input latest-wins, feedback command reliable
// =========================================================================
VMSGS_MACRO(joy, "dds://sensor/joy?qos=sensor", "vmsgs.proto.sensor.Joy")
VMSGS_MACRO(joy_feedback, "dds://sensor/joy_feedback", "vmsgs.proto.sensor.JoyFeedbackArray")

}  // namespace vmsg::interface::sensor
