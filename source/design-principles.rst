
..
  Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
  Security Alliance (GEISA), a Series of LF Projects, LLC
  This file is licensed under the Community Specification License 1.0
  available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

Design Principles
-----------------

The |GEISA| specification is written for constrained resource embedded 
industrial devices. A constrained embedded industrial device may consist of a 
simple microcontroller (e.g. Cortex-M class core) or leverage a more complex 
microprocessor (e.g. Cortex-A class core).

These devices are expected to operate in the field without manual intervention 
for prolonged periods of time; often two decades or longer.  While these 
devices have network interfaces and sensors (see :doc:`hardware`) they do not 
typically have on-board (graphical) user interfaces. 

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

As discussed in the :doc:`introduction`, GEISA defines four types of
interoperability:

LEE
   Linux Execution Environment
   **LEE** interoperability |geisa-lee-tux| provides a consistent operating 
   system environment built using Linux.
   The Linux Execution Environment provides a well-known open development 
   environment including many standard libraries and makes it easy to integrate 
   additional technology.  
   
   Applications written for the GEISA LEE will run on any LEE-conformant device.
   
**VEE**
   Virtual Execution Environment 
   
   VEE interoperability |geisa-vee-cloud| provides a consistent virtual 
   execution environment.  The Virtual Execution Environment provides a 
   fully-isolated managed code environment which supports the widely-used C/C++ 
   and Java |reg| language specifications.  

   Applications written for the GEISA VEE will run on any VEE-conformant device.

**ADM** 
  Application and Device Management
  ADM interoperability |geisa-adm-baton| enables conformant devices to 
  interoperate with conformant management systems.

**APIs**
   Application Programming Interface
   API interoperability |geisa-api-gear| provides consistent access to 
   resources such as sensors, actuators, networking, and more. 


Note that GEISA does not currently provide a tool-chain or a base-platform 
implementation.
[#]_ 

This release of the GEISA specification defines **source-code** interoperability 
for the LEE, VEE, & API, and network interoperability for ADM.  

Source written for the GEISA LEE should be compilable without modification,
and without needing conditional compilation or platform specific directives.
Similarly, source written for the GEISA VEE should be compilable for the target 
virtual execution environment with needing conditional compilation or 
platform-specific directives.

.. Warning::

  The LEE and VEE are two different environments. The LEE is specifically a 
  Linux environment.

  The VEE is agnostic to the underlying OS/RTOS, providing source-level 
  interoperability through supporting well-known languages.

  It is possible that a platform may support both LEE and VEE. In this case, 
  an application developer may need to determine the proper methods that 
  allows it to run on one or both execution environments when properly packaged. 
  Users may need to select applications according to the provided EE. 
  
See :doc:`system-architecture` for further discussion.

.. index::
   single: Constrained Environment

Constrained Environment
^^^^^^^^^^^^^^^^^^^^^^^

The GEISA EE is a minimal resource environment, having constraints on CPU, RAM, 
storage, and networking. See :doc:`hardware` for specific minimums that the 
GEISA specification assumes.

As much as possible, resources should be reserved for GEISA applications,
instead of being consumed by the underlying operating system.
While a GEISA conformant EE may offer more, it MUST reserve the following 
MINIMUM resources available for GEISA applications:

- For GEISA LEE |geisa-lee-tux|:

  - **256MB of RAM**
  - **256MB of persistent storage**

- For GEISA VEE |geisa-vee-cloud|:

  - **1 MB of RAM**
  - **8 MB of Flash memory** for code storage and execution
  - **8 MB of persistent storage**

Additionally, although hardware performance will vary considerably between 
platforms, GEISA EE SHOULD provide a minimum of **50% of the CPU** for GEISA 
applications |geisa-ee-globe|.

Efficiency is critical. The GEISA EE shall provide only those services which 
are so widely required that it would be less efficient to *not* provide them.

.. index::
   single: Minimal Implementation

Minimal Implementation
^^^^^^^^^^^^^^^^^^^^^^

Keeping systems up-to-date is challenging, both for utilities and for vendors.
The GEISA EE favors the minimal implementation; that is, the less there is, 
the less there is to maintain and the less there is to attack.

If there is an option that is not needed, then turn it off.  If there is an 
unwanted or un-necessary feature, leave it out.  GEISA should include only what 
is required.

.. index::
   single: Extensions

Core Specification with Extensions
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

In addition to the four keys aspects of interoperability (ADM, API, LEE, and 
VEE), future extensions may be added to to the GEISA specification may be added 
as the community determines the need.

Future extensions may define new areas of interoperability conformance beyond 
ADM, API, LEE, and VEE, or they may enable new capabilities that are only 
needed by selected devices types or in specific markets.  Extensions will allow 
GEISA to retain its `Minimal Implementation`_ design principle, while still 
allowing it to grow to meet the needs of platform vendors, application 
developers, and system operators.

Security
^^^^^^^^

Security is equally as important as interoperability within the GEISA 
specification.  All protocols included in the GEISA specification support 
robust security.  Security details and requirements are provided throughout 
the specification.  At every level, from minimizing the attack space, to 
hardening of the APIs and all services, GEISA security is foundational.

|geisa-pyramid|

.. [#] GEISA may provide a toolchain and base implementation in the future if 
  there is interest and support from the GEISA community.

