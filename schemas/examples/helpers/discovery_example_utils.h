//-----------------------------------------------------------------------------
// Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
// Security Alliance (GEISA), a Series of LF Projects, LLC
//
// Licensed under the Apache License, Version 2.0. See LICENSE.
//-----------------------------------------------------------------------------
//
// Shared helper utilities for GEISA embedded C Platform Discovery examples.
//-----------------------------------------------------------------------------

#ifndef GEISA_DISCOVERY_EXAMPLE_UTILS_H
#define GEISA_DISCOVERY_EXAMPLE_UTILS_H

#include <stdio.h>
#include <string.h>

#include "discovery.pb.h"
#include "geisa-status.pb.h"
#include "nanopb_example_utils.h"
#include "sensor.pb.h"
#include "waveform.pb.h"

#define GEISA_DISCOVERY_REQUEST_PATH "/tmp/discovery-request.bin"
#define GEISA_DISCOVERY_RESPONSE_PATH "/tmp/discovery-response.bin"

static inline const char *discovery_status_code_name(GeisaStatusCode code)
{
    switch (code)
    {
    case GeisaStatusCode_GEISA_STATUS_SUCCESS:
        return "GeisaStatusCode_GEISA_STATUS_SUCCESS";
    case GeisaStatusCode_GEISA_STATUS_CODE_UNSPECIFIED:
    default:
        return "GeisaStatusCode_GEISA_STATUS_CODE_UNSPECIFIED";
    }
}

static inline const char *discovery_device_type_name(GeisaPlatformDiscovery_DeviceType type)
{
    switch (type)
    {
    case GeisaPlatformDiscovery_DeviceType_TYPE_ELECTRIC_METER:
        return "GeisaPlatformDiscovery_DeviceType_TYPE_ELECTRIC_METER";
    case GeisaPlatformDiscovery_DeviceType_TYPE_COMPUTE_CARD:
        return "GeisaPlatformDiscovery_DeviceType_TYPE_COMPUTE_CARD";
    case GeisaPlatformDiscovery_DeviceType_TYPE_NETWORK_CARD:
        return "GeisaPlatformDiscovery_DeviceType_TYPE_NETWORK_CARD";
    case GeisaPlatformDiscovery_DeviceType_TYPE_METROLOGY_PROCESSOR:
        return "GeisaPlatformDiscovery_DeviceType_TYPE_METROLOGY_PROCESSOR";
    case GeisaPlatformDiscovery_DeviceType_TYPE_COPROCESSOR_CARD:
    default:
        return "GeisaPlatformDiscovery_DeviceType_TYPE_COPROCESSOR_CARD";
    }
}

static inline const char *discovery_network_class_name(GeisaPlatformDiscovery_NetworkClass value)
{
    switch (value)
    {
    case GeisaPlatformDiscovery_NetworkClass_NETWORK_CLASS_OPERATOR:
        return "GeisaPlatformDiscovery_NetworkClass_NETWORK_CLASS_OPERATOR";
    case GeisaPlatformDiscovery_NetworkClass_NETWORK_CLASS_INTERNET:
        return "GeisaPlatformDiscovery_NetworkClass_NETWORK_CLASS_INTERNET";
    case GeisaPlatformDiscovery_NetworkClass_NETWORK_CLASS_LOCAL:
        return "GeisaPlatformDiscovery_NetworkClass_NETWORK_CLASS_LOCAL";
    case GeisaPlatformDiscovery_NetworkClass_NETWORK_CLASS_OTHER:
        return "GeisaPlatformDiscovery_NetworkClass_NETWORK_CLASS_OTHER";
    case GeisaPlatformDiscovery_NetworkClass_NETWORK_CLASS_UNSPECIFIED:
    default:
        return "GeisaPlatformDiscovery_NetworkClass_NETWORK_CLASS_UNSPECIFIED";
    }
}

