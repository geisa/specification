//-----------------------------------------------------------------------------
// Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
// Security Alliance (GEISA), a Series of LF Projects, LLC
//
// Licensed under the Apache License, Version 2.0. See LICENSE.
//-----------------------------------------------------------------------------
//
// Shared helper utilities for GEISA C++ examples.
//
// These functions are example support functions only. They are not part of the
// GEISA APIs and are just used for the example code base.
//-----------------------------------------------------------------------------

#ifndef GEISA_EXAMPLE_HELPERS_H
#define GEISA_EXAMPLE_HELPERS_H

#include <cstdlib>
#include <fstream>
#include <initializer_list>
#include <iostream>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

#include "geisa-status.pb.h"

///////////////////////////////////////////////////////////////////////////////
// JSON helpers
///////////////////////////////////////////////////////////////////////////////

// Escapes a string for JSON-like output in examples..
inline void print_json_escaped(const std::string &value)
{
    std::cout << '"';
    for (const char ch : value)
    {
        switch (ch)
        {
        case '\\':
            std::cout << "\\\\";
            break;
        case '"':
            std::cout << "\\\"";
            break;
        case '\n':
            std::cout << "\\n";
            break;
        case '\r':
            std::cout << "\\r";
            break;
        case '\t':
            std::cout << "\\t";
            break;
        default:
            std::cout << ch;
            break;
        }
    }
    std::cout << '"';
}

// Prints a JSON-like object key prefix in examples
inline void print_json_key(const char *key)
{
    std::cout << '"' << key << "\":";
}

// Emits a comma separator between JSON-like fields in examples.
inline void print_json_comma_if_needed(bool *first_field)
{
    if (!*first_field)
    {
        std::cout << ',';
    }
    *first_field = false;
}

///////////////////////////////////////////////////////////////////////////////
// File helpers
///////////////////////////////////////////////////////////////////////////////

// Reads binary bytes from disk for example protobuf decode flows
inline bool read_binary_file(const char *path, std::string *contents)
{
    std::ifstream input(path, std::ios::binary);
    if (!input)
    {
        std::cerr << "Failed to open input file: " << path << '\n';
        return false;
    }

    contents->assign(std::istreambuf_iterator<char>(input),
                     std::istreambuf_iterator<char>());
    return true;
}

// Writes raw binary bytes to disk for example protobuf fixture/demo outputs
inline bool write_binary_file(const char *path, const std::string &bytes)
{
    std::ofstream output(path, std::ios::binary);
    if (!output)
    {
        std::cerr << "Failed to open output file: " << path << '\n';
        return false;
    }

    output.write(bytes.data(), static_cast<std::streamsize>(bytes.size()));
    if (!output.good())
    {
        std::cerr << "Failed to write output file: " << path << '\n';
        return false;
    }

    return true;
}

// Serializes a protobuf message then writes it to disk
template <typename MessageT>
inline bool serialize_protobuf_to_file(const char *path,
                                       const MessageT &message,
                                       const char *message_name)
{
    std::string bytes;
    if (!message.SerializeToString(&bytes))
    {
        std::cerr << "failed to serialize " << message_name << '\n';
        return false;
    }

    return write_binary_file(path, bytes);
}

///////////////////////////////////////////////////////////////////////////////
// Demo mode helpers
///////////////////////////////////////////////////////////////////////////////

// Resolves a sibling demo reader binary path with fallback to /tmp
inline std::string resolve_demo_reader_path(const std::string &argv0,
                                            const char *sibling_binary,
                                            const char *fallback_path)
{
    const std::size_t slash = argv0.find_last_of('/');
    if (slash != std::string::npos)
    {
        const std::string sibling =
            argv0.substr(0, slash + 1) + sibling_binary;
        if (::access(sibling.c_str(), X_OK) == 0)
        {
            return sibling;
        }
    }

    return fallback_path;
}

// Runs a reader subprocess command during --demo mode and returns its exit status
inline int run_demo_subprocess(const std::string &command)
{
    const int rc = std::system(command.c_str());
    if (rc == -1)
    {
        std::cerr << "Failed to launch reader subprocess\n";
        return EXIT_FAILURE;
    }

    if (WIFEXITED(rc))
    {
        return WEXITSTATUS(rc);
    }

    if (WIFSIGNALED(rc))
    {
        std::cerr << "Reader subprocess terminated by signal "
                  << WTERMSIG(rc) << '\n';
        return EXIT_FAILURE;
    }

    std::cerr << "Reader subprocess failed\n";
    return EXIT_FAILURE;
}

///////////////////////////////////////////////////////////////////////////////
// GEISA status helpers
///////////////////////////////////////////////////////////////////////////////

// Prints a GeisaStatus object in JSON-like form for example response outputs
inline void print_geisa_status_json(const GeisaStatus &status)
{
    std::cout << "{";
    print_json_key("code");
    print_json_escaped(GeisaStatusCode_Name(status.code()));

    if (!status.message().empty())
    {
        std::cout << ",\"message\":";
        print_json_escaped(status.message());
    }

    if (!status.details().empty())
    {
        std::cout << ",\"details\":";
        print_json_escaped(status.details());
    }

    std::cout << "}";
}

// CLI/demo text helpers

// Prints standardized usage lines for examples and returns EX_USAGE.
inline int print_example_usage_and_return(
    std::initializer_list<std::string> lines)
{
    for (const std::string &line : lines)
    {
        std::cerr << line << '\n';
    }
    return EX_USAGE;
}

// Prints standardized informational/demo lines for example walkthrough output.
inline void print_example_info_lines(
    std::initializer_list<std::string> lines)
{
    for (const std::string &line : lines)
    {
        std::cout << line << '\n';
    }
}

#endif  // GEISA_EXAMPLE_HELPERS_H
