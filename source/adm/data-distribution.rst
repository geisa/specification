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

.. admonition:: Draft

   This chapter is currently in Draft and is under review.

   See :ref:`Open Questions <data-distribution-open-questions>` for unresolved decisions and open questions.

Purpose and Scope
=================

GEISA Application and Device Management provides mechanisms for moving application and
operational information between Edge Devices and an Edge Management System (EMS).
Systems operating a GEISA deployment also need an interoperable way to distribute
selected GEISA data from the EMS to other authorized systems.

Data Distribution defines the common interfaces used to make selected GEISA data
available to consumers. Note that consumer systems may be operated by the
System Owner, System Operator, Application Vendor, or other authorized parties.

GEISA defines the data and interoperability requirements through the point where an
authorized consumer receives a common GEISA data record, at which point it may transform
the data as required for its own native ingestion. Transformation into consumer-specific
formats, further routing, persistence, business-system ingestion, user interfaces, and
other consumer-side processing are outside the scope of GEISA.

Data Distribution is intended to allow independently implemented systems to consume the
same GEISA data without requiring a GEISA deployment to adopt the native schema, data
models, or implementation technology of any consuming system(s).

A typical deployment includes:

#. one or more managed Edge Devices
#. an EMS receiving application, Platform, lifecycle, monitoring, event, and
   other ADM relevant information
#. one or more Data Distribution routes configured by the System Operator
#. one or more authorized consumers of the distributed GEISA data
#. adapters or other functions that translate the GEISA data records into
   formats used by consuming systems outside of GEISA

For example, the same application data may be consumed independently by:

* a Utility-operated data lake
* an Application Vendor system used for analytics or providing a user interface, and/or
* a Utility operations system that may receive only selected events or alarms
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
data or being required to be transported through ADM/EMS systems for distribution.

Note that EMS implementations MAY expose additional interfaces, including REST APIs,
operator interfaces, query APIs, MQTT interfaces, or implementation-specific integration
mechanisms, but such interfaces do not replace the interoperable Data Distribution
requirements defined here.  Direct IP communication by Edge Applications is a separate
mechanism described elsewhere in this specification and is not part of Data
Distribution.

GEISA Data Distribution SHALL use the Apache Kafka wire protocol for interoperable
communication between an EMS and the configured Data Distribution service.

This requirement applies to protocol behavior and does not require Apache Kafka
software as part of its implementation; a conformant deployment may use Apache
Kafka or another implementation or service that provides the Kafka protocol
capabilities required by this chapter.

Data Distribution does not define a separate message-delivery control path.
Application messages being delivered to an Edge Application are defined by
:doc:`Application Messaging and Configuration </adm/messaging>`, including
Object ``/3600`` Server Message and the corresponding Server to Client
application-message API. Platform configuration is handled through
``/3607`` GEISA Platform Requested Configuration and reported through ``/3606`` GEISA
Platform Effective Configuration. Application lifecycle operations remain defined by
``/9`` Software Management, and other device or Platform management actions remain defined by the applicable ADM Objects and LwM2M operations described under :doc:`OMA Lightweight M2M </adm/lwm2m>`.

Architecture and Interoperability Boundary
==========================================

Data Distribution provides the interoperability path between GEISA data available at the
EMS and authorized consumer systems.

A Data Distribution consumer receives a common GEISA data record. Once that record has
been consumed, the consumer may transform, store, route, or otherwise process
the data as required by the receiving system(s).

.. figure:: data-distribution-highlevel.*
   :alt: High-level GEISA Data Distribution architecture showing ADM inputs, EMS Data Distribution functions, the Kafka-compatible Data Distribution service, GEISA-facing consumers, and the GEISA interoperability boundary.
   :align: center

   Data Distribution Architecture and Interoperability Boundary

The System Owner retains final authority over Data Distribution policies for a
deployment environment. The System Operator is expected to configure and operate Data
Distribution within that policy.

