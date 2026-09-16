<!--
Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
Security Alliance (GEISA), a Series of LF Projects, LLC

Licensed under the Apache License, Version 2.0. See LICENSE.
-->

# Waveform example (C++)

This is the remaining supported C++ example in this repo.

This example demonstrates GEISA waveform control-plane protobuf payloads and
the waveform frame format (geisa_waveform_frame).

It currently supports two use cases:

1) **Local demo (no platform required)**: `--demo` generates a realistic sample
   `GeisaWaveform_Rsp` payload and a single `geisa_waveform_frame` sample, then
    decodes and prints a summary plus the first 10 time steps in both raw and
    scaled units.

2) **Platform response decode**: `--read-rsp <file>` parses a captured
  `GeisaWaveform_Rsp` response payload and attempts to read a waveform frame:
   - On Linux: it first attempts to open `socket_path` as an
   `AF_UNIX SOCK_SEQPACKET` socket.
   - On macOS: SOCK_SEQPACKET is not supported so the example uses the file
     fallback path.
   - If that fails, or if `socket_path` is a regular file, it falls back to
     reading raw frame bytes from the file path and decoding them.

## Build

From the repository root, the recommended build path is:

    make clean
    make examples

This generates protobuf sources and compiles the C++ examples into
`build/examples/`.

The manual commands below are retained for developers who want to compile a
single example directly or inspect the exact compiler inputs.

Generate the C++ protobuf sources:

    make clean
    make cpp

Compile the example (should work on most Linux and macOS):

    c++ -std=c++17 -O2 \
      -Ibuild/cpp \
      $(pkg-config --cflags protobuf) \
      examples/waveform_subscribe_and_read.cpp \
      build/cpp/waveform.pb.cc \
      build/cpp/geisa-status.pb.cc \
      $(pkg-config --libs protobuf) \
      -pthread \
      -o /tmp/waveform_subscribe_and_read

If protobuf headers/libs are already on default paths, this also works:

    c++ -std=c++17 -O2 \
      -Ibuild/cpp \
      examples/waveform_subscribe_and_read.cpp \
      build/cpp/waveform.pb.cc \
      build/cpp/geisa-status.pb.cc \
      -lprotobuf -pthread \
      -o /tmp/waveform_subscribe_and_read

## Quick start (recommended)

Using the Makefile-built binary:

    build/examples/waveform_subscribe_and_read --demo

This will create:

- `/tmp/waveform-rsp.bin`
- `/tmp/waveform-rsp.bin.frame`

…and then outputs:

- decoded response metadata (including channel counts, sample type, and optional
  filter metadata)
- frame header fields
- frame summary + per-channel min/max
- first 10 time steps in both raw and scaled units

## Demo output

- `timestamp_ms` is UTC epoch milliseconds; the local demo uses a fixed example
  value.
- Preview shows the first 10 time steps with raw `int16` values and scaled
  engineering units printed to 3 decimal places.
- A per-channel min/max summary is printed for quick waveform sanity checks.

## Control-plane request payload generation

Write a subscribe request payload (protobuf bytes):

    build/examples/waveform_subscribe_and_read --write-req /tmp/waveform-req.bin

The file contains raw bytes of a serialized `GeisaWaveform_Req`. In an actual
integration, these bytes are sent to the platform using your existing GEISA
transport and the platform returns a serialized `GeisaWaveform_Rsp` payload.

## Decoding a captured response payload

If you have captured a real platform response payload to a file (e.g.
  `/tmp/waveform-rsp.bin`):

    build/examples/waveform_subscribe_and_read --read-rsp /tmp/waveform-rsp.bin

If `subscribed=true`, the response includes `socket_path`, which is either:

- a unix socket path (Linux platforms), or
- a file path for the local demo/fallback mode.

The subscribe response also includes per-channel metadata:
`voltage-channel-count`, `current-channel-count`, `other-channel-count`, and
`total-channel-count` (where `total-channel-count == voltage-channel-count +
current-channel-count + other-channel-count`). Optional filter metadata fields
(`voltage-filter-lowpass`, `voltage-filter-highpass`, `current-filter-lowpass`,
`current-filter-highpass`) are present when the platform exposes
hardware/software filter characteristics.