static inline const char *discovery_network_owner_name(GeisaPlatformDiscovery_NetworkOwner value)
{
    switch (value)
    {
    case GeisaPlatformDiscovery_NetworkOwner_NETWORK_OWNER_OPERATOR:
        return "GeisaPlatformDiscovery_NetworkOwner_NETWORK_OWNER_OPERATOR";
    case GeisaPlatformDiscovery_NetworkOwner_NETWORK_OWNER_CONSUMER:
        return "GeisaPlatformDiscovery_NetworkOwner_NETWORK_OWNER_CONSUMER";
    case GeisaPlatformDiscovery_NetworkOwner_NETWORK_OWNER_THIRD_PARTY:
        return "GeisaPlatformDiscovery_NetworkOwner_NETWORK_OWNER_THIRD_PARTY";
    case GeisaPlatformDiscovery_NetworkOwner_NETWORK_OWNER_SHARED:
        return "GeisaPlatformDiscovery_NetworkOwner_NETWORK_OWNER_SHARED";
    case GeisaPlatformDiscovery_NetworkOwner_NETWORK_OWNER_OTHER:
        return "GeisaPlatformDiscovery_NetworkOwner_NETWORK_OWNER_OTHER";
    case GeisaPlatformDiscovery_NetworkOwner_NETWORK_OWNER_UNSPECIFIED:
    default:
        return "GeisaPlatformDiscovery_NetworkOwner_NETWORK_OWNER_UNSPECIFIED";
    }
}

static inline const char *discovery_network_technology_name(GeisaPlatformDiscovery_NetworkTechnology value)
{
    switch (value)
    {
    case GeisaPlatformDiscovery_NetworkTechnology_NETWORK_TECHNOLOGY_RF_MESH:
        return "GeisaPlatformDiscovery_NetworkTechnology_NETWORK_TECHNOLOGY_RF_MESH";
    case GeisaPlatformDiscovery_NetworkTechnology_NETWORK_TECHNOLOGY_CELLULAR:
        return "GeisaPlatformDiscovery_NetworkTechnology_NETWORK_TECHNOLOGY_CELLULAR";
    case GeisaPlatformDiscovery_NetworkTechnology_NETWORK_TECHNOLOGY_ETHERNET:
        return "GeisaPlatformDiscovery_NetworkTechnology_NETWORK_TECHNOLOGY_ETHERNET";
    case GeisaPlatformDiscovery_NetworkTechnology_NETWORK_TECHNOLOGY_FIBER:
        return "GeisaPlatformDiscovery_NetworkTechnology_NETWORK_TECHNOLOGY_FIBER";
    case GeisaPlatformDiscovery_NetworkTechnology_NETWORK_TECHNOLOGY_WIFI:
        return "GeisaPlatformDiscovery_NetworkTechnology_NETWORK_TECHNOLOGY_WIFI";
    case GeisaPlatformDiscovery_NetworkTechnology_NETWORK_TECHNOLOGY_OTHER:
        return "GeisaPlatformDiscovery_NetworkTechnology_NETWORK_TECHNOLOGY_OTHER";
    case GeisaPlatformDiscovery_NetworkTechnology_NETWORK_TECHNOLOGY_UNSPECIFIED:
    default:
        return "GeisaPlatformDiscovery_NetworkTechnology_NETWORK_TECHNOLOGY_UNSPECIFIED";
    }
}

static inline const char *discovery_sensor_type_name(GeisaSensorType type)
{
    switch (type)
    {
    case GeisaSensorType_GEISA_SENSOR_TYPE_TEMPERATURE:
        return "GeisaSensorType_GEISA_SENSOR_TYPE_TEMPERATURE";
    case GeisaSensorType_GEISA_SENSOR_TYPE_CUSTOM:
        return "GeisaSensorType_GEISA_SENSOR_TYPE_CUSTOM";
    case GeisaSensorType_GEISA_SENSOR_TYPE_UNSPECIFIED:
    default:
        return "GeisaSensorType_GEISA_SENSOR_TYPE_UNSPECIFIED";
    }
}

