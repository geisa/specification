//-----------------------------------------------------------------------------
// Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
// Security Alliance (GEISA), a Series of LF Projects, LLC
//
// Licensed under the Apache License, Version 2.0. See LICENSE.
//-----------------------------------------------------------------------------
//
// Example GEISA Platform Discovery embedded C request writer.
//
// This example writes a GeisaPlatformDiscovery_Req payload. `--demo` writes
// the standard `/tmp` request payload and immediately decodes it through the
// companion reader.
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers/discovery_example_utils.h"

int main(int argc, char *argv[])
{
    const bool demo_mode = (argc == 2 && strcmp(argv[1], "--demo") == 0);
    const bool default_mode = (argc == 1);
    const bool positional = (argc == 2 && !demo_mode);
    const char *path = default_mode || demo_mode ? GEISA_DISCOVERY_REQUEST_PATH : argv[1];
    GeisaPlatformDiscovery_Req request;

    if (!default_mode && !demo_mode && !positional)
    {
        fprintf(stderr, "usage: %s [request.bin | --demo]\n", argv[0]);
        return EXIT_FAILURE;
    }

    fill_demo_discovery_req(&request);
    if (!geisa_write_message_file(path, GeisaPlatformDiscovery_Req_fields, &request))
    {
        return EXIT_FAILURE;
    }

    if (!demo_mode)
    {
        printf("wrote %s\n", path);
        return EXIT_SUCCESS;
    }

    puts("Running Platform Discovery request write demo...");
    puts("Writing discovery request payload to /tmp");
    puts("Decoding the request payload immediately for walkthrough output");
    return discovery_decode_and_print_request_file(GEISA_DISCOVERY_REQUEST_PATH);
}
