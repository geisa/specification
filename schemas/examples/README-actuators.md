<!--
Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
Security Alliance (GEISA), a Series of LF Projects, LLC

Licensed under the Apache License, Version 2.0. See LICENSE.
-->

# Actuator Examples

This guide covers GEISA actuator query and control example payloads and the
companion protobuf reader/writer examples.

Actuator operations are permission-gated by deployment manifest and platform
policy. Examples here show payload structure and expected request/response
patterns only; they are not safety or authorization workflow definitions.

Note that the JSON files are human-readable schema examples. Runtime GEISA
actuator messages use protobuf payloads; JSON examples are provided for review,
diagnostics, tooling, and tests that convert protobuf messages to JSON.

## Build

From the repository root:

    make clean
    make examples

To build the embedded C actuator examples:

    make actuator-c NANOPB_GENERATOR=protoc-gen-nanopb
    make examples-actuator NANOPB_GENERATOR=protoc-gen-nanopb \
      NANOPB_DIR=/path/to/nanopb

Example binaries are written to:

    build/examples/

The embedded C actuator examples are the supported path in this repo.

## Example JSON files

- `actuator-get-request-service-switch-example.json`
- `actuator-get-response-service-switch-closed-example.json`
- `actuator-set-request-load-control-relay-example.json`
- `actuator-set-response-accepted-example.json`

## Embedded C examples

- `build/examples/actuator_read_example_c`
- `build/examples/actuator_write_response_example_c`

The embedded C reader uses the same explicit decode modes:

    build/examples/actuator_read_example_c --get-req <file>
    build/examples/actuator_read_example_c --get-rsp <file>
    build/examples/actuator_read_example_c --set-req <file>
    build/examples/actuator_read_example_c --set-rsp <file>

`actuator_write_response_example_c --demo` is the primary end-to-end
walkthrough: it writes the standard `/tmp` payloads and then decodes them.

`actuator_read_example_c --demo` is decode-only and expects those standard
`/tmp` payloads to already exist.

The embedded C writer emits the standard `/tmp` payloads with no arguments and
runs the end-to-end walkthrough with:

    build/examples/actuator_write_response_example_c --demo
