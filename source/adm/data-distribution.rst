..
  Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
  Security Alliance (GEISA), a Series of LF Projects, LLC
  This file is licensed under the Community Specification License 1.0
  available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

.. index:: single: Data Distribution

Data Distribution
-----------------

GEISA Application and Device Management provides mechanisms for moving application and
operational information between Edge Devices and an Edge Management System (EMS).
Systems operating a GEISA deployment also need an interoperable way to distribute
selected GEISA data from the EMS to other authorized systems.

Data Distribution defines the common interface used to make selected GEISA data
available to consumers. Note that consumer systems may be operated by the
System Owner, System Operator, Application Vendor, or another authorized party.

GEISA defines the data and interoperability requirements through the point where an
authorized consumer receives a common GEISA data record, at which point it may transform
the data as required for its own native ingestion. Transformation into consumer-specific
formats, further routing, persistence, business-system ingestion, user interfaces, and
other consumer-side processing are outside the scope of GEISA.

Purpose and Scope
=================

Data Distribution is intended to allow independently implemented systems to consume the
same GEISA data without requiring a GEISA deployment to adopt the native schema, data
models, or implementation technology of any consuming system.

For example, the same application data may be consumed independently by:

* a Utility-operated data lake
* an Application Vendor system used for analytics or providing a user interface, and/or
* a Utility operations system that receives only selected events or alarms
* other systems as required by the Utility and/or Operator

Consumption by one system SHALL NOT prevent the same data from being consumed by another
authorized system. Data Distribution does not require every deployed record to have
multiple consumers, but does require the system to support multiple independent
consumers as per System Operator configuration.

This section addresses data that is available within the ADM and EMS scope. Data exposed
by the :doc:`GEISA Application Programming Interface </api>` to Edge Applications does not
automatically become ADM data or require transport to the EMS or distribution to other
consumers. For example, metrology, waveform, sensor, or similar device data may be
exposed by the GEISA Platform to Edge Applications without becoming Platform operational
data or being transported through ADM.

Note that EMS implementations MAY expose additional interfaces, including REST APIs,
operator interfaces, query APIs, MQTT interfaces, or implementation-specific integration
mechanisms, but such interfaces do not replace the interoperable Data Distribution
requirements defined here.  Direct IP communication by Edge Applications is a separate
mechanism described elsewhere in this specification and is not part of Data
Distribution.

GEISA Data Distribution as defined in this section carries information from the EMS to
authorized consumers using the Apache Kafka wire protocol. This is a protocol requirement
and does not require use of Apache Kafka software.

.. note::

   Kafka consumers normally maintain a persistent broker connection and continuously
   consume one or more topics so that newly published records can be processed with low
   latency. At the Kafka wire-protocol level, this behavior uses consumer-initiated
   ``Fetch`` requests, which may remain outstanding while waiting for records. Subsequent
   Fetch requests normally reuse the existing broker connection.

   Consumer applications therefore experience Kafka as a continuous event stream
   rather than periodic polling. A GEISA-facing adapter may continuously consume this
   stream and immediately deliver, transform, or route records through the native interface
   expected by the consuming system.

Data Distribution does not define a separate message-delivery control path.
Application messages being delivered to an Edge Application are defined by
:doc:`Application Messaging and Configuration </adm/messaging>`, including
Object ``/3600`` Server Message and the corresponding Server to Client
application-message API. Platform configuration is handled through
``/3607`` GEISA Platform Requested Configuration and reported through ``/3606`` GEISA
Platform Effective Configuration. Application lifecycle operations remain defined by
``/9`` Software Management, and other device or Platform management actions remain defined by the applicable ADM Objects and LwM2M operations described in :doc:`OMA Lightweight M2M </adm/lwm2m>`.

Architecture and Interoperability Boundary
==========================================

Data Distribution provides the interoperability path between GEISA data available at the
EMS and authorized consumer systems.

A typical deployment includes:

#. one or more Edge Devices managed through ADM
#. an EMS receiving application, Platform, lifecycle, monitoring, event, and other ADM
   information
#. one or more Data Distribution routes configured by the System Operator
#. one or more authorized consumers of the distributed GEISA data
#. adapters or other functions that translate the GEISA data record into
   formats used by systems outside GEISA

A Data Distribution consumer receives a common GEISA data record. Once that record has
been consumed, the consumer may transform, enrich, store, route, or otherwise process
the data as required by the receiving system.

.. figure:: data-distribution-highlevel.*
   :alt: High-level GEISA Data Distribution architecture showing ADM inputs, EMS Data Distribution functions, the Kafka-compatible Data Distribution service, GEISA-facing consumers, and the GEISA interoperability boundary.
   :align: center

   Data Distribution Architecture and Interoperability Boundary

The System Owner retains final authority over Data Distribution policies for the
deployment environment. The System Operator is expected to configure and operate Data
Distribution within that policy.

Data Eligible for Distribution
==============================

Data Distribution may carry information originating from several GEISA scopes. The
original GEISA semantics SHALL be preserved when the data is distributed. For example,
an application message retains its AppID, message type, priority, content type,
timestamp, and other applicable GEISA metadata. Platform-originated data similarly
retains its defined source, state, severity, reason, event type, or other applicable
GEISA information rather than requiring consumers to reconstruct those
semantics.

Application-Originated Data
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Application-originated messages use the GEISA application messaging path defined by the :doc:`GEISA API </api>` and ADM Application Messaging Object ``/3600``.

Existing GEISA application message classifications include:

