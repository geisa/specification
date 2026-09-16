//-----------------------------------------------------------------------------
// Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
// Security Alliance (GEISA), a Series of LF Projects, LLC
//
// Licensed under the Apache License, Version 2.0. See LICENSE.
//-----------------------------------------------------------------------------
//
// Shared helper utilities for GEISA embedded C conn-status examples.
//-----------------------------------------------------------------------------

#ifndef GEISA_CONN_STATUS_EXAMPLE_UTILS_H
#define GEISA_CONN_STATUS_EXAMPLE_UTILS_H

#include <stdio.h>
#include <stdlib.h>

#include "conn-status.pb.h"
#include "nanopb_example_utils.h"

#define GEISA_CONN_PLATFORM_STATUS_PATH "/tmp/conn-status-platform-status.bin"
#define GEISA_CONN_PLATFORM_TO_APP_STATUS_PATH "/tmp/conn-status-platform-to-app-status.bin"
#define GEISA_CONN_APP_TO_PLATFORM_STATUS_PATH "/tmp/conn-status-app-to-platform-status.bin"

static inline const char *conn_status_state_name(GeisaConnState state)
{
    switch (state)
    {
    case GeisaConnState_CONN_ENABLED_DOWN:
        return "CONN_ENABLED_DOWN";
    case GeisaConnState_CONN_ENABLED_UP:
        return "CONN_ENABLED_UP";
    case GeisaConnState_CONN_DISABLED:
    default:
        return "CONN_DISABLED";
    }
}

static inline const char *conn_status_policy_name(GeisaConnPolicy policy)
{
    switch (policy)
    {
    case GeisaConnPolicy_CONN_POLICY_METERED:
        return "CONN_POLICY_METERED";
    case GeisaConnPolicy_CONN_POLICY_UNLIMITED:
        return "CONN_POLICY_UNLIMITED";
    case GeisaConnPolicy_CONN_POLICY_ZERO:
    default:
        return "CONN_POLICY_ZERO";
    }
}

static inline const char *platform_mode_name(GeisaPlatformMode mode)
{
    switch (mode)
    {
    case GeisaPlatformMode_PLATFORM_MODE_UNPROVISIONED:
        return "PLATFORM_MODE_UNPROVISIONED";
    case GeisaPlatformMode_PLATFORM_MODE_MANUFACTURING:
        return "PLATFORM_MODE_MANUFACTURING";
    case GeisaPlatformMode_PLATFORM_MODE_TEST:
        return "PLATFORM_MODE_TEST";
    case GeisaPlatformMode_PLATFORM_MODE_NORMAL:
    default:
        return "PLATFORM_MODE_NORMAL";
    }
}

static inline const char *app_to_platform_status_type_name(GeisaAppToPlatformStatusType type)
{
    switch (type)
    {
    case GeisaAppToPlatformStatusType_CLEARED_PII:
        return "CLEARED_PII";
    case GeisaAppToPlatformStatusType_SHUTTING_DOWN:
        return "SHUTTING_DOWN";
    case GeisaAppToPlatformStatusType_NEED_TERMINATE_RESTART:
        return "NEED_TERMINATE_RESTART";
    case GeisaAppToPlatformStatusType_NEED_TERMINATE_NORESTART:
        return "NEED_TERMINATE_NORESTART";
    case GeisaAppToPlatformStatusType_RUNNING:
    default:
        return "RUNNING";
    }
}

static inline void fill_demo_conn_info(GeisaConnInfo *info,
                                       GeisaConnState state,
                                       bool ipv4,
                                       bool ipv6,
                                       bool realtime)
{
    *info = (GeisaConnInfo)GeisaConnInfo_init_zero;
    info->state = state;
    info->ipv4 = ipv4;
    info->ipv6 = ipv6;
    info->realtime = realtime;
}

