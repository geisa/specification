//-----------------------------------------------------------------------------
// Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
// Security Alliance (GEISA), a Series of LF Projects, LLC
//
// Licensed under the Apache License, Version 2.0. See LICENSE.
//-----------------------------------------------------------------------------
//
// Shared helper utilities for GEISA embedded C sensor examples.
//-----------------------------------------------------------------------------

#ifndef GEISA_SENSOR_EXAMPLE_UTILS_H
#define GEISA_SENSOR_EXAMPLE_UTILS_H

#include <stdio.h>
#include <string.h>

#include "geisa-status.pb.h"
#include "nanopb_example_utils.h"
#include "sensor.pb.h"

#define GEISA_SENSOR_RESPONSE_PATH "/tmp/sensor-response.bin"

static inline const char *sensor_status_code_name(GeisaStatusCode code)
{
    switch (code)
    {
    case GeisaStatusCode_GEISA_STATUS_SUCCESS:
        return "GeisaStatusCode_GEISA_STATUS_SUCCESS";
    case GeisaStatusCode_GEISA_STATUS_CODE_DATA_STALE:
        return "GeisaStatusCode_GEISA_STATUS_CODE_DATA_STALE";
    case GeisaStatusCode_GEISA_STATUS_CODE_DATA_UNAVAILABLE:
        return "GeisaStatusCode_GEISA_STATUS_CODE_DATA_UNAVAILABLE";
    case GeisaStatusCode_GEISA_STATUS_CODE_UNSPECIFIED:
    default:
        return "GeisaStatusCode_GEISA_STATUS_CODE_UNSPECIFIED";
    }
}

static inline const char *sensor_type_name(GeisaSensorType type)
{
    switch (type)
    {
    case GeisaSensorType_GEISA_SENSOR_TYPE_TEMPERATURE:
        return "GeisaSensorType_GEISA_SENSOR_TYPE_TEMPERATURE";
    case GeisaSensorType_GEISA_SENSOR_TYPE_HUMIDITY:
        return "GeisaSensorType_GEISA_SENSOR_TYPE_HUMIDITY";
    case GeisaSensorType_GEISA_SENSOR_TYPE_CUSTOM:
        return "GeisaSensorType_GEISA_SENSOR_TYPE_CUSTOM";
    case GeisaSensorType_GEISA_SENSOR_TYPE_UNSPECIFIED:
    default:
        return "GeisaSensorType_GEISA_SENSOR_TYPE_UNSPECIFIED";
    }
}

static inline void fill_demo_sensor_value_double(GeisaSensorValue *value, double double_value)
{
    *value = (GeisaSensorValue)GeisaSensorValue_init_zero;
    value->which_value = GeisaSensorValue_double_value_tag;
    value->value.double_value = double_value;
}

static inline void fill_demo_sensor_value_string(GeisaSensorValue *value, const char *string_value)
{
    *value = (GeisaSensorValue)GeisaSensorValue_init_zero;
    value->which_value = GeisaSensorValue_string_value_tag;
    strncpy(value->value.string_value, string_value, sizeof(value->value.string_value) - 1);
}

static inline void fill_demo_sensor_readings_rsp(GeisaSensorReadings_Rsp *message)
{
    *message = (GeisaSensorReadings_Rsp)GeisaSensorReadings_Rsp_init_zero;
    message->has_status = true;
    message->status.code = GeisaStatusCode_GEISA_STATUS_SUCCESS;
    strncpy(message->status.message, "ok", sizeof(message->status.message) - 1);

    message->readings_count = 2;

    GeisaSensorReading *board = &message->readings[0];
    strncpy(board->sensor_id, "board-temp-1", sizeof(board->sensor_id) - 1);
    board->timestamp_ms = 1762862400000ULL;
    board->values_count = 2;
    fill_demo_sensor_value_double(&board->values[0], 47.25);
    fill_demo_sensor_value_double(&board->values[1], 47.38);
    board->has_unit = true;
    strncpy(board->unit, "Cel", sizeof(board->unit) - 1);
    board->has_quality = true;
    strncpy(board->quality, "GOOD", sizeof(board->quality) - 1);
    board->has_status = true;
    strncpy(board->status, "OK", sizeof(board->status) - 1);

    GeisaSensorReading *ambient = &message->readings[1];
    strncpy(ambient->sensor_id, "ambient-temp-1", sizeof(ambient->sensor_id) - 1);
    ambient->timestamp_ms = 1762862400000ULL;
    ambient->values_count = 1;
    fill_demo_sensor_value_double(&ambient->values[0], 22.70);
    ambient->has_unit = true;
    strncpy(ambient->unit, "Cel", sizeof(ambient->unit) - 1);
}

