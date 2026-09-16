# GEISA schemas

This repository contains the [protobuf](https://protobuf.dev/) and
[JSON Schema](https://json-schema.org/) schemas used by the
[Grid Edge Interoperability and Security Alliance
Specification](https://github.com/geisa/specification).

These schemas define message structures used by the GEISA API, message bus,
application manifests, profiles, and related examples.

For full documentation and context, refer to the
[GEISA Specification][geisa-spec].

## Repository contents

At a high level, this repository contains:

- `*.proto` files for protobuf message definitions
- `geisa-*-schema.json` files for JSON Schema definitions
- `profiles/*.json` files for additive conformance and capability profile
  overlays
- `examples/*.json` example payloads
- `examples/*.c` embedded C protobuf examples using nanopb.
- `examples/*.cpp` files with C++ protobuf encode/decode examples.
- `examples/helpers/*.h` files with shared example-only helper code.
- `examples/README*.md` example-specific build and run notes.

This schemas repository SHALL be used in conjunction with the GEISA
specification to enable creation of GEISA conformant implementations. The
content is intended to help users understand the structure, conformance, and
intent of GEISA messages and payloads.

Most API message payloads are covered in the GEISA specification as well as
here in the proto files, documented in JSON schemas, example code, and
further documented in this repo with example payload contents.

For items with proto files, the proto files are authoritative, while JSON
schemas, examples, and any conflicting documentation in the GEISA specification
for the same item are not.

Profile schemas under `profiles/` are additive overlays on top of the base JSON
schemas. They are intended for conformance validation and implementation
guidance for a specific device/device class or capability profile without
implying that all GEISA-conformant devices must implement all APIs or expose
all measurements.

## Prerequisites

The repository build targets assume these tools are available on `PATH`:

- `make`
- `protoc` (Protocol Buffers compiler)

Linting uses Node.js and `npm`. Install the repository Node dependencies before
running lint commands:

    npm ci

Generated outputs are written under `build/`.

The preferred C example path requires:

- a nanopb generator available either as `protoc-gen-nanopb` or through
  `NANOPB_GENERATOR_MODULE=nanopb.generator.nanopb_generator`
- a nanopb source checkout containing `pb_common.c`, `pb_encode.c`,
  `pb_decode.c`, and the matching headers, passed via `NANOPB_DIR=...` or
  `NANOPB_RUNTIME_DIR=...`

`NANOPB_DIR` or `NANOPB_RUNTIME_DIR` should point at the root of an external
nanopb source checkout that contains the runtime C sources and headers such as
`pb_common.c`, `pb_encode.c`, `pb_decode.c`, `pb.h`, `pb_encode.h`, and
`pb_decode.h`. Pointing only at a pip-installed Python package is not
sufficient because it does not include those runtime C source files.

The repository convention is to keep nanopb sidecar generator settings under
`nanopb_options/`. In this repository:

- `*.proto` files define the GEISA protobuf wire/API contract
- `geisa-*-schema.json` files define the JSON validation contract
- `nanopb_options/*.options` files define nanopb sidecar generation settings
  for this repository's embedded C examples

The `.options` bounds support generated example code and embedded C memory
layout. They are not GEISA protocol limits and do not define universal device
requirements.

The supported nanopb generator environment is the repository `venv`. Create or
refresh it with:

    make setup-dev

The embedded C runtime C files still come from an external nanopb source
checkout. By default, the Makefile uses `/tmp/nanopb` when it contains the
required nanopb runtime sources; use `NANOPB_DIR` or `NANOPB_RUNTIME_DIR` to
point at a different checkout.

The C++ example build target also requires:

- a C++17 compiler, such as `c++`, `g++`, or `clang++`
- `pkg-config`
- protobuf development headers and libraries discoverable through
  `pkg-config protobuf`

The legacy C generation target (`make c`) requires protobuf-c support,
including `protoc-gen-c` on `PATH`. It is a best-effort generator path and is
not the supported embedded C path for protos that use proto3 optional fields.

## Building protobuf outputs

The Makefile generates protobuf outputs into `build/`.

Build the default repository targets:

    make

Generate C++ protobuf bindings:

    make cpp

Generate C protobuf bindings using `protoc-c`:

    make c

Generate Java protobuf bindings:

    make java

Generate Python protobuf bindings:

    make python

Generate actuator embedded C bindings only:

    make actuator-c

Generate app-message embedded C bindings only:

    make app-message-c

Generate conn-status embedded C bindings only:

    make conn-status-c

Generate sensor embedded C bindings only:

    make sensor-c

Generate Platform Discovery embedded C bindings only:

    make discovery-c

Generate metered quantities embedded C bindings only:

    make metered-c

Build the default example set:

    make examples

Build examples if needed and run the supported example demo programs:

    make demos

Build the default repository targets:

    make

Build the embedded C example set explicitly:

    make examples-c NANOPB_DIR=/path/to/nanopb

Build the currently supported C++ example set explicitly
(`waveform_subscribe_and_read` only):

    make examples-cpp

Generate all supported language outputs:

    make langs

Show the top-level build target summary:

    make help

Clean generated outputs:

    make clean

The top-level `Makefile` is the human entrypoint and includes the implementation
fragments under `mk/`:

- `mk/proto.mk`
- `mk/nanopb.mk`
- `mk/examples.mk`

When `/tmp/nanopb` already exists as a valid nanopb checkout, `make` and
`make examples` build all currently supported examples. Otherwise they build
the supported C++ example set and print the exact primary setup command for the
embedded C path.

The `make langs` target intentionally omits legacy protobuf-c generation so it
does not fail on repo protos that use proto3 optional. Legacy protobuf-c code
generation remains available separately through `make c`.

Currently, waveform remains on the C++ example path. The embedded C examples
cover actuator, app-message, conn-status, sensor, Platform Discovery, and
metered quantities payloads.

## Examples

Example-specific build and run instructions are in the `examples/` directory:

- `examples/README.md`
- `examples/README-actuators.md`
- `examples/README-conn-status.md`
- `examples/README-discovery.md`
- `examples/README-metered-quantities.md`
- `examples/README-networking.md`
- `examples/README-waveform.md`
- `examples/README-sensors.md`

You can build the default example workflow directly from the repository root:

    make examples

To build examples if needed and run the supported example demo programs:

    make demos

For the default repository build:

    make

To build the currently supported C++ examples explicitly
(`waveform_subscribe_and_read` only):

    make examples-cpp

To build the embedded C example set explicitly:

    make examples-c NANOPB_DIR=/path/to/nanopb

This compiles the example binaries into `build/examples/`.

A typical embedded C workflow from the repository root is:

    make setup-dev
    test -d /tmp/nanopb/.git || git clone https://github.com/nanopb/nanopb /tmp/nanopb
    make clean
    make examples-c

The Makefile uses the repository `venv` Python directly when available, so
shell activation of the repository `venv` is not required. Once the venv has
been set up and `/tmp/nanopb` contains a nanopb source checkout, subsequent
`make examples` or `make examples-c` will build without issue.

The currently supported C++ example path is waveform:

    make clean
    make examples-cpp

If you already have a working `protoc-gen-nanopb` executable, you can use it
instead by setting `NANOPB_GENERATOR=protoc-gen-nanopb` or an explicit plugin
path as a shorter alternate path.

Then run the relevant binary from `build/examples/`. The topic-specific README
files include additional notes and example command lines for the supported
embedded C and C++ examples.

Embedded C examples are the preferred example path for this repo as the
nanopb-based build enables proper proto3 optional support. The remaining C++
example is for waveform, which does not yet have an equivalent C example but
will be updated in the future.

For the C examples, writer `--demo` modes are the primary end-to-end
walkthrough entry points: they generate payloads in `/tmp` and then
read them back through the companion decoder. Reader `--demo` modes are
decode-only and expect those `/tmp` payloads to already exist.

## Lint and validation

Linting is optional for consumers who only need to generate protobuf outputs,
but contributors should run it before opening pull requests.

After installing Node.js/`npm` and running `npm ci`, run all repository lint
checks with:

    npm run lint

To run markdown lint only:

    npm run lint:md

To run JSON syntax validation only:

    npm run lint:json

The lint baseline checks repository markdown and validates JSON files for
parseable JSON syntax. It does not perform JSON Schema semantic validation,
protobuf linting, or C/C++ formatting.

[geisa-spec]: https://github.com/geisa/specification
