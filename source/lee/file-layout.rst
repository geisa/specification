Base Filesystem
---------------

A GEISA LEE |geisa-lee-tux| container provides the following minimum filesystem within each Application Container environment.  The container filesystem contents may be derived from the platform host filesystem or separately constructed specifically for GEISA container environments.


Filesystem Mounts
^^^^^^^^^^^^^^^^^

Each GEISA Application MUST be provisioned in its own container environment separate from other Applications.  As such, application-specific names, IDs, and other identifiers do not need to be encoded in filesystem paths within the Application environment.

The GEISA platform implementation MUST provide the following virtual filesystem mounts:

- /

  - a read-only filesystem containing base binaries, libraries, the application and other files and directories not specifically listed below

- /proc

  - a Linux `procfs` filesystem populated by the kernel for the specific application's container

- /dev

  - MAY be part of the `/` filesystem or separate mount such as `tmpfs` or `devtmpfs` types
  - MUST contain at a minimum: `console` `full` `log` `null` `random` `stderr` `stdin` `stdout` `urandom` and `zero`

- /sys

  - a Linux `sysfs` filesystem populated by the kernel for the specific application's container

- /tmp

  - A filesystem that is writable by the Application process
  - MUST be limited in size as described in the Application's Deployment Manifest
  - MAY be backed by `tmpfs` or a persistent filesystem
  - Applications MUST handle stale files and cleanup contents it created to remain under limits
  - Platform MAY clean, purge, or delete contents while the Application is NOT running

- /home/geisa

  - A separate filesystem that is writable by the Application process
  - MUST be limited in size as described in the Application's Deployment Manifest
  - Applications MUST handle stale files and cleanup contents it created to remain under limits
  - MUST be persistent across application restarts and device reboots
  - Platform SHALL be responsible for metadata integrity (journaling, startup checks, etc...)
  - Application SHALL be tolerant to data corruption and missing files

Utilities and Environment
^^^^^^^^^^^^^^^^^^^^^^^^^

A base set of executables typically found in an embedded or minimal container environment MUST be present.

GEISA does not require a specific implementation, however `Busybox <https://busybox.net/>`_ is recommended with default build options.

A skeleton filesystem MUST be populated including typical paths for binaries and libraries:

- bin
- dev
- etc
- home
- lib
- proc
- sbin
- sys
- tmp
- usr/bin
- usr/lib
- var

A skeleton filesystem MUST be populated with typical files including at a minimum:

- /etc/group
- /etc/hostname
- /etc/hosts (including a `localhost` entry)
- /etc/passwd

and if provided by libc implementation:

- /etc/resolv.conf
- /etc/nsswitch.conf
- /etc/locale.conf
- /etc/services
- /etc/protocols
- /etc/shells
- /etc/timezone

The following environment variables MUST be set at a minimum when invoking Applications processes:

- SHELL
- HOME
- USER
- PATH

Base Libraries
^^^^^^^^^^^^^^

A set of base libraries SHALL be provided in the base filesystem.  See :doc:`base-libraries` for further details.


Construction of the Filesystem
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Each Application container filesystem has different content based on the specific Application.

GEISA recommends implementations construct a container filesystem using Linux `overlayfs` to reduce flash and ram waste containing:

- one or more `lower` directories with the base utilities and libraries common to all Applications
- a `lower` directory with the Application-specific binaries, libraries, and other files provided by the Application vendor
- a `lower` or `upper` containing generated files including the Application configuration and :doc:`/api/enumeration`.

|geisa-pyramid|
