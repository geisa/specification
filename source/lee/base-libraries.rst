
..
  Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
  Security Alliance (GEISA), a Series of LF Projects, LLC
  This file is licensed under the Community Specification License 1.0
  available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

Linux Base Libraries
--------------------

To facilitate clean and regular updates and to minimize container sizes, GEISA 
applications are encouraged to take advantage of the libraries provided in the 
base GEISA environment whenever possible.

This does not prevent GEISA applications from including their own libraries
in the event that the GEISA environment does not provide a needed library.

There are two major groups of libraries:

- C Language Runtime Libraries (e.g. gcc, uclibc, musl)
- Other C Libraries

The following list is the current MINIMUM expectation for libraries provided in 
the base GEISA environment.  This list is expected to grow over time as the base 
environment and specification evolves and as applications surface additional 
common needs.  

C Language and Toolchain-provided Runtime Libraries (may vary by implementation):

- libc - Core runtime support
- libgcc - GNU C Compiler Collection (low-level runtime support)
- libstdc++
- libcrypt - Password hashing (MD5, SHA-256)
- libdl - Dynamic loading
- libm - Math library
- libnsl - Network Services Library
- libpthread - POSIX Threads
- libresolv - DNS resolution and name services
- librt - Real-time
- libcap - POSIX capabilities

Other C Libraries (MUST):

- libasyncns - Asynchronous Name Service 
- libatomic - Atomic operations
- libcrypto - OpenSSL (hashing, encryption, digital signatures, random numbers, 
  certs/keys)
- libutil - Users, group,s pseudo-ttys (pty), etc.
- libz - compression
- libmosquitto - MQTT client implementation
- libprotobuf - C++ protobuf implementation

.. note::

  Many MQTT client libraries exist and applications MAY use `libmosquitto` listed 
  above or choose a `different implementation <https://mqtt.org/software/>`_ as 
  needed.

  Similarly, applications MAY use `libprotobuf` if their application is C++, 
  otherwise the application must bring their own implementation of protobufs 
  such as but not limited to one listed in 
  `Third-Party Add-ons for Protocol Buffers <https://github.com/protocolbuffers/protobuf/blob/main/docs/third_party.md>`_.

  The GEISA API is defined at the protocol level and does not mandate a specific 
  application SDK, programming language, or application implementation.

  While GEISA ADM |geisa-adm-baton| makes use of LWM2M for communication, GEISA
  Applications are unaware of this and do not require any LWM2M client libraries 
  or knowledge.