static inline const char *discovery_waveform_sample_type_name(GeisaWaveform_SampleType value)
{
    switch (value)
    {
    case GeisaWaveform_SampleType_WAVEFORM_SAMPLE_TYPE_INT16:
        return "GeisaWaveform_SampleType_WAVEFORM_SAMPLE_TYPE_INT16";
    case GeisaWaveform_SampleType_WAVEFORM_SAMPLE_TYPE_INT32:
        return "GeisaWaveform_SampleType_WAVEFORM_SAMPLE_TYPE_INT32";
    case GeisaWaveform_SampleType_WAVEFORM_SAMPLE_TYPE_FLOAT32:
        return "GeisaWaveform_SampleType_WAVEFORM_SAMPLE_TYPE_FLOAT32";
    case GeisaWaveform_SampleType_WAVEFORM_SAMPLE_TYPE_FLOAT64:
        return "GeisaWaveform_SampleType_WAVEFORM_SAMPLE_TYPE_FLOAT64";
    case GeisaWaveform_SampleType_WAVEFORM_SAMPLE_TYPE_UNSPECIFIED:
    default:
        return "GeisaWaveform_SampleType_WAVEFORM_SAMPLE_TYPE_UNSPECIFIED";
    }
}

static inline void fill_demo_discovery_req(GeisaPlatformDiscovery_Req *message)
{
    *message = (GeisaPlatformDiscovery_Req)GeisaPlatformDiscovery_Req_init_zero;
}

static inline void fill_demo_module(GeisaPlatformDiscovery_Module *module,
                                    GeisaPlatformDiscovery_DeviceType type,
                                    const char *manufacturer,
                                    const char *model,
                                    const char *serial,
                                    const char *hardware,
                                    const char *firmware)
{
    *module = (GeisaPlatformDiscovery_Module)GeisaPlatformDiscovery_Module_init_zero;
    module->type = type;
    strncpy(module->manufacturer, manufacturer, sizeof(module->manufacturer) - 1);
    strncpy(module->model, model, sizeof(module->model) - 1);
    strncpy(module->serial_number, serial, sizeof(module->serial_number) - 1);
    strncpy(module->hw_revision, hardware, sizeof(module->hw_revision) - 1);
    strncpy(module->fw_revision, firmware, sizeof(module->fw_revision) - 1);
}

static inline void fill_demo_discovery_sensor(GeisaSensorDescriptor *sensor)
{
    *sensor = (GeisaSensorDescriptor)GeisaSensorDescriptor_init_zero;
    strncpy(sensor->sensor_id, "board-temp-1", sizeof(sensor->sensor_id) - 1);
    sensor->sensor_type = GeisaSensorType_GEISA_SENSOR_TYPE_TEMPERATURE;
    sensor->has_name = true;
    strncpy(sensor->name, "Board temperature", sizeof(sensor->name) - 1);
    sensor->has_description = true;
    strncpy(sensor->description, "Temperature sensor on the compute board",
            sizeof(sensor->description) - 1);
    strncpy(sensor->unit, "Cel", sizeof(sensor->unit) - 1);
    sensor->supports_read = true;
    sensor->supports_publish = true;
    sensor->has_min_report_period_ms = true;
    sensor->min_report_period_ms = 1000ULL;
    sensor->has_max_report_period_ms = true;
    sensor->max_report_period_ms = 60000ULL;
}

static inline void fill_demo_network(GeisaPlatformDiscovery_Network_Instance *network,
                                     const char *interface_id,
                                     GeisaPlatformDiscovery_NetworkClass network_class,
                                     GeisaPlatformDiscovery_NetworkOwner owner,
                                     GeisaPlatformDiscovery_NetworkTechnology technology,
                                     const char *name)
{
    *network = (GeisaPlatformDiscovery_Network_Instance)GeisaPlatformDiscovery_Network_Instance_init_zero;
    strncpy(network->interface_id, interface_id, sizeof(network->interface_id) - 1);
    network->network_class = network_class;
    network->owner = owner;
    network->technology = technology;
    network->supports_ipv4 = true;
    network->supports_ipv6 = true;
    network->has_name = true;
    strncpy(network->name, name, sizeof(network->name) - 1);
}

