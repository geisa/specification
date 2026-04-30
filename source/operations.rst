..
  Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
  Security Alliance (GEISA), a Series of LF Projects, LLC
  This file is licensed under the Community Specification License 1.0
  available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

Operations
----------

This chapter provides a high-level operational view of how GEISA roles,
systems, artifacts, and interoperability areas relate to each other end
to end.

It is intended to help readers understand the overall system context
before moving into the more detailed materials covered elsewhere such as
:doc:`system-architecture`, :doc:`adm`, :doc:`linux-environment`,
:doc:`virtual-environment`, :doc:`api`, and :doc:`security`.

.. note::

   This chapter is explanatory in nature. Detailed protocols, APIs, payloads,
   lifecycle, and security requirements are defined in the relevant
   chapters of this specification.

Purpose and Scope
^^^^^^^^^^^^^^^^^

GEISA is intended to support end-to-end interoperability across the
lifecycle of utility edge platforms, edge applications, and other
upstream systems. In practice, the overall system can be difficult to
understand when viewed only through one protocol, one component, or
one's own specific organizational responsibilities.

This chapter reframes the system in terms of GEISA roles and major
operational interactions. It is intended to clarify how the management
plane, execution environments, application interfaces, trust decisions,
and operational reporting concerns all fit together at a system level.

The operational view in this chapter complements the interoperability
goals described in :doc:`introduction` and the general architectural
material in :doc:`system-architecture`.

Roles and Authorities
^^^^^^^^^^^^^^^^^^^^^

GEISA describes operational interactions in terms of roles rather than
broad organization categories, as a single organization may perform one
or more roles depending on the workflow being discussed and specific
implementations.

For example, a device manufacturer may also provide managed services and,
in a particular deployment, may act in the role of Platform Provider,
EMS Provider, or System Operator. In GEISA, responsibilities and
decision authority are tied to the role being performed in the relevant
interaction, regardless of the type of organization with specific role
responsibilities. However, there is one notable callout: the utility is
expected to often be the one driving the underlying operational
decisions, even in cases where another organization is performing the
day-to-day operational duties on their behalf.

The principal roles used in this operational view are:

- :term:`System Operator`

  The role responsible for approving, configuring, authorizing,
  deploying, and operating GEISA-managed devices and applications  
  within a specific operating environment in accordance with agreed-on
  policies.  The Operator effectively runs the day-to-day systems, although
  they may be beholden to another organization such as the Utility to 
  dictate actual policies to be followed.

- :term:`Platform Provider`

  The role responsible for supplying the platform hardware, platform
  software, and associated platform trust material where applicable.
  This may be a single provider or a Hardware Provider may be separate.
  In terms of GEISA, Platform Provider generally is noting the provider
  of the system software that is GEISA-conformant.

  - :term:`Application Publisher` / :term:`Application Vendor`

  The role responsible for producing and signing an application artifact
  and supplying its vendor manifest and associated publisher trust
  material.


- :term:`Application Certifier`

  An optional (as of this version of the specification) role that may
  independently assess, test, or countersign application artifacts as
  validated and safe for deployment purposes. Depending on the
  applicable program or market, this assessment may emphasize either a
  "does no harm" model focused on behavioral and policy safety, a more
  detailed "does what is promised" model focused on functional or
  analytic claims, or both.

- :term:`Edge Application`

  A workload running within a GEISA execution environment and using
  GEISA platform services and the GEISA :doc:`api`.

- ADM / Application and Device Management

  :term:`ADM` is the GEISA pillar for :doc:`adm`. It
  spans the capabilities required for application ingestion, operator
  approval for deployment, deployment, activation, deactivation,
  updates, and broader lifecycle management of both the platform and
  the applications running on it. These capabilities may be realized by
  a single EMS that leverages LwM2M, or by multiple cooperating
  components, provided the required GEISA ADM behaviors and
  transactions are satisfied. On the edge device, this capability set
  includes the EMA and related edge-side management functions.

- :term:`EMS`

  The management system role responsible for exposing GEISA-conformant
  management behavior to the operator and communicating with conformant
  platforms as described in :doc:`adm`.

- :term:`EMA`

  The platform-side management function that implements the required ADM
  support on a GEISA platform on edge devices.

The following terms are also important to this chapter:

- :term:`ADM` and :term:`API` are GEISA interoperability areas and
  components covered in detail in :doc:`adm` and :doc:`api`.

- :term:`LEE` and :term:`VEE` are GEISA execution environments covered
  in detail in :doc:`linux-environment` and :doc:`virtual-environment`.

- :term:`Platform Implementation` describes the realized combination of
  hardware and software that provides one or more GEISA-conformant
  interfaces.

When policy, approval, deployment scope, resource allocation, or trust
authorization is in question, the System Operator has final authority
for the target deployment environment.

End-to-End Operational Context
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

