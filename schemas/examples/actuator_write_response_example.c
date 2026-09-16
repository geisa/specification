//-----------------------------------------------------------------------------
// Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
// Security Alliance (GEISA), a Series of LF Projects, LLC
//
// Licensed under the Apache License, Version 2.0. See LICENSE.
//-----------------------------------------------------------------------------
//
// Example GEISA actuator embedded C writer.
//
// This example writes representative GeisaActuatorGet_Req,
// GeisaActuatorGet_Rsp, GeisaActuatorSet_Req, and GeisaActuatorSet_Rsp
// payloads. `--demo` is the main walkthrough entry point and immediately
// decodes the standard `/tmp` payload set through the companion reader.
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers/actuator_example_utils.h"

int main(int argc, char *argv[])
{
    const bool demo_mode = (argc == 2 && strcmp(argv[1], "--demo") == 0);
    const bool default_mode = (argc == 1);
    GeisaActuatorGet_Req get_req;
    GeisaActuatorGet_Rsp get_rsp;
    GeisaActuatorSet_Req set_req;
    GeisaActuatorSet_Rsp set_rsp;

    if (!default_mode && !demo_mode)
    {
        fprintf(stderr, "usage: %s [--demo]\n", argv[0]);
        return EXIT_FAILURE;
    }

    fill_demo_actuator_get_req(&get_req);
    fill_demo_actuator_get_rsp(&get_rsp);
    fill_demo_actuator_set_req(&set_req);
    fill_demo_actuator_set_rsp(&set_rsp);

    if (!geisa_write_message_file(GEISA_ACTUATOR_GET_REQ_PATH,
                                  GeisaActuatorGet_Req_fields,
                                  &get_req) ||
        !geisa_write_message_file(GEISA_ACTUATOR_GET_RSP_PATH,
                                  GeisaActuatorGet_Rsp_fields,
                                  &get_rsp) ||
        !geisa_write_message_file(GEISA_ACTUATOR_SET_REQ_PATH,
                                  GeisaActuatorSet_Req_fields,
                                  &set_req) ||
        !geisa_write_message_file(GEISA_ACTUATOR_SET_RSP_PATH,
                                  GeisaActuatorSet_Rsp_fields,
                                  &set_rsp))
    {
        return EXIT_FAILURE;
    }

    if (!demo_mode)
    {
        printf("wrote %s\n", GEISA_ACTUATOR_GET_REQ_PATH);
        printf("wrote %s\n", GEISA_ACTUATOR_GET_RSP_PATH);
        printf("wrote %s\n", GEISA_ACTUATOR_SET_REQ_PATH);
        printf("wrote %s\n", GEISA_ACTUATOR_SET_RSP_PATH);
        return EXIT_SUCCESS;
    }

    puts("Running actuator write demo...");
    puts("Writing actuator get/set request and response payloads to /tmp");
    puts("Decoding all actuator demo payloads immediately for walkthrough output");
    return actuator_run_demo_walkthrough();
}
