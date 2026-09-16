<!--
Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
Security Alliance (GEISA), a Series of LF Projects, LLC

Licensed under the Apache License, Version 2.0. See LICENSE.
-->

# GEISA Schema Examples

This directory contains reference example code for GEISA schema and protobuf
envelope examples.

The remaining C++ example emits and decodes binary protobuf envelopes for the
waveform control-plane path. The embedded C examples use nanopb for the same
protobuf message contracts in the actuator, app-message, conn-status, sensor,
Platform Discovery, and metered quantities areas.

For the embedded C path, writer `--demo` modes are the primary end-to-end
walkthrough entry points: they generate payloads in `/tmp` and then decode
them immediately. Reader `--demo` modes are decode-only and expect those
standard `/tmp` payloads to already exist.

## Building examples

From the repository root:

    make clean
    make examples

To build examples if needed and run the demo-capable example binaries:

    make demos

Or run the default top-level entrypoint:

    make

Compiled example binaries are written to:

    build/examples/

The embedded C build uses the repository `venv` for nanopb generation plus an
external nanopb runtime source tree:

    make setup-dev
    test -d /tmp/nanopb/.git || git clone https://github.com/nanopb/nanopb /tmp/nanopb
    make examples-c

The Makefile uses the repository `venv` Python directly when available, so
shell activation of the repository `venv` is not required.  The build will
use the repository venv Python directly when available.

If you already have a working `protoc-gen-nanopb` executable, you can use it
instead by setting `NANOPB_GENERATOR=protoc-gen-nanopb` or an explicit plugin
path.

Target summary:

- `make` / `make all`: default repo artifacts plus all supported examples that
  can be built with the available tools
- `make langs`: supported binding/code generation only; no example binaries
- `make examples`: all supported example binaries
- `make demos`: build examples if needed and run the demo-capable example
  binaries
- `make examples-c`: embedded C / nanopb examples and clear prerequisite
  failure when nanopb is not ready
- `make examples-cpp`: active C++ example binaries
  (`waveform_subscribe_and_read` only)
- `make help`: concise target summary from the top-level Makefile

## Directory organization

- `*.c`: embedded C protobuf writer/reader examples using nanopb
- `*.cpp`: C++ protobuf writer/reader examples
- `*.json`: JSON examples aligned to schemas
- `helpers/*.h`: shared example-only helper utilities
- `README-*.md`: topic-specific guides

## Topic guides

- Platform Discovery: `README-discovery.md`
- Metered quantities: `README-metered-quantities.md`
- Connection status: `README-conn-status.md`
- Networking / app-message: `README-networking.md`
- Actuators: `README-actuators.md`
- Sensors: `README-sensors.md`
- Waveform: `README-waveform.md`
- Application manifests: `README-manifests.md`

## C++ and embedded C paths

Embedded C examples are available for:

- actuators
- app-message / networking
- conn-status
- sensors
- Platform Discovery
- metered quantities

Embedded C examples are the preferred example path for this repository because
the nanopb-based build supports proto3 optional fields.

The legacy `make c` protobuf-c generation path remains available for standalone
code generation, but it is not the primary C example path for this repository.

The currently supported C++ example path is waveform. The Platform Discovery
embedded C example includes waveform metadata in the discovery response; it
does not convert the waveform frame example path.

When `/tmp/nanopb` already exists as a valid nanopb checkout, `make` and
`make examples` build the supported C++ and embedded C example sets. Use
`make examples-c` when you want the embedded C path explicitly and fail-fast on
missing nanopb prerequisites.

`make demos` uses the same embedded C / nanopb prerequisites as the embedded C
example builds.

Note that these examples are not part of the GEISA API specification, and do
not imply that GEISA applications must be written in C or C++. GEISA APIs are
defined at the protocol level using MQTT topics and protobuf envelopes, with
some payloads carrying opaque application bytes selected by `content-type`.
Applications may use the MQTT/protobuf implementation that best fits their
execution environment, language, and platform constraints.

## Retired C++ example code

The following C++ example sources were retired after equivalent embedded C /
nanopb examples were added:

- `examples/actuator_read_example.cpp`
- `examples/actuator_write_response_example.cpp`
- `examples/app_message_read_example.cpp`
- `examples/app_message_write_response_example.cpp`
- `examples/discovery_read_example.cpp`
- `examples/discovery_write_request_example.cpp`
- `examples/discovery_write_response_example.cpp`
- `examples/sensor_read_example.cpp`
- `examples/sensor_write_response_example.cpp`

They remain available in git history. To retrieve one later:

- `git log -- examples/<file>.cpp`
- `git show <commit>:examples/<file>.cpp`
