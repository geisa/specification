Design Principles
-----------------

The GEISA design principles are:

- Interoperability
- Constrained Environment
- Minimal Implementation
- Core Specification w/Extensions
- Security

Each design principle is described in more detail below.


Interoperability
^^^^^^^^^^^^^^^^

The EE
must enable
**source-code interoperable** applications,
isolating them from the underlying hardware implementation.

All GEISA applications must use a single, consistent **GEISA API**
to access resources such as
sensors,
actuators,
persisten storage,
networking,
and more.

All GIESA application must be assureed
that they will have the resources they need
based on their **requirements manifest**.

Constrained Environment
^^^^^^^^^^^^^^^^^^^^^^^

The GEISA EE is a minimal resource environment,
having contraints on CPU, RAM, storage, and networking.

As much as possible.
resources should be reserved for GEISA applications,
not consumed by the underlying operating system.

.. note::

    The original text in the spec was for the overall platform,
    but this is for the GIESA EE. The idea is GEISA EE cares
    about how much available for EE and not total on the platform.

While a GEISA compliant EE may offer more,
the minimal GEISA EE has **TBD of RAM** and **TBD of storage**
reserved for GEISA applications.

Efficiency is critical.
The EE shall provide only those services
which are so widely required
that it would be less effience to *not* provide them.

Minimal Implementation
^^^^^^^^^^^^^^^^^^^^^^^

The less there is, the less there is to maintain
and
the less there is to attack.

Keeping the system up-to-date is challenging,
both for
utilities
and for
vendors.

The GEISA EE favors the minimal implementation.
If there is an option that is not needed, then turn it off.
If there is an unwanted feature, leave it out.

The GEISA should include only what is required.

Core Specification w/Extensions
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

This initial GEISA specification covers the GEISA Core EE,
that is,
the EE that will be provided by all GEISA compliant systems.

In the future, additional extensions to the GEISA specification
will be added as the comunity determines that they are needed.

Security
^^^^^^^^

GEISA security is at the same level of importance as GEISA interpoerability.

At every level, from minimizing the attack space,
to harding of the APIs and all services,
GEISA security is front and center.




