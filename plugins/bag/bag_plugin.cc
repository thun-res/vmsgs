/*
 * Copyright (C) 2026 by Thun Lu. All rights reserved.
 * Author: Thun Lu <thun.lu@zohomail.cn>
 */

#include <vlink/base/helpers.h>
#include <vlink/base/utils.h>
#include <vlink/extension/bag_plugin_interface.h>
#include <vlink/extension/bag_processor.h>
#include <vlink/extension/schema_plugin_manager.h>
#include <vlink/serializer.h>
#include <vlink/zerocopy/message_parser.h>
#include <vlink/zerocopy/point_cloud.h>

#ifdef VMSGS_ENABLE_PROTOBUF
#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>
#endif

#ifdef VMSGS_ENABLE_FLATBUFFERS
#include <flatbuffers/reflection.h>
#endif

#include <charconv>
#include <cstdint>
#include <iostream>
#include <limits>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <system_error>
#include <unordered_map>
#include <utility>
#include <variant>

namespace vmsgs {

static constexpr int64_t kDefaultCacheTime{500};
static constexpr int64_t kDefaultCacheSize{512};
static constexpr int64_t kDefaultJumpTime{10000};
static constexpr int64_t kBytesPerMb{1024LL * 1024LL};
static constexpr int64_t kNsPerUs{1000};
static constexpr char kPointCloudType[]{"vlink::zerocopy::PointCloud"};

static int64_t parse_positive_int64(const std::string& value, int64_t fallback) noexcept {
  if (value.empty()) {
    return fallback;
  }

  int64_t parsed_value = 0;
  const auto result = std::from_chars(value.data(), value.data() + value.size(), parsed_value);

  if (result.ec != std::errc() || result.ptr != value.data() + value.size() || parsed_value <= 0) {
    return fallback;
  }

  return parsed_value;
}

static bool timestamp_ns_to_us(uint64_t timestamp_ns, int64_t& timestamp_us) noexcept {
  const uint64_t value = timestamp_ns / static_cast<uint64_t>(kNsPerUs);

  if VUNLIKELY (value == 0 || value > static_cast<uint64_t>(std::numeric_limits<int64_t>::max())) {
    return false;
  }

  timestamp_us = static_cast<int64_t>(value);
  return true;
}

#ifdef VMSGS_ENABLE_PROTOBUF
static bool extract_protobuf_timestamp(const std::string& ser_type, const vlink::Bytes& data, int64_t& timestamp_us) {
  const auto* descriptor = google::protobuf::DescriptorPool::generated_pool()->FindMessageTypeByName(ser_type);

  if VUNLIKELY (descriptor == nullptr) {
    return false;
  }

  const auto* header_field = descriptor->FindFieldByName("header");

  if VUNLIKELY (header_field == nullptr || header_field->is_repeated() || header_field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE || header_field->message_type() == nullptr ||
                header_field->message_type()->full_name() != "vmsgs.proto.common.Header") {
    return false;
  }

  if VUNLIKELY (data.size() > static_cast<size_t>(std::numeric_limits<int>::max())) {
    return false;
  }

  const auto* prototype = google::protobuf::MessageFactory::generated_factory()->GetPrototype(descriptor);

  if VUNLIKELY (prototype == nullptr) {
    return false;
  }

  std::unique_ptr<google::protobuf::Message> message(prototype->New());

  if VUNLIKELY (!message->ParseFromArray(data.data(), static_cast<int>(data.size()))) {
    return false;
  }

  const auto* reflection = message->GetReflection();

  if VUNLIKELY (!reflection->HasField(*message, header_field)) {
    return false;
  }

  const auto& header = reflection->GetMessage(*message, header_field);
  const auto* time_meas_field = header.GetDescriptor()->FindFieldByName("time_meas");

  if VUNLIKELY (time_meas_field == nullptr || time_meas_field->is_repeated() || time_meas_field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_UINT64) {
    return false;
  }

  return timestamp_ns_to_us(header.GetReflection()->GetUInt64(header, time_meas_field), timestamp_us);
}
#endif

#ifdef VMSGS_ENABLE_FLATBUFFERS
struct FlatbuffersExtractor final {
  const reflection::Schema* schema{nullptr};
  const reflection::Object* root{nullptr};
  const reflection::Field* header{nullptr};
  const reflection::Field* time_meas{nullptr};
};

static bool build_flatbuffers_extractor(const reflection::Schema* schema, FlatbuffersExtractor& extractor) {
  if VUNLIKELY (schema == nullptr || schema->objects() == nullptr || schema->root_table() == nullptr || schema->root_table()->is_struct() || schema->root_table()->fields() == nullptr) {
    return false;
  }

  const auto* header = schema->root_table()->fields()->LookupByKey("header");

  if VUNLIKELY (header == nullptr || header->type() == nullptr || header->type()->base_type() != reflection::Obj || header->type()->index() < 0 ||
                static_cast<flatbuffers::uoffset_t>(header->type()->index()) >= schema->objects()->size()) {
    return false;
  }

  const auto* header_object = schema->objects()->Get(static_cast<flatbuffers::uoffset_t>(header->type()->index()));

  if VUNLIKELY (header_object == nullptr || header_object->name() == nullptr || header_object->name()->string_view() != "vmsgs.fbs.common.Header" || header_object->is_struct() ||
                header_object->fields() == nullptr) {
    return false;
  }

  const auto* time_meas = header_object->fields()->LookupByKey("time_meas");

  if VUNLIKELY (time_meas == nullptr || time_meas->type() == nullptr || time_meas->type()->base_type() != reflection::ULong) {
    return false;
  }

  extractor = {schema, schema->root_table(), header, time_meas};

  return true;
}

static bool extract_flatbuffers_message_timestamp(const FlatbuffersExtractor& extractor, const vlink::Bytes& data, int64_t& timestamp_us) {
  if VUNLIKELY (data.data() == nullptr || data.size() < FLATBUFFERS_MIN_BUFFER_SIZE || !flatbuffers::Verify(*extractor.schema, *extractor.root, data.data(), data.size())) {
    return false;
  }

  const auto* root = flatbuffers::GetAnyRoot(data.data());
  const auto* header = flatbuffers::GetFieldT(*root, *extractor.header);

  if VUNLIKELY (header == nullptr) {
    return false;
  }

  return timestamp_ns_to_us(flatbuffers::GetFieldI<uint64_t>(*header, *extractor.time_meas), timestamp_us);
}
#endif

static bool extract_zerocopy_timestamp(const std::string& ser_type, const vlink::Bytes& data, int64_t& timestamp_us) {
  vlink::zerocopy::MessageParser parser;

  if VUNLIKELY (!parser.parse(ser_type, data)) {
    return false;
  }

  vlink::zerocopy::MessageParser::Value value;

  if (parser.type() == vlink::zerocopy::MessageParser::Type::kProxyData) {
    if VUNLIKELY (!parser.value("timestamp", value)) {
      return false;
    }

    const auto* const timestamp = std::get_if<int64_t>(&value);

    if VUNLIKELY (timestamp == nullptr || *timestamp <= 0) {
      return false;
    }

    timestamp_us = *timestamp;
    return true;
  }

  if VUNLIKELY (!parser.value("header.time_meas", value)) {
    return false;
  }

  const auto* timestamp_ns = std::get_if<uint64_t>(&value);
  return timestamp_ns != nullptr && timestamp_ns_to_us(*timestamp_ns, timestamp_us);
}

class BagPlugin final : public vlink::BagPluginInterface {
 public:
  BagPlugin() : enable_lidar_vertical_(vlink::Utils::get_env("VMSGS_BAG_LIDAR_VERTICAL", "1") == "1") {
    std::cout << "* VMSGS_BAG_LIDAR_VERTICAL: " << (enable_lidar_vertical_ ? 1 : 0) << std::endl;

    if (vlink::Utils::get_env("VMSGS_BAG_RESORT") != "1") {
      std::cout << "* VMSGS_BAG_RESORT:         0" << std::endl;
      return;
    }

    vlink::BagProcessor::Config config;
    config.min_cache_time = parse_positive_int64(vlink::Utils::get_env("VMSGS_BAG_CACHE_TIME"), kDefaultCacheTime);

    const int64_t cache_size_mb = parse_positive_int64(vlink::Utils::get_env("VMSGS_BAG_CACHE_SIZE"), kDefaultCacheSize);
    config.max_cache_size = cache_size_mb > std::numeric_limits<int64_t>::max() / kBytesPerMb ? kDefaultCacheSize * kBytesPerMb : cache_size_mb * kBytesPerMb;
    config.max_jump_time = parse_positive_int64(vlink::Utils::get_env("VMSGS_BAG_JUMP_TIME"), kDefaultJumpTime);

    std::cout << "* VMSGS_BAG_RESORT:         1" << std::endl;
    std::cout << "* VMSGS_BAG_CACHE_TIME:     " << config.min_cache_time << std::endl;
    std::cout << "* VMSGS_BAG_CACHE_SIZE:     " << config.max_cache_size / kBytesPerMb << std::endl;
    std::cout << "* VMSGS_BAG_JUMP_TIME:      " << config.max_jump_time << std::endl;

    processor_.emplace(config);
    processor_->register_output_callback([this](const vlink::Frame& frame) { do_callback(frame); });
  }

