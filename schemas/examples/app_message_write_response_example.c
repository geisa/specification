//-----------------------------------------------------------------------------
// Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
// Security Alliance (GEISA), a Series of LF Projects, LLC
//
// Licensed under the Apache License, Version 2.0. See LICENSE.
//-----------------------------------------------------------------------------
//
// Example GEISA app-message embedded C writer.
//
// This example writes one GeisaAppMessage_Req payload and one
// GeisaAppMessage_Rsp payload. 
// `--demo` is the main walkthrough entry point and immediately decodes both 
// through the companion reader.
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers/app_message_example_utils.h"

int main(int argc, char *argv[])
{
    const bool demo_mode = (argc == 2 && strcmp(argv[1], "--demo") == 0);
    const bool positional = (argc == 3 && !demo_mode);
    const bool default_mode = (argc == 1);
    const char *req_path = default_mode || demo_mode ? GEISA_APP_MESSAGE_REQ_PATH : argv[1];
    const char *rsp_path = default_mode || demo_mode ? GEISA_APP_MESSAGE_RSP_PATH : argv[2];
    GeisaAppMessage_Req req;
    GeisaAppMessage_Rsp rsp;

    if (!default_mode && !demo_mode && !positional)
    {
        fprintf(stderr, "usage: %s [req.bin rsp.bin | --demo]\n", argv[0]);
        return EXIT_FAILURE;
    }

    fill_demo_app_message_req(&req);
    fill_demo_app_message_rsp(&rsp);

    if (!geisa_write_message_file(req_path, GeisaAppMessage_Req_fields, &req) ||
        !geisa_write_message_file(rsp_path, GeisaAppMessage_Rsp_fields, &rsp))
    {
        return EXIT_FAILURE;
    }

    if (!demo_mode)
    {
        printf("wrote %s\n", req_path);
        printf("wrote %s\n", rsp_path);
        return EXIT_SUCCESS;
    }

    puts("Running app-message write demo...");
    puts("Writing request and response payloads to /tmp");
    puts("Decoding both app-message demo payloads immediately for walkthrough output");
    return app_message_run_demo_walkthrough();
}