static inline void fill_demo_conn_app_msg(GeisaConnAppMsg *message)
{
    *message = (GeisaConnAppMsg)GeisaConnAppMsg_init_zero;
    message->yesterday_used = 158;
    message->today_used = 42;
    message->today_limit = 500;
    message->today_remaining = 458;
    message->next_daily_reset_ms = 1762905600000ULL;
}

static inline void fill_demo_conn_app_info(GeisaConnAppInfo *info,
                                           GeisaConnPolicy policy,
                                           uint64_t yesterday_unlimited,
                                           uint64_t yesterday_metered,
                                           uint64_t today_unlimited,
                                           uint64_t today_metered,
                                           uint64_t limit_metered,
                                           uint64_t remaining_metered)
{
    *info = (GeisaConnAppInfo)GeisaConnAppInfo_init_zero;
    info->policy = policy;
    info->yesterday_used_unlimited = yesterday_unlimited;
    info->yesterday_used_metered = yesterday_metered;
    info->today_used_unlimited = today_unlimited;
    info->today_used_metered = today_metered;
    info->today_limit_metered = limit_metered;
    info->today_remaining_metered = remaining_metered;
    info->next_daily_reset_ms = 1762905600000ULL;
}

static inline void fill_demo_platform_status(GeisaPlatformStatus *message)
{
    *message = (GeisaPlatformStatus)GeisaPlatformStatus_init_zero;
    message->timestamp_ms = 1762862400000ULL;
    message->mode = GeisaPlatformMode_PLATFORM_MODE_NORMAL;
    message->conn_msg = GeisaConnState_CONN_ENABLED_UP;
    message->has_conn_oper = true;
    fill_demo_conn_info(&message->conn_oper, GeisaConnState_CONN_ENABLED_UP, true, true, true);
    message->has_conn_inet = true;
    fill_demo_conn_info(&message->conn_inet, GeisaConnState_CONN_ENABLED_DOWN, true, true, false);
    message->has_conn_local = true;
    fill_demo_conn_info(&message->conn_local, GeisaConnState_CONN_ENABLED_UP, true, false, true);
}

static inline void fill_demo_platform_to_app_status(GeisaPlatformToAppStatus *message)
{
    *message = (GeisaPlatformToAppStatus)GeisaPlatformToAppStatus_init_zero;
    message->cmd_send_status = true;
    message->cmd_shut_down = false;
    message->cmd_clear_pii = false;
    message->timestamp_ms = 1762862405000ULL;
    message->cpu_usage = 34.5f;
    message->cpu_limit = 80.0f;
    message->memory_usage = 8388608U;
    message->memory_limit = 33554432U;
    message->persist_storage_usage = 4194304U;
    message->persist_storage_limit = 67108864U;
    message->nonpersist_storage_usage = 1048576U;
    message->nonpersist_storage_limit = 8388608U;
    message->has_conn_msg = true;
    fill_demo_conn_app_msg(&message->conn_msg);
    message->has_conn_oper = true;
    fill_demo_conn_app_info(&message->conn_oper, GeisaConnPolicy_CONN_POLICY_METERED, 1024U, 8192U, 512U, 4096U, 65536U, 61440U);
    message->has_conn_inet = true;
    fill_demo_conn_app_info(&message->conn_inet, GeisaConnPolicy_CONN_POLICY_UNLIMITED, 20480U, 0U, 10240U, 0U, 0U, 0U);
    message->has_conn_local = true;
    fill_demo_conn_app_info(&message->conn_local, GeisaConnPolicy_CONN_POLICY_UNLIMITED, 4096U, 0U, 2048U, 0U, 0U, 0U);
}

static inline void fill_demo_app_to_platform_status(GeisaAppToPlatformStatus *message)
{
    *message = (GeisaAppToPlatformStatus)GeisaAppToPlatformStatus_init_zero;
    message->type = GeisaAppToPlatformStatusType_RUNNING;
    message->next_status = 60;
    message->next_status_timeout = 150;
}

