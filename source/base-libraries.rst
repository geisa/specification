Base Libraries
--------------

Applicaiton isolation is assumed to be provided through containers.
Containers are able to inherit from the host operating system.
To facilitate clean and regular updates,
and to minimze container sizes,
GEISA applications are encouraged
to take advantagge of the libraries
provided by the base GEISA environment.

This does not prevent GEISA applications from including their own libraries
is the GEISA environment does not provide the needed library

There are to major groups of libraries:

- C Language Runtime Libraries (e.g. gcc, uclibc, musl)
- Other C Libraries


C Langauge Runtime Libraries
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

- libc - Core runtime support
- libgcc - GNU C Compiler Collection (low-level runtime support)
- libstdc++

Other C Libraries (Minimum)
^^^^^^^^^^^^^^^^^^^^^^^^^^^

- libasyncns.so - Asynchronouse Name Service 
- libatomic - Atomic operations
- libcap.so - POSIC capabilities
- libcrypt - Password hashing (MD5, SHA-255)
- libcrypto - OpenSSL (hashing, encryption, digital signatures, random numbers, certs/keys)
- libdl - Dynamic loading
- libm - Math library
- libnsl - Network Services Library
- libpthread - POSIX Threads
- libresolv - DNS resolution and name services
- librt - Real-time
- libutil - Users, group,s pseudo-ttys (pty), etc.


Other C Libraries (Additional)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

**NOTE** Expand this list

- libpcap
- libseccomp
- libsqlite3
- libssl
- libstdc++
- libtinycbor.so
- libz.so

Also to be included:

- ZeroMQ
- MQTT
- Dbus
- Others