* ``CONFIG``
* ``COMMAND``
* ``COMMAND_RESULT``
* ``STATUS``
* ``EVENT``
* ``ALARM``
* ``APP_DATA``
* ``TELEMETRY``

Data Distribution does not define additional application message types, and messages
retain their original message classification and associated GEISA metadata when
distributed.

An ADM-conformant EMS receiving ``/3600`` Client to Server application messages
MUST make those messages available for Kafka-protocol Data Distribution as
defined in this chapter. Actual publication is determined by the configured
Data Distribution routes.

Data Distribution MUST preserve application payload bytes unchanged unless an
explicitly defined GEISA transformation applies. Transformation for native
system ingestion occurs outside of the GEISA Data Distribution boundary.

GEISA does not define the internal schema of an application's opaque payload.
The EMS is not required to understand that payload. This does not prohibit the
EMS or System Operator from carrying, storing, inspecting, interpreting, or
processing it when authorized and when its content type or format is known.
Data Distribution MUST preserve the GEISA metadata required to identify and
interpret the record.

Platform-Originated Operational Data
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The GEISA Platform provides operational state and monitoring information through several
ADM Objects. Depending on the Object, this may include current state, counters,
timestamps, reason codes, lifecycle information, Platform actions, queue or API status,
and other operational data. Relevant ADM Objects include:

* ``/3601`` GEISA Host Monitoring
* ``/3602`` GEISA App Accounting
* ``/3604`` GEISA App Monitoring
* ``/3605`` GEISA Platform Monitoring
* ``/3608`` GEISA Platform Component Monitoring, when implemented

Other standard OMA Objects may provide additional ADM information where applicable.

Note that the current monitoring state is not necessarily a discrete event. A Data
Distribution route may distribute state, events, alarms, accounting information, or
other selected operational information according to System Operator configuration.

Data exposed by the Platform to Edge Applications through APIs such as metrology,
waveform, or sensor APIs is also not considered to be Platform operational data solely
because the Platform provides access to it.

Durable Event and Log Data
~~~~~~~~~~~~~~~~~~~~~~~~~~

Event Log Object ``/20`` provides durable event, log, audit, diagnostic, Platform, and
application records.

Records already available to the EMS through ``/20`` may be selected for Data
Distribution like other eligible ADM data. Data Distribution does not require every
``/20`` record to be distributed.

Separately, ``/20`` may be considered as a possible mechanism for carrying
Platform-originated events from an Edge Device to the EMS, potentially using structured
GEISA event records and LwM2M Send. That use is discussed under Platform Event Reporting
and is not yet finalized.

Other ADM Data
~~~~~~~~~~~~~~

Additional ADM data may be relevant for Data Distribution when the information has an
interoperable GEISA or OMA representation and the System Operator has configured it for
distribution.

The inclusion of additional ADM data does not change the scope or meaning of the source
Object or Resource.

Platform Event Reporting
========================

GEISA already defines extensive state, monitoring, accounting, lifecycle, and durable
event capabilities. The current draft still needs to determine whether those mechanisms
are sufficient for Platform-originated behavioral events or whether a distinct Platform
Event Reporting mechanism is required.

This section describes the interoperability problem and candidate approaches. It
intentionally does not decide or dictate the final Platform Event Reporting transport or
OMA Object.

Current Mechanisms
~~~~~~~~~~~~~~~~~~

Current ADM mechanisms provide several ways to observe Platform and application
behavior:

* Read retrieves current Resource state
* Observe and Notify can provide asynchronous notifications when selected Resource
  values change
* Monitoring Objects provide current state, counters, timestamps, latest reason codes,
  Platform actions, and other accumulated monitoring information
* Event Log Object ``/20`` provides durable event and log history
* LwM2M Send may provide unsolicited Client-to-Server reporting where GEISA makes the
  applicable behavior mandatory
* Remote logging may provide additional operational logging where configured

These mechanisms overlap but serve different purposes.

Why Isn't Observe/Notify Enough?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Observe/Notify is appropriate for reporting current state and changes to monitored
Resources. In many cases, it may be all that is required. A consumer observing
application lifecycle state, Platform health, queue status, or component state can
receive timely notification when those values change.

Monitoring Objects describe current state and accumulated monitoring information. Event
reporting preserves discrete occurrences and the relationship between the cause,
subject, action, and time of an occurrence.

If all relevant Resources are observed, every meaningful transition changes an observed
Resource, every notification is received, and related Resource changes can be correlated
correctly, the EMS may have enough information to reconstruct what occurred, but those
assumptions do not always hold.

Multiple Resource Changes May Represent One Occurrence
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

A single policy or lifecycle occurrence may update several independent Resources.

For example, one application policy violation might result in:

* an application policy-violation counter increasing
* an accounting or monitoring reason changing
* the application lifecycle state changing
* an exit reason being updated
* the Platform recording that it stopped or forcibly terminated the application

Individual Resource notifications do not inherently establish that these changes all
resulted from the same occurrence.

Several Occurrences or Events May Happen Before the EMS Receives the Resulting State
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

An application may crash, restart, crash again, and eventually reach a restart limit
while the EMS is temporarily unreachable or while several state changes occur in a short
period.

The resulting monitoring state may correctly indicate that:

* the application is stopped or failed
* the restart count increased several times
* the most recent exit resulted from a crash
* the most recent Platform action stopped the application

That state does not necessarily retain the ordered sequence, occurrence time, or reason
associated with each individual transition.

Counters Preserve Quantity But Not Necessarily Occurrence Detail
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

