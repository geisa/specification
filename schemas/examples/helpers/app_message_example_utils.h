//-----------------------------------------------------------------------------
// Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
// Security Alliance (GEISA), a Series of LF Projects, LLC
//
// Licensed under the Apache License, Version 2.0. See LICENSE.
//-----------------------------------------------------------------------------
//
// Shared helper utilities for GEISA embedded C app-message examples.
//-----------------------------------------------------------------------------

#ifndef GEISA_APP_MESSAGE_EXAMPLE_UTILS_H
#define GEISA_APP_MESSAGE_EXAMPLE_UTILS_H

#include <stdio.h>
#include <string.h>

#include "app-message.pb.h"
#include "nanopb_example_utils.h"

#define GEISA_APP_MESSAGE_REQ_PATH "/tmp/app-message-req.bin"
#define GEISA_APP_MESSAGE_RSP_PATH "/tmp/app-message-rsp.bin"

static inline const char *geisa_app_message_priority_name(GeisaAppMessagePriority value)
{
    switch (value)
    {
    case GeisaAppMessagePriority_GEISA_APP_MESSAGE_PRIORITY_URGENT:
        return "GeisaAppMessagePriority_GEISA_APP_MESSAGE_PRIORITY_URGENT";
    case GeisaAppMessagePriority_GEISA_APP_MESSAGE_PRIORITY_IMMEDIATE:
        return "GeisaAppMessagePriority_GEISA_APP_MESSAGE_PRIORITY_IMMEDIATE";
    case GeisaAppMessagePriority_GEISA_APP_MESSAGE_PRIORITY_BEST_EFFORT:
        return "GeisaAppMessagePriority_GEISA_APP_MESSAGE_PRIORITY_BEST_EFFORT";
    case GeisaAppMessagePriority_GEISA_APP_MESSAGE_PRIORITY_LATEST:
        return "GeisaAppMessagePriority_GEISA_APP_MESSAGE_PRIORITY_LATEST";
    case GeisaAppMessagePriority_GEISA_APP_MESSAGE_PRIORITY_UNSPECIFIED:
    default:
        return "GeisaAppMessagePriority_GEISA_APP_MESSAGE_PRIORITY_UNSPECIFIED";
    }
}

static inline const char *geisa_app_message_type_name(GeisaAppMessageType value)
{
    switch (value)
    {
    case GeisaAppMessageType_GEISA_APP_MESSAGE_TYPE_CONFIG:
        return "GeisaAppMessageType_GEISA_APP_MESSAGE_TYPE_CONFIG";
    case GeisaAppMessageType_GEISA_APP_MESSAGE_TYPE_COMMAND:
        return "GeisaAppMessageType_GEISA_APP_MESSAGE_TYPE_COMMAND";
    case GeisaAppMessageType_GEISA_APP_MESSAGE_TYPE_COMMAND_RESULT:
        return "GeisaAppMessageType_GEISA_APP_MESSAGE_TYPE_COMMAND_RESULT";
    case GeisaAppMessageType_GEISA_APP_MESSAGE_TYPE_STATUS:
        return "GeisaAppMessageType_GEISA_APP_MESSAGE_TYPE_STATUS";
    case GeisaAppMessageType_GEISA_APP_MESSAGE_TYPE_EVENT:
        return "GeisaAppMessageType_GEISA_APP_MESSAGE_TYPE_EVENT";
    case GeisaAppMessageType_GEISA_APP_MESSAGE_TYPE_ALARM:
        return "GeisaAppMessageType_GEISA_APP_MESSAGE_TYPE_ALARM";
    case GeisaAppMessageType_GEISA_APP_MESSAGE_TYPE_APP_DATA:
        return "GeisaAppMessageType_GEISA_APP_MESSAGE_TYPE_APP_DATA";
    case GeisaAppMessageType_GEISA_APP_MESSAGE_TYPE_TELEMETRY:
        return "GeisaAppMessageType_GEISA_APP_MESSAGE_TYPE_TELEMETRY";
    case GeisaAppMessageType_GEISA_APP_MESSAGE_TYPE_UNSPECIFIED:
    default:
        return "GeisaAppMessageType_GEISA_APP_MESSAGE_TYPE_UNSPECIFIED";
    }
}

static inline const char *geisa_app_message_status_name(GeisaAppMessageStatus value)
{
    switch (value)
    {
    case GeisaAppMessageStatus_GEISA_APP_MESSAGE_STATUS_ACCEPTED:
        return "GeisaAppMessageStatus_GEISA_APP_MESSAGE_STATUS_ACCEPTED";
    case GeisaAppMessageStatus_GEISA_APP_MESSAGE_STATUS_REJECTED:
        return "GeisaAppMessageStatus_GEISA_APP_MESSAGE_STATUS_REJECTED";
    case GeisaAppMessageStatus_GEISA_APP_MESSAGE_STATUS_PERMISSION_DENIED:
        return "GeisaAppMessageStatus_GEISA_APP_MESSAGE_STATUS_PERMISSION_DENIED";
    case GeisaAppMessageStatus_GEISA_APP_MESSAGE_STATUS_QUOTA_EXCEEDED:
        return "GeisaAppMessageStatus_GEISA_APP_MESSAGE_STATUS_QUOTA_EXCEEDED";
    case GeisaAppMessageStatus_GEISA_APP_MESSAGE_STATUS_UNAVAILABLE:
        return "GeisaAppMessageStatus_GEISA_APP_MESSAGE_STATUS_UNAVAILABLE";
    case GeisaAppMessageStatus_GEISA_APP_MESSAGE_STATUS_EXPIRED:
        return "GeisaAppMessageStatus_GEISA_APP_MESSAGE_STATUS_EXPIRED";
    case GeisaAppMessageStatus_GEISA_APP_MESSAGE_STATUS_OTHER:
        return "GeisaAppMessageStatus_GEISA_APP_MESSAGE_STATUS_OTHER";
    case GeisaAppMessageStatus_GEISA_APP_MESSAGE_STATUS_UNSPECIFIED:
    default:
        return "GeisaAppMessageStatus_GEISA_APP_MESSAGE_STATUS_UNSPECIFIED";
    }
}

