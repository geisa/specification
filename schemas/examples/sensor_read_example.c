//-----------------------------------------------------------------------------
// Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
// Security Alliance (GEISA), a Series of LF Projects, LLC
//
// Licensed under the Apache License, Version 2.0. See LICENSE.
//-----------------------------------------------------------------------------
//
// Example GEISA sensor embedded C decoder.
//
// This example decodes a GeisaSensorReadings_Rsp protobuf payload and prints a
// JSON-like representation for logging, diagnostics, or downstream tooling.
//
// `--demo` reads the standard `/tmp` payload written by
// sensor_write_response_example_c.
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers/sensor_example_utils.h"

int main(int argc, char *argv[])
{
    if (argc == 2 && strcmp(argv[1], "--demo") == 0)
    {
        puts("Running sensor read demo...");
        return sensor_run_demo_walkthrough();
    }

    if (argc != 2)
    {
        fprintf(stderr, "usage: %s response.bin | --demo\n", argv[0]);
        return EXIT_FAILURE;
    }

    return sensor_decode_and_print_response_file(argv[1]);
}