At a high level, the System Operator uses an :term:`EMS` to manage
conformant platforms, authorize application deployment, and obtain
operational visibility into the deployed fleet.

Within the platform, :term:`ADM` provides the management behavior needed
for device onboarding, lifecycle control, and application deployment as
described in :doc:`adm`. The platform may provide one or both of the
GEISA execution environments, :term:`LEE` and :term:`VEE`, as described
in :doc:`linux-environment` and :doc:`virtual-environment`.
Applications use the GEISA :term:`API` to interact with platform
capabilities and platform-provided data as described in :doc:`api`.

The Application Publisher supplies the application artifact and vendor
manifest. The System Operator determines whether that application is
approved for use in the relevant environment, such as test, limited
deployment, or production deployment. The EMS then carries out the
authorized deployment and lifecycle actions on the target devices.

The Platform Provider supplies the platform implementation and
associated device or platform trust material where applicable. The same
provider may also supply additional services or systems, but those
services are distinct from the role boundaries used within this
specification.

This figure is intentionally high-level. It is provided to help readers
understand how the principal GEISA roles, systems, and interoperability
areas relate end to end.

.. figure:: operations/end-to-end-lwm2m-only.*
   :alt: LwM2M only version
   :align: center

   High-level GEISA operational context showing how principal roles,
   platform-side and off-device management functions, execution
   environments, and utility or enterprise interaction points relate
   end to end (2 diagrams, second is a continuation from System Operator
   through to to the Edge Device)

.. figure:: operations/app-lifecycle-A.*
   :alt: High-level GEISA application lifecycle reference flow
   :align: center

   High-Level End to End Sequence Diagram 1 of 2

.. figure:: operations/app-lifecycle-B.*
   :alt: High-level GEISA application lifecycle reference flow
   :align: center

   High-Level End to End Sequence Diagram 2 of 2


Operational Capability
^^^^^^^^^^^^^^^^^^^^^^

This chapter is explanatory and does not add or alter specific
requirements detailed elsewhere in this specification. In particular,
:doc:`adm` continues to define required interoperable ADM behaviors and
transactions.

Operational capability includes management, lifecycle, deployment,
visibility, reporting, and integration concerns across platform and
operator workflows.

Device Onboarding and Management Overview
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

GEISA device onboarding establishes the management relationship between
a conformant platform and a conformant EMS. In operational terms, this
includes device provisioning, network attachment, bootstrap or initial
trust establishment, registration, and subsequent lifecycle management.

.. figure:: operations/reference-device-onboarding.*
   :alt: High-level GEISA operational context
   :align: center

   Reference device onboarding and management establishment flow
   retained for comparison and discussion.

Additional detailed device onboarding workflows and requirements may be added 
in a future revision of the specification.

Application Approval and Deployment Overview
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

GEISA application deployment begins with application sourcing and review,
continues through operator authorization and deployment preparation, and
ends with transfer and installation on target devices.

This specification distinguishes between the vendor manifest supplied by
the Application Publisher and the effective deployment manifest approved
by the System Operator. Operationally, this means publisher-provided
identity, compatibility, defaults, and requested resources are inputs to
the deployment decision, but the final approved deployment parameters
remain under operator control.

Additional detailed application approval and deployment workflows and 
requirements may be added in a future revision of the specification.

Application Activation and Runtime Visibility
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

After installation, GEISA applications are activated under operator
control and execute within the platform's selected execution
environment. During runtime, the platform and EMS provide visibility
into application and platform state, including activation state,
execution state, status, and other operationally relevant data.

Additional detailed application activation and state information  
requirements may be added in a future revision of the specification.

Operational Reporting and Visibility
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

GEISA deployments require operational visibility into both the managed
platform and the applications running on it. For purposes of this
operational discussion, it is useful to distinguish between four broad
reporting classes:

- Application alerts

  Near-real-time when feasible. These are application-originated alerts
  or condition notifications for which delayed awareness may materially
  reduce operator usefulness.

- Application data

  Data generated by applications for their own systemic use and
  consumption. This data is not necessarily as time-critical as
  application alerts and may be pushed on a periodic schedule or pulled
  periodically in a manner agreed to by the utility, relevant platform
  provider, and application publisher.

- Platform-originated behavioral events

  Near-real-time when urgent, otherwise routine or batched as
  appropriate. These are platform-originated observations or actions
  relating to application or platform behavior, such as repeated restart
  failure, policy violations, throttling, disablement, denied access
  attempts, unexpected outbound messaging, signature or hash mismatch
  events, or severe and persistent threshold violations.

- Routine operational reporting

  Slower and/or batched as appropriate. This includes lower-urgency
  operational data intended primarily for visibility, trending, support,
  audits, planning, license or usage review, and similar operational
  purposes.

This model preserves an important distinction between what an
application reports, what the platform reports about the application,
and what the platform or operator may do as a result of that behavior
and data. Application-originated condition notifications or data messages
may flow through GEISA messaging and off-device communication paths, but
those messages are distinct from the broader operational reporting model
for the platform or managed device fleet.

