#!/bin/sh
#-----------------------------------------------------------------------------
# Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
# Security Alliance (GEISA), a Series of LF Projects, LLC
#
# Licensed under the Apache License, Version 2.0. See LICENSE.
#-----------------------------------------------------------------------------
#
# Purpose:
#   Build example binaries when needed and run the supported GEISA example
#   demo walkthroughs from a repository checkout.
#
# Responsibilities:
#   - detect whether source-present demo binaries are missing
#   - invoke make examples when a build is needed
#   - run writer demos that perform end-to-end write/read checks
#   - run the self-contained waveform demo
#   - skip branch-dependent demos whose source files are absent
#
# This script is intentionally a lightweight local validation helper. It is
# not part of the GEISA API contract and its diagnostic output is not a
# normative JSON schema artifact.

set -eu

# Resolve the repository root from the script path so callers can run this from
# any working directory.
ROOT_DIR="$(CDPATH= cd -- "$(dirname "$0")/.." && pwd)"
cd "$ROOT_DIR"

# Set when a demo source exists but its expected binary has not been built.
needs_build=no

section()
{
  printf '\n==> %s\n' "$1"
}

check_demo_binary()
{
  source_path="$1"
  binary_path="$2"

  # Source presence makes the demo branch-relevant; binary absence means one
  # shared example build should happen before any demo runs.
  if [ -f "$source_path" ] && [ ! -x "$binary_path" ]; then
    needs_build=yes
  fi
}

# Branch-dependent source absence is a SKIP, but a missing binary for a present
# source remains an error after the build step.
run_demo()
{
  label="$1"
  source_path="$2"
  binary_path="$3"
  shift 3

  section "$label"

  if [ ! -f "$source_path" ]; then
    printf 'SKIP %s (source not present on this branch)\n' "$binary_path"
    return
  fi

  if [ ! -x "$binary_path" ]; then
    printf 'ERROR: required demo binary missing after make examples: %s\n' "$binary_path" >&2
    exit 1
  fi

  "$binary_path" "$@"
}

check_demo_binary examples/actuator_write_response_example.c build/examples/actuator_write_response_example_c
check_demo_binary examples/app_message_write_response_example.c build/examples/app_message_write_response_example_c
check_demo_binary examples/conn_status_write_example.c build/examples/conn_status_write_example_c
check_demo_binary examples/discovery_write_request_example.c build/examples/discovery_write_request_example_c
check_demo_binary examples/discovery_write_response_example.c build/examples/discovery_write_response_example_c
check_demo_binary examples/sensor_write_response_example.c build/examples/sensor_write_response_example_c
check_demo_binary examples/metered_quantities_write_example.c build/examples/metered_quantities_write_example_c
check_demo_binary examples/waveform_subscribe_and_read.cpp build/examples/waveform_subscribe_and_read

if [ "$needs_build" = yes ]; then
  # Build examples once before demo execution instead of rebuilding per binary.
  section "Building examples"
  make examples
fi

# Writer --demo paths generate standard payloads and immediately decode them,
# making them the preferred end-to-end checks for embedded C examples.
run_demo "Actuator writer demo" \
  examples/actuator_write_response_example.c \
  build/examples/actuator_write_response_example_c \
  --demo

run_demo "App-message writer demo" \
  examples/app_message_write_response_example.c \
  build/examples/app_message_write_response_example_c \
  --demo

run_demo "Connection status writer demo" \
  examples/conn_status_write_example.c \
  build/examples/conn_status_write_example_c \
  --demo

run_demo "Platform Discovery request writer demo" \
  examples/discovery_write_request_example.c \
  build/examples/discovery_write_request_example_c \
  --demo

run_demo "Platform Discovery response writer demo" \
  examples/discovery_write_response_example.c \
  build/examples/discovery_write_response_example_c \
  --demo

run_demo "Sensor writer demo" \
  examples/sensor_write_response_example.c \
  build/examples/sensor_write_response_example_c \
  --demo

run_demo "Metered quantities writer demo" \
  examples/metered_quantities_write_example.c \
  build/examples/metered_quantities_write_example_c \
  --demo

# Waveform is a self-contained C++ response/frame validation demo.
run_demo "Waveform demo" \
  examples/waveform_subscribe_and_read.cpp \
  build/examples/waveform_subscribe_and_read \
  --demo