static inline void fill_demo_discovery_rsp(GeisaPlatformDiscovery_Rsp *message)
{
    *message = (GeisaPlatformDiscovery_Rsp)GeisaPlatformDiscovery_Rsp_init_zero;

    message->has_status = true;
    message->status.code = GeisaStatusCode_GEISA_STATUS_SUCCESS;
    strncpy(message->status.message, "ok", sizeof(message->status.message) - 1);

    message->has_geisa = true;
    message->geisa.ver_major = 0;
    message->geisa.ver_minor = 9;
    message->geisa.ver_rev = 0;
    message->geisa.pillar_adm = true;
    message->geisa.pillar_api = true;
    message->geisa.pillar_lee = true;
    message->geisa.pillar_vee = false;

    message->has_device = true;
    message->device.has_top_module = true;
    fill_demo_module(&message->device.top_module,
                     GeisaPlatformDiscovery_DeviceType_TYPE_ELECTRIC_METER,
                     "GEISA Example",
                     "Edge Meter 2000",
                     "EM2000-0001",
                     "1.0",
                     "0.9.0");
    message->device.sub_module_count = 1;
    fill_demo_module(&message->device.sub_module[0],
                     GeisaPlatformDiscovery_DeviceType_TYPE_COMPUTE_CARD,
                     "GEISA Example",
                     "Compute Card A",
                     "CCA-0001",
                     "1.1",
                     "0.9.0");

    message->has_operator = true;
    strncpy(message->operator.operator_name, "Example Utility", sizeof(message->operator.operator_name) - 1);
    strncpy(message->operator.operator_identifier, "utility-001",
            sizeof(message->operator.operator_identifier) - 1);

    message->has_metrology = true;
    strncpy(message->metrology.meter_rating_class, "CL200",
            sizeof(message->metrology.meter_rating_class) - 1);
    strncpy(message->metrology.meter_form, "2S", sizeof(message->metrology.meter_form) - 1);
    message->metrology.phase_count = 1;
    message->metrology.neutral_connected = true;
    message->metrology.nominal_phase_angle_deg = 180.0;
    message->metrology.nominal_frequency_hz = 60;
    message->metrology.nominal_phase_to_phase_voltage_v = 240.0;
    message->metrology.nominal_phase_to_neutral_voltage_v = 120.0;

    message->has_sensor = true;
    message->sensor.sensors_count = 1;
    fill_demo_discovery_sensor(&message->sensor.sensors[0]);

    message->has_network = true;
    message->network.interfaces_count = 3;
    fill_demo_network(&message->network.interfaces[0],
                      "operator-rfmesh-0",
                      GeisaPlatformDiscovery_NetworkClass_NETWORK_CLASS_OPERATOR,
                      GeisaPlatformDiscovery_NetworkOwner_NETWORK_OWNER_OPERATOR,
                      GeisaPlatformDiscovery_NetworkTechnology_NETWORK_TECHNOLOGY_RF_MESH,
                      "Operator RF mesh");
    fill_demo_network(&message->network.interfaces[1],
                      "internet-cellular-0",
                      GeisaPlatformDiscovery_NetworkClass_NETWORK_CLASS_INTERNET,
                      GeisaPlatformDiscovery_NetworkOwner_NETWORK_OWNER_OPERATOR,
                      GeisaPlatformDiscovery_NetworkTechnology_NETWORK_TECHNOLOGY_CELLULAR,
                      "Cellular internet");
    fill_demo_network(&message->network.interfaces[2],
                      "local-wifi-0",
                      GeisaPlatformDiscovery_NetworkClass_NETWORK_CLASS_LOCAL,
                      GeisaPlatformDiscovery_NetworkOwner_NETWORK_OWNER_CONSUMER,
                      GeisaPlatformDiscovery_NetworkTechnology_NETWORK_TECHNOLOGY_WIFI,
                      "Local Wi-Fi");

    message->has_waveform = true;
    message->waveform.streams_count = 1;
    GeisaPlatformDiscovery_Waveform_Instance *stream = &message->waveform.streams[0];
    strncpy(stream->stream_id, "waveform-base", sizeof(stream->stream_id) - 1);
    strncpy(stream->name, "Baseline waveform", sizeof(stream->name) - 1);
    strncpy(stream->description, "Cycle-aligned voltage and current waveform stream",
            sizeof(stream->description) - 1);
    stream->sample_type = GeisaWaveform_SampleType_WAVEFORM_SAMPLE_TYPE_INT16;
    stream->voltage_scale = 0.01;
    stream->current_scale = 0.001;
    stream->voltage_channel_count = 2;
    stream->current_channel_count = 2;
    stream->other_channel_count = 0;
    stream->total_channel_count = 4;
    stream->cycle_aligned = true;
    stream->zero_crossing_aligned = true;
    stream->sample_rate_hz = 15360;
    stream->samples_per_cycle = 256;
    stream->nominal_frequency_hz = 60;
    stream->expected_frame_period_ms = 16;
    stream->voltage_filter_lowpass = 5000;
    stream->current_filter_lowpass = 5000;
}

