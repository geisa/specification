<!--
Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
Security Alliance (GEISA), a Series of LF Projects, LLC

Licensed under the Apache License, Version 2.0. See LICENSE.
-->

# Networking app-message examples

These examples demonstrate how to write and decode the GEISA app-message
protobuf envelopes for request submission and per-request disposition. The
message payload bytes are opaque and interpreted via `content-type`, not as
protobuf by default.

- `GeisaAppMessage_Req`
- `GeisaAppMessage_Rsp`

MQTT topics:

- App publishes request to `geisa/api/message/upstream/req/<userid>`
- Platform publishes per-request disposition to
  `geisa/api/message/upstream/rsp/<userid>`

Scope notes:

- `GEISA_APP_MESSAGE_STATUS_QUOTA_EXCEEDED` means the platform rejected the
  request because accepting it would exceed an applicable quota or policy
  limit.
- Quota counters, usage, remaining, and reset reporting remain out-of-band via
  Platform/App Status surfaces.
- Deployment Manifest and Platform Discovery cover static policy and allowance
  context.

## Build

From the repository root:

    make clean
    make examples

To build the embedded C app-message examples:

    make app-message-c NANOPB_GENERATOR=protoc-gen-nanopb
    make examples-app-message NANOPB_GENERATOR=protoc-gen-nanopb \
      NANOPB_DIR=/path/to/nanopb

Example binaries are written to:

    build/examples/

The embedded C app-message examples are the supported path in this repo.

## Embedded C examples

- `build/examples/app_message_read_example_c`
- `build/examples/app_message_write_response_example_c`

Quick start:

    build/examples/app_message_write_response_example_c --demo

This is the primary end-to-end walkthrough: it writes the standard `/tmp`
request and response payloads and then decodes both immediately.

`build/examples/app_message_read_example_c --demo` is decode-only and expects
those standard `/tmp` payloads to already exist.

Manual write + read loop:

    build/examples/app_message_write_response_example_c
    build/examples/app_message_read_example_c --req /tmp/app-message-req.bin
    build/examples/app_message_read_example_c --rsp /tmp/app-message-rsp.bin
