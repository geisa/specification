//-----------------------------------------------------------------------------
// Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
// Security Alliance (GEISA), a Series of LF Projects, LLC
//
// Licensed under the Apache License, Version 2.0. See LICENSE.
//-----------------------------------------------------------------------------
//
// Example GEISA app-message embedded C decoder.
//
// This example decodes GeisaAppMessage_Req or GeisaAppMessage_Rsp from a
// binary protobuf file and prints a JSON-like representation. Opaque payload
// bytes are rendered as hex so the output stays readable in a terminal.
//
// `--demo` reads the standard `/tmp` request and response payloads.
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers/app_message_example_utils.h"

static int run_demo(void)
{
    puts("Running app-message read demo...");
    return app_message_run_demo_walkthrough();
}

int main(int argc, char *argv[])
{
    if (argc == 2 && strcmp(argv[1], "--demo") == 0)
    {
        return run_demo();
    }

    if (argc != 3)
    {
        fprintf(stderr, "usage: %s --req|--rsp payload.bin | --demo\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "--req") == 0)
    {
        return app_message_decode_and_print_req_file(argv[2]);
    }
    if (strcmp(argv[1], "--rsp") == 0)
    {
        return app_message_decode_and_print_rsp_file(argv[2]);
    }

    fprintf(stderr, "unknown mode: %s\n", argv[1]);
    return EXIT_FAILURE;
}
