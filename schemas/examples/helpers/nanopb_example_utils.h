//-----------------------------------------------------------------------------
// Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
// Security Alliance (GEISA), a Series of LF Projects, LLC
//
// Licensed under the Apache License, Version 2.0. See LICENSE.
//-----------------------------------------------------------------------------
//
// Shared helper utilities for GEISA embedded C protobuf examples.
//
// These functions are example support code only. They are not part of the
// GEISA APIs and are intended only to keep the example readers and writers
// focused on message construction and decode flow.
//-----------------------------------------------------------------------------

#ifndef GEISA_NANOPB_EXAMPLE_UTILS_H
#define GEISA_NANOPB_EXAMPLE_UTILS_H

#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "pb_decode.h"
#include "pb_encode.h"

static inline bool geisa_example_ensure_directory(const char *path)
{
    if (mkdir(path, 0777) == 0 || errno == EEXIST)
    {
        return true;
    }

    fprintf(stderr, "failed to create %s: %s\n", path, strerror(errno));
    return false;
}

static inline bool geisa_write_message_file(const char *path,
                                            const pb_msgdesc_t *fields,
                                            const void *message)
{
    FILE *file = fopen(path, "wb");
    if (file == NULL)
    {
        fprintf(stderr, "failed to open %s: %s\n", path, strerror(errno));
        return false;
    }

    pb_ostream_t size_stream = PB_OSTREAM_SIZING;
    if (!pb_encode(&size_stream, fields, message))
    {
        fprintf(stderr, "failed to size %s: %s\n", path, PB_GET_ERROR(&size_stream));
        fclose(file);
        return false;
    }

    const size_t encoded_size = size_stream.bytes_written;
    uint8_t *buffer = (uint8_t *)malloc(encoded_size == 0 ? 1 : encoded_size);
    if (buffer == NULL)
    {
        fprintf(stderr, "failed to allocate encode buffer for %s\n", path);
        fclose(file);
        return false;
    }

    pb_ostream_t stream = pb_ostream_from_buffer(buffer, encoded_size);
    bool ok = pb_encode(&stream, fields, message);
    if (!ok)
    {
        fprintf(stderr, "failed to encode %s: %s\n", path, PB_GET_ERROR(&stream));
        free(buffer);
        fclose(file);
        return false;
    }

    if (fwrite(buffer, 1, stream.bytes_written, file) != stream.bytes_written)
    {
        fprintf(stderr, "failed to write %s: %s\n", path, strerror(errno));
        free(buffer);
        fclose(file);
        return false;
    }

    free(buffer);
    fclose(file);
    return true;
}

static inline bool geisa_read_message_file(const char *path,
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

static inline void geisa_print_json_escaped(const char *value)
{
    putchar('"');
    for (const unsigned char *p = (const unsigned char *)value; *p != '\0'; ++p)
    {
        switch (*p)
        {
        case '\\':
            fputs("\\\\", stdout);
            break;
        case '"':
            fputs("\\\"", stdout);
            break;
        case '\n':
            fputs("\\n", stdout);
            break;
        case '\r':
            fputs("\\r", stdout);
            break;
        case '\t':
            fputs("\\t", stdout);
            break;
        default:
            putchar((int)*p);
            break;
        }
    }
    putchar('"');
}

static inline void geisa_print_json_key(const char *key)
{
    putchar('"');
    fputs(key, stdout);
    fputs("\":", stdout);
}

static inline void geisa_print_json_bytes_hex(const pb_bytes_array_t *bytes)
{
    static const char *hex = "0123456789abcdef";
    putchar('"');
    for (size_t i = 0; i < bytes->size; ++i)
    {
        const uint8_t byte = bytes->bytes[i];
        putchar(hex[(byte >> 4U) & 0x0FU]);
        putchar(hex[byte & 0x0FU]);
    }
    putchar('"');
}

#endif
