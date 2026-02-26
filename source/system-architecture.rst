
..
  Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
  Security Alliance (GEISA), a Series of LF Projects, LLC
  This file is licensed under the Community Specification License 1.0
  available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

System Architecture
------------------------------

General Architecture
=========================

As discussed in :doc:`introduction`, the |GEISA| specification describes 
four types of interoperability: ADM, API, LEE, and VEE.  
These types of interoperability live in a general system context, which is 
shown below in
:numref:`geisa-architecture`.

.. _geisa-architecture:
.. figure:: /images/geisa-architecture.*

   GEISA Architecture

GEISA is focused on interoperability and security.  Where it is possible to 
maintain interoperability without specifying aspects of the implementation, 
details are left to the implementer.

|geisa-adm-hdr|

In a full implementation of the GEISA architecture, there is a GEISA Edge 
Management System (EMS) that implements the ADM interface as described in 
:doc:`adm`.  The EMS implements a network protocol based interface and is able 
to use that protocol to interact with ADM interface conformant GEISA platform 
implementations.  Internal details of the EMS are beyond the scope of this 
specification.  GEISA simply requires that a conformant EMS expose the required
functions to the system operator in some meaningful way, and that it implements 
the specified network protocol and transactions in response to user commands.  
An EMS could provide a GUI, a command line interface, or an API and still be 
considered to be conformant.

Interacting with the GEISA EMS is one or more platform implementations.  An 
ADM-conformant platform interface will be able to communicate with the GEISA 
EMS using the ADM protocol and transactions.  In :numref:`geisa-architecture` 
above, the ADM conformant implementation is shown as the GEISA Edge Management 
Agent.  Implementation details are beyond the scope of this specification.
Implementers may provide a standalone EMA within their platform, or integrate 
EMA functions within other elements of their platform as they see fit.

GEISA ADM elements |geisa-adm-baton| are shown in red in 
:numref:`geisa-architecture` above.

|geisa-pyramid|

The system operator is able to use the GEISA EMS to deploy and activate GEISA 
edge applications to GEISA platform implementations.  A fully conformant GEISA 
platform implementation will provide both a GEISA-conformant EE / execution 
environment and a GEISA-conformant API / application programming interface.

|geisa-ee-hdr|

GEISA defines two different execution environments:

* **Linux Execution Environment (LEE)** |geisa-lee-tux|

* **Virtual Execution Environment (VEE)** |geisa-vee-cloud|

Platforms may offer one or both of these execution environments (EE).

While the GEISA API should be accessible from both EEs, there is no
expectation that code written for one EE will operate on the other
without being ported. 

.. note::

  It is possible, though not planned at this time, that GEISA may support 
  additional execution environments in the future.

|geisa-lee-hdr|

LEE GEISA applications are provided as container images, as detailed in
:doc:`lee/app-isolation`.  An LEE conformant GEISA implementation is able to
mount a container image and grant that container the rights the system operator
permitted the application in the deployment manifest.  The container runtime
used by the platform implementation is out of scope, but conformant
implementations MUST be able to enforce the permissions and controls the GEISA
specification requires.

An LEE-conformant GEISA implementation must provide a set of
:doc:`lee/base-libraries` and :doc:`lee/core-services` to containers running in
the environment.  The goal of GEISA LEE conformance is to provide a consistent
and efficient execution environment to edge applications running on the 
platform.  Platform implementers may use any GNU/Linux variant they see fit,
provided it meets the requirements noted in :doc:`lee/operating-system`;
however, for security and efficiency reasons, implementers SHOULD NOT use full
general purpose GNU/Linux operating system distributions.  Implementers SHOULD 
use distributions specifically built for embedded environments and should 
excise any unnecessary system components and/or services.

GEISA LEE elements |geisa-lee-tux| are shown in blue in :numref:`geisa-architecture` 
above.

|geisa-pyramid|

|geisa-vee-hdr|

VEE GEISA applications are provided as loadable VEE archives, as detailed in 
:doc:`virtual-environment`.  A VEE conformant GEISA implementation is able to 
launch the archive in a VEE as necessary and grant the application the rights 
which the system operator permitted to the application in the application 
deployment manifest.  

The VEE used by the platform implementation is out of scope of this 
specification, but conformant implementations MUST be able to enforce the 
permissions and controls the GEISA specification requires, and support the APIs 
required by the GEISA specification.

Note that GEISA VEE elements |geisa-vee-cloud| are not currently shown in 
:numref:`geisa-architecture` above.

|geisa-pyramid|

|geisa-api-hdr|

