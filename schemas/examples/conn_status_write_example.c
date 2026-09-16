//-----------------------------------------------------------------------------
// Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
// Security Alliance (GEISA), a Series of LF Projects, LLC
//
// Licensed under the Apache License, Version 2.0. See LICENSE.
//-----------------------------------------------------------------------------
//
// Example GEISA conn-status embedded C writer.
//
// This example writes representative GeisaPlatformStatus,
// GeisaPlatformToAppStatus, and GeisaAppToPlatformStatus payloads. `--demo`
// is the main walkthrough entry point and immediately decodes the standard
// `/tmp` payload set through the companion reader.
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers/conn_status_example_utils.h"

int main(int argc, char *argv[])
{
    const bool demo_mode = (argc == 2 && strcmp(argv[1], "--demo") == 0);
    const bool default_mode = (argc == 1);
    const bool positional = (argc == 4 && !demo_mode);
    const char *platform_path = default_mode || demo_mode ? GEISA_CONN_PLATFORM_STATUS_PATH : argv[1];
    const char *to_app_path = default_mode || demo_mode ? GEISA_CONN_PLATFORM_TO_APP_STATUS_PATH : argv[2];
    const char *from_app_path = default_mode || demo_mode ? GEISA_CONN_APP_TO_PLATFORM_STATUS_PATH : argv[3];
    GeisaPlatformStatus platform_status;
    GeisaPlatformToAppStatus platform_to_app_status;
    GeisaAppToPlatformStatus app_to_platform_status;

    if (!default_mode && !demo_mode && !positional)
    {
        fprintf(stderr, "usage: %s [platform.bin platform-to-app.bin app-to-platform.bin | --demo]\n", argv[0]);
        return EXIT_FAILURE;
    }

    fill_demo_platform_status(&platform_status);
    fill_demo_platform_to_app_status(&platform_to_app_status);
    fill_demo_app_to_platform_status(&app_to_platform_status);

    if (!geisa_write_message_file(platform_path, GeisaPlatformStatus_fields, &platform_status) ||
        !geisa_write_message_file(to_app_path, GeisaPlatformToAppStatus_fields, &platform_to_app_status) ||
        !geisa_write_message_file(from_app_path, GeisaAppToPlatformStatus_fields, &app_to_platform_status))
    {
        return EXIT_FAILURE;
    }

    if (!demo_mode)
    {
        printf("wrote %s\n", platform_path);
        printf("wrote %s\n", to_app_path);
        printf("wrote %s\n", from_app_path);
        return EXIT_SUCCESS;
    }

    puts("Running conn-status write demo...");
    puts("Writing platform and app status payloads to /tmp");
    puts("Decoding all conn-status demo payloads immediately for walkthrough output");
    return conn_status_run_demo_walkthrough();
}
