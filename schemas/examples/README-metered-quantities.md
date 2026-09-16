<!--
Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
Security Alliance (GEISA), a Series of LF Projects, LLC

Licensed under the Apache License, Version 2.0. See LICENSE.
-->

# Metered quantities examples

These examples write and read metered quantity protobuf payloads using the
embedded C generation path (nanopb).

## What the example covers

- GEISA 0.9 AC meter profile required instantaneous scalar fields
- GEISA 0.9 billing profile required billing fields
- proto3 optional scalar presence
- fixed-point electrical values in micro-units
- power factor as a unitless ratio
- billing power factor is interval/window-qualified through
  `measurement-period-s`
- bounded harmonic arrays suitable for nanopb static allocation

Note that the writer `--demo` mode writes both standard `/tmp` payloads and
immediately walks through the instantaneous and billing decode output. The
demo values model a plausible shoulder-season residential snapshot with a
~1,000 kWh/month baseline. Reader `--demo` decodes those same standard `/tmp`
payloads and prints both sections directly.

## Build

From the repository root, prepare the repo `venv` used for nanopb generation:

    bash scripts/setup-dev-venv.sh

After that, direct metered targets such as `make metered-c` and
`make examples-metered` use the repo `venv` automatically unless you override
the nanopb generator settings explicitly.

Generate metered nanopb bindings only:

    make metered-c

To also compile the embedded C metered examples, provide a nanopb source tree
containing `pb_common.c`, `pb_encode.c`, and `pb_decode.c`. The default Makefile
path uses `/tmp/nanopb` when available:

    test -d /tmp/nanopb/.git || git clone https://github.com/nanopb/nanopb /tmp/nanopb
    make examples-metered

Or use the aggregate embedded C example path:

    make examples-c

If you already have a working `protoc-gen-nanopb` executable, you can use it
instead by setting `NANOPB_GENERATOR=...` in place of
`NANOPB_GENERATOR_MODULE=...`.

The embedded C build uses the repo `venv` for generator packaging plus an
external nanopb source tree for the runtime C sources.

`NANOPB_DIR` or `NANOPB_RUNTIME_DIR` should point at the root of an external
nanopb source checkout that contains the runtime C sources and headers such as
`pb_common.c`, `pb_encode.c`, `pb_decode.c`, `pb.h`, `pb_encode.h`, and
`pb_decode.h`. Pointing only at a pip-installed Python package is not
sufficient because it does not include those runtime C source files.

A typical quick-start workflow is:

    make setup-dev
    test -d /tmp/nanopb/.git || git clone https://github.com/nanopb/nanopb /tmp/nanopb
    make examples-metered
    build/examples/metered_quantities_write_example_c --demo

## Run

Write the standard demo payloads to `/tmp`:

    build/examples/metered_quantities_write_example_c

Run the writer quick-start walkthrough:

    build/examples/metered_quantities_write_example_c --demo

Run the reader quick-start walkthrough:

    build/examples/metered_quantities_read_example_c --demo

Decode the instantaneous payload:

    build/examples/metered_quantities_read_example_c instantaneous \
      /tmp/geisa-metered-instantaneous.bin

Decode the billing payload:

    build/examples/metered_quantities_read_example_c billing \
      /tmp/geisa-metered-billing.bin