A counter can show that an event occurred one or more times, but does not identify each
occurrence.

For example, a change in an unauthorized API attempt counter can show that additional
unauthorized attempts occurred. The counter alone does not necessarily identify each
occurrence, its exact time, its subject, its reason, or an action taken in response.

Temporary Communication Loss Can Limit Reconstruction
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

After a management communication outage, monitoring state can accurately tell the EMS
what is true now. Counters can also show accumulated activity that occurred while
communication was unavailable.

Those mechanisms do not necessarily identify every discrete occurrence that took place
during the outage.

Event Log ``/20`` may provide the durable history required to fill this gap. Whether
``/20`` plus LwM2M Send is sufficient for interoperable Platform Event Reporting remains
an open design question.

Not Every State Change Requires an Event
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Platform Event Reporting should not duplicate monitoring by generating a separate event
for every Resource transition.

Explicit event reporting is most relevant when a discrete occurrence needs one or more
of the following:

* independent routing
* durable traceability
* accounting over time
* recovery after missed notifications
* correlation of several related state changes
* preservation of occurrence-specific information not represented by current state

Platform Event Information
~~~~~~~~~~~~~~~~~~~~~~~~~~

A Platform event representation needs enough information for the EMS to understand the
occurrence without reconstructing it from unrelated monitoring Resources.

The initial Platform Event model should contain enough information for an EMS to
identify a discrete occurrence without reconstructing it from multiple monitoring
Resources. The intent is to reuse existing GEISA fields and enumerations wherever
possible rather than define another parallel event model.

The following is the initial working model for discussion:

.. list-table::
   :header-rows: 1
   :widths: 24 25 51

   * - Information
     - Initial direction
     - Example
   * - Origin Event ID
     - Core
     - A Platform-generated identifier for this occurrence, unique within the originating Edge Device.
   * - Occurrence Time
     - Core
     - Time at which an application crash, policy violation, component failure, or other occurrence took place.
   * - Message Type
     - Core
     - Reuse an existing GEISA type such as ``EVENT`` or ``ALARM``.
   * - Event Code
     - Core, new only where needed
     - ``APP_RESTART_LIMIT_EXCEEDED``, ``COMPONENT_FAILED``, ``AUTHORIZATION_DENIED``, or another GEISA-defined occurrence.
   * - Subject
     - Core
     - Application, Platform, Platform component, queue, API, or other defined GEISA scope.
   * - Subject Identity
     - Required when subject is not the Platform overall
     - AppID and Software Instance for an application, or a ``/3608`` component reference or identifier for a Platform component.
   * - Reason Code
     - When applicable
     - Reuse an existing GEISA reason such as ``Restart limit exceeded``, ``Authorization denied``, ``Timeout``, or ``Security restriction``.
   * - Platform Action
     - When applicable
     - Reuse an existing action such as ``Stopped``, ``Killed or forcibly terminated``, ``Restarted``, or ``Quarantined``.
   * - Severity
     - When applicable
     - Reuse the GEISA severity levels already used by Platform reporting configuration.
   * - Condition or Correlation ID
     - When needed
     - Associates an asserted alarm or condition with a later update or clear/recovery report.
   * - Additional Data
     - Optional
     - Structured or opaque information needed by the specific event, identified by an appropriate content type.

For example, an application that repeatedly crashes until the configured restart limit
is exceeded might produce an event equivalent to:

.. code-block:: text

   Origin Event ID:     1842
   Occurrence Time:     2026-10-12T16:42:13Z
   Message Type:        ALARM
   Event Code:          APP_RESTART_LIMIT_EXCEEDED
   Subject:             Application
   AppID:               42
   Software Instance:   /9/7
   Reason Code:         Restart limit exceeded
   Platform Action:     Stopped
   Severity:            Major

The current application monitoring Objects would continue to expose the resulting state,
restart counters, latest exit reason, and Platform action. The Platform event identifies
the discrete occurrence that caused those values to change.

Similarly, a Platform component failure might produce:

.. code-block:: text

   Origin Event ID:     1843
   Occurrence Time:     2026-10-12T16:44:02Z
   Message Type:        ALARM
   Event Code:          COMPONENT_FAILED
   Subject:             Platform Component
   Component:           /3608/3
   Reason Code:         Timeout
   Severity:            Major

If the component later recovers, a subsequent event may refer to the same condition so
an EMS can associate the recovery with the earlier failure:

.. code-block:: text

   Origin Event ID:     1844
   Occurrence Time:     2026-10-12T16:45:17Z
   Message Type:        EVENT
   Event Code:          COMPONENT_RECOVERED
   Subject:             Platform Component
   Component:           /3608/3
   Condition ID:        <same condition as the failure>

An authorization failure provides a different example. Existing aggregate monitoring may
report that the unauthorized-attempt counter increased, while a discrete event can
retain the information associated with a particular occurrence:

.. code-block:: text

   Origin Event ID:     1845
   Occurrence Time:     2026-10-12T16:47:31Z
   Message Type:        EVENT
   Event Code:          AUTHORIZATION_DENIED
   Subject:             Application
   AppID:               42
   Reason Code:         Authorization denied

These examples are not intended to define the final event-code set or require every
listed field for every event. They illustrate the information that may otherwise be lost
when an EMS only observes current state, counters, or the most recent reason and action.

Existing GEISA enums and identifiers SHOULD be reused whenever their semantics match.
Platform Event Reporting should not create separate definitions for concepts already
represented by GEISA message types, reason codes, Platform actions, priorities,
severities, AppIDs, Software Instance references, or Platform component identifiers.

