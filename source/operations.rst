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
before moving into the more detailed materials in
:doc:`system-architecture`, :doc:`adm`, :doc:`linux-environment`,
:doc:`virtual-environment`, :doc:`api`, and :doc:`security`.

.. note::

   This chapter is explanatory in nature. Detailed protocol, payload,
   lifecycle, and security requirements are defined in the relevant
   chapters of this specification.

Purpose and Scope
^^^^^^^^^^^^^^^^^

GEISA is intended to support end-to-end interoperability across the
lifecycle of utility edge platforms, edge applications, and other
upstream systems. In practice, the overall system can be difficult to
understand when viewed only through one protocol, one component, or
one's specific organizational responsibilities.

This chapter reframes the system in terms of GEISA roles and major
operational interactions. It is intended to clarify how the management
plane, execution environments, application interfaces, trust decisions,
and operational reporting concerns fit together at a system level.

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
EMS provider, or System Operator. In GEISA, responsibilities and
decision authority are tied to the role being performed in the relevant
interaction, regardless of the type of organization with specific role
responsibilities. However, there is one notable callout: the utility is
expected to often be the one driving the underlying operational
decisions, even in cases where another organization is performing the
day-to-day operational duties.

The principal roles used in this operational view are:

- System Operator

  The role responsible for approving, configuring, authorizing,
  deploying, and operating GEISA-managed devices and applications in a
  target environment.

- Platform Provider

  The role responsible for supplying the platform hardware, platform
  software, and associated platform trust material where applicable.

- Edge Application

  A workload running within a GEISA execution environment and using
  GEISA platform services and the GEISA :term:`API`.

- ADM / Application and Device Management

  ADM is the GEISA pillar for application and device management. It
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
  support on a GEISA platform.

- Application Publisher / Application Vendor

  The role responsible for producing and signing an application artifact
  and supplying its vendor manifest and associated publisher trust
  material.

- Application Certifier

  An optional (as of this version of the specification) role that may
  independently assess, test, or countersign application artifacts as
  validated and safe for deployment purposes. Depending on the
  applicable program or market, this assessment may emphasize either a
  "does no harm" model focused on behavioral and policy safety, a more
  detailed "does what is promised" model focused on functional or
  analytic claims, or both.

The following terms are also important to this chapter:

- :term:`ADM`, :term:`API`, :term:`LEE`, and :term:`VEE` are GEISA
  interoperability areas and components covered in detail in their
  respective sections.

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

.. figure:: operations/end-to-end.*
   :alt: High-level GEISA operational context with LwM2M and additional EMS capabilities or cooperating components
   :align: center

   High-level GEISA operational context showing one architectural option
   in which LwM2M is used as the required interoperable ADM transport and
   control substrate, while additional EMS-side and/or operator-side
   capabilities or cooperating components may participate in
   application intake, behavioral governance, operational alerting,
   reporting, analytics, certification handling, or other workflows.

.. figure:: operations/end-to-end-lwm2m-only.*
   :alt: High-level GEISA operational context using an LwM2M-only upstream EMS posture
   :align: center

   High-level GEISA operational context showing an alternative
   discussion model in which the EMS and the LwM2M client/server
   relationship are treated as the sole authoritative upstream
   operational path, with other systems consuming information exposed by
   or through that path.

.. figure:: operations/reference-app-lifecycle.*
   :alt: High-level GEISA application lifecycle reference flow
   :align: center

   Reference application lifecycle flow retained for comparison and
   discussion.

Operational Capability Discussion
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

This section frames an active architectural discussion within GEISA
regarding the extent to which the required LwM2M client and server
relationship is, by itself, sufficient to realize the operational
capabilities expected of a GEISA Edge Management System and associated
operator workflows.

This discussion is explanatory and does not, by itself, change the
normative requirements defined elsewhere in this specification. In
particular, :doc:`adm` continues to define the required interoperable ADM
behaviors and transactions, while :doc:`api` and :doc:`security` define
the relevant application-facing, off-device communication, isolation,
policy-control, and resilience mechanisms.

Option A: LwM2M is sufficient for ADM / EMS capabilities
""""""""""""""""""""""""""""""""""""""""""""""""""""""""

.. figure:: operations/end-to-end-lwm2m-only.*
   :alt: High-level GEISA operational context using an LwM2M-only upstream EMS posture
   :align: center

   High-level GEISA operational context showing this Option A discussion
   model in which the EMS and the LwM2M client/server relationship are
   treated as the sole authoritative upstream operational path, with
   other systems consuming information exposed by or through that path.

Under this architectural view, the EMS and its LwM2M server/client
relationship are treated as the sole authoritative upstream operational
path, even if the EMS later integrates with or forwards information to
other systems.

