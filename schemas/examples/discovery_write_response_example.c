//-----------------------------------------------------------------------------
// Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
// Security Alliance (GEISA), a Series of LF Projects, LLC
//
// Licensed under the Apache License, Version 2.0. See LICENSE.
//-----------------------------------------------------------------------------
//
// Example GEISA Platform Discovery embedded C response writer.
//
// This example creates a sample GeisaPlatformDiscovery_Rsp payload and writes
// it to a binary file for decoding with the companion reader. `--demo` is the
// main walkthrough entry point.
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers/discovery_example_utils.h"

int main(int argc, char *argv[])
{
    const bool demo_mode = (argc == 2 && strcmp(argv[1], "--demo") == 0);
    const bool write_rsp_mode = (argc == 3 && strcmp(argv[1], "--write-rsp-sample") == 0);
    const bool default_mode = (argc == 1);
    const bool positional = (argc == 2 && !demo_mode);
    const char *path = default_mode || demo_mode ? GEISA_DISCOVERY_RESPONSE_PATH :
                                                  (write_rsp_mode ? argv[2] : argv[1]);
    GeisaPlatformDiscovery_Rsp response;

    if (!default_mode && !demo_mode && !positional && !write_rsp_mode)
    {
        fprintf(stderr, "usage: %s [response.bin | --write-rsp-sample response.bin | --demo]\n", argv[0]);
        return EXIT_FAILURE;
    }

    fill_demo_discovery_rsp(&response);
    if (!geisa_write_message_file(path, GeisaPlatformDiscovery_Rsp_fields, &response))
    {
        return EXIT_FAILURE;
    }

    if (!demo_mode)
    {
        printf("wrote %s\n", path);
        return EXIT_SUCCESS;
    }

    puts("Running Platform Discovery response write demo...");
    puts("Writing discovery response payload to /tmp");
    puts("Decoding the response payload immediately for walkthrough output");
    return discovery_decode_and_print_response_file(GEISA_DISCOVERY_RESPONSE_PATH);
}