Open questions include:

* whether every Platform event requires an explicit severity or whether severity may be
  defined by the event type or Platform policy
* whether Event Code requires a new common GEISA enumeration or can mostly be expressed
  through existing reason and action combinations
* whether a separate Condition ID is required in addition to the Origin Event ID
* whether an origin sequence number is needed to detect missing events
* which occurrences require a discrete Platform event rather than being sufficiently
  represented through Observe/Notify and current monitoring state
* whether this information is carried through structured ``/20`` records and LwM2M Send
  or through a dedicated Platform Event Reporting Object

An edge-generated occurrence identifier is not required to be globally unique. It must
be usable together with the identity of the originating managed device to distinguish
the occurrence within the applicable management domain. However, an Edge Device does not
need to contact the EMS to obtain an identifier before reporting an event.

A separate identifier may be needed to associate an asserted condition with later
updates or a clear/recovery report. Whether a separate condition identifier is required
is an open question.

Candidate Reporting Mechanisms
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The following mechanisms should be reviewed and considered before finalizing Platform
Event Reporting behavior.

Monitoring, Observe/Notify, and Event Log
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Current monitoring Objects provide state and accumulated monitoring information.
Observe/Notify provides timely state-change reporting, while ``/20`` provides durable
history.

This option adds the least new protocol or Object behavior but may require the EMS to
correlate several state changes in order to reconstruct one operational occurrence.

Structured GEISA Event Records Through Event Log and LwM2M Send
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

GEISA may define a structured Platform event representation stored through ``/20`` and
reported using ``LogDataIncremental`` and LwM2M Send.

This option reuses the existing Event Log and LwM2M Information Reporting mechanisms.

If this approach is selected, GEISA may need to:

* make the applicable LwM2M Send behavior mandatory
* define the structured GEISA event representation carried by ``/20``
* define how Platform-scoped records are represented when ``/20`` AppID is mandatory
* determine whether a reserved AppID value represents the GEISA Platform

Dedicated Platform Event Reporting Object
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

GEISA may define a separate Platform Event Reporting Object or equivalent ADM interface.

This provides a clear distinction between current monitoring state, durable log history,
and discrete event reporting, but adds another GEISA-defined ADM interface and should
only be selected if the existing ``/20`` and Information Reporting mechanisms cannot
meet the interoperability requirements cleanly.

Remote Logging
^^^^^^^^^^^^^^

Remote logging may supplement Platform Event Reporting and provide integration with
established operational logging systems.

Remote logging alone should not be assumed to provide the structured, interoperable
GEISA event semantics required for Data Distribution.

Distribution Routes and Configuration
=====================================

The System Operator configures Data Distribution routes. A route maps selection
criteria to a Data Distribution target. The System Owner retains final policy
authority, and the System Operator configures routes and targets under that
policy.

The exact configuration representation remains under review.

Data Selection
~~~~~~~~~~~~~~

The System Operator MUST be able to select data for a route using defined GEISA
metadata, including where applicable:

* source scope or class
* :ref:` ``operator-identifier`` <operator-identifier>`
* AppID
* message type, including a set of message types
* event or record type
* Platform or component identity

Criteria MAY be combined. Routing MUST use GEISA semantics and MUST NOT require
the EMS to inspect or interpret an opaque application payload. This version does
not define a general-purpose policy language or utility-specific fleet grouping
system. Implementations MAY provide additional grouping, tag, region, device
class, or similar conveniences.

For every configured route that matches a GEISA record, the EMS MUST publish the
record to that route's Data Distribution target. Multiple Data Distribution
routes MAY select the same GEISA record.

For example, a System Operator may configure these routes with separate
targets/topics:

* all messages for ``AppID = 17`` to a Vendor Application Server target/topic
* ``message-type = EVENT`` or ``ALARM`` to a Utility Operations target/topic
* all application-message records to a Utility Data Lake target/topic

An ``AppID = 17`` ``ALARM`` record matches all three routes and is published
to all three targets. An ``AppID = 17`` ``TELEMETRY`` record matches the
Vendor Application Server and Utility Data Lake routes and is published to
those two targets.

Distribution Target
~~~~~~~~~~~~~~~~~~~

The System Operator MUST be able to configure a Data Distribution target.

For Kafka-protocol distribution, each configured target MUST include at least:

* enabled or disabled state
* Kafka endpoint or bootstrap server information
* target topic
* applicable security and authentication configuration

Additional configuration may be required after the Kafka protocol profile,
routing behavior, partitioning, and security requirements are finalized.

Topic names remain System Operator configuration. The EMS producer MUST NOT
autonomously create a topic merely because a new consumer exists. The System
Operator determines routes, authorization boundaries, and configured targets.
Kafka topic creation, ACL administration, identities, credentials, partitions,
and other broker administration MAY be performed by Kafka tooling, an operator
provisioning system, an EMS operator interface, or another implementation-
specific system.

GEISA does not require Kafka topic names to encode AppID,
``operator-identifier``, message type, or other selection criteria. Route
selection uses defined GEISA metadata, and the System Operator chooses the
configured target/topic name. GEISA does not prescribe a topic naming
convention.

Authorization Boundary
~~~~~~~~~~~~~~~~~~~~~~

A Data Distribution target and its Kafka topic are an authorization boundary.
Every consumer authorized to read a target MUST be permitted to receive every
record published to it. Consumers with the same data-selection and
authorization requirements MAY share one target/topic and maintain independent
consumption positions. Records with different data-selection or authorization
requirements MUST be assigned to separate targets. Kafka consumer-side
per-record filtering MUST NOT be used as an access-control mechanism. Record-
level encryption is not the baseline solution for separating these requirements.