  ~BagPlugin() override = default;

  void on_read(const vlink::Frame& frame) override { do_callback(frame); }

  void on_write(const vlink::Frame& frame) override {
    int64_t data_timestamp = -1;

    const bool is_zerocopy = frame.schema_type == vlink::SchemaType::kZeroCopy || frame.schema_type == vlink::SchemaType::kUnknown;
    const bool is_point_cloud = is_zerocopy && frame.ser_type == kPointCloudType;

    if (is_point_cloud) {
      vlink::zerocopy::PointCloud point_cloud;

      if (vlink::Serializer::convert(frame.data, point_cloud) && point_cloud.is_valid()) {
        (void)timestamp_ns_to_us(point_cloud.header.time_meas, data_timestamp);

        if (enable_lidar_vertical_ && !point_cloud.get_vertical()) {
          point_cloud.set_vertical(true);
          vlink::Frame converted_frame = frame;
          converted_frame.data.clear();

          if VLIKELY (vlink::Serializer::serialize(point_cloud, converted_frame.data)) {
            if (!processor_) {
              do_callback(converted_frame);
            } else {
              processor_->push(data_timestamp, converted_frame);
            }

            return;
          }
        }
      }
    } else {
      (void)extract_data_timestamp(frame, data_timestamp);
    }

    if (!processor_) {
      do_callback(frame);
      return;
    }

    processor_->push(data_timestamp, frame);
  }

