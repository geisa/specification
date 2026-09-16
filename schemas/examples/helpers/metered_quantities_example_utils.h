//-----------------------------------------------------------------------------
// Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
// Security Alliance (GEISA), a Series of LF Projects, LLC
//
// Licensed under the Apache License, Version 2.0. See LICENSE.
//-----------------------------------------------------------------------------
//
// Shared helper utilities for GEISA nanopb metered_quantities examples.
//
// These functions are example support functions only. They are not part of the
// GEISA APIs and are just used for the example code base.
//
// These helpers keep message construction and file-based encode/decode support
// out of the top-level examples. They are example utilities, not a transport
// layer or production framing library.
//-----------------------------------------------------------------------------

#ifndef GEISA_METERED_QUANTITIES_EXAMPLE_UTILS_H
#define GEISA_METERED_QUANTITIES_EXAMPLE_UTILS_H

#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "metered_quantities.pb.h"
#include "pb_decode.h"
#include "pb_encode.h"

static inline void print_harmonic_preview(const GeisaTypeHarmonic *harmonics);

// Creates an output directory for example artifacts if it does not already
// exist.
static inline bool metered_ensure_directory(const char *path)
{
    if (mkdir(path, 0777) == 0 || errno == EEXIST)
    {
        return true;
    }

    fprintf(stderr, "failed to create %s: %s\n", path, strerror(errno));
    return false;
}

// Encodes a nanopb message directly to a binary file.
//
// `fields` is the generated nanopb message descriptor and `message` points to
// the corresponding generated message struct.
static inline bool metered_write_message_file(const char *path,
                                              const pb_msgdesc_t *fields,
                                              const void *message)
{
    FILE *file = fopen(path, "wb");
    if (file == NULL)
    {
        fprintf(stderr, "failed to open %s: %s\n", path, strerror(errno));
        return false;
    }

    size_t encoded_size = 0;
    pb_ostream_t size_stream = PB_OSTREAM_SIZING;
    if (!pb_encode(&size_stream, fields, message))
    {
        fprintf(stderr, "failed to size %s: %s\n", path, PB_GET_ERROR(&size_stream));
        fclose(file);
        return false;
    }
    encoded_size = size_stream.bytes_written;

    uint8_t *buffer = (uint8_t *)malloc(encoded_size == 0 ? 1 : encoded_size);
    if (buffer == NULL)
    {
        fprintf(stderr, "failed to allocate encode buffer for %s\n", path);
        fclose(file);
        return false;
    }

    pb_ostream_t stream = pb_ostream_from_buffer(buffer, encoded_size);
    const bool ok = pb_encode(&stream, fields, message);
    if (!ok)
    {
        fprintf(stderr, "failed to encode %s: %s\n", path, PB_GET_ERROR(&stream));
    }
    else if (fwrite(buffer, 1, stream.bytes_written, file) != stream.bytes_written)
    {
        fprintf(stderr, "failed to write %s: %s\n", path, strerror(errno));
        free(buffer);
        fclose(file);
        return false;
    }

    free(buffer);
    fclose(file);
    return ok;
}

// Decodes a nanopb message directly from a binary file
static inline bool metered_read_message_file(const char *path,
                                             const pb_msgdesc_t *fields,
                                             void *message)
{
    FILE *file = fopen(path, "rb");
    if (file == NULL)
    {
        fprintf(stderr, "failed to open %s: %s\n", path, strerror(errno));
        return false;
    }

    if (fseek(file, 0, SEEK_END) != 0)
    {
        fprintf(stderr, "failed to seek %s: %s\n", path, strerror(errno));
        fclose(file);
        return false;
    }

    const long file_size = ftell(file);
    if (file_size < 0)
    {
        fprintf(stderr, "failed to size %s: %s\n", path, strerror(errno));
        fclose(file);
        return false;
    }
    rewind(file);

    uint8_t *buffer = (uint8_t *)malloc((size_t)file_size == 0 ? 1 : (size_t)file_size);
    if (buffer == NULL)
    {
        fprintf(stderr, "failed to allocate decode buffer for %s\n", path);
        fclose(file);
        return false;
    }

    if (fread(buffer, 1, (size_t)file_size, file) != (size_t)file_size)
    {
        fprintf(stderr, "failed to read %s: %s\n", path, strerror(errno));
        free(buffer);
        fclose(file);
        return false;
    }

    pb_istream_t stream = pb_istream_from_buffer(buffer, (size_t)file_size);
    const bool ok = pb_decode(&stream, fields, message);
    if (!ok)
    {
        fprintf(stderr, "failed to decode %s: %s\n", path, PB_GET_ERROR(&stream));
    }

    free(buffer);
    fclose(file);
    return ok;
}

