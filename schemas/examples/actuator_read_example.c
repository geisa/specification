//-----------------------------------------------------------------------------
// Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
// Security Alliance (GEISA), a Series of LF Projects, LLC
//
// Licensed under the Apache License, Version 2.0. See LICENSE.
//-----------------------------------------------------------------------------
//
// Example GEISA actuator embedded C decoder.
//
// This example decodes GeisaActuatorGet_Req, GeisaActuatorGet_Rsp,
// GeisaActuatorSet_Req, or GeisaActuatorSet_Rsp from a binary protobuf file
// and prints a JSON-like representation for logging or diagnostics.
//
// `--demo` reads the standard `/tmp` payload set written by
// actuator_write_response_example_c.
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers/actuator_example_utils.h"

static int run_demo(void)
{
    puts("Running actuator read demo...");
    return actuator_run_demo_walkthrough();
}

int main(int argc, char *argv[])
{
    if (argc == 2 && strcmp(argv[1], "--demo") == 0)
    {
        return run_demo();
    }

    if (argc != 3)
    {
        fprintf(stderr,
                "usage: %s --get-req|--get-rsp|--set-req|--set-rsp payload.bin | --demo\n",
                argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "--get-req") == 0)
    {
        return actuator_decode_and_print_get_req_file(argv[2]);
    }
    if (strcmp(argv[1], "--get-rsp") == 0)
    {
        return actuator_decode_and_print_get_rsp_file(argv[2]);
    }
    if (strcmp(argv[1], "--set-req") == 0)
    {
        return actuator_decode_and_print_set_req_file(argv[2]);
    }
    if (strcmp(argv[1], "--set-rsp") == 0)
    {
        return actuator_decode_and_print_set_rsp_file(argv[2]);
    }

    fprintf(stderr, "unknown mode: %s\n", argv[1]);
    return EXIT_FAILURE;
}
