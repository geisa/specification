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

From the `specification/schemas/` directory:

    make clean
    make examples

Before building the embedded C examples, complete the nanopb setup described in
`../README.md`: run `make setup-dev` and provide the external nanopb runtime
source checkout. The schemas `venv` does not need to be activated.

Then build the discovery examples:

    make examples-discovery

If the runtime checkout is not under `/tmp/nanopb`, set `NANOPB_DIR` or
`NANOPB_RUNTIME_DIR` to its location.

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