// Fills an instantaneous payload that covers the GEISA 0.9 AC meter profile
// required fields. The values below model a plausible shoulder-season live
// residential snapshot and leave a few optional values present for presence
// handling.
static inline void fill_demo_instantaneous(
    GeisaInstantaneousQuantities *message)
{
    *message = (GeisaInstantaneousQuantities)GeisaInstantaneousQuantities_init_zero;
    message->timestamp_us = 1736035200123456ULL;
    message->message_version = 1;
    message->has_frequency_hz = true;
    message->frequency_hz = 60.0;
    message->has_temperature_celsius = true;
    message->temperature_celsius = 34.5;

    message->has_phase_a = true;
    message->phase_a = (GeisaTypeInstantaneousQuantities_PerPhase)GeisaTypeInstantaneousQuantities_PerPhase_init_zero;
    message->phase_a.message_version = 1;
    message->phase_a.phase = GeisaTypePhase_PHASE_A;
    message->phase_a.has_current_micro_a = true;
    message->phase_a.current_micro_a = 8246588;
    message->phase_a.has_voltage_micro_v = true;
    message->phase_a.voltage_micro_v = 120150000;
    message->phase_a.has_active_power_micro_w_sum = true;
    message->phase_a.active_power_micro_w_sum = 983000000;
    message->phase_a.has_reactive_power_micro_var_sum = true;
    message->phase_a.reactive_power_micro_var_sum = 124300000;
    message->phase_a.has_apparent_power_micro_va_sum = true;
    message->phase_a.apparent_power_micro_va_sum = 990828000;
    message->phase_a.has_active_power_micro_w_del = true;
    message->phase_a.active_power_micro_w_del = 983000000;
    message->phase_a.has_power_factor = true;
    message->phase_a.power_factor = 0.9921;
    message->phase_a.has_current_angle_deg = true;
    message->phase_a.current_angle_deg = -7.2;
    message->phase_a.has_voltage_angle_deg = true;
    message->phase_a.voltage_angle_deg = 0.0;
    message->phase_a.has_current_thd_percent = true;
    message->phase_a.current_thd_percent = 2.4;
    message->phase_a.has_voltage_thd_percent = true;
    message->phase_a.voltage_thd_percent = 1.6;
    message->phase_a.has_current_tdd_percent = true;
    message->phase_a.current_tdd_percent = 2.8;

    message->has_phase_n = true;
    message->phase_n = (GeisaTypeInstantaneousQuantities_PerPhase)GeisaTypeInstantaneousQuantities_PerPhase_init_zero;
    message->phase_n.message_version = 1;
    message->phase_n.phase = GeisaTypePhase_PHASE_N;
    message->phase_n.has_current_micro_a = true;
    message->phase_n.current_micro_a = 61500;

    message->has_system = true;
    message->system = (GeisaTypeInstantaneousQuantities_System)GeisaTypeInstantaneousQuantities_System_init_zero;
    message->system.message_version = 1;
    message->system.timestamp_us = message->timestamp_us;
    message->system.has_frequency_hz = true;
    message->system.frequency_hz = 60.0;
    message->system.has_active_power_micro_w_sum = true;
    message->system.active_power_micro_w_sum = 2050000000;
    message->system.has_active_power_micro_w_del = true;
    message->system.active_power_micro_w_del = 2050000000;
    message->system.has_reactive_power_micro_var_sum = true;
    message->system.reactive_power_micro_var_sum = 259200000;
    message->system.has_apparent_power_micro_va_sum_arithmetic = true;
    message->system.apparent_power_micro_va_sum_arithmetic = 2066324000;
    message->system.has_power_factor_arithmetic = true;
    message->system.power_factor_arithmetic = 0.9921;

    message->has_other = true;
    message->other = (GeisaTypeInstantaneousQuantities_Other)GeisaTypeInstantaneousQuantities_Other_init_zero;
    message->other.message_version = 1;
    message->other.timestamp_us = message->timestamp_us;
    message->other.has_neutral_current_imputed_micro_a = true;
    message->other.neutral_current_imputed_micro_a = 62000;
    message->other.has_neutral_current_micro_a = true;
    message->other.neutral_current_micro_a = 61500;

    message->has_harmonic = true;
    message->harmonic = (GeisaInstantaneousQuantities_Harmonic)GeisaInstantaneousQuantities_Harmonic_init_zero;
    message->harmonic.message_version = 1;
    message->harmonic.timestamp_us = message->timestamp_us;
    message->harmonic.has_phase_a_current_harmonic_2nd_micro_a = true;
    message->harmonic.phase_a_current_harmonic_2nd_micro_a = 12100;
    message->harmonic.has_phase_a_voltage_harmonic_2nd_micro_v = true;
    message->harmonic.phase_a_voltage_harmonic_2nd_micro_v = 205000;
    message->harmonic.has_phase_a_harmonics = true;
    message->harmonic.phase_a_harmonics = (GeisaTypeHarmonic)GeisaTypeHarmonic_init_zero;
    message->harmonic.phase_a_harmonics.voltage_harmonic_micro_v_count = 3;
    message->harmonic.phase_a_harmonics.voltage_harmonic_micro_v[0] = 205000;
    message->harmonic.phase_a_harmonics.voltage_harmonic_micro_v[1] = 115000;
    message->harmonic.phase_a_harmonics.voltage_harmonic_micro_v[2] = 86000;
    message->harmonic.phase_a_harmonics.current_harmonic_micro_a_count = 3;
    message->harmonic.phase_a_harmonics.current_harmonic_micro_a[0] = 12100;
    message->harmonic.phase_a_harmonics.current_harmonic_micro_a[1] = 8700;
    message->harmonic.phase_a_harmonics.current_harmonic_micro_a[2] = 6500;
}

