###############################################################################
# Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
# Security Alliance (GEISA), a Series of LF Projects, LLC
#
# Licensed under the Apache License, Version 2.0. See LICENSE.
###############################################################################
# Human entrypoint for the GEISA schemas build.
#
# Primary targets:
#   make / make all  - default repo artifacts plus all supported examples
#   make examples    - all supported examples
#   make demos       - build examples if needed and run supported demo programs
#   make examples-c  - explicit embedded C / nanopb examples
#   make examples-cpp - active C++ examples (waveform only)
#   make langs       - supported binding/code generation only (no examples)
#
# Implementation is split under mk/:
#   mk/proto.mk     - standard protobuf descriptor and language generation
#   mk/nanopb.mk    - nanopb generation for embedded C examples
#   mk/examples.mk  - example binary compilation

###############################################################################

.DEFAULT_GOAL := all

PROTOS ?= $(wildcard *.proto)

BUILDDIR ?= build
BINPBDIR := $(BUILDDIR)/binpb
CDIR := $(BUILDDIR)/c
CPPDIR := $(BUILDDIR)/cpp
JAVADIR := $(BUILDDIR)/java
PYTHONDIR := $(BUILDDIR)/python
EXAMPLESDIR := $(BUILDDIR)/examples
NANOPBDIR := $(BUILDDIR)/nanopb

PROTOC ?= protoc
PYTHON ?= $(if $(wildcard $(CURDIR)/venv/bin/python),$(CURDIR)/venv/bin/python,python3)
NANOPB_HOST_PYTHON ?= $(if $(wildcard /usr/local/bin/python3),/usr/local/bin/python3,python3)
NANOPB_GENERATOR ?= protoc-gen-nanopb
NANOPB_DIR ?=
ifeq ($(strip $(NANOPB_DIR)),)
ifneq ($(and $(wildcard /tmp/nanopb/pb_common.c),$(wildcard /tmp/nanopb/pb_encode.c),$(wildcard /tmp/nanopb/pb_decode.c)),)
NANOPB_DIR := /tmp/nanopb
endif
endif
NANOPB_RUNTIME_DIR ?= $(NANOPB_DIR)
NANOPB_OPTIONS_DIR ?= nanopb_options
NANOPB_RUNTIME_DIR_EFFECTIVE := $(strip $(NANOPB_RUNTIME_DIR))
NANOPB_VENV_SITE_PACKAGES := $(firstword $(wildcard $(CURDIR)/venv/lib/python*/site-packages))
NANOPB_GENERATOR_MODULE ?= $(if $(NANOPB_VENV_SITE_PACKAGES),nanopb.generator.nanopb_generator,)

PROTOC_VERSION := $(shell $(PROTOC) --version | awk '{print $$2}')
PROTOC_FLAGS ?=
ifeq ($(shell printf "3.12.0\n$(PROTOC_VERSION)\n" | sort -V | head -n1),3.12.0)
  ifneq ($(shell printf "$(PROTOC_VERSION)\n3.15.0\n" | sort -V | head -n1),3.15.0)
    PROTOC_FLAGS += --experimental_allow_proto3_optional
  endif
endif
PROTOC_OPTS ?= $(PROTOC_FLAGS)
PROTOBUF_CFLAGS := $(shell pkg-config --cflags protobuf 2>/dev/null)
PROTOBUF_LIBS := $(shell pkg-config --libs protobuf 2>/dev/null)

include mk/proto.mk
include mk/nanopb.mk
include mk/examples.mk

all: proto-descriptors examples

setup-dev:
	bash scripts/setup-dev-venv.sh

help:
	@printf '%s\n' \
	  'GEISA schemas build targets:' \
	  '' \
	  'Proto generation:' \
	  '  make / make all    Build default proto descriptors and all supported examples.' \
	  '  make langs         Build supported binding/code-generation outputs only (cpp, java, python).' \
	  '  make c             Generate C bindings via protoc-c (best-effort).' \
	  '  make cpp           Generate C++ protobuf bindings.' \
	  '  make java          Generate Java protobuf bindings.' \
	  '  make python        Generate Python protobuf bindings.' \
	  '' \
	  'Nanopb generation:' \
	  '  make actuator-c    Generate actuator nanopb bindings.' \
	  '  make app-message-c Generate app-message nanopb bindings.' \
	  '  make conn-status-c Generate conn-status nanopb bindings.' \
	  '  make sensor-c      Generate sensor nanopb bindings.' \
	  '  make discovery-c   Generate discovery nanopb bindings.' \
	  '  make metered-c     Generate metered quantities nanopb bindings.' \
	  '' \
	  'Examples:' \
	  '  make examples      Build all supported examples.' \
	  '  make demos         Build examples if needed and run supported demo programs.' \
	  '  make examples-c    Build embedded C / nanopb examples.' \
	  '  make examples-cpp  Build the active C++ example set (waveform only).' \
	  '  make examples-actuator       Build actuator examples only.' \
	  '  make examples-app-message    Build app-message examples only.' \
	  '  make examples-conn-status    Build conn-status examples only.' \
	  '  make examples-sensor         Build sensor examples only.' \
	  '  make examples-discovery      Build discovery examples only.' \
	  '  make examples-metered        Build metered quantities examples only.' \
	  '' \
	  'Utilities:' \
	  '  make clean         Remove generated outputs under build/.' \
	  '  make setup-dev     Refresh the repository venv used for the nanopb module path.'

clean:
	rm -rf $(BUILDDIR)

.PHONY: all setup-dev help clean
