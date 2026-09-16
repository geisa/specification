//-----------------------------------------------------------------------------
// Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
// Security Alliance (GEISA), a Series of LF Projects, LLC
//
// Licensed under the Apache License, Version 2.0. See LICENSE.
//-----------------------------------------------------------------------------
//
// Example GEISA conn-status embedded C decoder.
//
// This example decodes GeisaPlatformStatus, GeisaPlatformToAppStatus, or
// GeisaAppToPlatformStatus from a binary protobuf file and prints a JSON-like
// representation for logging or diagnostics.
//
// `--demo` reads the standard `/tmp` payload set written by
// conn_status_write_example_c.
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers/conn_status_example_utils.h"

int main(int argc, char *argv[])
{
    if (argc == 2 && strcmp(argv[1], "--demo") == 0)
    {
        puts("Running conn-status read demo...");
        return conn_status_run_demo_walkthrough();
    }

    if (argc != 3)
    {
        fprintf(stderr, "usage: %s --platform|--to-app|--from-app payload.bin | --demo\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "--platform") == 0)
    {
        return conn_status_decode_and_print_platform_status_file(argv[2]);
    }
    if (strcmp(argv[1], "--to-app") == 0)
    {
        return conn_status_decode_and_print_platform_to_app_file(argv[2]);
    }
    if (strcmp(argv[1], "--from-app") == 0)
    {
        return conn_status_decode_and_print_app_to_platform_file(argv[2]);
    }

    fprintf(stderr, "unknown mode: %s\n", argv[1]);
    return EXIT_FAILURE;
}