static inline const char *metered_phase_name(GeisaTypePhase phase)
{
    switch (phase)
    {
    case GeisaTypePhase_PHASE_A:
        return "PHASE_A";
    case GeisaTypePhase_PHASE_B:
        return "PHASE_B";
    case GeisaTypePhase_PHASE_C:
        return "PHASE_C";
    case GeisaTypePhase_PHASE_N:
        return "PHASE_N";
    default:
        return "PHASE_UNKNOWN";
    }
}

static inline void metered_print_json_integer_field(bool *first_field,
                                                    const char *name,
                                                    long long value)
{
    if (!*first_field)
    {
        printf(",");
    }
    printf("\"%s\":%lld", name, value);
    *first_field = false;
}

static inline void metered_print_json_number_field(bool *first_field,
                                                   const char *name,
                                                   double value,
                                                   int precision)
{
    if (!*first_field)
    {
        printf(",");
    }
    printf("\"%s\":%.*f", name, precision, value);
    *first_field = false;
}

static inline void metered_print_json_string_field(bool *first_field,
                                                   const char *name,
                                                   const char *value)
{
    if (!*first_field)
    {
        printf(",");
    }
    printf("\"%s\":\"%s\"", name, value);
    *first_field = false;
}

static inline void metered_print_metadata_json(
    bool *first_field, const GeisaTypeMeasurementMetadata *metadata)
{
    if (!metadata->has_measurement_period_s)
    {
        return;
    }

    if (!*first_field)
    {
        printf(",");
    }
    printf("\"metadata\":{\"measurement-period-s\":%.3f}",
           metadata->measurement_period_s);
    *first_field = false;
}

