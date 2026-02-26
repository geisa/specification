
..
  Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
  Security Alliance (GEISA), a Series of LF Projects, LLC
  This file is licensed under the Community Specification License 1.0
  available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

Base Filesystem
---------------

A GEISA LEE |geisa-lee-tux| container provides the following minimum filesystem
within each Application Container environment.  The container filesystem
contents may be derived from the platform host filesystem or separately
constructed specifically for GEISA container environments.


Filesystem Mounts
^^^^^^^^^^^^^^^^^

Each GEISA Application MUST be provisioned in its own container environment
separate from other Applications.  As such, application-specific names, IDs,
and other identifiers do not need to be encoded in filesystem paths within the
Application environment.

The GEISA platform implementation MUST provide the following virtual filesystem 
mounts within the container environment:

- /

  - a read-only filesystem containing base binaries, libraries, the application 
    and other files and directories not specifically listed below

- /proc

  - a Linux `procfs` filesystem populated by the kernel for the specific 
    application's container

- /dev

  - MAY be part of the `/` filesystem or separate mount such as `tmpfs` or 
    `devtmpfs` types
  - MUST contain at a minimum: `console` `full` `log` `null` `random` `stderr` 
    `stdin` `stdout` `urandom` and `zero`

- /sys

  - a Linux `sysfs` filesystem populated by the kernel for the specific 
    application's container

- /tmp

  - A filesystem that is writable by the Application process
  - MUST be limited in size as described in the Application's Deployment Manifest
  - MAY be backed by `tmpfs` or a persistent filesystem
  - Applications MUST handle stale files and cleanup contents it created to 
    remain under limits
  - Platform MAY clean, purge, or delete contents while the Application is NOT 
    running

- /home/geisa

  - A separate filesystem that is writable by the Application process
  - MUST be limited in size as described in the Application's Deployment Manifest
  - Applications MUST handle stale files and cleanup contents it created to 
    remain under limits
  - MUST be persistent across application restarts and device reboots
  - Platform SHALL be responsible for metadata integrity (journaling, startup 
    checks, etc...)
  - Application SHALL be tolerant to data corruption and missing files

Utilities and Environment
^^^^^^^^^^^^^^^^^^^^^^^^^

A base set of executables typically found in an embedded or minimal container 
environment MUST be present.

GEISA does not require a specific implementation, however 
`Busybox <https://busybox.net/>`_ is recommended with the default build options.

A skeleton filesystem MUST be populated including typical paths for binaries and 
libraries:

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

A skeleton filesystem MUST be populated with typical files including at a 
minimum:

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

The following environment variables MUST be set at a minimum when invoking 
Applications processes:

- SHELL
- HOME
- USER
- PATH

GEISA Components
^^^^^^^^^^^^^^^^

The Application needs to determine information about the environment it is
running on and as such can expect certain GEISA specific configuration to be
present.  As explained in :doc:`/api/architecture` and :doc:`/api/discovery`
these files are placed in `/etc/geisa` within the container environment.


Base Libraries
^^^^^^^^^^^^^^

A set of base libraries SHALL be provided in the base filesystem.
See :doc:`base-libraries` for further details.


Construction of the Filesystem
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Each Application container filesystem has different content based on the specific 
Application.

GEISA implementations SHOULD construct a container filesystem using Linux
``overlayfs`` to reduce flash and ram waste containing:

- one or more ``lower`` directories with the base utilities and libraries 
  common to all Applications
- a ``lower`` directory with the Application-specific binaries, libraries, and 
  other files provided by the Application vendor
- a ``lower`` containing generated files including the configuration files in
  ``/etc/geisa``. *Note: ``/etc/geisa`` could also placed by the platform in the
  upper filesystem instead, though this would make it mutable.* 
- an ``upper`` containing generated files including the configuration files in
  ``/etc/geisa`` as well as any unix domain sockets for communication.

Using three separate lower directories allows for a separate base image, shared
across applications, a configuration folder, generated by the platform, and an
application image signed by the application vendor, all being combined into a
single file system for the application.

It is recommended to use an efficient read-only file system, like ``squashfs``
for the base, but this is not required.

Overlayfs allows an Application to provide their own or even replace a base
library, fixed data, and executables as needed without having to construct a
copy of the lower layer data in flash or ram.

When an Application is upgraded, its overlayfs MUST be re-constructed and any
non-persistent files (in `/tmp` or elsewhere) be deleted while the persistant
files (in `/home/geisa`) MUST be preserved.

.. note::

  GEISA EE SHOULD have their `/` filesystem mounted read-only
  in the kernel to follow the principle of least privilege. This prevents
  Applications from modifying or adding files in unexpected places and forces
  deterministic Application behavior on each startup.

  If an implementation chooses to mount `/` read-write, it MUST enforce file 
  and directory permissions appropriately as well as limit the growable size of 
  the filesystem to the same limits as the Application's Deployment Manifest 
  specifies for non-persistent storage.  In this case a seperate `/tmp` mount 
  is unnecessary and any changes outside of the persistent `/home/geisa` are 
  non-persistent.

|geisa-pyramid|

