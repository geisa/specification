//-----------------------------------------------------------------------------
// Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
// Security Alliance (GEISA), a Series of LF Projects, LLC
//
// Licensed under the Apache License, Version 2.0. See LICENSE.
//-----------------------------------------------------------------------------
//
// Shared helper utilities for GEISA embedded C actuator examples.
//-----------------------------------------------------------------------------

#ifndef GEISA_ACTUATOR_EXAMPLE_UTILS_H
#define GEISA_ACTUATOR_EXAMPLE_UTILS_H

#include <stdio.h>
#include <string.h>

#include "actuator.pb.h"
#include "geisa-status.pb.h"
#include "nanopb_example_utils.h"

#define GEISA_ACTUATOR_GET_REQ_PATH "/tmp/actuator-get-req.bin"
#define GEISA_ACTUATOR_GET_RSP_PATH "/tmp/actuator-get-rsp.bin"
#define GEISA_ACTUATOR_SET_REQ_PATH "/tmp/actuator-set-req.bin"
#define GEISA_ACTUATOR_SET_RSP_PATH "/tmp/actuator-set-rsp.bin"

static inline const char *geisa_status_code_name(GeisaStatusCode code)
{
    switch (code)
    {
    case GeisaStatusCode_GEISA_STATUS_SUCCESS:
        return "GeisaStatusCode_GEISA_STATUS_SUCCESS";
    case GeisaStatusCode_GEISA_STATUS_CODE_REQUEST_BAD_REQUEST:
        return "GeisaStatusCode_GEISA_STATUS_CODE_REQUEST_BAD_REQUEST";
    case GeisaStatusCode_GEISA_STATUS_CODE_REQUEST_INVALID_ARGUMENT:
        return "GeisaStatusCode_GEISA_STATUS_CODE_REQUEST_INVALID_ARGUMENT";
    case GeisaStatusCode_GEISA_STATUS_CODE_REQUEST_MALFORMED_PAYLOAD:
        return "GeisaStatusCode_GEISA_STATUS_CODE_REQUEST_MALFORMED_PAYLOAD";
    case GeisaStatusCode_GEISA_STATUS_CODE_REQUEST_DUPLICATE_TARGET:
        return "GeisaStatusCode_GEISA_STATUS_CODE_REQUEST_DUPLICATE_TARGET";
    case GeisaStatusCode_GEISA_STATUS_CODE_REQUEST_OUT_OF_RANGE:
        return "GeisaStatusCode_GEISA_STATUS_CODE_REQUEST_OUT_OF_RANGE";
    case GeisaStatusCode_GEISA_STATUS_CODE_REQUEST_UNSUPPORTED:
        return "GeisaStatusCode_GEISA_STATUS_CODE_REQUEST_UNSUPPORTED";
    case GeisaStatusCode_GEISA_STATUS_CODE_AUTH_UNAUTHORIZED:
        return "GeisaStatusCode_GEISA_STATUS_CODE_AUTH_UNAUTHORIZED";
    case GeisaStatusCode_GEISA_STATUS_CODE_AUTH_FORBIDDEN:
        return "GeisaStatusCode_GEISA_STATUS_CODE_AUTH_FORBIDDEN";
    case GeisaStatusCode_GEISA_STATUS_CODE_RESOURCE_NOT_FOUND:
        return "GeisaStatusCode_GEISA_STATUS_CODE_RESOURCE_NOT_FOUND";
    case GeisaStatusCode_GEISA_STATUS_CODE_RESOURCE_BUSY:
        return "GeisaStatusCode_GEISA_STATUS_CODE_RESOURCE_BUSY";
    case GeisaStatusCode_GEISA_STATUS_CODE_RESOURCE_CONFLICT:
        return "GeisaStatusCode_GEISA_STATUS_CODE_RESOURCE_CONFLICT";
    case GeisaStatusCode_GEISA_STATUS_CODE_RESOURCE_NO_RESOURCES:
        return "GeisaStatusCode_GEISA_STATUS_CODE_RESOURCE_NO_RESOURCES";
    case GeisaStatusCode_GEISA_STATUS_CODE_RESOURCE_RATE_LIMITED:
        return "GeisaStatusCode_GEISA_STATUS_CODE_RESOURCE_RATE_LIMITED";
    case GeisaStatusCode_GEISA_STATUS_CODE_EXEC_TIMEOUT:
        return "GeisaStatusCode_GEISA_STATUS_CODE_EXEC_TIMEOUT";
    case GeisaStatusCode_GEISA_STATUS_CODE_EXEC_NOT_SUPPORTED:
        return "GeisaStatusCode_GEISA_STATUS_CODE_EXEC_NOT_SUPPORTED";
    case GeisaStatusCode_GEISA_STATUS_CODE_EXEC_PLATFORM_ERROR:
        return "GeisaStatusCode_GEISA_STATUS_CODE_EXEC_PLATFORM_ERROR";
    case GeisaStatusCode_GEISA_STATUS_CODE_EXEC_INTERNAL_ERROR:
        return "GeisaStatusCode_GEISA_STATUS_CODE_EXEC_INTERNAL_ERROR";
    case GeisaStatusCode_GEISA_STATUS_CODE_EXEC_PARTIAL_FAILURE:
        return "GeisaStatusCode_GEISA_STATUS_CODE_EXEC_PARTIAL_FAILURE";
    case GeisaStatusCode_GEISA_STATUS_CODE_DATA_UNAVAILABLE:
        return "GeisaStatusCode_GEISA_STATUS_CODE_DATA_UNAVAILABLE";
    case GeisaStatusCode_GEISA_STATUS_CODE_DATA_STALE:
        return "GeisaStatusCode_GEISA_STATUS_CODE_DATA_STALE";
    case GeisaStatusCode_GEISA_STATUS_CODE_UNSPECIFIED:
    default:
        return "GeisaStatusCode_GEISA_STATUS_CODE_UNSPECIFIED";
    }
}

