
..
  Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
  Security Alliance (GEISA), a Series of LF Projects, LLC
  This file is licensed under the Community Specification License 1.0
  available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

Security Capability Expectations
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
To address the risks identified in this threat model, conformant implementations
must realize these capabilities within the COE, which serves as the enforcement
layer for application behavior, resource governance, and authorized interaction
with connected systems while ensuring that operators retain control of the 
ability to set and enforce policy, protect system integrity, and maintain 
trust relationships across defined trust boundaries.

The GEISA specification defines the security outcomes that must be achievable,
but does not prescribe specific technologies or implementation approaches.

Identity and Authentication
~~~~~~~~~~~~~~~~~~~~~~~~~~~
Implementations shall support verifiable identity for:

* Devices or platforms (e.g., meters, NICs, or other edge hardware),
  hereafter referred to as the *Device/Platform Provider* where such
  identity is supplied by the hardware or platform manufacturer.
* Applications and associated software artifacts produced by an
  *Application Publisher* (the entity responsible for creating and
  signing an application or workload).
* External systems interacting across trust boundaries.

These identities establish provenance, accountability, and authorization
context for software deployment and operation within the COE.

Such identities may represent organizational provenance used to establish trust
in software origin and authorization for deployment within the COE.

Identity mechanisms must protect associated credential material from
unauthorized extraction, duplication, or misuse and support secure lifecycle
management of those credentials.

Authorization and Policy Enforcement
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The COE must enable operator-defined policy controlling application execution,
resource access, and permitted interactions across networks and systems.

Integrity Protection
~~~~~~~~~~~~~~~~~~~~
Implementations must protect software, configuration, and operational data from
unauthorized modification.

Isolation of Workloads
~~~~~~~~~~~~~~~~~~~~~~
The COE shall provide isolation sufficient to prevent privilege escalation or
cross-application interference.

Secure Lifecycle Management
~~~~~~~~~~~~~~~~~~~~~~~~~~~
Implementations must support secure deployment, update, validation, and removal
of software throughout the device lifecycle.

Protection of Data
~~~~~~~~~~~~~~~~~~
Implementations shall protect sensitive data from unauthorized disclosure or
manipulation when stored or transmitted across trust boundaries.

Auditability and Visibility
~~~~~~~~~~~~~~~~~~~~~~~~~~~
The COE shall enable logging and monitoring sufficient to detect unauthorized
activity and support operational accountability.

Resilience and Availability
~~~~~~~~~~~~~~~~~~~~~~~~~~~
Security mechanisms shall support continued safe operation and policy
enforcement under degraded connectivity conditions.

These capabilities are intended to enable interoperable yet independently
governed deployments across diverse utility environments.

|geisa-pyramid|