Data Distribution may carry information originating from several GEISA scopes. The
original GEISA record's semantics and applicable metadata SHALL be preserved, including
identifiers, message types, timestamps, priorities, reason codes, and payloads. For
example, an application message retains its AppID, message type, priority, content type,
timestamp, and other applicable GEISA metadata.

Platform-originated data similarly retains its defined source, state, severity,
reason, event type, and/or other applicable GEISA information rather than
requiring consumers to reconstruct them.

A consumer must receive enough information to interpret the distributed record without
depending on implementation-specific EMS behavior in order to ensure interoperability.

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

A GEISA Data Distribution record MUST contain the identifiers, metadata, and payload,
where applicable, needed to interpret the record without depending on Kafka topic names,
record keys, or Kafka-specific headers. This does not prohibit duplicating metadata in
Kafka headers or record keys for routing, partitioning, or other purposes.

Distribution Configuration and Topics
=====================================

The System Owner retains final authority over Data Distribution policy.
The System Operator configures Data Distribution routes, destinations, security,
and other deployment-specific behavior in accordance with System Owner policy.

A route maps selection criteria to a Data Distribution target.

Data Selection
~~~~~~~~~~~~~~

The System Operator MUST be able to select data for a route using defined GEISA
metadata, including where applicable:

* source scope or class
* :ref:`operator-identifier <operator-identifier>`
* AppID
* message type, including a set of message types
* event or record type
* Platform or component identity

Criteria MAY be combined. Routing MUST use GEISA semantics and MUST NOT require
the EMS to inspect or interpret an opaque application payload. This version does
not define a general-purpose policy language or utility-specific fleet grouping
system. Implementations MAY provide additional grouping, tag, region, device
class, or similar conveniences.

For every enabled route that matches a GEISA record, the EMS MUST publish the
record to that route's Data Distribution target. Multiple Data Distribution
routes MAY select the same GEISA record.

For example, a System Operator may configure these routes, each with its own
configured target and topic:

* all messages for ``AppID = 17`` to a Vendor Application Server target/topic
* ``message-type = EVENT`` or ``ALARM`` to a Utility Operations target/topic
* all application-message records to a Utility Data Lake target/topic

An ``AppID = 17`` ``ALARM`` record matches all three routes and is published
to each matching route's configured target. Multiple independent authorized
consumers of one target consume that target's publication independently and do
not require separate EMS publications.

Distribution Target
~~~~~~~~~~~~~~~~~~~

The System Operator MUST be able to configure a Data Distribution target.

Each configured target MUST include at least:

* enabled or disabled state
* Kafka endpoint or bootstrap server information
* target topic
* applicable security and authentication configuration

The System Operator configures Data Distribution targets under System Owner
policy. The EMS uses its configured publication targets, applicable topic names,
and producer credentials. Kafka topics, credentials, permissions, and related
broker infrastructure MAY be provisioned by an infrastructure operations team
using Kafka administration or provisioning tools. The EMS is not required to
create topics or administer Kafka infrastructure. EMS implementations MAY
provide additional administrative capabilities, but they are not required for
interoperability. The EMS MUST NOT autonomously create a topic merely because a
new consumer exists.

Kafka topic names used by GEISA Data Distribution MUST be structured.

The illustrative format ``appid.type`` uses the reverse-DNS application
identifier from the manifest for ``appid`` and an existing GEISA Message Type
for ``type``. For example, ``com.example.geisa.waveformanalyzer.ALARM``.
This is not the finalized topic grammar. Numeric OMA AppID is a separate
identifier.

.. note::

   Objects ``/20``, ``/3600``, ``/3602``, and ``/3604`` use an Unsigned Integer
   for Resource 4050 (AppID), while the application manifest represents
   ``app-id`` as a reverse-DNS string. The EMS MUST be able to resolve the
   numeric ``AppID`` to the corresponding manifest ``app-id`` using the
   originating Edge Device identity and its application deployment or
   provisioning information. Numeric AppID values are not necessarily unique
   across Edge Devices.

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

