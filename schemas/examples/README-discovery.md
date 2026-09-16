<!--
Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
Security Alliance (GEISA), a Series of LF Projects, LLC

Licensed under the Apache License, Version 2.0. See LICENSE.
-->

# Platform Discovery examples

These examples demonstrate GEISA Platform Discovery request and response
protobuf payloads:

- `GeisaPlatformDiscovery_Req`
- `GeisaPlatformDiscovery_Rsp`

The embedded C response example includes device, metrology, sensor, network,
and waveform metadata. Waveform frame delivery remains a separate example path.

## Build

From the repository root:

    make clean
    make examples

Build the embedded C discovery examples with an external nanopb runtime
checkout:

    make examples-discovery NANOPB_DIR=/path/to/nanopb

Compiled binaries are written to:

    build/examples/

The embedded C Platform Discovery examples are the supported path in this
branch.

## Quick start

Run the embedded C request walkthrough:

    build/examples/discovery_write_request_example_c --demo

This writes the standard `/tmp` discovery request payload and then decodes it
immediately.

Run the embedded C response walkthrough:

    build/examples/discovery_write_response_example_c --demo

This writes the standard `/tmp` discovery response payload and then decodes it
immediately.

Decode both standard `/tmp` payloads:

    build/examples/discovery_read_example_c --demo

The reader `--demo` path is decode-only and expects those standard `/tmp`
payloads to already exist.

## Manual write + read loop

Write sample binary discovery payloads:

    build/examples/discovery_write_request_example_c /tmp/discovery-request.bin
    build/examples/discovery_write_response_example_c /tmp/discovery-response.bin

Decode those payloads:

    build/examples/discovery_read_example_c --req /tmp/discovery-request.bin
    build/examples/discovery_read_example_c --rsp /tmp/discovery-response.bin