In this model, platform onboarding, lifecycle control, software and
firmware management, application messaging, runtime visibility, policy
reporting, and most or all EMS-facing operational behaviors are treated
as realizable through the LwM2M-centered management path and closely
related EMS functions.

This option is best aligned with procurement simplicity, baseline
interoperability, easier adoption, and easier implementation,
particularly for Platform Providers and for operators integrating around
a well-known management interface.

However, this option can materially reduce urgent operator awareness
during FAN impairment, including awareness of critical application
alerts and Platform-originated behavioral events. In practical terms, if
urgent information must effectively round-trip only through the EMS and
the primary FAN path, the operator may incorrectly believe the fleet is
healthy, critical field conditions may be under-reported, and triage or
corrective action may be delayed.

This concern is especially important for cases in which edge
applications are deployed specifically to provide emergency, safety, or
high-value situational awareness. For example, during a storm, a
tree-impact, wildfire, or similar safety-relevant application may need
to emit an alert immediately even if the FAN path is impaired.
Likewise, if the platform disables that application because of repeated
restart failure, a critical policy violation, or a signature or hash
mismatch suggesting attempted malicious injection, operator awareness of
that disablement is itself urgent. Otherwise, the operator may not know
that either the underlying event or the loss of that application's
visibility path has occurred.

Option A also does not eliminate the need for meaningful local platform
logic. Restart suppression, throttling, stop or disable decisions,
policy enforcement, and similar controls still have to exist locally on
the platform. Choosing an LwM2M-only EMS posture mainly constrains how
those outcomes are surfaced upstream.

Option B: LwM2M plus additional EMS capabilities and/or components
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

.. figure:: operations/end-to-end.*
   :alt: High-level GEISA operational context with LwM2M and additional EMS 
     capabilities or cooperating components
   :align: center

   High-level GEISA operational context showing this Option B discussion
   model in which LwM2M is used as the required interoperable ADM
   transport and control substrate, while additional EMS-side and/or
   operator-side capabilities or cooperating components may participate
   in application intake, behavioral governance, operational alerting,
   reporting, analytics, certification handling, or other workflows.


Under this architectural view, LwM2M remains the required interoperable
ADM transport and control substrate, but it is not treated as the sole
expression of all operational capability.

In this model, GEISA still relies on the required LwM2M-based ADM path
for onboarding, registration, lifecycle control, deployment,
activation and deactivation, and related management behavior. However,
operator-facing and platform-originated operational capabilities may
also include additional EMS-side and/or operator-side capabilities for:

- urgent alert routing;
- Platform-originated behavioral event reporting and enforcement
  visibility;
- persistence and deferred forwarding when connectivity is impaired;
- certification record handling;
- analytics and fleet-level visibility; and
- integration with enterprise systems, ingestion pipelines, message
  buses, or similar upstream systems.

Under this option, the EMS remains the management authority, but urgent
application alerts and urgent Platform-originated behavioral events may
also be forwarded to agreed ingestion or integration paths when operator
policy permits. Operator policy SHOULD strongly consider allowing
critical application alerts and critical Platform-originated behavioral
events to use any permitted available communications path, because loss
of the primary FAN and EMS path may coincide with the very emergency
conditions the applications were deployed to detect.

This option more directly reflects deployments in which the platform
continues local enforcement even when the primary upstream management
path is impaired, persists urgent or routine events locally as needed,
and forwards them upstream as soon as feasible over an available
permitted path.

The primary benefit of this option is improved resilience, timeliness,
and operational truth for the System Operator. It also better supports
shorter field-trial and emergency triage cycles for application
developers and publishers, and more cleanly separates application
behavior from platform enforcement outcomes for does-no-harm style
certification.

The primary detriment of this option is increased policy, integration,
and implementation work. The System Operator may need to define and
govern another layer of policy, access, filtering, and ingestion rules.
The Platform Provider may need to support more than "just set up the
LwM2M server and client" behavior. Some certification programs may also
need to account for more than one upstream evidence path depending on
how the deployment is realized.

Reporting model discussion
"""""""""""""""""""""""""

For purposes of this operational discussion, it is useful to distinguish
three broad reporting classes:

- Application alerts

  Near-real-time when feasible. These are application-originated alerts
  or condition notifications for which delayed awareness may materially
  reduce operator usefulness.

- Platform-originated behavioral events

  Near-real-time when urgent, otherwise routine or batched as
  appropriate. These are platform-originated observations or actions
  relating to application or platform behavior, such as repeated restart
  failure, policy violations, throttling, disablement, denied access
  attempts, unexpected outbound messaging, signature or hash mismatch
  events, or severe and persistent threshold violations.

- Routine operational reporting

  Slower and/or batched as appropriate. These are lower-urgency
  operational data intended primarily for visibility, trending, support,
  audit, or planning.

