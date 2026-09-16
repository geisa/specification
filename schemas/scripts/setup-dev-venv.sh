#!/bin/sh
#-----------------------------------------------------------------------------
# Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
# Security Alliance (GEISA), a Series of LF Projects, LLC
#
# Licensed under the Apache License, Version 2.0. See LICENSE.
#-----------------------------------------------------------------------------

set -eu

ROOT_DIR="$(CDPATH= cd -- "$(dirname "$0")/.." && pwd)"
VENV_DIR="$ROOT_DIR/venv"
PYTHON_BIN="${PYTHON:-python3}"

echo "Using Python interpreter: $PYTHON_BIN"

if ! command -v "$PYTHON_BIN" >/dev/null 2>&1; then
  echo "Python interpreter not found: $PYTHON_BIN" >&2
  exit 1
fi

if [ ! -d "$VENV_DIR" ]; then
  echo "Creating repository venv at $VENV_DIR"
  "$PYTHON_BIN" -m venv "$VENV_DIR"
else
  echo "Reusing repository venv at $VENV_DIR"
fi

VENV_PYTHON="$VENV_DIR/bin/python"

if [ ! -x "$VENV_PYTHON" ]; then
  echo "Repository venv is missing $VENV_PYTHON" >&2
  exit 1
fi

echo "Upgrading pip, setuptools, and wheel"
"$VENV_PYTHON" -m pip install --upgrade pip setuptools wheel

echo "Installing Python development dependencies"
"$VENV_PYTHON" -m pip install -r "$ROOT_DIR/requirements-dev.txt"

cat <<EOF

Repository venv is ready.

Next embedded C example build:
  test -d /tmp/nanopb/.git || git clone https://github.com/nanopb/nanopb /tmp/nanopb
  make examples-c

The Makefile uses the repository venv Python directly when available, so shell
activation of venv is not required for Makefile targets.

Use NANOPB_DIR or NANOPB_RUNTIME_DIR only if your nanopb checkout lives
somewhere other than /tmp/nanopb.

Use NANOPB_GENERATOR or NANOPB_GENERATOR_MODULE only when you need to override
the default generator path explicitly.
EOF
