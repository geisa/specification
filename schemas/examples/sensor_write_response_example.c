//-----------------------------------------------------------------------------
// Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
// Security Alliance (GEISA), a Series of LF Projects, LLC
//
// Licensed under the Apache License, Version 2.0. See LICENSE.
//-----------------------------------------------------------------------------
//
// Example GEISA sensor embedded C writer.
//
// This example creates a GeisaSensorReadings_Rsp payload containing multiple
// readings. `--demo` is the main walkthrough entry point and immediately
// decodes the standard `/tmp` payload through the companion reader.
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers/sensor_example_utils.h"

int main(int argc, char *argv[])
{
    const bool demo_mode = (argc == 2 && strcmp(argv[1], "--demo") == 0);
    const bool default_mode = (argc == 1);
    const bool positional = (argc == 2 && !demo_mode);
    const char *path = default_mode || demo_mode ? GEISA_SENSOR_RESPONSE_PATH : argv[1];
    GeisaSensorReadings_Rsp response;

    if (!default_mode && !demo_mode && !positional)
    {
        fprintf(stderr, "usage: %s [response.bin | --demo]\n", argv[0]);
        return EXIT_FAILURE;
    }

    fill_demo_sensor_readings_rsp(&response);
    if (!geisa_write_message_file(path, GeisaSensorReadings_Rsp_fields, &response))
    {
        return EXIT_FAILURE;
    }

    if (!demo_mode)
    {
        printf("wrote %s\n", path);
        return EXIT_SUCCESS;
    }

    puts("Running sensor write demo...");
    puts("Writing sensor readings response payload to /tmp");
    puts("Decoding the sensor demo payload immediately for walkthrough output");
    return sensor_run_demo_walkthrough();
}