static inline void print_sensor_status_json(const GeisaStatus *status)
{
    putchar('{');
    geisa_print_json_key("code");
    geisa_print_json_escaped(sensor_status_code_name(status->code));
    if (status->message[0] != '\0')
    {
        fputs(",\"message\":", stdout);
        geisa_print_json_escaped(status->message);
    }
    if (status->details[0] != '\0')
    {
        fputs(",\"details\":", stdout);
        geisa_print_json_escaped(status->details);
    }
    putchar('}');
}

static inline void print_sensor_value_json(const GeisaSensorValue *value)
{
    putchar('{');
    switch (value->which_value)
    {
    case GeisaSensorValue_double_value_tag:
        printf("\"double-value\":%.6g", value->value.double_value);
        break;
    case GeisaSensorValue_int64_value_tag:
        printf("\"int64-value\":%lld", (long long)value->value.int64_value);
        break;
    case GeisaSensorValue_bool_value_tag:
        fputs("\"bool-value\":", stdout);
        fputs(value->value.bool_value ? "true" : "false", stdout);
        break;
    case GeisaSensorValue_string_value_tag:
        geisa_print_json_key("string-value");
        geisa_print_json_escaped(value->value.string_value);
        break;
    default:
        geisa_print_json_key("unset");
        geisa_print_json_escaped("true");
        break;
    }
    putchar('}');
}

static inline void print_sensor_reading_json(const GeisaSensorReading *reading)
{
    putchar('{');
    geisa_print_json_key("sensor-id");
    geisa_print_json_escaped(reading->sensor_id);
    printf(",\"timestamp-ms\":%llu", (unsigned long long)reading->timestamp_ms);
    fputs(",\"values\":[", stdout);
    for (pb_size_t i = 0; i < reading->values_count; ++i)
    {
        if (i > 0)
        {
            putchar(',');
        }
        print_sensor_value_json(&reading->values[i]);
    }
    putchar(']');
    if (reading->has_unit)
    {
        fputs(",\"unit\":", stdout);
        geisa_print_json_escaped(reading->unit);
    }
    if (reading->has_quality)
    {
        fputs(",\"quality\":", stdout);
        geisa_print_json_escaped(reading->quality);
    }
    if (reading->has_status)
    {
        fputs(",\"status\":", stdout);
        geisa_print_json_escaped(reading->status);
    }
    putchar('}');
}

static inline int sensor_decode_and_print_response_file(const char *path)
{
    GeisaSensorReadings_Rsp message = (GeisaSensorReadings_Rsp)GeisaSensorReadings_Rsp_init_zero;
    if (!geisa_read_message_file(path, GeisaSensorReadings_Rsp_fields, &message))
    {
        return EXIT_FAILURE;
    }

    fputs("{\"geisa-sensor-readings-rsp\":{", stdout);
    if (message.has_status)
    {
        geisa_print_json_key("status");
        print_sensor_status_json(&message.status);
        putchar(',');
    }
    fputs("\"readings\":[", stdout);
    for (pb_size_t i = 0; i < message.readings_count; ++i)
    {
        if (i > 0)
        {
            putchar(',');
        }
        print_sensor_reading_json(&message.readings[i]);
    }
    fputs("]}}\n", stdout);
    return EXIT_SUCCESS;
}

static inline int sensor_run_demo_walkthrough(void)
{
    puts("Sensor readings response:");
    return sensor_decode_and_print_response_file(GEISA_SENSOR_RESPONSE_PATH);
}

#endif
