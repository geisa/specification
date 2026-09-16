<!--
Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
Security Alliance (GEISA), a Series of LF Projects, LLC

Licensed under the Apache License, Version 2.0. See LICENSE.
-->

# Sensor examples

These examples demonstrate GEISA sensor request/response payload patterns using
JSON examples plus protobuf writer/reader flows.

The embedded C examples exercise:

- proto3 optional presence for reading metadata such as unit, quality, and
  status
- repeated sensor values in a single reading
- oneof sensor values through the `double-value` path

JSON examples in this directory include:

- `sensor-readings-request-example.json`
- `sensor-temperature-example.json`
- `sensor-temperature-reading-example.json`
- `sensor-temperature-response-example.json`

## Build

From the repository root:

    make clean
    make examples

Build the embedded C sensor examples with an external nanopb runtime checkout:

    make examples-sensor NANOPB_DIR=/path/to/nanopb

Compiled binaries are written to:

    build/examples/

The embedded C sensor examples are the supported path in this repo.

## Quick start

Run the embedded C writer walkthrough:

    build/examples/sensor_write_response_example_c --demo

This is the primary end-to-end walkthrough: it writes the standard `/tmp`
sensor payload and then decodes it immediately.

Run the embedded C reader walkthrough for the standard `/tmp` payload:

    build/examples/sensor_read_example_c --demo

The reader `--demo` path is decode-only and expects that standard `/tmp`
payload to already exist.

## Manual write + read loop

Write a sample sensor response payload:

    build/examples/sensor_write_response_example_c /tmp/sensor-response.bin

Decode that payload:

    build/examples/sensor_read_example_c /tmp/sensor-response.bin