// Prints the instantaneous payload in the same JSON-like form used by the
// read example. Optional values are rendered only when nanopb presence flags
// show that the field was encoded..
static inline void metered_print_instantaneous(
    const GeisaInstantaneousQuantities *instantaneous)
{
    printf("{\"message-version\":%u", instantaneous->message_version);
    printf(",\"timestamp-us\":%llu",
           (unsigned long long)instantaneous->timestamp_us);

    if (instantaneous->has_frequency_hz)
    {
        printf(",\"frequency-hz\":%.3f", instantaneous->frequency_hz);
    }

    if (instantaneous->has_phase_a)
    {
        bool first_field = true;
        printf(",\"phase-a\":{");
        metered_print_json_integer_field(
            &first_field, "message-version",
            (long long)instantaneous->phase_a.message_version);
        metered_print_json_string_field(
            &first_field, "phase",
            metered_phase_name(instantaneous->phase_a.phase));
        if (instantaneous->phase_a.has_current_micro_a)
        {
            metered_print_json_integer_field(
                &first_field, "current-micro-a",
                (long long)instantaneous->phase_a.current_micro_a);
        }
        if (instantaneous->phase_a.has_voltage_micro_v)
        {
            metered_print_json_integer_field(
                &first_field, "voltage-micro-v",
                (long long)instantaneous->phase_a.voltage_micro_v);
        }
        if (instantaneous->phase_a.has_active_power_micro_w_sum)
        {
            metered_print_json_integer_field(
                &first_field, "active-power-micro-w-sum",
                (long long)instantaneous->phase_a.active_power_micro_w_sum);
        }
        if (instantaneous->phase_a.has_reactive_power_micro_var_sum)
        {
            metered_print_json_integer_field(
                &first_field, "reactive-power-micro-var-sum",
                (long long)instantaneous->phase_a.reactive_power_micro_var_sum);
        }
        if (instantaneous->phase_a.has_apparent_power_micro_va_sum)
        {
            metered_print_json_integer_field(
                &first_field, "apparent-power-micro-va-sum",
                (long long)instantaneous->phase_a.apparent_power_micro_va_sum);
        }
        if (instantaneous->phase_a.has_power_factor)
        {
            metered_print_json_number_field(
                &first_field, "power-factor",
                instantaneous->phase_a.power_factor, 4);
        }
        if (instantaneous->phase_a.has_current_angle_deg)
        {
            metered_print_json_number_field(
                &first_field, "current-angle-deg",
                instantaneous->phase_a.current_angle_deg, 3);
        }
        if (instantaneous->phase_a.has_voltage_angle_deg)
        {
            metered_print_json_number_field(
                &first_field, "voltage-angle-deg",
                instantaneous->phase_a.voltage_angle_deg, 3);
        }
        if (instantaneous->phase_a.has_current_thd_percent)
        {
            metered_print_json_number_field(
                &first_field, "current-thd-percent",
                instantaneous->phase_a.current_thd_percent, 3);
        }
        if (instantaneous->phase_a.has_voltage_thd_percent)
        {
            metered_print_json_number_field(
                &first_field, "voltage-thd-percent",
                instantaneous->phase_a.voltage_thd_percent, 3);
        }
        if (instantaneous->phase_a.has_current_tdd_percent)
        {
            metered_print_json_number_field(
                &first_field, "current-tdd-percent",
                instantaneous->phase_a.current_tdd_percent, 3);
        }
        printf("}");
    }

    if (instantaneous->has_system)
    {
        bool first_field = true;
        printf(",\"system\":{");
        metered_print_json_integer_field(
            &first_field, "message-version",
            (long long)instantaneous->system.message_version);
        metered_print_json_integer_field(
            &first_field, "timestamp-us",
            (long long)instantaneous->system.timestamp_us);
        if (instantaneous->system.has_frequency_hz)
        {
            metered_print_json_number_field(
                &first_field, "frequency-hz",
                instantaneous->system.frequency_hz, 3);
        }
        if (instantaneous->system.has_active_power_micro_w_sum)
        {
            metered_print_json_integer_field(
                &first_field, "active-power-micro-w-sum",
                (long long)instantaneous->system.active_power_micro_w_sum);
        }
        if (instantaneous->system.has_reactive_power_micro_var_sum)
        {
            metered_print_json_integer_field(
                &first_field, "reactive-power-micro-var-sum",
                (long long)instantaneous->system.reactive_power_micro_var_sum);
        }
        if (instantaneous->system.has_apparent_power_micro_va_sum_arithmetic)
        {
            metered_print_json_integer_field(
                &first_field, "apparent-power-micro-va-sum-arithmetic",
                (long long)instantaneous->system.apparent_power_micro_va_sum_arithmetic);
        }
        if (instantaneous->system.has_power_factor_arithmetic)
        {
            metered_print_json_number_field(
                &first_field, "power-factor-arithmetic",
                instantaneous->system.power_factor_arithmetic, 4);
        }
        printf("}");
    }

    if (instantaneous->has_other)
    {
        bool first_field = true;
        printf(",\"other\":{");
        if (instantaneous->other.has_neutral_current_imputed_micro_a)
        {
            metered_print_json_integer_field(
                &first_field, "neutral-current-imputed-micro-a",
                (long long)instantaneous->other.neutral_current_imputed_micro_a);
        }
        if (instantaneous->other.has_neutral_current_micro_a)
        {
            metered_print_json_integer_field(
                &first_field, "neutral-current-micro-a",
                (long long)instantaneous->other.neutral_current_micro_a);
        }
        printf("}");
    }

    if (instantaneous->has_harmonic &&
        instantaneous->harmonic.has_phase_a_harmonics)
    {
        printf(",\"phase-a-harmonics\":");
        print_harmonic_preview(&instantaneous->harmonic.phase_a_harmonics);
    }

    printf("}\n");
}