Topic subscription does not by itself grant authorization. The configured
access policy determines whether a subscribed consumer is authorized.

Kafka Record Keys
~~~~~~~~~~~~~~~~~

GEISA does not require a topic per Edge Device. Topic selection is determined by
the System Operator's route configuration. Application-message Kafka record keys
SHALL identify the originating Edge Device and application using
``operator-identifier`` and numeric ``AppID``.

Application Publishers or Application Vendors may provide integration
requirements or recommendations, but they do not control the System Operator's
Data Distribution configuration.

.. figure:: data-distribution-overlapping-routes.*
   :alt: Example showing one AppID 17 ALARM record matching three routes to a structured topic and multiple independently authorized consumers.
   :align: center

   Overlapping Data Distribution Routes

Data Distribution for Applications
==================================

Application messaging uses three distinct paths:

* Edge-to-consumer distribution: Client to Server messages from Edge Devices
  use ``/3600`` and Kafka Data Distribution to reach authorized consumers.
* External-to-Edge delivery: an authorized Vendor Application Server or Utility
  Operations client submits a message to the EMS over HTTPS POST. The EMS
  delivers it to the Edge Application through ``/3600``. See
  :doc:`Application Messaging and Configuration </adm/messaging>`.
* EMS message retrieval: an authorized Vendor Application Server or Utility
  Operations client uses HTTPS GET to retrieve the latest available matching
  message or historical messages. Request ID may be used as an optional lookup
  or filter criterion. See
  :doc:`Application Messaging and Configuration </adm/messaging>`.

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
explicitly defined GEISA transformation applies. Transformation for responses
for non-GEISA system ingestion formats occurs outside of the GEISA Data
Distribution boundary.

GEISA does not define the internal schema of an application's opaque payload,
and an EMS is not required to understand that payload. This does not prohibit
the EMS or System Operator from carrying, storing, inspecting, interpreting, or
processing it when authorized and when its content type or format is known.
Data Distribution MUST preserve the GEISA metadata required to identify and
interpret the record.

Minimum ``/3600`` Application-Message Fields
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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

Retention duration and capacity for these queries are not prescribed by GEISA;
they are determined by agreement between the Application Vendor and the
Utility/System Owner.

``DATA_DISTRIBUTION`` is not a GEISA message type. Data Distribution describes what is
done with a record, not what the record means.

For ``/3600`` application messages, the provisioned ``operator-identifier``
MUST identify the originating Edge Device within the System Operator's managed
deployment. The EMS MUST obtain or map this identifier from its managed-device
or provisioning context. ``/3`` Serial Number and the LwM2M Endpoint Name MUST
NOT be repurposed as the external application-message device identifier.

Where a record concerns an application, the existing AppID and other applicable
application identity SHOULD be retained.

Data Distribution for Platform
==============================

The GEISA Platform provides operational state and monitoring information through
several ADM Objects. Depending on the Object, this may include current state,
counters, timestamps, reason codes, lifecycle information, Platform actions,
queue or API status and/or other operational data.

Relevant ADM Objects include:

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
waveform, or sensor APIs is also not considered to be Platform operational data
solely because the Platform provides access to it.

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

Where a record concerns a Platform component, the applicable Platform or component
identity SHOULD be retained.

For Platform-scoped ``/20`` records, GEISA may reserve an AppID value to represent the
Platform. The need for such a value and its numeric assignment remain open questions.

Platform Event Reporting
~~~~~~~~~~~~~~~~~~~~~~~~

Current ADM mechanisms provide several ways to observe Platform and application
behavior:

* Read retrieves the current Resource state
* Observe and Notify can provide asynchronous notifications when selected Resource
  values change
* Monitoring Objects provide current state, counters, timestamps, latest reason codes,
  Platform actions, and other accumulated monitoring information