static inline void print_conn_info_json(const GeisaConnInfo *info)
{
    putchar('{');
    geisa_print_json_key("state");
    geisa_print_json_escaped(conn_status_state_name(info->state));
    fputs(",\"ipv4\":", stdout);
    fputs(info->ipv4 ? "true" : "false", stdout);
    fputs(",\"ipv6\":", stdout);
    fputs(info->ipv6 ? "true" : "false", stdout);
    fputs(",\"realtime\":", stdout);
    fputs(info->realtime ? "true" : "false", stdout);
    putchar('}');
}

static inline void print_conn_app_msg_json(const GeisaConnAppMsg *message)
{
    printf("{\"yesterday-used\":%u,\"today-used\":%u,\"today-limit\":%u,\"today-remaining\":%u,"
           "\"next-daily-reset-ms\":%llu}",
           (unsigned)message->yesterday_used,
           (unsigned)message->today_used,
           (unsigned)message->today_limit,
           (unsigned)message->today_remaining,
           (unsigned long long)message->next_daily_reset_ms);
}

static inline void print_conn_app_info_json(const GeisaConnAppInfo *info)
{
    putchar('{');
    geisa_print_json_key("policy");
    geisa_print_json_escaped(conn_status_policy_name(info->policy));
    printf(",\"yesterday-used-unlimited\":%llu", (unsigned long long)info->yesterday_used_unlimited);
    printf(",\"yesterday-used-metered\":%llu", (unsigned long long)info->yesterday_used_metered);
    printf(",\"today-used-unlimited\":%llu", (unsigned long long)info->today_used_unlimited);
    printf(",\"today-used-metered\":%llu", (unsigned long long)info->today_used_metered);
    printf(",\"today-limit-metered\":%llu", (unsigned long long)info->today_limit_metered);
    printf(",\"today-remaining-metered\":%llu", (unsigned long long)info->today_remaining_metered);
    printf(",\"next-daily-reset-ms\":%llu", (unsigned long long)info->next_daily_reset_ms);
    putchar('}');
}

static inline int conn_status_decode_and_print_platform_status_file(const char *path)
{
    GeisaPlatformStatus message = (GeisaPlatformStatus)GeisaPlatformStatus_init_zero;
    if (!geisa_read_message_file(path, GeisaPlatformStatus_fields, &message))
    {
        return EXIT_FAILURE;
    }

    fputs("{\"geisa-platform-status\":{", stdout);
    printf("\"timestamp-ms\":%llu,", (unsigned long long)message.timestamp_ms);
    geisa_print_json_key("mode");
    geisa_print_json_escaped(platform_mode_name(message.mode));
    fputs(",\"conn-msg\":", stdout);
    geisa_print_json_escaped(conn_status_state_name(message.conn_msg));
    fputs(",\"conn-oper\":", stdout);
    print_conn_info_json(&message.conn_oper);
    fputs(",\"conn-inet\":", stdout);
    print_conn_info_json(&message.conn_inet);
    fputs(",\"conn-local\":", stdout);
    print_conn_info_json(&message.conn_local);
    fputs(",\"sys-over-temp\":", stdout);
    fputs(message.sys_over_temp ? "true" : "false", stdout);
    fputs(",\"sys-high-cpu\":", stdout);
    fputs(message.sys_high_cpu ? "true" : "false", stdout);
    fputs(",\"sys-low-mem\":", stdout);
    fputs(message.sys_low_mem ? "true" : "false", stdout);
    fputs(",\"sys-power-degraded\":", stdout);
    fputs(message.sys_power_degraded ? "true" : "false", stdout);
    fputs(",\"sys-power-loss\":", stdout);
    fputs(message.sys_power_loss ? "true" : "false", stdout);
    fputs(",\"sys-reboot-soon\":", stdout);
    fputs(message.sys_reboot_soon ? "true" : "false", stdout);
    fputs(",\"sys-shutdown-soon\":", stdout);
    fputs(message.sys_shutdown_soon ? "true" : "false", stdout);
    fputs("}}\n", stdout);
    return EXIT_SUCCESS;
}