// Fills a billing payload that covers the GEISA 0.9 billing profile required
// fields. The values below model a typical NC ~1,000 kWh/month residential
// baseline with a normal monthly peak and leaves a few optional values present
// for presence checks
static inline void fill_demo_billing(GeisaBillingQuantities *message)
{
    *message = (GeisaBillingQuantities)GeisaBillingQuantities_init_zero;
    message->message_version = 1;

    message->has_summation_total = true;
    message->summation_total = (GeisaBillingQuantities_Summation_Total)GeisaBillingQuantities_Summation_Total_init_zero;
    message->summation_total.message_version = 1;
    message->summation_total.timestamp_us = 1736035200123456ULL;
    message->summation_total.has_active_energy_micro_wh_del = true;
    message->summation_total.active_energy_micro_wh_del = 1000000000000LL;
    message->summation_total.has_active_energy_micro_wh_sum = true;
    message->summation_total.active_energy_micro_wh_sum = 1000000000000LL;
    message->summation_total.has_reactive_energy_micro_varh_q1_plus_q4 = true;
    message->summation_total.reactive_energy_micro_varh_q1_plus_q4 = 162000000000LL;
    message->summation_total.has_apparent_energy_micro_vah_sum_arithmetic = true;
    message->summation_total.apparent_energy_micro_vah_sum_arithmetic = 1013000000000LL;
    message->summation_total.has_power_factor_sum_arithmetic = true;
    message->summation_total.power_factor_sum_arithmetic = 0.9870;
    message->summation_total.has_power_factor_sum_vectorial = true;
    message->summation_total.power_factor_sum_vectorial = 0.9852;
    message->summation_total.has_metadata = true;
    message->summation_total.metadata = (GeisaTypeMeasurementMetadata)GeisaTypeMeasurementMetadata_init_zero;
    message->summation_total.metadata.has_measurement_period_s = true;
    message->summation_total.metadata.measurement_period_s = 900.0;

    message->has_demand_total = true;
    message->demand_total = (GeisaBillingQuantities_Demand_Total)GeisaBillingQuantities_Demand_Total_init_zero;
    message->demand_total.message_version = 1;
    message->demand_total.timestamp_us = 1736035200123456ULL;
    message->demand_total.has_active_power_micro_w_del = true;
    message->demand_total.active_power_micro_w_del = (GeisaTypeMaxDemand)GeisaTypeMaxDemand_init_zero;
    message->demand_total.active_power_micro_w_del.max_demand_time_us =
        1736031600000000ULL;
    message->demand_total.active_power_micro_w_del.has_quantity = true;
    message->demand_total.active_power_micro_w_del.quantity = 5800000000LL;
    message->demand_total.has_active_power_micro_w_sum = true;
    message->demand_total.active_power_micro_w_sum = (GeisaTypeMaxDemand)GeisaTypeMaxDemand_init_zero;
    message->demand_total.active_power_micro_w_sum.max_demand_time_us =
        1736031600000000ULL;
    message->demand_total.active_power_micro_w_sum.has_quantity = true;
    message->demand_total.active_power_micro_w_sum.quantity = 5800000000LL;
    message->demand_total.has_metadata = true;
    message->demand_total.metadata = (GeisaTypeMeasurementMetadata)GeisaTypeMeasurementMetadata_init_zero;
    message->demand_total.metadata.has_measurement_period_s = true;
    message->demand_total.metadata.measurement_period_s = 900.0;
}