General operating system functions such as file system access, math libraries, 
and network socket APIs are provided by the GEISA LEE or VEE discussed above.  
The GEISA API facilitates access to platform capabilities that are not serviced 
by the LEE's or VEE's respective APIs.  The GEISA API is described in detail 
in :doc:`api`.  The GEISA API will provide access to metrological data, sensor 
data, billing data, actuators, and, for GEISA ADM conformant implementations, 
message exchange with the EMS.

GEISA API conformant platform implementations MUST provide an implementation of 
the message bus described in :doc:`api` and MUST respond appropriately to all 
required API transactions.  Connecting the GEISA API implementation to the 
underlying platform is out of scope for the GEISA specification.  

Platform implementers may use any supporting implementation they see fit; 
however, implementers SHOULD consider the security implications of the 
implementation and ensure they are robust against both unintended abuse and 
deliberate attacks.

GEISA API elements |geisa-api-gear| are shown in green in 
:numref:`geisa-architecture` above.

|geisa-pyramid|


Application Isolation
=====================

.. note::

  Application Isolation is required of all GEISA execution environments.  This 
  section discusses what execution environments must achieve.  Requirements 
  specific to a given EE are covered in the respective EE chapters.

GEISA applications shall be isolated from each other and the core
platform for the following reasons:

- To ensure that one application cannot impact another application.

- To ensure that one application cannot see the artifacts, resources,
  data, or state of another application.

- To ensure that applications cannot impact the platform or workloads
  outside of the GEISA implementation.

Because the GEISA specification defines multiple execution environments, the
Application Isolation Implementation (AII) is expected to vary between
execution environments and may vary from one platform to another within an
execution environment.  Regardless of AII (e.g. LXC container, systemd, VEE,
etc.), an **authenticated application manifest** shall control access to
platform resources and the GEISA API.  Additionally, it shall enforce the
principle of least-privilege.

The application isolation implementation of GEISA conformant platforms shall
ensure that:

- Applications run in independent processes
- Applications run with least privilege
- Application access permissions are deny by default
- Application-to-application communication are denied by default 
- Applications cannot access other application's memory or other resources
- Applications do not know about other applications unless explicitly informed
- Applications cannot access the platform's local file-system
- Applications cannot impact the performance of the platform
- Applications cannot impact the stability of the platform
- Applications cannot impact the performance of other applications
- Applications cannot impact the stability of other applications
- Applications cannot create denial-of-service situations
- Resources are fairly distributed when oversubscribed


Application Manifest
^^^^^^^^^^^^^^^^^^^^

The same application manifest is used across all AII.  Because of this, all AII
SHALL support the same controls, in support of the settings defined in the
application manifest, even if their underlying implementation is substantially
different.  Application manifests are documented in :doc:`adm/manifests`.


Networking Control
^^^^^^^^^^^^^^^^^^

The AII must control access to the network interface.  By default, applications 
are not granted any network access.  The application manifest may indicate that 
a given application is allowed to natively access the local network interface.

The AII shall control:

- Whether direct network access is allowed.

- Which network interfaces an application may access (none by default),
  including HAN/LAN and FAN/WAN interfaces.

- The allowed instantaneous bandwidth an application may use.

- The allowed average network volume an application may use over a
  defined period (e.g., 1 hour or 24 hours).

- Allowed destination addresses.

- Allowed destination ports.

API Control
^^^^^^^^^^^

These permissions relate to controlling application access to the GEISA API
provided by the platform.  See :doc:`api` for details.  Each defined API shall
have its own set of permissions.


Container Resource Management
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Container resource limits shall include the following:

- CPU limit (% of CPU)
- Memory Limit (in 1KiB units)
- Persistent Storage Limit (in 1KiB units)
- Non-Persistent Storage Limit (in 1KiB units)

.. note::

  An Application or Deployment manifest can be modified and re-deployed during
  an Application upgrade or administrative change.  Changes to the resource 
  requirements SHOULD not require an Application restart, but an EE 
  implementation MAY stop, modify, and restart an Application if necessary.

  All resource requirements can be changed including the persistent storage 
  limit.  If that limit is increased, an implementation MUST honor that change 
  and provide the application with a larger volume or limit without loss of 
  persistent data.  If that limit is reduced, an implementation SHOULD attempt 
  to honor that change and reduce the volume or limit, however if the Application 
  is using more than the new limit an alarm or exception SHOULD be raised to 
  the EMS and the action MUST be aborted, leaving the Application running with 
  the previous limit.

|geisa-pyramid|

