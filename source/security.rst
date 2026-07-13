
..
  Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
  Security Alliance (GEISA), a Series of LF Projects, LLC
  This file is licensed under the Community Specification License 1.0
  available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

Security
--------
Security is fundamental to the GEISA specification, so much so that it is
included in the name itself: Grid Edge Interoperability and **Security**
Alliance. This specification was developed with prevailing security and privacy 
design principles in mind, such as NIST 800-53, CCPA and NERC CIP standards, and enables 
implementers to incorporate security controls appropriate to their operational contexts
and needs.

Security in GEISA exists to enable trusted interoperability across independently
developed hardware, software, and operational domains without requiring a single
vendor-controlled platform.  It is designed to allow applications from different 
vendors to co-exist, to allow utilities to trust in portable secure workloads 
and/or edge applications, and allows for interoperability without shared
implementations, while allowing the Utility or Operator to dictate their specific
policies and standards.

This chapter is broadly divided into sets of sections.  The first section covers the
threat model, responsibilities, and expectations.  These constitute the
security philosophy and approach of GEISA.  Specifically this includes:

* :doc:`security/responsibilities`
* :doc:`security/threatmodel`
* :doc:`security/conformance`
* :doc:`security/expectations`

The second section covers practical aspects of security:

* :doc:`security/signatures`
* :doc:`security/certificates`
* :doc:`security/API`
* :doc:`security/network`

.. Note::

  GEISA security is focused on application-level transactions.  GEISA does not
  address network security directly.  GEISA does require a variety of LwM2M
  objects that facilitate management of different network substrates (see
  :doc:`/adm/lwm2m`), which may allow for network security management; however,
  network security implementation details are outside of the scope of GEISA.
  Implementations MUST support the native security mechanisms for the network
  technologies they use (e.g. EAP-TLS for Wi-SUN, eSIMs/SIMs for Cellular, WPA
  for Wi-Fi, etc.).  Implementations MUST NOT rely exclusively on application
  security.  That said, this specification focuses on application security
  mechanisms, leaving implementation details regarding network technologies for
  other specifications and standards.

.. toctree::
  :hidden:

  security/responsibilities.rst
  security/threatmodel.rst
  security/conformance.rst
  security/expectations.rst
  security/signatures.rst
  security/certificates.rst
  security/network.rst
  security/API.rst

|geisa-pyramid|