static inline const char *geisa_actuator_name(GeisaTypeActuator value)
{
    switch (value)
    {
    case GeisaTypeActuator_GEISA_TYPE_ACTUATOR_SERVICE_SWITCH:
        return "service-switch";
    case GeisaTypeActuator_GEISA_TYPE_ACTUATOR_DER_SWITCH:
        return "der-switch";
    case GeisaTypeActuator_GEISA_TYPE_ACTUATOR_LC_RELAY_0:
        return "lc-relay-0";
    case GeisaTypeActuator_GEISA_TYPE_ACTUATOR_LC_RELAY_1:
        return "lc-relay-1";
    case GeisaTypeActuator_GEISA_TYPE_ACTUATOR_LC_RELAY_2:
        return "lc-relay-2";
    case GeisaTypeActuator_GEISA_TYPE_ACTUATOR_LC_RELAY_3:
        return "lc-relay-3";
    case GeisaTypeActuator_GEISA_TYPE_ACTUATOR_UNSPECIFIED:
    default:
        return "unspecified";
    }
}

static inline const char *geisa_onoff_name(GeisaTypeOnOff value)
{
    switch (value)
    {
    case GeisaTypeOnOff_GEISA_TYPE_ON_OFF_ON:
        return "on";
    case GeisaTypeOnOff_GEISA_TYPE_ON_OFF_OFF:
        return "off";
    case GeisaTypeOnOff_GEISA_TYPE_ON_OFF_UNSPECIFIED:
    default:
        return "unspecified";
    }
}

