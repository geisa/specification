//-----------------------------------------------------------------------------
// Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
// Security Alliance (GEISA), a Series of LF Projects, LLC
//
// Licensed under the Apache License, Version 2.0. See LICENSE.
//-----------------------------------------------------------------------------
//
// Example GEISA Platform Discovery embedded C decoder.
//
// This example decodes GeisaPlatformDiscovery_Req or
// GeisaPlatformDiscovery_Rsp from a binary protobuf file and prints a
// JSON-like representation for logging, diagnostics, or handoff into other
// tooling.
//
// `--demo` reads the standard `/tmp` request and response payloads.
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers/discovery_example_utils.h"

int main(int argc, char *argv[])
{
    if (argc == 2 && strcmp(argv[1], "--demo") == 0)
    {
        puts("Running Platform Discovery read demo...");
        return discovery_run_demo_walkthrough();
    }

    if (argc != 3)
    {
        fprintf(stderr, "usage: %s --req request.bin | --rsp response.bin | --demo\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "--req") == 0)
    {
        return discovery_decode_and_print_request_file(argv[2]);
    }
    if (strcmp(argv[1], "--rsp") == 0)
    {
        return discovery_decode_and_print_response_file(argv[2]);
    }

    fprintf(stderr, "unknown mode: %s\n", argv[1]);
    return EXIT_FAILURE;
}
