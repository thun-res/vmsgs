# vmsgs-bag

`vmsgs-bag` is a VLink `BagPluginInterface` 2.0 plugin. On both the read and write paths it extracts the measurement timestamp from vmsgs Protobuf and FlatBuffers messages, or from VLink ZeroCopy messages, and reorders frames through `BagProcessor`. PointCloud vertical-layout conversion remains write-only.

Enable reordering before starting the process:

```bash
export VMSGS_BAG_RESORT=1
export VLINK_PLUGIN_DIR=/path/to/vmsgs/lib
export VLINK_SCHEMA_PLUGIN=vmsgs
vlink-bag record --plugin vmsgs-bag ...
```

The bag plugin resolves Protobuf descriptors and FlatBuffers BFBS metadata at runtime through the loaded vmsgs schema plugin. It does not contain a fixed FlatBuffers message list.

The shared library uses the VMsgs project version while retaining the unversioned plugin name used by the VLink loader.

| Environment variable | Default | Meaning |
| --- | ---: | --- |
| `VMSGS_BAG_LIDAR_VERTICAL` | `1` | Store VLink ZeroCopy `PointCloud` payloads in vertical layout. |
| `VMSGS_BAG_RESORT` | `1` | Set to `0` to disable data-timestamp reordering. |
| `VMSGS_BAG_CACHE_TIME` | `1000` | Reorder window in milliseconds. |
| `VMSGS_BAG_CACHE_SIZE` | `1024` | Maximum buffered payload size in MiB. |
| `VMSGS_BAG_JUMP_TIME` | `10000` | Maximum accepted data-timestamp jump in milliseconds. |

PointCloud layout conversion is independent of reordering; set `VMSGS_BAG_LIDAR_VERTICAL=0` to preserve the input layout.

Timestamp sources are `vmsgs.proto.*.header.time_meas`, `vmsgs.fbs.*.header.time_meas`, and VLink ZeroCopy `header.time_meas`. `ProxyData` uses its microsecond `timestamp` field. Frames without a valid supported timestamp retain the BagProcessor fallback ordering based on their record timestamps.
