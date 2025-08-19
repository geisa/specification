Linux Base Libraries
-----------------------

To facilitate clean and regular updates,
and to minimize container sizes,
GEISA applications are encouraged
to take advantage of the libraries
provided in the base GEISA environment.

This does not prevent GEISA applications from including their own libraries
if the GEISA environment does not provide the needed library.

There are to major groups of libraries:

- C Language Runtime Libraries (e.g. gcc, uclibc, musl)
- Other C Libraries


C Language and Toolchain provided Runtime Libraries (may vary by implementation):

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
- libcrypto - OpenSSL (hashing, encryption, digital signatures, random numbers, certs/keys)
- libutil - Users, group,s pseudo-ttys (pty), etc.
- libz - compression
- libmosquitto - MQTT client implementation
- libprotobuf - C++ protobuf implementation

.. note::

  Many MQTT client libraries exist and applications MAY use `libmosquitto` above or choose a `different implementation <https://mqtt.org/software/>`_ as needed.

  Similarly, applications MAY use `libprotobuf` if their application is C++, otherwise the application must bring their own implementation of protobufs such as one listed in `Third-Party Add-ons for Protocol Buffers <https://github.com/protocolbuffers/protobuf/blob/main/docs/third_party.md>`_.

  GEISA API is defined at the protocol level and does not mandate a specific application SDK, programming language, or application implementation.

  While GEISA ADM |geisa-adm-baton| makes use of LWM2M for communication, GEISA
  Applications are unaware of this and do not require any LWM2M client
  libraries or knowledge.