static inline void print_geisa_status_json_c(const GeisaStatus *status)
{
    putchar('{');
    geisa_print_json_key("code");
    geisa_print_json_escaped(geisa_status_code_name(status->code));
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

static inline void print_actuator_status_json(const GeisaActuatorStatus *status)
{
    putchar('{');
    geisa_print_json_key("actuator");
    geisa_print_json_escaped(geisa_actuator_name(status->actuator));
    fputs(",\"state\":", stdout);
    geisa_print_json_escaped(geisa_onoff_name(status->on));
    fputs(",\"position-present\":", stdout);
    fputs(status->position_present ? "true" : "false", stdout);
    if (status->position_present)
    {
        printf(",\"position\":%d", status->position);
    }
    putchar('}');
}

static inline void fill_demo_actuator_get_req(GeisaActuatorGet_Req *message)
{
    *message = (GeisaActuatorGet_Req)GeisaActuatorGet_Req_init_zero;
    message->actuator = GeisaTypeActuator_GEISA_TYPE_ACTUATOR_SERVICE_SWITCH;
}

static inline void fill_demo_actuator_get_rsp(GeisaActuatorGet_Rsp *message)
{
    *message = (GeisaActuatorGet_Rsp)GeisaActuatorGet_Rsp_init_zero;
    message->has_status = true;
    message->has_actuator_status = true;
    message->status.code = GeisaStatusCode_GEISA_STATUS_SUCCESS;
    strncpy(message->status.message, "ok", sizeof(message->status.message) - 1);
    message->actuator_status.actuator = GeisaTypeActuator_GEISA_TYPE_ACTUATOR_SERVICE_SWITCH;
    message->actuator_status.on = GeisaTypeOnOff_GEISA_TYPE_ON_OFF_ON;
    message->actuator_status.position_present = false;
}

static inline void fill_demo_actuator_set_req(GeisaActuatorSet_Req *message)
{
    *message = (GeisaActuatorSet_Req)GeisaActuatorSet_Req_init_zero;
    message->new_settings_count = 1;
    message->new_settings[0] = (GeisaActuatorStatus)GeisaActuatorStatus_init_zero;
    message->new_settings[0].actuator = GeisaTypeActuator_GEISA_TYPE_ACTUATOR_LC_RELAY_0;
    message->new_settings[0].on = GeisaTypeOnOff_GEISA_TYPE_ON_OFF_OFF;
    message->new_settings[0].position_present = false;
}

static inline void fill_demo_actuator_set_rsp(GeisaActuatorSet_Rsp *message)
{
    *message = (GeisaActuatorSet_Rsp)GeisaActuatorSet_Rsp_init_zero;
    message->has_status = true;
    message->status.code = GeisaStatusCode_GEISA_STATUS_SUCCESS;
    strncpy(message->status.message, "accepted", sizeof(message->status.message) - 1);
}

static inline int actuator_decode_and_print_get_req_file(const char *path)
{
    GeisaActuatorGet_Req message = (GeisaActuatorGet_Req)GeisaActuatorGet_Req_init_zero;
    if (!geisa_read_message_file(path, GeisaActuatorGet_Req_fields, &message))
    {
        return EXIT_FAILURE;
    }
    fputs("{\"geisa-actuator-get-req\":{\"actuator\":", stdout);
    geisa_print_json_escaped(geisa_actuator_name(message.actuator));
    fputs("}}\n", stdout);
    return EXIT_SUCCESS;
}

static inline int actuator_decode_and_print_get_rsp_file(const char *path)
{
    GeisaActuatorGet_Rsp message = (GeisaActuatorGet_Rsp)GeisaActuatorGet_Rsp_init_zero;
    if (!geisa_read_message_file(path, GeisaActuatorGet_Rsp_fields, &message))
    {
        return EXIT_FAILURE;
    }
    fputs("{\"geisa-actuator-get-rsp\":{\"status\":", stdout);
    print_geisa_status_json_c(&message.status);
    fputs(",\"actuator-status\":", stdout);
    print_actuator_status_json(&message.actuator_status);
    fputs("}}\n", stdout);
    return EXIT_SUCCESS;
}

static inline int actuator_decode_and_print_set_req_file(const char *path)
{
    GeisaActuatorSet_Req message = (GeisaActuatorSet_Req)GeisaActuatorSet_Req_init_zero;
    if (!geisa_read_message_file(path, GeisaActuatorSet_Req_fields, &message))
    {
        return EXIT_FAILURE;
    }
    fputs("{\"geisa-actuator-set-req\":{\"new-settings\":[", stdout);
    for (pb_size_t i = 0; i < message.new_settings_count; ++i)
    {
        if (i > 0)
        {
            putchar(',');
        }
        print_actuator_status_json(&message.new_settings[i]);
    }
    fputs("]}}\n", stdout);
    return EXIT_SUCCESS;
}

static inline int actuator_decode_and_print_set_rsp_file(const char *path)
{
    GeisaActuatorSet_Rsp message = (GeisaActuatorSet_Rsp)GeisaActuatorSet_Rsp_init_zero;
    if (!geisa_read_message_file(path, GeisaActuatorSet_Rsp_fields, &message))
    {
        return EXIT_FAILURE;
    }
    fputs("{\"geisa-actuator-set-rsp\":{\"status\":", stdout);
    print_geisa_status_json_c(&message.status);
    fputs("}}\n", stdout);
    return EXIT_SUCCESS;
}

static inline int actuator_run_demo_walkthrough(void)
{
    puts("Actuator get request:");
    if (actuator_decode_and_print_get_req_file(GEISA_ACTUATOR_GET_REQ_PATH) != EXIT_SUCCESS)
    {
        return EXIT_FAILURE;
    }
    puts("Actuator get response:");
    if (actuator_decode_and_print_get_rsp_file(GEISA_ACTUATOR_GET_RSP_PATH) != EXIT_SUCCESS)
    {
        return EXIT_FAILURE;
    }
    puts("Actuator set request:");
    if (actuator_decode_and_print_set_req_file(GEISA_ACTUATOR_SET_REQ_PATH) != EXIT_SUCCESS)
    {
        return EXIT_FAILURE;
    }
    puts("Actuator set response:");
    if (actuator_decode_and_print_set_rsp_file(GEISA_ACTUATOR_SET_RSP_PATH) != EXIT_SUCCESS)
    {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

#endif
