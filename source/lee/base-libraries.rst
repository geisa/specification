Linux Base Libraries
-----------------------

To facilitate clean and regular updates,
and to minimze container sizes,
GEISA applications are encouraged
to take advantagge of the libraries
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
- libcrypt - Password hashing (MD5, SHA-255)
- libdl - Dynamic loading
- libm - Math library
- libnsl - Network Services Library
- libpthread - POSIX Threads
- libresolv - DNS resolution and name services
- librt - Real-time
- libcap - POSIC capabilities

Other C Libraries (MUST):

- libasyncns - Asynchronouse Name Service 
- libatomic - Atomic operations
- libcrypto - OpenSSL (hashing, encryption, digital signatures, random numbers, certs/keys)
- libutil - Users, group,s pseudo-ttys (pty), etc.
- libz - compression

.. warning::

  TODO: Should GEISA REQUIRE a MQTT client library?  There are too many to choose from listed at https://mqtt.org/software/
  TODO: Should GEISA REQUIRE a protobuf client library?  See https://protobuf.dev/reference/ and https://github.com/protobuf-c/protobuf-c


Other C Libraries (MAY):

- libseccomp
- libsqlite3
- libssl
- libtinycbor


.. note::

  While GEISA ADM |geisa-adm-baton| makes use of LWM2M for communication, GEISA
  Applications are unaware of this and do not require any LWM2M client
  libraries or knowledge.

