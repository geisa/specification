
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

  - a filesystem containing base binaries, libraries, the application and other 
    files and directories not specifically listed below.  It MUST be 
    either mounted read-only or the application lack write permission to all 
    items within except as explained below

- /proc

  - a Linux `procfs` filesystem populated by the kernel for the specific 
    application's container

- /dev

  - MAY be part of the `/` filesystem or separate mount such as `tmpfs` or 
    `devtmpfs` types
  - MUST contain at a minimum: `console` `full` `log` `null` `random` `stderr` 
    `stdin` `stdout` `urandom` and `zero`
  - `/dev/log` MUST be backed by the platform to filter and direct logs into 
    the GEISA ADM or another system logging mechanism if the implementation is 
    not ADM conformant

- /sys

  - a Linux `sysfs` filesystem populated by the kernel for the specific 
    application's container

- /tmp

  - A separate filesystem or directory within / that is writable by the 
    Application process
  - MUST be limited in size as described in the Application's Deployment Manifest
  - MAY be backed by `tmpfs` or a persistent filesystem
  - Applications MUST handle stale files and cleanup contents it created to 
    remain under limits
  - Platform MAY clean, purge, or delete contents while the Application is NOT 
    running

- /home/geisa

  - A separate filesystem or directory within / that is writable by the 
    Application process
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
- sys
- tmp
- var

and optionally:

- sbin
- usr/sbin
- usr/bin
- usr/lib
- run (if present, SHOULD be non-persistent and share `/tmp` size limits)

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
``overlayfs`` to reduce flash and ram waste.

Immutable images such as the base utilities and libraries common to all 
Applications and Application-specific binaries, libraries, and other files 
provided by the Application vendor SHOULD be ``overlayfs`` ``lower`` layers, 
while the ``upper`` MAY be used for generated configuration files, any unix 
domain sockets and/or the non-persistent storage depending on the design 
choices of the LEE.

An efficient read-only file system, like ``squashfs`` for the base and 
application images SHOULD be used, but this is not required.

Overlayfs allows an Application to provide their own or even replace a base
library, fixed data, and executables as needed without having to construct a
copy of the lower layer data in flash or ram.

When an Application is upgraded, its overlayfs MUST be re-constructed and any
non-persistent files deleted while the persistant files (in `/home/geisa`)
MUST be preserved.

When an Application is stopped and restarted (or device rebooted), the 
platform MAY re-construct the filesystem including deletion of any 
non-persistent files while the persistant files (in `/home/geisa`)
MUST be preserved.


Example Filesystem Construction
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

As an example of how this might be composed, consider a platform using ``lxc``
as its container engine.  ``/platform`` is persistant storage for the GEISA 
platform and a shared base image is at ``/platform/base/geisa-base-1.0.0.sqfs``.

The Platform receives an application manifest for a given application, 
including the image's digital signature.  Upon receiving the application image 
through the application download process, the platform stores the 
application image in ``/platform/apps/geisa-app-1/app-1.0.1.sqfs``, and then 
validates the image against the digital signature contained in the manifest.  

Based on the permissions specified in the manifest, the platform creates the
necessary MQTT user for the application, granting that user access to the
necessary APIs allowed in the manifest.  It generates a random login token for 
the application and stores the username and token as the application's user
credentials in ``/platform/apps/geisa-app-1/config/etc/geisa/mqtt.conf``.

To launch the application the platform will mount each of the required file
system images.  This example LEE implementation uses a separate writable 
``/tmp`` filesystem mount with the rootfs mounted read-only.

For a system running ``lxc``, the platform might create a
``geisa-app-1`` directory under ``/var/lib/lxc``.  Then sub-directories for the 
various ``overlayfs`` layers and a resulting ``rootfs`` directory.

The application persistant storage is in ``/platform/apps/geisa-app-1/persist`` 
and this example LEE uses a quota to limit application usage as specified in the 
deployment manifest.  Other mechanisms could be used to limit a persistent 
volume such as a file-backed loopback device.

Example geisa-app-1 with 50MiB persistent and 4MiB non-persistant volumes ::


  mkdir -p /platform/apps/geisa-app-1/config/etc/geisa
  geisa_create_mqtt_conf geisa-app-1 /platform/apps/geisa-app-1/config/etc/geisa/mqtt.conf

  mkdir -p /platform/apps/geisa-app-1/persist
  chown geisa-app-1:nogroup /platform/apps/geisa-app-1/persist
  chmod 0700 /platform/apps/geisa-app-1/persist
  setquota -u geisa-app-1 50M 50M 0 0 /platform

  mkdir -p /var/lxc/geisa-app-1/{base,app,config,upper,work,rootfs}
  mount -t squashfs /platform/base/geisa-base-1.0.0.sqfs /var/lxc/geisa-app-1/base
  mount -t squashfs -o nosuid,nodev /platform/apps/geisa-app-1/app-1.0.1.sqfs /var/lxc/geisa-app-1/app
  mount --bind /platform/apps/geisa-app-1/config /var/lxc/geisa-app-1/config

  mount -t overlay -oro overlay \
  -olowerdir=/var/lxc/geisa-app-1/base:/var/lxc/geisa-app-1/app:/var/lxc/geisa-app-1/config \
  -oupperdir=/var/lxc/geisa-app-1/upper \
  -oworkdir=/var/lxc/geisa-app-1/work \
  /var/lxc/geisa-app-1/rootfs

  mount --bind /platform/apps/geisa-app-1/persist /var/lxc/geisa-app-1/rootfs/home/geisa
  mount -t tmpfs -osize=4M,mode=1777 tmpfs /var/lxc/geisa-app-1/rootfs/tmp
  mount -t sysfs sysfs /var/lxc/geisa-app-1/rootfs/sys
  mount -t proc proc /var/lxc/geisa-app-1/rootfs/proc


.. note::

  GEISA LEE SHOULD have their `/` filesystem mounted read-only
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