static inline int conn_status_decode_and_print_platform_to_app_file(const char *path)
{
    GeisaPlatformToAppStatus message = (GeisaPlatformToAppStatus)GeisaPlatformToAppStatus_init_zero;
    if (!geisa_read_message_file(path, GeisaPlatformToAppStatus_fields, &message))
    {
        return EXIT_FAILURE;
    }

    fputs("{\"geisa-platform-to-app-status\":{", stdout);
    fputs("\"cmd-send-status\":", stdout);
    fputs(message.cmd_send_status ? "true" : "false", stdout);
    fputs(",\"cmd-shut-down\":", stdout);
    fputs(message.cmd_shut_down ? "true" : "false", stdout);
    fputs(",\"cmd-clear-pii\":", stdout);
    fputs(message.cmd_clear_pii ? "true" : "false", stdout);
    printf(",\"timestamp-ms\":%llu", (unsigned long long)message.timestamp_ms);
    printf(",\"cpu-usage\":%.6g", message.cpu_usage);
    printf(",\"cpu-limit\":%.6g", message.cpu_limit);
    printf(",\"memory-usage\":%u", (unsigned)message.memory_usage);
    printf(",\"memory-limit\":%u", (unsigned)message.memory_limit);
    printf(",\"persist-storage-usage\":%u", (unsigned)message.persist_storage_usage);
    printf(",\"persist-storage-limit\":%u", (unsigned)message.persist_storage_limit);
    printf(",\"nonpersist-storage-usage\":%u", (unsigned)message.nonpersist_storage_usage);
    printf(",\"nonpersist-storage-limit\":%u", (unsigned)message.nonpersist_storage_limit);
    fputs(",\"conn-msg\":", stdout);
    print_conn_app_msg_json(&message.conn_msg);
    fputs(",\"conn-oper\":", stdout);
    print_conn_app_info_json(&message.conn_oper);
    fputs(",\"conn-inet\":", stdout);
    print_conn_app_info_json(&message.conn_inet);
    fputs(",\"conn-local\":", stdout);
    print_conn_app_info_json(&message.conn_local);
    fputs("}}\n", stdout);
    return EXIT_SUCCESS;
}

static inline int conn_status_decode_and_print_app_to_platform_file(const char *path)
{
    GeisaAppToPlatformStatus message = (GeisaAppToPlatformStatus)GeisaAppToPlatformStatus_init_zero;
    if (!geisa_read_message_file(path, GeisaAppToPlatformStatus_fields, &message))
    {
        return EXIT_FAILURE;
    }

    fputs("{\"geisa-app-to-platform-status\":{", stdout);
    geisa_print_json_key("type");
    geisa_print_json_escaped(app_to_platform_status_type_name(message.type));
    printf(",\"next-status\":%ld", (long)message.next_status);
    printf(",\"next-status-timeout\":%ld", (long)message.next_status_timeout);
    fputs("}}\n", stdout);
    return EXIT_SUCCESS;
}

static inline int conn_status_run_demo_walkthrough(void)
{
    puts("Platform status:");
    if (conn_status_decode_and_print_platform_status_file(GEISA_CONN_PLATFORM_STATUS_PATH) != EXIT_SUCCESS)
    {
        return EXIT_FAILURE;
    }

    puts("Platform to app status:");
    if (conn_status_decode_and_print_platform_to_app_file(GEISA_CONN_PLATFORM_TO_APP_STATUS_PATH) != EXIT_SUCCESS)
    {
        return EXIT_FAILURE;
    }

    puts("App to platform status:");
    return conn_status_decode_and_print_app_to_platform_file(GEISA_CONN_APP_TO_PLATFORM_STATUS_PATH);
}

#endif