Expected categories of operational reporting and visibility include:

- Lifecycle

  Install counts, versions, uninstall counts, start and stop counts, and
  stated or desired reasons for transitions. This information is mostly
  routine, though some lifecycle transitions may require urgent
  visibility.

- Behavioral / Stability

  Crashes, forced shutdowns, restarts, throttling events, crash logs,
  policy violations, signature or hash mismatches, denied access
  attempts, unexpected outbound messaging, and similar platform-originated
  behavioral events. This category includes both routine visibility and
  urgent events that may require operator intervention.

- Resource Consumption

  Resource usage by application instance or group, threshold crossings,
  average and peak CPU, time above threshold, average and peak memory,
  and similar bounded-behavior metrics. Resource reporting is generally
  routine, but threshold crossings may escalate in urgency based on
  severity or persistence.

- Platform / API / Data Reliability

  Platform or device errors, API failures, failed calls, data gaps,
  timeout rates, and related indications that the deployed application
  or platform capability is not performing as intended. These conditions
  may be urgent when they materially impair the intended operational
  purpose of an application or platform capability.

- Connectivity and Environment

  Connectivity uptime, time synchronization status or drift, failed
  sends, average latencies, DNS failures, storage wear warnings, and
  similar conditions affecting reliable operation. This category is
  especially important when applications are deployed for emergency,
  safety, or other time-sensitive operational visibility.

- License Count / Usage

  Install counts, usage counts, or similar license-related visibility as
  applicable to the deployment or application business model. This
  information is generally routine and suitable for slower or batched
  reporting.

Detailed operational reporting and visibility workflow material may be
added in a future revision of the GEISA specification.

Utility and Enterprise Interaction Points
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

GEISA exists within a broader utility operational environment. In
practice, the operator-facing GEISA systems and workflows may interact
with utility or enterprise systems responsible for fleet operations,
metering operations, analytics, customer or service workflows, and other
business processes.

Detailed utility and enterprise integration workflow material may be
added in a future revision of this chapter.

Application Certification
^^^^^^^^^^^^^^^^^^^^^^^^^

This chapter distinguishes between two broad certification models that
may be relevant to GEISA application ecosystems.  The industry continues 
to evolve and this may be expanded in a future revision.  Costs as well as
capabilities of individual providers able to be located to perform this 
function as a Utility may desire may also come into play.

Regardless, there are two broad types of certification we will consider at
this time.

- Basic - 'does no harm' certification

  This model focuses primarily on whether the application remains within
  approved behavioral, resource, security, and policy bounds for safe
  deployment. Examples may include validating that the application does
  not access interfaces or data it was not granted, does not exhibit
  unacceptable restart or memory-growth behavior, does not exceed
  approved policy or threshold limits, does not produce unexpected
  outbound messaging, and does not otherwise destabilize or negatively
  impact the platform or adjacent functions.

  Evidence of interest to such a program may include denied access
  attempts, restart storms, persistent memory or resource threshold
  violations, throttling, shutdown or disablement actions, signature or
  hash mismatch events, and related Platform-originated behavioral
  events.

- Deeper Functional Certification

  This model focuses more directly on validating whether an application
  satisfies a deeper specific functional and/or performance claim, such as
  analytics accuracy, condition-detection fidelity, expected true or
  false positive rates, interoperability with specific external devices,
  or similar claims. It is essentially - 'does this application do what is 
  promised?'
  
  This type of certification may be substantially more complex and
  expensive, particularly for applications that make use of local AI
  inferencing, hybrid edge/cloud processing, behind-the-meter
  integrations, or other advanced workflows.

  This model may also require access to details, methods, or validation
  detail that some publishers may consider sensitive or proprietary.

.. figure:: operations/app-lifecycle-A.*
   :alt: High-level optional certification flow example
   :align: center

As of this version of the specification, GEISA does not define a
singular or specific certification program or require either model.
However, it is useful to distinguish these models explicitly because
they address different operator, certifier, publisher, and ecosystem
concerns. In the near term, GEISA or GEISA-conformant systems may more
naturally support does-no-harm style certification than exhaustive
functional-claim certification, although Platform Providers and
Operators should consider if a given Platform provides enough
capabilities to support both types of Certification.

Future Considerations
^^^^^^^^^^^^^^^^^^^^^
This chapter is intended to establish the operational frame for the
GEISA system. Additional operational detail is expected to be added over
time.

Examples of areas that may be expanded in a subsequent version of the
specification include detailed application certification workflows,
richer operator-side discovery or notification of newly available
applications, enterprise integration patterns, meter-specific lifecycle
workflows such as meter swap or move-in and move-out support, more
detailed operational reporting and visibility models, and more explicit
event taxonomies for application alerts and Platform-originated
behavioral events.