* Event Log Object ``/20`` provides durable event and log history
* LwM2M Send may provide unsolicited Client-to-Server reporting where GEISA makes the
  applicable behavior mandatory
* Remote logging may provide additional operational logging where configured

These mechanisms overlap but serve different purposes.

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

A single policy or lifecycle occurrence may update several independent Resources.

For example, one application policy violation might result in:

* an application policy-violation counter increasing
* an accounting or monitoring reason changing
* the application lifecycle state changing
* an exit reason being updated
* the Platform recording that it stopped or forcibly terminated the application

Individual Resource notifications do not establish that these changes all
resulted from the same occurrence.

An application may crash, restart, crash again, and eventually reach a restart limit
while the EMS is temporarily unreachable or while several state changes occur in a short
period.

The resulting monitoring state may correctly indicate that:

* the application is stopped or failed
* the restart count increased several times
* the most recent exit resulted from a crash
* the most recent Platform action stopped the application

That state does not necessarily retain the ordered sequence, occurrence time,
or reasons associated with each individual transition.

A counter can show that an event occurred one or more times, but does not
identify each occurrence.

For example, a change in an unauthorized API attempt counter can show that additional
unauthorized attempts occurred. The counter alone does not necessarily identify
each occurrence, its exact time, its subject, its reason, or an action taken in
response.

After a management communication outage, monitoring state can accurately tell the EMS
what is true now at the current point in time. Counters can also show accumulated
activity that occurred while communication was unavailable.

Those mechanisms do not nescessarily identify every discrete occurrence that took place
during the outage.

Event Log ``/20`` may provide the durable history required to fill this gap. Whether
``/20`` plus LwM2M Send is sufficient for interoperable Platform Event Reporting remains
an open design question.

Platform Event Reporting should not duplicate monitoring by generating a separate
event for every Resource transition.

Explicit event reporting is most relevant when a discrete occurrence needs one
or more of the following:

* independent routing
* durable traceability
* accounting over time
* recovery after missed notifications
* correlation of several related state changes
* preservation of occurrence-specific information not represented by current state

Platform Event Information
^^^^^^^^^^^^^^^^^^^^^^^^^^

The initial Platform Event model should contain enough information for an EMS to
identify a discrete occurrence without reconstructing it from multiple monitoring
Resources. The intent is to reuse existing GEISA fields and enumerations wherever
possible rather than define another parallel event model.

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

Note that these examples are not intended to define the final event-code set or
require every listed field for every event, but are intended to illustrate the
information that may otherwise be lost when an EMS only observes current state,
counters, or the most recent reason and action.

Existing GEISA enums and identifiers SHOULD be reused whenever possible and their
intent and semantics match.  Platform Event Reporting should not create separate
definitions for concepts already represented by GEISA message types, reason codes,
Platform actions, priorities, severities, AppIDs, Software Instance references,
or Platform component identifiers.

See :ref:`Open Questions <data-distribution-open-questions>` for unresolved Platform
Event Reporting decisions.

Event and Condition Identity
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

An Edge Device may generate event information while disconnected from its EMS.

Any origin event identifier therefore SHALL NOT require an EMS round trip before the
event can be created.

An origin event identifier may be unique only within the originating device scope. The
combination of managed-device identity and origin event identifier can identify the
event within the management domain.

Candidate Reporting Mechanisms
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

**Monitoring, Observe/Notify, and Event Log**

Current monitoring Objects provide state and accumulated monitoring information.
Observe/Notify provides timely state-change reporting, while ``/20`` provides durable
history.

This option adds the least new protocol or Object behavior but may require the EMS to
correlate several state changes in order to reconstruct one operational occurrence.

**Structured GEISA Event Records Through Event Log and LwM2M Send**

GEISA may define a structured Platform event representation stored through ``/20`` and
reported using ``LogDataIncremental`` and LwM2M Send.