Kafka Record Key
~~~~~~~~~~~~~~~~

GEISA does not define a topic per Edge Device. Topic selection is determined by
the System Operator's route configuration. For application-message
partitioning or ordering, the combination of ``operator-identifier`` and
``AppID`` is the candidate Kafka record-key scope for later definition. This
does not establish a mandatory ordering guarantee.

Configuration Authority
~~~~~~~~~~~~~~~~~~~~~~~

The System Owner retains final authority over Data Distribution policy.

The System Operator configures Data Distribution routes, destinations, security, and
other deployment-specific behavior in accordance with System Owner policy.

Application Publishers or Application Vendors may provide integration requirements or
recommendations, but they do not control the System Operator's Data Distribution
configuration.

Relationship to Platform Configuration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Objects ``/3606`` and ``/3607`` describe effective and requested GEISA Platform
configuration on the Edge Device.

Existing Platform configuration includes concepts such as:

* minimum upstream severity
* event suppression period
* clear/recovery reporting
* reporting priority
* message and queue TTL
* queue or spool limits
* other Platform-side reporting behavior

These controls affect behavior between the Edge Device and EMS.

Data Distribution routing and Kafka retention are EMS-side or Data Distribution service
concerns and are not part of ``/3606`` or ``/3607``. For example, Platform Queue TTL
controls how long an Edge Device may retain an upstream message while attempting
delivery to the EMS. Kafka retention controls how long a record remains available to
consumers after publication to the Data Distribution service. They are
separate policies and SHALL NOT be implicitly mapped to one another.

The Data Distribution configuration model should reuse existing GEISA concepts where
applicable without mixing EMS-side routing or Kafka-service configuration into Edge
Device Platform configuration.

GEISA Data Distribution Record
==============================

A consumer must receive enough information to interpret the distributed record without
depending on implementation-specific EMS behavior in order to ensure interoperability.

The common GEISA Data Distribution record format for data classes other than
the ``/3600`` application-message minimum below remains under review.

Preservation of GEISA Semantics
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Data Distribution SHALL preserve the semantics of the original GEISA information.

Where the source already defines:

* message type
* priority
* reason code
* action
* severity
* AppID
* Software Instance
* timestamp
* content type
* other interoperable metadata

the Data Distribution record SHOULD reuse that information rather than defining
another equivalent value.

Minimum ``/3600`` Application-Message Metadata
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

For each distributed ``/3600`` Client to Server application message, the
Data Distribution record MUST carry at least:

* ``operator-identifier``
* ``AppID``
* ``request-id``
* ``priority``
* ``message-type``
* ``timestamp-us``
* ``ttl-seconds``
* ``content-type``
* ``payload``

These names and meanings reuse Platform Discovery and the GEISA application-
message envelope. The EMS obtains ``operator-identifier`` from managed-device
or provisioning context; it is not required in the Edge Application's message
envelope. Software Instance MAY be included as additional metadata but is not
required by this minimum.

``DATA_DISTRIBUTION`` is not a GEISA message type. Data Distribution describes what is
done with a record, not what the record means.

Origin and Subject Identity
~~~~~~~~~~~~~~~~~~~~~~~~~~~

For ``/3600`` application messages, the provisioned ``operator-identifier``
MUST identify the originating Edge Device within the System Operator's managed
deployment. The EMS MUST obtain or map this identifier from its managed-device
or provisioning context. ``/3`` Serial Number and the LwM2M Endpoint Name MUST
NOT be repurposed as the external application-message device identifier.

Identity requirements for Data Distribution records other than ``/3600``
application messages remain under review.

Where a record concerns an application, the existing AppID and other applicable
application identity SHOULD be retained.

Where a record concerns a Platform component, the applicable Platform or component
identity SHOULD be retained.

For Platform-scoped ``/20`` records, GEISA may reserve an AppID value to represent the
Platform. The need for such a value and its numeric assignment remain open questions.

Event and Condition Identity
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

An Edge Device may generate event information while disconnected from its EMS.

Any origin event identifier therefore SHALL NOT require an EMS round trip before the
event can be created.

An origin event identifier may be unique only within the originating device scope. The
combination of managed-device identity and origin event identifier can identify the
event within the management domain.

GEISA should determine whether a separate condition identifier is required for an alarm
or other condition that produces later update or clear/recovery records.

Payload and Encoding
~~~~~~~~~~~~~~~~~~~~

Where the source record carries an opaque application payload, Data Distribution SHALL
preserve the payload bytes unless an explicitly defined GEISA transformation applies.

The Data Distribution record SHOULD be self-contained and should not require a
consumer to reconstruct essential GEISA semantics from Kafka-specific headers.

The final Data Distribution record may reuse an existing GEISA schema, extend
an existing schema, or define a Data Distribution envelope if required.

Kafka Protocol Profile
======================

GEISA Data Distribution SHALL use the Apache Kafka wire protocol for interoperable
communication between an EMS and the configured Data Distribution service.

This requirement applies to protocol behavior and does not require Apache Kafka
software. A conformant deployment may use Apache Kafka or another implementation or
service that provides the Kafka protocol capabilities required by this section.

Consumer Delivery Model
~~~~~~~~~~~~~~~~~~~~~~~

