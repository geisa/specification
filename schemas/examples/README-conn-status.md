<!--
Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
Security Alliance (GEISA), a Series of LF Projects, LLC

Licensed under the Apache License, Version 2.0. See LICENSE.
-->

# Connection status examples

These examples demonstrate GEISA platform and app connection status payloads:

- `GeisaPlatformStatus`
- `GeisaPlatformToAppStatus`
- `GeisaAppToPlatformStatus`

## Build

From the repository root:

    make clean
    make examples

Building the embedded C conn-status examples with an external nanopb runtime
checkout:

    make examples-conn-status NANOPB_DIR=/path/to/nanopb

Compiled binaries are written to:

    build/examples/

The embedded C conn-status examples are the preferred path in this repo. A
matching C++ example family does not exist here.

## Quick start

Run the embedded C writer walkthrough:

    build/examples/conn_status_write_example_c --demo

This is the primary end-to-end walkthrough: it writes the standard `/tmp`
conn-status payload set and then decodes all three payloads immediately.

Decode the standard `/tmp` conn-status payloads:

    build/examples/conn_status_read_example_c --demo

The reader `--demo` path is decode-only and expects those standard `/tmp`
payloads to already exist.

## Manual write + read loop

Write sample binary conn-status payloads:

    build/examples/conn_status_write_example_c

Decode those payloads:

    build/examples/conn_status_read_example_c --platform /tmp/conn-status-platform-status.bin
    build/examples/conn_status_read_example_c --to-app /tmp/conn-status-platform-to-app-status.bin
    build/examples/conn_status_read_example_c --from-app /tmp/conn-status-app-to-platform-status.bin
