
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

While platforms may use any container mechanism they choose, for clarity of
intent, this portion of the GEISA specification uses ``lxc`` for various 
examples.  


Isolation Requirements
======================

General Requirements
^^^^^^^^^^^^^^^^^^^^

GEISA applications SHALL be isolated from each other as described 
in :doc:`/system-architecture`.

Resource Management
^^^^^^^^^^^^^^^^^^^

The platform SHALL control every aspect of a GEISA applications access to
system resources, including:

- The number of CPUs allocated (e.g. cgroups ``limits.cpu``)
- The percentage of CPU allowed (e.g. cgroups ``limits.cpu.allowance``) 
- The priority of the application (e.g. cgroups ``limits.cpu.priority``)
- The maximum RAM (e.g. cgroups ``limits.memory``)
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

GEISA applications MAY be granted limited network access as described 
in :doc:`/system-architecture`.

If granted permissions in the operator manifest, the platform SHALL provide the 
application with the ability to use standard socket-based IP connectivity from 
within the containerized environment via the Linux kernel.  The platform SHALL 
be responsible for enforcing the access control list and volume limits described 
in the application's manifest.

GEISA does not require a specific mechanism for providing network interface 
access to the containerized environment, however typical options would be a 
veth pair or passthrough interface using iptables/nftables for policy 
enforcement.

API Control
^^^^^^^^^^^

Access to the GEISA API is controlled via MQTT permissions.  The platform will
assign a userid and token (provided to the application in its unique
``/etc/geisa/mqtt.conf`` file) that the application will use to connect to
the message bus.  That user will be restricted according to the permissions in
the application manifest.  Please see :doc:`/api` and :doc:`/adm/manifests` for
additional details.

Container Image Requirements
============================

Container images in GEISA are composed by combining a base image (provided by 
the platform), an application configuration image or directory (provided by the 
platform), an application image (provided by the application vendor), a 
non-persistent temporary filesystem or directory (provided by the platform) and 
a persistent file system or directory (provided by the platform).  This 
combination is mounted as the root file system for the application container.  
Details of the contents and an example of this file systems can be found 
in :doc:`/lee/file-layout`

|geisa-pyramid|