static inline void fill_demo_app_message_req(GeisaAppMessage_Req *message)
{
    static const char payload[] = "{\"event\":\"meter-snapshot\",\"kwh\":1234567}";
    *message = (GeisaAppMessage_Req)GeisaAppMessage_Req_init_zero;
    strncpy(message->request_id, "req-0001", sizeof(message->request_id) - 1);
    message->priority = GeisaAppMessagePriority_GEISA_APP_MESSAGE_PRIORITY_IMMEDIATE;
    message->message_type = GeisaAppMessageType_GEISA_APP_MESSAGE_TYPE_APP_DATA;
    message->timestamp_ms = 1762862400000ULL;
    message->ttl_seconds = 300ULL;
    strncpy(message->content_type, "application/json", sizeof(message->content_type) - 1);
    message->payload.size = sizeof(payload) - 1;
    memcpy(message->payload.bytes, payload, sizeof(payload) - 1);
}

static inline void fill_demo_app_message_rsp(GeisaAppMessage_Rsp *message)
{
    *message = (GeisaAppMessage_Rsp)GeisaAppMessage_Rsp_init_zero;
    strncpy(message->request_id, "req-0001", sizeof(message->request_id) - 1);
    message->status = GeisaAppMessageStatus_GEISA_APP_MESSAGE_STATUS_ACCEPTED;
    strncpy(message->status_text, "accepted for processing", sizeof(message->status_text) - 1);
    message->timestamp_ms = 1762862400100ULL;
}

static inline int app_message_decode_and_print_req_file(const char *path)
{
    GeisaAppMessage_Req message = (GeisaAppMessage_Req)GeisaAppMessage_Req_init_zero;
    if (!geisa_read_message_file(path, GeisaAppMessage_Req_fields, &message))
    {
        return EXIT_FAILURE;
    }
    fputs("{\"geisa-app-message-req\":{", stdout);
    geisa_print_json_key("request-id");
    geisa_print_json_escaped(message.request_id);
    fputs(",\"priority\":", stdout);
    geisa_print_json_escaped(geisa_app_message_priority_name(message.priority));
    fputs(",\"message-type\":", stdout);
    geisa_print_json_escaped(geisa_app_message_type_name(message.message_type));
    printf(",\"timestamp-ms\":%llu", (unsigned long long)message.timestamp_ms);
    printf(",\"ttl-seconds\":%llu", (unsigned long long)message.ttl_seconds);
    if (message.content_type[0] != '\0')
    {
        fputs(",\"content-type\":", stdout);
        geisa_print_json_escaped(message.content_type);
    }
    if (message.payload.size > 0)
    {
        fputs(",\"payload-hex\":", stdout);
        geisa_print_json_bytes_hex((const pb_bytes_array_t *)&message.payload);
    }
    fputs("}}\n", stdout);
    return EXIT_SUCCESS;
}

static inline int app_message_decode_and_print_rsp_file(const char *path)
{
    GeisaAppMessage_Rsp message = (GeisaAppMessage_Rsp)GeisaAppMessage_Rsp_init_zero;
    if (!geisa_read_message_file(path, GeisaAppMessage_Rsp_fields, &message))
    {
        return EXIT_FAILURE;
    }
    fputs("{\"geisa-app-message-rsp\":{", stdout);
    geisa_print_json_key("request-id");
    geisa_print_json_escaped(message.request_id);
    fputs(",\"status\":", stdout);
    geisa_print_json_escaped(geisa_app_message_status_name(message.status));
    printf(",\"timestamp-ms\":%llu", (unsigned long long)message.timestamp_ms);
    if (message.status_text[0] != '\0')
    {
        fputs(",\"status-text\":", stdout);
        geisa_print_json_escaped(message.status_text);
    }
    fputs("}}\n", stdout);
    return EXIT_SUCCESS;
}

static inline int app_message_run_demo_walkthrough(void)
{
    puts("App-message request:");
    if (app_message_decode_and_print_req_file(GEISA_APP_MESSAGE_REQ_PATH) != EXIT_SUCCESS)
    {
        return EXIT_FAILURE;
    }
    puts("App-message response:");
    if (app_message_decode_and_print_rsp_file(GEISA_APP_MESSAGE_RSP_PATH) != EXIT_SUCCESS)
    {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

#endif
