
..
  Copyright 2025, Contributors to the Grid Edge Interoperability & Security Alliance (GEISA) a Series of LF Projects, LLC  
  This file is licensed under the Community Specification License 1.0 available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

Design Principles
-----------------

The |GEISA| specification is written for constrained embedded industrial devices.
A constrained embedded industrial device can be made of a simple microcontroller (Cortex-M class core) 
or leverage a complex microprocessor (Cortex-A class core).
These devices are expected to operate in the field without manual intervention for two decades
or more.  While these devices have network interfaces and sensors (see :doc:`hardware`)
they do not typically have on-board (graphical) user interfaces. 
This device target informs the overall design principles of the specification.

GEISA design principles include:

- Interoperability
- Constrained Environment
- Minimal Implementation
- Core Specification with Extensions
- Security

Each design principle is described in more detail below.

Interoperability
^^^^^^^^^^^^^^^^

As dicussed in the :doc:`introduction`, GEISA defines four types of interoperability: ADM, API, LEE & VEE. 
GEISA does not currently provide a tool-chain or a base-platform implementation. [#]_ 
This release of the GEISA specification defines **source-code** interoperability for the
LEE & API, **binary-code** interoperability for the VEE & API, and network interoperability for ADM.  
Source written for the GEISA LEE should be compilable without modification,
and without needing conditional compilation or platform specific directives.
Managed binary code for the GEISA VEE does not rely on any transformation (such as compilation), 
and it shall be linkable at runtime without needing compilation. 

**LEE** interoperability |geisa-lee-tux| provides a consistent operating system environment 
built using Linux.  
The Linux Execution Environment provides a well-known open development environment including
many standard libraries and makes it easy to integrate additional technology.
Applications written for the GEISA LEE will run on any LEE conformant device.

**VEE** interoperability |geisa-vee-cloud| provides a consistent virtual execution environment.
The Virtual Execution Environment provides a fully-isolated managed code environment 
which supports the widely-used C/C++ and Java |reg| language specifications.
Applications written for the GEISA VEE will run on any VEE conformant device.

**API** interoperability |geisa-api-gear| provides consistent 
access to resources such as sensors, actuators, networking, and more.

**ADM** interoperability |geisa-adm-baton| enables conformant devices 
to interoperate with conformant management systems.

.. Warning::

  The LEE and VEE are two different environments: the LEE is source-based for Linux only,
  while the the VEE is agnostic to OS/RTOS and binary-based for a multi-threaded environment. 
  It is possible that a platform would support both LEE and VEE. 
  An application developer may need to select for an app the manner (package) 
  that allows it to run on one or both execution environments when properly packaged. 
  Users may need to select applications according to the provided EE. 
  
See :doc:`system-architecture` for further discussion.

.. index::
   single: Constrained Environment

Constrained Environment
^^^^^^^^^^^^^^^^^^^^^^^

The GEISA EE is a minimal resource environment,
having constraints on CPU, RAM, storage, and networking. 
See :doc:`hardware` for specific minimums that the GEISA specification 
assumes.

As much as possible, resources should be reserved for GEISA applications,
not consumed by the underlying operating system.
While a GEISA-compliant EE may offer more, it MUST reserve the following 
resources for GEISA applications:

- For GEISA LEE |geisa-lee-tux|:

  - **256MB of RAM**
  - **256MB of persistent storage**

- For GEISA VEE |geisa-vee-cloud|:

  - **1 MB of RAM**
  - **8 MB of Flash memory** for code storage and execution
  - **8 MB of persistent storage**

Additionally, although hardware performance will vary considerably between platforms, 
GEISA EE SHOULD provide **50% of the CPU** for GEISA applications |geisa-ee-globe|.

Efficiency is critical. The GEISA EE shall provide only those services
which are so widely required that it would be less efficient to *not* provide them.

.. index::
   single: Minimal Implementation

Minimal Implementation
^^^^^^^^^^^^^^^^^^^^^^^

The less there is, the less there is to maintain
and the less there is to attack.
Keeping systems up-to-date is challenging,
both for utilities and for vendors.
The GEISA EE favors the minimal implementation.
If there is an option that is not needed, then turn it off.
If there is an unwanted feature, leave it out.
The GEISA should include only what is required.

.. index::
   single: Extensions

Core Specification with Extensions
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The initial GEISA specification defines four keys aspects of interoperability: ADM, API, LEE, and VEE.
In the future, extensions to the GEISA specification
will be added as the comunity determines that they are needed.
Extensions may define new areas of interoperability conformance beyond ADM, API, LEE, and VEE,
or they may enable new capabilities that are only needed by selected devices types or in
particular markets.  Extensions will allow GEISA to retain its `Minimal Implementation`_
design principle, while still allowing it to grow to meet the needs of platform vendors,
application developers, and system operators.

Security
^^^^^^^^

Security is equally as important as interoperability within the GEISA specification.
All protocols included in the GEISA specification support robust security.
Security details and requirements are provided throughout the specification.  
At every level, from minimizing the attack space,
to harding of the APIs and all services,
GEISA security is foundational.

|geisa-pyramid|

.. [#] GEISA may provide a toolchain and base implementation in the future if there is interest and support from the GEISA community.