This model is intended to preserve an important distinction between what
the application says, what the platform says about the application, and
what the platform or operator may do because of that behavior.

Device Onboarding and Management Overview
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

GEISA device onboarding establishes the management relationship between
a conformant platform and a conformant EMS. In operational terms, this
includes device provisioning, network attachment, bootstrap or initial
trust establishment, registration, and subsequent lifecycle management.

.. figure:: operations/reference-device-onboarding.*
   :alt: High-level GEISA operational context
   :align: center

   Reference application approval, deployment, and optional
   certification flow retained for comparison and discussion.

See :doc:`operations/device-onboarding`.

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

See :doc:`operations/application-approval-deployment`.

Application Activation and Runtime Visibility
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

After installation, GEISA applications are activated under operator
control and execute within the platform's selected execution
environment. During runtime, the platform and EMS provide visibility
into application and platform state, including activation state,
execution state, status, and other operationally relevant data.

See :doc:`operations/application-activation-runtime`.

Operational Reporting and Visibility
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

GEISA deployments require operational visibility into both the managed
platform and the applications running on it. At a high level, expected
categories of operational reporting and visibility include lifecycle
state, behavioral and stability information, resource consumption,
platform, API, and data reliability, connectivity and environment, and
license or usage information where applicable.

Operational reporting and visibility are distinct from
application-originated data, condition notifications, or alert-like
outputs. A GEISA application may emit condition or data messages through
the GEISA messaging and off-device communication paths, but those
messages represent application behavior or detected conditions rather
than the broader operational reporting model for the platform or managed
fleet.

For clarity, the broader operational reporting model may itself include
both urgent and routine elements. In general:

- lifecycle information is mostly routine, though some transitions may
  be urgent;
- behavioral and stability information includes both routine visibility
  and urgent intervention-required events;
- resource consumption is generally routine, but threshold crossings may
  escalate in urgency based on severity or persistence;
- platform, API, and data reliability information may be urgent when it
  materially impairs the intended operational purpose of an application
  or platform capability;
- connectivity and environment information is especially important when
  applications are deployed specifically for emergency, safety, or other
  time-sensitive operational visibility; and
- license count or usage information is generally routine and suitable
  for slower or batched reporting.

Examples of reporting categories to consider include:

- Lifecycle

  Install counts, versions, uninstall counts, start and stop counts, and
  desired reasons for transitions.

- Behavioral / Stability

  Crashes, forced shutdowns, restarts, throttling events, crash logs,
  policy violations, signature or hash mismatches, denied access
  attempts, unexpected outbound messaging, and similar Platform-originated
  behavioral events.

- Resource Consumption

  Resource usage by application instance or group, threshold crossings,
  average and peak CPU, time above threshold, average and peak memory,
  and similar bounded-behavior metrics.

- Platform / API / Data Reliability

  Platform or device errors, API failures, failed calls, data gaps,
  timeout rates, and related indications that the deployed application
  or platform is not performing as intended.

- Connectivity and Environment

  Connectivity uptime, time synchronization status or drift, failed
  sends, average latencies, DNS failures, storage wear warnings, and
  similar conditions affecting reliable operation.

- License Count / Usage

  Install counts, usage counts, or similar license-related visibility as
  applicable to the deployment or application business model.

See :doc:`operations/reporting-and-visibility`.

Utility and Enterprise Interaction Points
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

GEISA exists within a broader utility operational environment. In
practice, the operator-facing GEISA systems and workflows may interact
with utility or enterprise systems responsible for fleet operations,
metering operations, analytics, customer or service workflows, and other
business processes.

See :doc:`operations/utility-enterprise-interaction`.

Deferred Areas
^^^^^^^^^^^^^^

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

Certification discussion
^^^^^^^^^^^^^^^^^^^^^^^^

This chapter distinguishes between two broad certification models that
may be relevant to GEISA application ecosystems.

- Does no harm certification

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

- Does what is promised certification

  This model focuses more directly on validating whether an application
  satisfies a deeper functional or performance claim set, such as
  analytics accuracy, condition-detection fidelity, expected true or
  false positive rates, interoperability with specific external devices,
  or similar claims. This may be substantially more complex and
  expensive, particularly for applications that make use of local AI
  inferencing, hybrid edge/cloud processing, behind-the-meter
  integrations, or other advanced workflows.

  This model may also require access to evidence, methods, or validation
  detail that some publishers may consider sensitive or proprietary.

As of this version of the specification, GEISA does not define a
normative certification program or require either model. However, it is
useful to distinguish these models explicitly because they address
different operator, certifier, publisher, and ecosystem concerns. In the
near term, GEISA may more naturally support does-no-harm style
certification than exhaustive functional-claim certification. A third
party or industry program may choose to offer one or both forms of
assessment in the future.