// Prints the billing payload in the same JSON-like form used by the read
// example. Optional values are rendered only when the generated presence flags
// show that the field was encoded.
static inline void metered_print_billing(const GeisaBillingQuantities *billing)
{
    printf("{\"message-version\":%u", billing->message_version);

    if (billing->has_summation_total)
    {
        bool first_field = true;
        printf(",\"summation-total\":{");
        metered_print_json_integer_field(
            &first_field, "message-version",
            (long long)billing->summation_total.message_version);
        metered_print_json_integer_field(
            &first_field, "timestamp-us",
            (long long)billing->summation_total.timestamp_us);
        if (billing->summation_total.has_active_energy_micro_wh_del)
        {
            metered_print_json_integer_field(
                &first_field, "active-energy-micro-wh-del",
                (long long)billing->summation_total.active_energy_micro_wh_del);
        }
        if (billing->summation_total.has_power_factor_sum_arithmetic)
        {
            metered_print_json_number_field(
                &first_field, "power-factor-sum-arithmetic",
                billing->summation_total.power_factor_sum_arithmetic, 4);
        }
        if (billing->summation_total.has_power_factor_sum_vectorial)
        {
            metered_print_json_number_field(
                &first_field, "power-factor-sum-vectorial",
                billing->summation_total.power_factor_sum_vectorial, 4);
        }
        if (billing->summation_total.has_metadata)
        {
            metered_print_metadata_json(&first_field,
                                        &billing->summation_total.metadata);
        }
        printf("}");
    }

    if (billing->has_demand_total)
    {
        bool first_field = true;
        printf(",\"demand-total\":{");
        metered_print_json_integer_field(
            &first_field, "message-version",
            (long long)billing->demand_total.message_version);
        metered_print_json_integer_field(
            &first_field, "timestamp-us",
            (long long)billing->demand_total.timestamp_us);
        if (billing->demand_total.has_active_power_micro_w_del)
        {
            if (!first_field)
            {
                printf(",");
            }
            printf("\"active-power-micro-w-del\":{");
            printf("\"max-demand-time-us\":%llu",
                   (unsigned long long)billing->demand_total
                       .active_power_micro_w_del.max_demand_time_us);
            if (billing->demand_total.active_power_micro_w_del.has_quantity)
            {
                printf(",\"quantity\":%lld",
                       (long long)billing->demand_total.active_power_micro_w_del.quantity);
            }
            printf("}");
            first_field = false;
        }
        if (billing->demand_total.has_active_power_micro_w_sum)
        {
            if (!first_field)
            {
                printf(",");
            }
            printf("\"active-power-micro-w-sum\":{");
            printf("\"max-demand-time-us\":%llu",
                   (unsigned long long)billing->demand_total
                       .active_power_micro_w_sum.max_demand_time_us);
            if (billing->demand_total.active_power_micro_w_sum.has_quantity)
            {
                printf(",\"quantity\":%lld",
                       (long long)billing->demand_total.active_power_micro_w_sum.quantity);
            }
            printf("}");
            first_field = false;
        }
        if (billing->demand_total.has_metadata)
        {
            metered_print_metadata_json(&first_field,
                                        &billing->demand_total.metadata);
        }
        printf("}");
    }

    printf("}\n");
}

static inline int metered_decode_and_print_instantaneous_file(const char *path)
{
    GeisaInstantaneousQuantities instantaneous =
        GeisaInstantaneousQuantities_init_zero;

    if (!metered_read_message_file(path, GeisaInstantaneousQuantities_fields,
                                   &instantaneous))
    {
        return EXIT_FAILURE;
    }

    metered_print_instantaneous(&instantaneous);
    return EXIT_SUCCESS;
}

static inline int metered_decode_and_print_billing_file(const char *path)
{
    GeisaBillingQuantities billing = GeisaBillingQuantities_init_zero;

    if (!metered_read_message_file(path, GeisaBillingQuantities_fields, &billing))
    {
        return EXIT_FAILURE;
    }

    metered_print_billing(&billing);
    return EXIT_SUCCESS;
}

// Runs the standard /tmp walkthrough for both metered payloads. This is the
// quick-start flow used by the reader and writer --demo modes.
static inline int metered_run_demo_walkthrough(void)
{
    printf("Decoding instantaneous demo payload from /tmp/geisa-metered-instantaneous.bin\n");
    printf("---- instantaneous ----\n");
    if (metered_decode_and_print_instantaneous_file(
            "/tmp/geisa-metered-instantaneous.bin") != EXIT_SUCCESS)
    {
        return EXIT_FAILURE;
    }

    printf("Decoding billing demo payload from /tmp/geisa-metered-billing.bin\n");
    printf("---- billing ----\n");
    if (metered_decode_and_print_billing_file(
            "/tmp/geisa-metered-billing.bin") != EXIT_SUCCESS)
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

// Prints a compact preview of the harmonic array counts.
static inline void print_harmonic_preview(const GeisaTypeHarmonic *harmonics)
{
    printf("{\"voltage-harmonic-count\":%u,\"current-harmonic-count\":%u}",
           (unsigned)harmonics->voltage_harmonic_micro_v_count,
           (unsigned)harmonics->current_harmonic_micro_a_count);
}

#endif  // GEISA_METERED_QUANTITIES_EXAMPLE_UTILS_H
