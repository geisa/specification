//-----------------------------------------------------------------------------
// Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
// Security Alliance (GEISA), a Series of LF Projects, LLC
//
// Licensed under the Apache License, Version 2.0. See LICENSE.
//-----------------------------------------------------------------------------
//
// Example GEISA metered_quantities protobuf decoder.
//
// Usage:
//   metered_quantities_read_example instantaneous <file>
//   metered_quantities_read_example billing <file>
//   metered_quantities_read_example --demo
//
// The output is compact and JSON-like so the example can be used as a quick
// check for field presence and naming. The --demo mode is a quick-start
// walkthrough that decodes both standard demo payloads from /tmp.
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers/metered_quantities_example_utils.h"

static int run_demo(void)
{
    printf("Running metered quantities read demo...\n");
    return metered_run_demo_walkthrough();
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
                "usage: %s instantaneous|billing payload.bin | --demo\n",
                argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "instantaneous") == 0)
    {
        return metered_decode_and_print_instantaneous_file(argv[2]);
    }

    if (strcmp(argv[1], "billing") == 0)
    {
        return metered_decode_and_print_billing_file(argv[2]);
    }

    fprintf(stderr, "unknown mode: %s\n", argv[1]);
    return EXIT_FAILURE;
}