Kafka consumers subscribe to one or more topics and normally maintain persistent broker
connections and continuous consumption of newly available records. At the Kafka
wire-protocol level, consumers use the ``Fetch`` API. A Fetch request may remain
outstanding until records become available or the configured wait expires. Subsequent
Fetch requests normally reuse the existing broker connection, allowing newly published
records to be returned with low latency without repeated connection setup or periodic
interval polling.

This model provides several properties relevant to GEISA Data Distribution, including
independent consumer pacing, retained records, replay from a previous offset, and recovery
after consumer interruption.

Where an existing system uses a push-oriented native interface, a GEISA-facing adapter
may continuously consume the Kafka stream and immediately deliver records through that
interface. The native delivery mechanism and any transformation performed after
consumption of the GEISA data record are outside the GEISA interoperability boundary.

GEISA should confirm that this continuous-consumption model satisfies operational
requirements for time-sensitive ``EVENT`` and ``ALARM`` delivery.

Kafka Protocol Baseline
~~~~~~~~~~~~~~~~~~~~~~~

GEISA will identify a Kafka protocol baseline used for interoperability and conformance
testing.

Implementations MAY support later compatible Kafka protocol versions provided they
continue to support the GEISA baseline.

The exact protocol-version baseline remains under review.

Required Kafka Protocol Operations
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The following is the initial protocol profile for discussion.

.. list-table::
   :header-rows: 1
   :widths: 24 14 25 37

   * - Kafka API or capability
     - Requirement
     - Applies to
     - Purpose
   * - ``ApiVersions``
     - MUST
     - EMS and distribution endpoint
     - Negotiate mutually supported Kafka API versions
   * - ``Metadata``
     - MUST
     - EMS and consumer
     - Discover topic and partition metadata
   * - ``Produce``
     - MUST
     - EMS producer
     - Publish GEISA Data Distribution records
   * - ``Fetch``
     - MUST
     - Distribution endpoint
     - Allow consumers to retrieve records
   * - ``ListOffsets``
     - MUST
     - Distribution endpoint
     - Locate available offsets for resume or reprocessing
   * - ``FindCoordinator``
     - MUST
     - Distribution endpoint
     - Locate the coordinator used for broker-managed consumer position
   * - ``OffsetCommit``
     - MUST
     - Distribution endpoint
     - Allow a consumer to persist its consumed position
   * - ``OffsetFetch``
     - MUST
     - Distribution endpoint
     - Allow a consumer to recover its previously committed position
   * - ``SaslHandshake``
     - Conditional
     - EMS and distribution endpoint
     - Required when the configured security profile uses Kafka SASL negotiation
   * - ``SaslAuthenticate``
     - Conditional
     - EMS and distribution endpoint
     - Required when the configured security profile uses SASL authentication
   * - ``JoinGroup``, ``SyncGroup``, ``Heartbeat``, ``LeaveGroup``
     - MAY
     - Distribution endpoint
     - Support consumer-group membership and automatic partition assignment
   * - ``DescribeGroups``, ``ListGroups`` and related group operations
     - MAY
     - Distribution endpoint
     - Support consumer-group inspection and administration
   * - ``InitProducerId``
     - MAY
     - EMS producer
     - Support idempotent or transactional producer behavior

The requirement to support ``OffsetCommit``, ``OffsetFetch``, and ``FindCoordinator``
provides a standard Kafka mechanism for an independent logical consumer to retain and
recover its position. This does not require consumers to use Kafka consumer groups for
worker scaling or automatic partition assignment.

Kafka Protocol Operations Not Required
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The following Kafka capabilities are not required for GEISA Data Distribution unless
another section explicitly makes them applicable:

.. list-table::
   :header-rows: 1
   :widths: 24 25 51

   * - Kafka API or feature family
     - Requirement
     - Reason
   * - ``CreateTopics``, ``DeleteTopics``, ``CreatePartitions``
     - Not required
     - The EMS is not required to provision Kafka infrastructure
   * - ``AlterConfigs``, ``IncrementalAlterConfigs``, related admin APIs
     - Not required
     - Kafka service administration is separate from the EMS producer role
   * - Transaction APIs
     - Not required
     - Distributed Kafka transactions and exactly-once processing are not required
   * - ACL administration APIs
     - Not required
     - The EMS uses configured authorization and is not required to administer Kafka ACLs
   * - SCRAM credential administration APIs
     - Not required
     - The EMS is not required to administer Kafka identities or credentials
   * - Broker, replica, quorum, controller, or cluster administration
     - Not required
     - Kafka infrastructure operation is outside the Data Distribution producer role
   * - Kafka Streams
     - Not required
     - Consumer-side stream-processing architecture is outside GEISA
   * - Kafka Connect
     - Not required
     - Consumer-side connector architecture is outside GEISA
   * - Share-group, Streams-group, telemetry, and other newer Kafka API families
     - Not required
     - These capabilities are not required for the Data Distribution interoperability model

Kafka-Compatible Implementations
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Kafka protocol compatibility is available from implementations other than Apache Kafka
itself. The following examples are included to support discussion and are not an
endorsement or exhaustive list.

.. list-table::
   :header-rows: 1
   :widths: 24 25 51

   * - Implementation
     - Type
     - Notes
   * - Apache Kafka
     - Open-source broker
     - Reference implementation of the Kafka protocol and API model
   * - Nisshi, formerly Tansu
     - Open-source Kafka-compatible broker
     - Apache-2.0 implementation with PostgreSQL, SQLite, S3, or memory storage options
   * - Redpanda
     - Source-available Kafka-compatible broker
     - Independent broker implementation supporting standard Kafka clients and core Kafka APIs
   * - Azure Event Hubs
     - Managed cloud service
     - Exposes a Kafka protocol endpoint without requiring an Apache Kafka cluster
   * - WarpStream
     - Kafka-compatible streaming service
     - Implements Kafka protocol operations over a substantially different storage and broker architecture