  void flush() override {
    if (processor_) {
      processor_->flush();
    }
  }

 private:
#if defined(VMSGS_ENABLE_PROTOBUF) || defined(VMSGS_ENABLE_FLATBUFFERS)
  bool ensure_schema_plugin() {
    if VUNLIKELY (!schema_plugin_) {
      schema_plugin_ = vlink::SchemaPluginManager::get().get_interface();
    }

    return schema_plugin_ != nullptr;
  }
#endif

#ifdef VMSGS_ENABLE_FLATBUFFERS
  bool extract_flatbuffers_timestamp(const std::string& ser_type, const vlink::Bytes& data, int64_t& timestamp_us) {
    auto iter = flatbuffers_extractors_.find(ser_type);

    if VUNLIKELY (iter == flatbuffers_extractors_.end()) {
      if VUNLIKELY (!ensure_schema_plugin()) {
        return false;
      }

      FlatbuffersExtractor extractor;
      const auto* schema = reinterpret_cast<const reflection::Schema*>(schema_plugin_->search_flatbuffers_schema(ser_type));

      if VUNLIKELY (schema == nullptr || schema->root_table() == nullptr || schema->root_table()->name() == nullptr || schema->root_table()->name()->string_view() != ser_type ||
                    !build_flatbuffers_extractor(schema, extractor)) {
        return false;
      }

      iter = flatbuffers_extractors_.emplace(ser_type, extractor).first;
    }

    return extract_flatbuffers_message_timestamp(iter->second, data, timestamp_us);
  }
#endif

  bool extract_data_timestamp(const vlink::Frame& frame, int64_t& timestamp_us) {
    if (frame.schema_type == vlink::SchemaType::kZeroCopy) {
      return extract_zerocopy_timestamp(frame.ser_type, frame.data, timestamp_us);
    }

#ifdef VMSGS_ENABLE_PROTOBUF
    if (frame.schema_type == vlink::SchemaType::kProtobuf) {
      if VUNLIKELY (!ensure_schema_plugin()) {
        return false;
      }

      return extract_protobuf_timestamp(frame.ser_type, frame.data, timestamp_us);
    }
#endif

#ifdef VMSGS_ENABLE_FLATBUFFERS
    if (frame.schema_type == vlink::SchemaType::kFlatbuffers) {
      return extract_flatbuffers_timestamp(frame.ser_type, frame.data, timestamp_us);
    }
#endif

    if (frame.schema_type != vlink::SchemaType::kUnknown) {
      return false;
    }

    if (vlink::zerocopy::MessageParser::detect_type(frame.ser_type) != vlink::zerocopy::MessageParser::Type::kUnknown) {
      return extract_zerocopy_timestamp(frame.ser_type, frame.data, timestamp_us);
    }

#ifdef VMSGS_ENABLE_PROTOBUF
    if (vlink::Helpers::has_startwith(frame.ser_type, "vmsgs.proto.")) {
      if VUNLIKELY (!ensure_schema_plugin()) {
        return false;
      }

      return extract_protobuf_timestamp(frame.ser_type, frame.data, timestamp_us);
    }
#endif

#ifdef VMSGS_ENABLE_FLATBUFFERS
    if (vlink::Helpers::has_startwith(frame.ser_type, "vmsgs.fbs.")) {
      return extract_flatbuffers_timestamp(frame.ser_type, frame.data, timestamp_us);
    }
#endif

    return false;
  }

#if defined(VMSGS_ENABLE_PROTOBUF) || defined(VMSGS_ENABLE_FLATBUFFERS)
  std::shared_ptr<vlink::SchemaPluginInterface> schema_plugin_;
#endif
#ifdef VMSGS_ENABLE_FLATBUFFERS
  std::unordered_map<std::string, FlatbuffersExtractor> flatbuffers_extractors_;
#endif
  bool enable_lidar_vertical_{true};
  std::optional<vlink::BagProcessor> processor_;
};

}  // namespace vmsgs

VLINK_PLUGIN_DECLARE(vmsgs::BagPlugin, 2, 0)