static inline void print_discovery_status_json(const GeisaStatus *status)
{
    putchar('{');
    geisa_print_json_key("code");
    geisa_print_json_escaped(discovery_status_code_name(status->code));
    if (status->message[0] != '\0')
    {
        fputs(",\"message\":", stdout);
        geisa_print_json_escaped(status->message);
    }
    putchar('}');
}

static inline void print_discovery_module_json(const GeisaPlatformDiscovery_Module *module)
{
    putchar('{');
    geisa_print_json_key("type");
    geisa_print_json_escaped(discovery_device_type_name(module->type));
    fputs(",\"manufacturer\":", stdout);
    geisa_print_json_escaped(module->manufacturer);
    fputs(",\"model\":", stdout);
    geisa_print_json_escaped(module->model);
    fputs(",\"serial-number\":", stdout);
    geisa_print_json_escaped(module->serial_number);
    fputs(",\"hw-revision\":", stdout);
    geisa_print_json_escaped(module->hw_revision);
    fputs(",\"fw-revision\":", stdout);
    geisa_print_json_escaped(module->fw_revision);
    putchar('}');
}

static inline void print_discovery_sensor_descriptor_json(const GeisaSensorDescriptor *sensor)
{
    putchar('{');
    geisa_print_json_key("sensor-id");
    geisa_print_json_escaped(sensor->sensor_id);
    fputs(",\"sensor-type\":", stdout);
    geisa_print_json_escaped(discovery_sensor_type_name(sensor->sensor_type));
    if (sensor->has_name)
    {
        fputs(",\"name\":", stdout);
        geisa_print_json_escaped(sensor->name);
    }
    if (sensor->has_description)
    {
        fputs(",\"description\":", stdout);
        geisa_print_json_escaped(sensor->description);
    }
    fputs(",\"unit\":", stdout);
    geisa_print_json_escaped(sensor->unit);
    fputs(",\"supports-read\":", stdout);
    fputs(sensor->supports_read ? "true" : "false", stdout);
    fputs(",\"supports-publish\":", stdout);
    fputs(sensor->supports_publish ? "true" : "false", stdout);
    if (sensor->has_min_report_period_ms)
    {
        printf(",\"min-report-period-ms\":%llu", (unsigned long long)sensor->min_report_period_ms);
    }
    if (sensor->has_max_report_period_ms)
    {
        printf(",\"max-report-period-ms\":%llu", (unsigned long long)sensor->max_report_period_ms);
    }
    putchar('}');
}