This option reuses the existing Event Log and LwM2M Information Reporting mechanisms.

If this approach is selected, GEISA may need to:

* make the applicable LwM2M Send behavior mandatory
* define the structured GEISA event representation carried by ``/20``
* define how Platform-scoped records are represented when ``/20`` AppID is mandatory
* determine whether a reserved AppID value represents the GEISA Platform

**Dedicated Platform Event Reporting Object**

GEISA may define a separate Platform Event Reporting Object or equivalent ADM interface.

This provides a clear distinction between current monitoring state, durable log history,
and discrete event reporting, but adds another GEISA-defined ADM interface and should
only be selected if the existing ``/20`` and Information Reporting mechanisms cannot
meet the interoperability requirements cleanly.

**Remote Logging**

Remote logging may supplement Platform Event Reporting and provide integration with
established operational logging systems.

Remote logging alone should not be assumed to provide the structured, interoperable
GEISA event semantics required for Data Distribution.


Kafka Protocol and Operations
=============================

Consumer Delivery Model
~~~~~~~~~~~~~~~~~~~~~~~

Kafka consumers subscribe to one or more topics and normally maintain persistent
broker connections and continuous consumption of newly available records. At the
Kafka wire-protocol level, consumers use the ``Fetch`` API. A Fetch request may
remain outstanding until records become available or the configured wait
expires. Subsequent Fetch requests normally reuse the existing broker connection,
allowing newly published records to be returned with low latency without repeated
connection setup or periodic interval polling.

This model provides several properties relevant to GEISA Data Distribution,
including independent consumer pacing, retained records, replay from a previous
offset, and recovery after consumer interruption.

Where an existing system uses a push-oriented native interface, a GEISA-facing
adapter may continuously consume the Kafka stream and immediately deliver records
through that interface. The native delivery mechanism and any transformation
performed after consumption of the GEISA data record are outside the GEISA
interoperability boundary.

Kafka Protocol Baseline
~~~~~~~~~~~~~~~~~~~~~~~

Implementations MAY support later compatible Kafka protocol versions provided
they continue to support the GEISA baseline.

The exact protocol-version baseline remains under review.

Required Kafka Protocol Operations
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The table below lists the required and conditional Kafka protocol capabilities for
interoperability among the EMS producer, distribution endpoint, and consumers.

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
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Multiple Independent Consumers
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Data Distribution SHALL permit the same distributed GEISA record to be consumed
independently by multiple authorized logical consumers.

The EMS MUST NOT publish a separate copy of a record solely because multiple
logical consumers are authorized for the same target.
Multiple authorized independent logical consumers MUST be able to maintain
independent consumption positions for the same target. Consumption, outage,
acknowledgement, or processing by one logical consumer SHALL NOT prevent another
authorized logical consumer from consuming the same retained record.

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

Ordering
^^^^^^^^

Ordering guarantees for Data Distribution remain under review:

* by originating Edge Device
* by application
* by Data Distribution route
* by Kafka partition
* or through another defined scope

GEISA does not require global ordering across an entire deployment unless it is
shown to be required for interoperability.

Publication and Failure Behavior
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The EMS must be able to detect whether publication to the configured Data Distribution
target succeeds or fails. Publication failure conditions include:

* temporary Data Distribution endpoint unavailability
* producer retries
* duplicate records resulting from retry
* record expiration
* failures that prevent a record from being published

Detailed retry algorithms and fixed retry timing are deployment concerns unless required
for interoperability.

Consumer Outage and Recovery
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

A consumer becomes unavailable while the EMS continues publishing records.

The Kafka service retains records according to deployment configuration.

When the consumer returns, it resumes consumption of records that remain available.
Other independent consumers continue operating during the outage.

.. figure:: data-distribution-consumer-outage-recovery.*
   :alt: Sequence showing continued Data Distribution publication while one consumer is unavailable and later resumes from its committed position.
   :align: center

   Consumer Outage and Recovery

