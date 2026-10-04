
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
applications are encouraged to take advantage of libraries provided by the base
GEISA environment whenever possible.

GEISA defines a baseline set of runtime and application libraries provided by
the platform for use within the GEISA execution environment. Applications MAY
include additional libraries that are not part of this baseline.

C Language and Toolchain-provided Runtime Libraries
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The following runtime libraries are part of the GEISA baseline. The specific
implementation may vary by platform and toolchain.

- libc - Core runtime support
- libgcc - GNU C Compiler Collection (low-level runtime support)
- libstdc++
- libatomic - Atomic operations
- libcrypt - Password hashing
- libdl - Dynamic loading
- libm - Math library
- libpthread - POSIX Threads
- libresolv - DNS resolution and name services
- librt - Real-time
- libcap - POSIX capabilities

Common Application Libraries
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The following common application libraries, or function-compatible alternate
implementations as described below, MUST be provided by the platform and
available to applications within the GEISA execution environment:

- libcrypto - OpenSSL (hashing, encryption, digital signatures, random numbers,
  certs/keys)
- libnsl - Network Services Library
- libz - Compression
- libmosquitto - MQTT client implementation

A platform implementation MAY provide an alternate library implementation in
place of one of the named libraries above, provided that the alternate
implementation is function-compatible with the named library.

Optional Application Libraries
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Platform implementations MAY provide additional commonly used libraries in the
base GEISA environment. When provided as part of that environment, these
libraries MUST be available to GEISA applications within their execution
environment.

Examples include:

- libasyncns - Asynchronous Name Service
- libutil - Users, groups, pseudo-ttys (pty), etc.
- libprotobuf - C++ protobuf implementation

Applications MAY include additional libraries or alternate implementations when
needed.

.. note::

   Applications MAY use a platform-provided `libprotobuf` when suitable, or
   another protobuf implementation such as one listed in
   `Third-Party Add-ons for Protocol Buffers
   <https://github.com/protocolbuffers/protobuf/blob/main/docs/third_party.md>`_.

   The GEISA API is defined at the protocol level and does not mandate a
   specific application SDK, programming language, or application
   implementation.

   While GEISA ADM |geisa-adm-baton| makes use of LwM2M for communication,
   GEISA Applications are unaware of this and do not require any LwM2M client
   libraries or knowledge.