static inline void print_discovery_network_json(const GeisaPlatformDiscovery_Network_Instance *network)
{
    putchar('{');
    geisa_print_json_key("interface-id");
    geisa_print_json_escaped(network->interface_id);
    fputs(",\"network-class\":", stdout);
    geisa_print_json_escaped(discovery_network_class_name(network->network_class));
    fputs(",\"owner\":", stdout);
    geisa_print_json_escaped(discovery_network_owner_name(network->owner));
    fputs(",\"technology\":", stdout);
    geisa_print_json_escaped(discovery_network_technology_name(network->technology));
    fputs(",\"supports-ipv4\":", stdout);
    fputs(network->supports_ipv4 ? "true" : "false", stdout);
    fputs(",\"supports-ipv6\":", stdout);
    fputs(network->supports_ipv6 ? "true" : "false", stdout);
    if (network->has_name)
    {
        fputs(",\"name\":", stdout);
        geisa_print_json_escaped(network->name);
    }
    if (network->has_description)
    {
        fputs(",\"description\":", stdout);
        geisa_print_json_escaped(network->description);
    }
    putchar('}');
}

static inline void print_discovery_waveform_json(const GeisaPlatformDiscovery_Waveform_Instance *stream)
{
    putchar('{');
    geisa_print_json_key("stream-id");
    geisa_print_json_escaped(stream->stream_id);
    fputs(",\"name\":", stdout);
    geisa_print_json_escaped(stream->name);
    fputs(",\"description\":", stdout);
    geisa_print_json_escaped(stream->description);
    fputs(",\"sample-type\":", stdout);
    geisa_print_json_escaped(discovery_waveform_sample_type_name(stream->sample_type));
    printf(",\"voltage-scale\":%.6g", stream->voltage_scale);
    printf(",\"current-scale\":%.6g", stream->current_scale);
    printf(",\"voltage-channel-count\":%u", stream->voltage_channel_count);
    printf(",\"current-channel-count\":%u", stream->current_channel_count);
    printf(",\"other-channel-count\":%u", stream->other_channel_count);
    printf(",\"total-channel-count\":%u", stream->total_channel_count);
    printf(",\"cycle-aligned\":%s", stream->cycle_aligned ? "true" : "false");
    printf(",\"zero-crossing-aligned\":%s",
           stream->zero_crossing_aligned ? "true" : "false");
    printf(",\"sample-rate-hz\":%u", stream->sample_rate_hz);
    printf(",\"samples-per-cycle\":%u", stream->samples_per_cycle);
    printf(",\"nominal-frequency-hz\":%u", stream->nominal_frequency_hz);
    printf(",\"expected-frame-period-ms\":%u", stream->expected_frame_period_ms);
    if (stream->voltage_filter_lowpass != 0)
    {
        printf(",\"voltage-filter-lowpass\":%d", stream->voltage_filter_lowpass);
    }
    if (stream->voltage_filter_highpass != 0)
    {
        printf(",\"voltage-filter-highpass\":%d", stream->voltage_filter_highpass);
    }
    if (stream->current_filter_lowpass != 0)
    {
        printf(",\"current-filter-lowpass\":%d", stream->current_filter_lowpass);
    }
    if (stream->current_filter_highpass != 0)
    {
        printf(",\"current-filter-highpass\":%d", stream->current_filter_highpass);
    }
    putchar('}');
}

static inline int discovery_decode_and_print_request_file(const char *path)
{
    GeisaPlatformDiscovery_Req message = (GeisaPlatformDiscovery_Req)GeisaPlatformDiscovery_Req_init_zero;
    if (!geisa_read_message_file(path, GeisaPlatformDiscovery_Req_fields, &message))
    {
        return EXIT_FAILURE;
    }
    fputs("{\"geisa-platform-discovery-req\":{}}\n", stdout);
    return EXIT_SUCCESS;
}