Consumer Interruption, Retention, and Recovery
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Data Distribution must account for temporary consumer outages without requiring the
Kafka service to become the permanent historical system of record.

A consumer may disconnect and later resume consumption of records that remain available
within the configured Kafka retention window.

Temporary failure of one consumer SHALL NOT affect the delivery state of another
independent consumer.


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

Kafka retention is a Data Distribution service concern and is separate from
``/3606`` and ``/3607`` Platform configuration. It SHALL NOT be implicitly mapped
to or derived from their queue, spool, or message TTL settings.

The Data Distribution configuration model should reuse existing GEISA concepts where
applicable without mixing EMS-side routing or Kafka-service configuration into Edge
Device Platform configuration.


These responsibilities are distinct even when an implementation uses shared storage:

.. list-table::
   :header-rows: 1
   :widths: 22 78

   * - Responsibility
     - Scope
   * - Edge buffering
     - Queue, spool, message TTL, and connectivity govern delivery from the Edge Device
       to the EMS.
   * - EMS publication buffering
     - Where implemented, buffering before successful Kafka publication retains records
       awaiting publication.
   * - Kafka retention
     - The Data Distribution service retains published records for independent consumer
       positions and recovery.
   * - EMS latest-message and historical retrieval
     - EMS query capabilities expose available messages separately from Edge buffering
       and Kafka retention.
   * - Application/Vendor storage and processing
     - Application/Vendor-side storage and processing after receipt are outside the
       GEISA Data Distribution boundary.

Retention
^^^^^^^^^

The Data Distribution service SHALL support configurable retention of published records
so that consumers may disconnect and later resume consumption while records remain
available.

GEISA does not prescribe a fixed retention period or storage size. The System Owner
retains authority over retention policy and the System Operator SHALL be able to
configure or approve the retention policy used by each Data Distribution target.

When the Data Distribution service is integrated with or operated as part of the EMS,
the EMS may expose the applicable retention configuration to the System Operator.

When an external Kafka-compatible service is used, the System Operator may configure
retention through that service's administrative interface before the target is placed
into service.

Reprocessing
^^^^^^^^^^^^

A consumer may reprocess data that remains available from the Kafka service.

Historical Retrieval
^^^^^^^^^^^^^^^^^^^^

Historical retrieval is separate from Kafka replay. The historical query time
range, response representation, and error behavior remain under review. Data that
is older than the Kafka retention window may be available through other mechanisms,
including:

* EMS query or REST APIs
* Event Log ``/20``
* utility-operated archives or data lakes
* application or Edge Device resend mechanisms where supported

Data Distribution is not required to serve as the long-term historical system of record.


Security
~~~~~~~~

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
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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

.. _data-distribution-open-questions:

Open Questions
==============

The following questions remain open for review and discussion.

Northbound ReST API
~~~~~~~~~~~~~~~~~~~

* What time-range representation and boundary semantics should historical GET use?

* What response and error behavior should GET define?

* How should ``request-id`` selection combine with the target, Message Type, and
  historical time-range criteria?

* How should the EMS report delivery failures to the originating Vendor
  Application Server?  (This would be asyncronous and presumably as a
  Platform-type message.. )

Data Selection and Routing
~~~~~~~~~~~~~~~~~~~~~~~~~~

* What configuration representation, if any, should GEISA define for Data
  Distribution routes and targets?

* Beyond /3600 Application Messaging, which ADM data sources must an EMS
  support for Data Distribution?

* When multiple routes resolve to the same Kafka endpoint and topic, should
  the EMS publish the matching record only once?

* How should structured ``appid.type`` topics handle different authorization
  scopes? For example, a vendor authorized for alarms from 500 of 10,000
  devices must not receive alarms from the remaining devices.

* Should topic names use the reverse-DNS manifest ``app-id`` or numeric OMA
  ``AppID``, and what exact naming rules should GEISA define?