These examples demonstrate why GEISA specifies protocol behavior rather than a
particular broker product or internal architecture.

Consumer Groups
~~~~~~~~~~~~~~~

A Data Distribution consumer MAY use Kafka consumer groups to distribute records across
multiple worker instances belonging to the same logical consumer.

For example, a Vendor Application Server may run several worker processes using
one consumer group for scaling or failover.

GEISA does not require a Data Distribution consumer to use consumer groups or
prescribe its worker architecture.

Consumer groups are separate from the required support for independent logical
consumers. A Utility data-lake consumer and a Vendor Application Server consumer
must be able to consume the same Data Distribution records independently.

Distribution and Consumer Behavior
==================================

Multiple Independent Consumers
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Data Distribution SHALL permit the same distributed GEISA record to be consumed
independently by multiple authorized logical consumers.

The EMS MUST NOT publish a separate copy of a record solely because multiple
logical consumers are authorized for the same target.
Multiple authorized independent logical consumers MUST be able to maintain
independent consumption positions for the same target. Consumption, outage,
acknowledgement, or processing by one logical consumer SHALL NOT prevent another
authorized logical consumer from consuming the same retained record.

Ordering
~~~~~~~~

The ordering guarantees required by GEISA remains TBD at this point in time.

The specification should determine whether ordering is required:

* by originating Edge Device
* by application
* by Data Distribution route
* by Kafka partition
* or through another defined scope

GEISA does not require global ordering across an entire deployment unless such a
requirement is shown to be required for interoperability.

Publication and Failure Behavior
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The EMS must be able to detect whether publication to the configured Data Distribution
target succeeds or fails.

GEISA should define the minimum required behavior for:

* temporary Data Distribution endpoint unavailability
* producer retries
* duplicate records resulting from retry
* record expiration
* failures that prevent a record from being published

Detailed retry algorithms and fixed retry timing are deployment concerns unless required
for interoperability.

Consumer Interruption, Retention, and Recovery
==============================================

Data Distribution must account for temporary consumer outages without requiring the
Kafka service to become the permanent historical system of record.

Temporary Consumer Interruption
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A consumer may disconnect and later resume consumption of records that remain available
within the configured Kafka retention window.

Temporary failure of one consumer SHALL NOT affect the delivery state of another
independent consumer.

Retention
~~~~~~~~~

The Data Distribution service SHALL support configurable retention of published records
so that consumers may disconnect and later resume consumption while records remain
available.

GEISA does not prescribe a fixed retention period or storage size. The System Owner
retains authority over retention policy and the System Operator SHALL be able to
configure or approve the retention policy used by each Data Distribution target.

Kafka retention is configuration of the Data Distribution service or topic. It is not
GEISA Platform configuration and SHALL NOT be derived from ``/3606`` or ``/3607`` queue,
spool, or message TTL settings.

When the Data Distribution service is integrated with or operated as part of the EMS,
the EMS may expose the applicable retention configuration to the System Operator.

When an external Kafka-compatible service is used, the System Operator may configure
retention through that service's administrative interface before the target is placed
into service.

Reprocessing
~~~~~~~~~~~~

A consumer may reprocess data that remains available from the Kafka service.

GEISA should define only the minimum protocol capabilities needed to enable such
behavior and should not prescribe consumer-side processing or replay policy.

Historical Retrieval
~~~~~~~~~~~~~~~~~~~~

Data that is older than the Data Distribution retention window may be available through
other mechanisms, including:

* EMS query or REST APIs
* Event Log ``/20``
* utility-operated archives or data lakes
* application or Edge Device resend mechanisms where supported

Data Distribution is not required to serve as the long-term historical system of record.

Security
========

Data Distribution crosses the GEISA operational boundary and therefore requires
authenticated and encrypted communication.

GEISA must define a minimum interoperable security profile for Kafka-protocol Data
Distribution.

The security profile should address:

* encrypted transport
* authentication of the Kafka endpoint
* authentication of the EMS producer
* credential and trust configuration under System Operator control
* authorization of consumers and topics as applicable

GEISA does not require support for every security option implemented by Apache Kafka.

Insecure Kafka modes should not become mandatory merely because they are supported by
the Kafka protocol or a particular Kafka implementation.

The exact mandatory TLS and authentication mechanisms remain under review.

Operational Visibility and Failure Handling
===========================================

The System Operator needs enough visibility to determine whether Data Distribution is
operating correctly.

The implementation should expose information sufficient to determine at least:

* whether a configured Data Distribution route is enabled
* whether the configured endpoint is reachable
* whether authentication succeeds
* whether publication is succeeding or failing
* whether records are waiting for publication where buffering is implemented
* whether records have expired or been dropped
* the time of recent successful and failed Data Distribution activity

GEISA should first determine whether existing monitoring Objects can represent this
information before defining another monitoring Object or additional Resources.

Examples and Sequences
======================

Multiple Independent Consumers
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A GEISA application generates a record that reaches the EMS. The EMS publishes
the record to a configured target. Two authorized independent logical
consumers of that target, such as a utility data-lake adapter and a Vendor
Application Server, consume the same record and maintain separate positions.
This arrangement is appropriate only when both consumers are authorized to
receive every record in the target. An outage or commit by one consumer does not
affect the other.

