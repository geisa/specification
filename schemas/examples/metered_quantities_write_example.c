//-----------------------------------------------------------------------------
// Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
// Security Alliance (GEISA), a Series of LF Projects, LLC
//
// Licensed under the Apache License, Version 2.0. See LICENSE.
//-----------------------------------------------------------------------------
//
// Example GEISA metered_quantities protobuf writer.
//
// This example writes two payloads:
// - GeisaInstantaneousQuantities
// - GeisaBillingQuantities
//
// The payload data exercises:
// - GEISA 0.9 AC meter profile required instantaneous scalar fields
// - GEISA 0.9 billing profile required billing fields
// - proto3 optional scalar presence
// - fixed-point micro-unit electrical values
// - power factor as a unitless ratio
// - a harmonic array with bounded nanopb storage
//
// The example builds generated message structs in memory and encodes them to
// binary protobuf payloads that stand in for GEISA message bodies. The
// --demo mode is a quick-start walkthrough that writes the standard files and
// immediately decodes both payloads.
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>

#include "helpers/metered_quantities_example_utils.h"

int main(int argc, char *argv[])
{
    const bool demo_mode = (argc == 2 && strcmp(argv[1], "--demo") == 0);
    const bool positional = (argc == 2 && !demo_mode);
    const bool default_mode = (argc == 1);
    const char *outdir = NULL;
    char instantaneous_path[512];
    char billing_path[512];
    GeisaInstantaneousQuantities instantaneous;
    GeisaBillingQuantities billing;

    if (!default_mode && !demo_mode && !positional)
    {
        fprintf(stderr, "usage: %s [output-dir | --demo]\n", argv[0]);
        return EXIT_FAILURE;
    }

    outdir = positional ? argv[1] : "/tmp";

    if (!metered_ensure_directory(outdir))
    {
        return EXIT_FAILURE;
    }

    snprintf(instantaneous_path, sizeof(instantaneous_path), "%s/%s", outdir,
             "geisa-metered-instantaneous.bin");
    snprintf(billing_path, sizeof(billing_path), "%s/%s", outdir,
             "geisa-metered-billing.bin");

    fill_demo_instantaneous(&instantaneous);
    fill_demo_billing(&billing);

    // The generated `*_fields` descriptor tells nanopb how to walk the struct
    // in memory during encoding
    if (!metered_write_message_file(instantaneous_path,
                                    GeisaInstantaneousQuantities_fields,
                                    &instantaneous))
    {
        return EXIT_FAILURE;
    }

    if (!metered_write_message_file(billing_path, GeisaBillingQuantities_fields,
                                    &billing))
    {
        return EXIT_FAILURE;
    }

    if (!demo_mode)
    {
        printf("wrote %s\n", instantaneous_path);
        printf("wrote %s\n", billing_path);
        return EXIT_SUCCESS;
    }

    printf("Running metered quantities write demo...\n");
    printf("Writing instantaneous demo payload to %s\n", instantaneous_path);
    printf("Writing billing demo payload to %s\n", billing_path);
    printf("Decoding both demo payloads immediately for walkthrough output\n");
    if (metered_run_demo_walkthrough() != EXIT_SUCCESS)
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
