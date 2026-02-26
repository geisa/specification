
..
  Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
  Security Alliance (GEISA), a Series of LF Projects, LLC
  This file is licensed under the Community Specification License 1.0
  available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

Application Isolation
---------------------

Linux Execution Environments are expected to use the containerization
capabilites provided natively within the Linux Kernel via cgroups.  GEISA does
not specify which container engine or management system a platform should use,
but it does specify how app images are provided.  Platform implementations may
use any engine or management system they choose, but they MUST meet the
requirements described in this chapter, they MUST provide a base image, and
they MUST accept application images.

GEISA applications shall be isolated from each other for the following reasons:

- To ensure that one application cannot impact any other application.
- To ensure that one application cannot see the artifacts, resources, data, or 
  state of any other application.

Regardless of the specific application isolation implementation (e.g. LXC 
container, systemd, VEE, etc.), an **authenticated application manifest** shall 
control access to all system resources.  This includes access to network 
interfaces, GEISA API calls, and hardware resources (CPU, RAM, storage).  The
containerization system shall also control application-to-application 
communications, if any.

While platforms may use any container mechanism they choose, for clarity of
intent, this portion of the GEISA specification uses ``lxc`` for various 
examples.  


Isolation Requirements
======================

General Requirements
^^^^^^^^^^^^^^^^^^^^

GEISA LEE requires that:

- Applications SHALL run in independent processes
- Applications SHALL not run as root
- Application access permissions SHALL be deny by default
- Application-to-application communication SHALL be denied by default 
- Applications SHALL not be able to access other applications memory or other 
  resources
- Applications SHALL not know about other applications unless explicitly informed
- Applications SHALL not have access to the underlying platform file-system 

GEISA LEE requires the application isolation mechanism to ensure that:

- Applications cannot impact the performance of the system
- Applications cannot impact the stability of the system
- Applications cannot impact the performance of other applications
- Applications cannot impact the stability of other applications
- Applications cannot create denial-of-service situations
- System and non-GEISA components may have priority, but cannot consume all 
  resources to the point of GEISA Applications starvation
- Operators MAY choose to oversubscribe CPU resources but not RAM and storage resources
- If oversubscribed, available resources must be fairly distributed between Apps

Resource Management
^^^^^^^^^^^^^^^^^^^

The platform SHALL control every aspect of a GEISA applications access to
system resources, including:

- The number of CPUs allocated (cgroups ``limits.cpu``)
- The percentage of CPU allowed (cgroups ``limits.cpu.allowance``) 
- The priority of the application (cgroups ``limits.cpu.priority``)
- The maximum RAM (cgroups ``limits.memory``)
- Persistent Storage 
- Non-Persistent Storage 

.. note::

  Storage limits can be enforced in a variety of ways, depending on the 
  underlying chosen technologies in place.  For example, LXC supports the ``root size`` 
  option.  ``tmpfs`` supports size limits.  Quotas may be used.  It is up to 
  the platform provider to choose the appropriate technology to enforce limits.

Networking Control
^^^^^^^^^^^^^^^^^^

By default, applications are not given any network access.  Applications which 
need relatively simple communication may use the application messaging API that 
is part of the GEISA API.  Apps that require direct access to a network 
interface may be granted specific permission.

- Which network interfaces (none by default)
- Instantaneous Bandwidth
- Average network volume over a period (e.g. 1 hour, 24 hours)
- Direct versus Indirect Access
- Allowed destination addresses
- Allowed destination ports

API Control
^^^^^^^^^^^

Access to the GEISA API is controlled via MQTT permissions.  The platform will
assign a userid and password (provided to the application in its unique
``/etc/geisa/config.binpb`` file) that the application will use to connect to
the message bus.  That user will be restricted according to the permissions in
the application manifest.  Please see :doc:`/api` and :doc:`/adm/manifests` for
additional details.

Container Image Requirements
============================

Container images in GEISA are composed by combining a base image (provided by 
the platform), an application configuration image or folder (provided by the 
platform), an application image (provided by the application creator), a 
non-persistent tmpfs (provided by the platform) and a persistent file system 
(provided by the platform).  This combination is mounted as the root file 
system for the application container.  Details of the contents of these file 
systems can be found in :doc:`/lee/file-layout`

As an example of how this might be composed, consider a platform using ``lxc``
as its container engine.  The platform has a shared base image at
``/plaform/base/geisa-base-1.0.0.sqfs``.  It receives an application manifest 
for a given application, including the image's digital signature.  Upon 
receiving the application image through the application download process, the 
platform stores the application image in ``/platform/apps/geisa-app-1/geisa-app-1-1.0.1.sqfs``,
and then validates the image against the digital signature contained in the
manifest.  

Based on the permissions specified in the manifest, the platform creates the
necessary MQTT user for the application, granting that user access to the
necessary APIs allowed in the manifest.  It stores this the application's user
credentials in ``/platform/apps/geisa-app-1/config/etc/geisa/config.binpb`` or
in a ``/etc/geisa/config.pb`` file in an appropriate image file, stored in the
``/platform/apps/geisa-app-1`` directory.

To launch the application the platform will mount each of the required file
system images.  For a system running ``lxc``, the platform might create a
``geisa-app-1`` folder under ``/var/lib/lxc``.  Under that folder, it could 
create folders for ``base``, ``config``, ``app``, ``persistent``, ``work``, and
``rootfs``.  For ``base``, ``config`` and ``app``, the platform could mount the
respective file system images::

  mount -t squashfs /platform/base/geisa-base-1.0.0.squashfs /var/lxc/geisa-app-1/base
  mount -t squashfs /platform/apps/geisa-app-1-1.0.1.squashfs /var/lxc/geisa-app-1/app
  mount -t squashfs /platform/apps/geisa-app-1-config.squashfs /var/lxc/geisa-app-1/config

Once these images are mounted, the images can be merged using the overlayfs::

  mount -t overlay overlay \
  -olowerdir=/var/lxc/geisa-app-1/base:/var/lxc/geisa-app-1/app:/var/lxc/geisa-app-1/config \
  -oupperdir=/var/lxc/geisa-app-1/persistent \
  -oworkdir=/var/lxc/geisa-app-1/work /var/lxc/geisa-app-1/rootfs

The platform could then mount a ``tmpfs`` instance specific to ``geisa-app-1`` 
at ``/var/lxc/geisa-app-1/rootfs/tmp``.  Launching the application could be 
done via ``lxc-start geisa-app-1`` or ``lxc-execute geisa-app-1`` depending on 
the design.

|geisa-pyramid|