static inline int discovery_decode_and_print_response_file(const char *path)
{
    GeisaPlatformDiscovery_Rsp message = (GeisaPlatformDiscovery_Rsp)GeisaPlatformDiscovery_Rsp_init_zero;
    if (!geisa_read_message_file(path, GeisaPlatformDiscovery_Rsp_fields, &message))
    {
        return EXIT_FAILURE;
    }

    fputs("{\"geisa-platform-discovery-rsp\":{", stdout);
    if (message.has_status)
    {
        geisa_print_json_key("status");
        print_discovery_status_json(&message.status);
    }
    if (message.has_geisa)
    {
        printf(",\"geisa\":{\"ver-major\":%u,\"ver-minor\":%u,\"ver-rev\":%u,"
               "\"pillar-adm\":%s,\"pillar-api\":%s,\"pillar-lee\":%s,\"pillar-vee\":%s}",
               message.geisa.ver_major,
               message.geisa.ver_minor,
               message.geisa.ver_rev,
               message.geisa.pillar_adm ? "true" : "false",
               message.geisa.pillar_api ? "true" : "false",
               message.geisa.pillar_lee ? "true" : "false",
               message.geisa.pillar_vee ? "true" : "false");
    }
    if (message.has_device)
    {
        fputs(",\"device\":{\"top-module\":", stdout);
        if (message.device.has_top_module)
        {
            print_discovery_module_json(&message.device.top_module);
        }
        else
        {
            fputs("null", stdout);
        }
        fputs(",\"sub-module\":[", stdout);
        for (pb_size_t i = 0; i < message.device.sub_module_count; ++i)
        {
            if (i > 0)
            {
                putchar(',');
            }
            print_discovery_module_json(&message.device.sub_module[i]);
        }
        fputs("]}", stdout);
    }
    if (message.has_operator)
    {
        fputs(",\"operator\":{", stdout);
        geisa_print_json_key("operator-name");
        geisa_print_json_escaped(message.operator.operator_name);
        fputs(",\"operator-identifier\":", stdout);
        geisa_print_json_escaped(message.operator.operator_identifier);
        putchar('}');
    }
    if (message.has_metrology)
    {
        printf(",\"metrology\":{\"meter-rating-class\":");
        geisa_print_json_escaped(message.metrology.meter_rating_class);
        fputs(",\"meter-form\":", stdout);
        geisa_print_json_escaped(message.metrology.meter_form);
        printf(",\"phase-count\":%u,\"neutral-connected\":%s,"
               "\"nominal-frequency-hz\":%u,"
               "\"nominal-phase-to-phase-voltage-v\":%.6g,"
               "\"nominal-phase-to-neutral-voltage-v\":%.6g}",
               message.metrology.phase_count,
               message.metrology.neutral_connected ? "true" : "false",
               message.metrology.nominal_frequency_hz,
               message.metrology.nominal_phase_to_phase_voltage_v,
               message.metrology.nominal_phase_to_neutral_voltage_v);
    }
    if (message.has_sensor)
    {
        fputs(",\"sensor\":{\"sensors\":[", stdout);
        for (pb_size_t i = 0; i < message.sensor.sensors_count; ++i)
        {
            if (i > 0)
            {
                putchar(',');
            }
            print_discovery_sensor_descriptor_json(&message.sensor.sensors[i]);
        }
        fputs("]}", stdout);
    }
    if (message.has_network)
    {
        fputs(",\"network\":{\"interfaces\":[", stdout);
        for (pb_size_t i = 0; i < message.network.interfaces_count; ++i)
        {
            if (i > 0)
            {
                putchar(',');
            }
            print_discovery_network_json(&message.network.interfaces[i]);
        }
        fputs("]}", stdout);
    }
    if (message.has_waveform)
    {
        fputs(",\"waveform\":{\"streams\":[", stdout);
        for (pb_size_t i = 0; i < message.waveform.streams_count; ++i)
        {
            if (i > 0)
            {
                putchar(',');
            }
            print_discovery_waveform_json(&message.waveform.streams[i]);
        }
        fputs("]}", stdout);
    }
    fputs("}}\n", stdout);
    return EXIT_SUCCESS;
}

static inline int discovery_run_demo_walkthrough(void)
{
    puts("Platform Discovery request:");
    if (discovery_decode_and_print_request_file(GEISA_DISCOVERY_REQUEST_PATH) != EXIT_SUCCESS)
    {
        return EXIT_FAILURE;
    }
    puts("Platform Discovery response:");
    return discovery_decode_and_print_response_file(GEISA_DISCOVERY_RESPONSE_PATH);
}

#endif