.. figure:: data-distribution-multiple-consumers.*
   :alt: Sequence showing one published GEISA record consumed independently by two authorized logical consumers of the same target.
   :align: center

   Multiple Independent Data Distribution Consumers

Overlapping Distribution Routes
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

For example, a System Operator configures these routes:

* ``AppID = 17`` to a Vendor Application Server topic
* ``message-type = EVENT`` or ``ALARM`` to a utility operations topic
* all application-message records to a utility data-lake topic

An ``AppID = 17`` ``ALARM`` record matches all three routes and is published to
all three targets. Each record includes ``operator-identifier``, so records for
AppID 17 from different managed devices remain distinguishable even when they
use the same Vendor Application Server topic.

.. figure:: data-distribution-overlapping-routes.*
   :alt: Example showing an AppID 17 ALARM record matching vendor, utility operations, and data-lake routes, with device identity retained in each record.
   :align: center

   Overlapping Data Distribution Routes

Consumer Outage and Recovery
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A consumer becomes unavailable while the EMS continues publishing records.

The Kafka service retains records according to deployment configuration.

When the consumer returns, it resumes consumption of records that remain available.
Other independent consumers continue operating during the outage.

.. figure:: data-distribution-consumer-outage-recovery.*
   :alt: Sequence showing continued Data Distribution publication while one consumer is unavailable and later resumes from its committed position.
   :align: center

   Consumer Outage and Recovery

Platform Event Reporting
~~~~~~~~~~~~~~~~~~~~~~~~

A Platform Event Reporting sequence should be added after GEISA selects the
Platform-to-EMS event mechanism.

Candidate sequences should include an occurrence where several monitoring Resources
change as the result of one Platform action, such as restart-policy exhaustion or a
policy violation.

Open Questions
==============

The following questions remain open for review and discussion.

Platform Event Reporting
~~~~~~~~~~~~~~~~~~~~~~~~

* Which Platform occurrences require explicit event reporting rather than current state
  plus Observe/Notify?

  Possible direction: require explicit reporting only when an occurrence needs
  independent routing, durable traceability, recovery after missed notifications, or
  correlation of multiple state changes.

* Should Platform Event Reporting use ``/20`` plus LwM2M Send or a dedicated Platform
  Event Reporting Object?

  Possible direction: first determine whether a structured GEISA event representation
  fits cleanly into ``/20`` ``LogDataIncremental``.

* If ``/20`` plus Send is selected, this implies the applicable LwM2M Send behavior
  becomes mandatory/MUST for ADM.

* How should Platform-scoped ``/20`` records satisfy the mandatory AppID Resource?

  Possible direction: reserve a GEISA AppID value representing the Platform.

* What identifier is required for an edge-generated event?

  Possible direction: use an origin-scoped event identifier that is unique within the
  managed Edge Device, with the EMS retaining the originating device identity.

* Do ongoing conditions need a separate condition identifier so an assertion, update,
  and clear/recovery can be correlated?

* Is a source sequence number needed so the EMS can detect missing discrete events?

* Which existing GEISA message types apply to Platform events?

  Possible direction: reuse ``EVENT`` and ``ALARM`` initially and avoid creating another
  message-type taxonomy.

* How much new event-code vocabulary is actually required after existing reason codes,
  Platform actions, states, and other enums are reused?

* When event suppression combines repeated equivalent occurrences, what occurrence count
  or timing information must be retained?

Data Selection and Routing
~~~~~~~~~~~~~~~~~~~~~~~~~~

* Which ADM data classes must an EMS be able to route through Data Distribution, and
  which are optional?

GEISA Data Distribution Record
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* Can an existing GEISA schema serve as the common Data Distribution representation, or
  is a small Data Distribution envelope required?

* Which source identifiers are required for Data Distribution records other than
  ``/3600`` application messages?

* Which fields can be reused directly from Platform monitoring, application
  monitoring, Event Log, or other ADM Objects for non-``/3600`` records?

* Should Kafka record headers contain only transport hints while the GEISA value remains
  self-contained?

Kafka Profile
~~~~~~~~~~~~~

* Does Kafka continuous consumption provide the required behavior and latency for
  time-sensitive ``EVENT`` and ``ALARM`` delivery, or is a separate GEISA push-capable
  interface required?

* Which Kafka protocol/version baseline should GEISA require?

* Should ``FindCoordinator``, ``OffsetCommit``, and ``OffsetFetch`` remain required
  endpoint capabilities for independent consumer position and recovery, or should GEISA
  allow consumers to manage position without broker-managed offsets?

* Should Kafka consumer-group APIs be required of the distribution endpoint even though
  use of consumer groups remains optional for consumers?

* What producer acknowledgement and retry behavior is needed for GEISA interoperability?

* What ordering guarantee is required, and at what scope?

Retention and Recovery
~~~~~~~~~~~~~~~~~~~~~~

* What minimum consumer-resume behavior belongs in GEISA conformance?

* Should GEISA define a minimum retention period or storage size for
  conformance, or leave both to System Owner policy?

* At what point should consumers use EMS historical APIs, Event Log, or another system
  instead of Kafka replay?

Security
~~~~~~~~

* Which TLS and Kafka authentication mechanism or mechanisms form the mandatory
  baseline?

* Which additional Kafka security mechanisms should be optional?

* What configuration information must the EMS expose to the System Operator without
  requiring the EMS to administer the Kafka security system?

|geisa-pyramid|
