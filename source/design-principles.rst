Design Principles
-----------------

The |GEISA| specification is written for constrained embedded industrial devices.  
These devices are expected to operate in the field without manual intervention for two decades
or more.  While these devices have network interfaces and sensors (see :doc:`hardware`)
they do not typically have user interfaces.  This device target informs the overall
design principles of the specification.

GEISA design principles include:

- Interoperability
- Constrained Environment
- Minimal Implementation
- Core Specification with Extensions
- Security

Each design principle is described in more detail below.

Interoperability
^^^^^^^^^^^^^^^^

As dicussed in the :doc:`introduction`, GEISA defines three types of interoperability: ADM, API, & EE. 
GEISA does not currently provide a tool-chain or a base-platform implementation. [#]_ 
This release of the GEISA specification defines **source-code** interoperability for the
API and EE, and network interoperability for ADM.  
Source written for the GEISA EE and API should be compilable without modification,
and without needing conditional compilation or platform specific directives.
**EE** interoperability |geisa-ee-globe| provides a consistent operating system environment 
and isolates applications from the underlying hardware implementation,
allowing applications written to the GEISA specification
to be run on platforms from different vendors.  
**API** interoperability |geisa-api-gear| provides consistent 
access to resources such as sensors, actuators, networking, and more.
**ADM** interoperability |geisa-adm-baton| enables conformant devices 
to interoperate with conformant management systems.

See :doc:`system-architecture` for further discussion.

.. index::
   single: Constrained Environment

Constrained Environment
^^^^^^^^^^^^^^^^^^^^^^^

The GEISA EE is a minimal resource environment,
having contraints on CPU, RAM, storage, and networking. 
See :doc:`hardware` for specific minimums that the GEISA specication 
assumes.

As much as possible, resources should be reserved for GEISA applications,
not consumed by the underlying operating system.
While a GEISA compliant EE may offer more,
the minimal GEISA EE MUST provide **256MB of RAM** and **256MB of persistent storage**
reserved for GEISA applications. |geisa-ee-globe|

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

The initial GEISA specification defines three keys aspects of interoperability: ADM, API, and EE.
In the future, extensions to the GEISA specification
will be added as the comunity determines that they are needed.
Extensions may define new areas of interoperability conformance beyond ADM, API, and EE,
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