GEISA Data Distribution Record
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Identity requirements for Data Distribution records other than ``/3600``
application messages remain under review.

* Can an existing GEISA schema serve as the common Data Distribution representation, or
  is a small Data Distribution envelope or other changes needed?

* Should distributed ``/3600`` records include the manifest's reverse-DNS
	``app-id`` in addition to numeric ``AppID``, so external consumers can
	identify the application without a separate mapping?

* Which source identifiers are required for Data Distribution records other than
  ``/3600`` application messages?

* Which fields can be reused directly from Platform monitoring, application
  monitoring, Event Log, or other ADM Objects for non-``/3600`` records? Do
  we need to add any additional into existing OMA objects?

Kafka Profile
~~~~~~~~~~~~~

* What, if any, delivery-latency requirements should GEISA define for
  time-sensitive ``EVENT`` and ``ALARM`` messages over Kafka?

* Which Kafka protocol/version baseline should GEISA require in the spec as minimum?

* Should ``FindCoordinator``, ``OffsetCommit``, and ``OffsetFetch`` remain required
  endpoint capabilities for independent consumer position and recovery, or should GEISA
  allow consumers to manage position without broker-managed offsets?

* Should Kafka consumer-group APIs be required of the distribution endpoint even though
  use of consumer groups currently is optional for consumers?

* What, if any, producer acknowledgement and retry behavior is needed for GEISA
  interoperability?

* What is required for publication failure, record expiration, and records that
  cannot be published?

* What ordering guarantee is required, and at what scope?

* How should application-message record keys encode ``operator-identifier`` and numeric
  (or reverse-DNS) ``AppID``?

Retention and Recovery
~~~~~~~~~~~~~~~~~~~~~~

* What minimum consumer-resume behavior belongs in GEISA conformance/mandate?

* How should consumers determine when to use EMS historical queries, Event Log, or
  another system instead of Kafka replay?

Security
~~~~~~~~

* Which TLS and Kafka authentication mechanism or mechanisms form the mandatory
  baseline?

* Which additional Kafka security mechanisms should be optional?

* What configuration information must the EMS expose to the System Operator without
  requiring the EMS to administer the Kafka security system?

Platform Event Reporting
~~~~~~~~~~~~~~~~~~~~~~~~

* Which Platform occurrences require explicit event reporting vs current state
  plus Observe/Notify?

  Possible direction: require explicit reporting only when an occurrence needs
  independent routing, durable traceability, recovery after missed
  notifications, or correlation of multiple state changes.

* Should Platform Event Reporting use ``/20`` plus LwM2M Send or a dedicated
  Platform Event Reporting Object?

  Possible direction: first determine whether a structured GEISA event
  representation fits cleanly into ``/20`` ``LogDataIncremental``.

* If ``/20`` plus Send is selected, which LwM2M Send behaviors need to become
  mandatory/MUST for ADM interoperability?

* How should Platform-scoped ``/20`` records satisfy the mandatory AppID Resource?

  Possible direction: reserve a GEISA AppID value representing the Platform.

* What identifier is required for an edge-generated event?

  Possible direction: use an origin-scoped event identifier that is unique within
  the managed Edge Device, with the EMS retaining the originating device identity.

* Do ongoing conditions need a separate condition identifier so an assertion, update,
  and clear/recovery can be correlated?

* Is a source sequence number needed so the EMS can detect missing discrete events?

* Which existing GEISA message types apply to Platform events?

  Possible direction: reuse ``EVENT`` and ``ALARM`` initially and avoid creating another
  message-type taxonomy.

* How much new event-code vocabulary, if any, is needed vs existing reason codes,
  Platform actions, states, and other enums are reused?

* Does each Platform event require explicit severity, or can severity be defined by
  the event type or Platform policy?

* When event suppression combines repeated equivalent occurrences, what occurrence count
  or timing information must be retained?

|geisa-pyramid|
