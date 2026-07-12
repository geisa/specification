
..
  Copyright 2025-2026, Contributors to the Grid Edge Interoperability & 
  Security Alliance (GEISA) a Series of LF Projects, LLC  
  This file is licensed under the Community Specification License 1.0 available 
  at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

Application Messaging and Configuration
---------------------------------------

GEISA LwM2M Object ``/3600`` provides an app-scoped messaging path for a
specific application or application instance. Distinct resources are defined
for Server to Client messaging and Client to Server messaging. Each Object
Instance represents the ADM messaging path for one managed application
instance or application messaging scope identified by resource ``4050`` AppID.

Object ``/3600`` is intended for application-facing message payload exchange,
configuration delivery, and transport metadata. It can carry app-domain
configuration, commands, command results, status, events, alarms, application
data, telemetry, and other application-specific payloads as classified by the
Message Type resource. It is not a durable event, message, or log history
store.

Server to Client messages are written to resource ``0`` Server Message. They
typically carry app-facing configuration, commands, or other application
payloads from an upstream consumer application, EMS, or operator workflow to
the edge application. An ADM-conformant platform receiving a Server Message
SHALL route the message payload and associated message metadata to the
application or application instance identified by resource ``4050`` AppID
through the corresponding GEISA downstream application-facing message API,
subject to authorization, routing policy, application lifecycle state, and
platform policy.

Client to Server messages are exposed through resource ``1`` Client Message
and are typically consumed by upstream applications, EMS workflows, or other
authorized endpoints. They typically carry command results, status, events,
alarms, application data, telemetry, or effective configuration state from
the edge application toward an upstream consumer application, EMS, or
operator workflow. An ADM-conformant EMS MAY read or observe this resource
according to the advertised object model, operator policy, authorization, and
deployment network constraints.

Message Priority values are:

* ``0`` -- Unspecified
* ``1`` -- Urgent: highest priority; send immediately when possible
* ``2`` -- Immediate: high priority; send as soon as possible
* ``3`` -- BestEffort: normal priority; send when resources are available
* ``4`` -- Latest: lowest priority; retain/send only the latest applicable
  message.  When a "Latest" message is received, older messages of the same
  type for the same AppID may be superseded/dropped.
* ``5`` through ``100`` -- Reserved for future GEISA use
* ``101`` through ``254`` -- Reserved for proprietary use
* ``255`` -- Reserved

Message Type values are:

* ``0`` -- ``UNSPECIFIED``: message type is not specified or not yet classified
* ``1`` -- ``CONFIG``: app-facing desired or effective configuration state
* ``2`` -- ``COMMAND``: action request to perform work now or soon
* ``3`` -- ``COMMAND_RESULT``: result of a ``COMMAND`` execution, distinct
  from transport-level response acceptance
* ``4`` -- ``STATUS``: current state, lifecycle, readiness, mode, or
  policy/quota state
* ``5`` -- ``EVENT``: operationally meaningful occurrence worth recording or
  routing
* ``6`` -- ``ALARM``: actionable, high-severity, security, safety, or policy
  condition requiring prompt attention or special handling
* ``7`` -- ``APP_DATA``: supplemental application-specific data that
  intentionally does not fit ``CONFIG``, ``COMMAND``, ``STATUS``, ``EVENT``,
  ``ALARM``, ``COMMAND_RESULT``, or ``TELEMETRY``
* ``8`` -- ``TELEMETRY``: measurement-oriented numeric or structured
  observations, usually time-series, snapshot, interval, or resource metrics
* ``9`` through ``100`` -- Reserved for future GEISA use
* ``101`` through ``254`` -- Reserved for proprietary use
* ``255`` -- Reserved

Each app message is associated with Message Priority, Message Type, Message
TTL, and Content Type metadata. The platform and EMS use this metadata to
classify, schedule, route, retain, expire, and interpret app-message payloads
exchanged through resource ``0`` or resource ``1``. Resource ``4`` Message TTL
does not define event-log retention, and resource ``5`` Content Type does not
expose payload history.

Application configuration carried through Object ``/3600`` is edge application
configuration. It is configuration payload exchanged between an upstream
consumer application, EMS, or operator workflow and the edge application
identified by resource ``4050`` AppID. A Server to Client message with Message
Type ``CONFIG`` may carry desired application configuration, or request current
configuration. A Client to Server message with Message Type ``CONFIG`` or
``STATUS`` may carry application-reported effective configuration,
configuration status, or configuration-related state.

Object ``/3600`` does not define the internal schema of an application
configuration payload. The payload format is identified by Content Type and is
interpreted according to the application, operator, or deployment contract.
Acceptance of a Server Message by the ADM path does not by itself prove that
the application accepted or applied the configuration. Application-level
acceptance, rejection, effective state, or error detail should be reported
through an appropriate app message, status, event, alarm, or durable record.

Application configuration through Object ``/3600`` does not replace the
application manifest, Software Management Object ``/9``, Application
Accounting Object ``/3602``, Application Monitoring Object ``/3604``, or GEISA
Platform Configuration Object ``/3606``. Manifest and deployment policy define
what an application is allowed to do; Object ``/3600`` carries app-facing
configuration payloads within those permissions and platform policies.

===========  ================  =========  ================  ==================================================================
Resource ID  Name              Operation  Data Type         Description
===========  ================  =========  ================  ==================================================================
0            Server Message    Write      Opaque            Server to Client app-message payload.
1            Client Message    Read       Opaque            Client to Server app-message payload.
2            Message Priority  ReadWrite  Unsigned Integer  Per-message priority for ordering, scheduling, throttling, or delivery.
3            Message Type      ReadWrite  Unsigned Integer  Per-message payload classification.
4            Message TTL       ReadWrite  Unsigned Integer  Per-message time-to-live, in seconds.
5            Content Type      ReadWrite  String            Media type for the app-message payload encoding.
4050         AppID             ReadWrite  Unsigned Integer  Local-scope identifier for the edge application.
===========  ================  =========  ================  ==================================================================

.. figure:: app-messaging-data.*

Edge App Message Reporting

.. figure:: app-messaging-config.*

Edge App Message Delivery
