
..
  Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
  Security Alliance (GEISA) a Series of LF Projects, LLC
  This file is licensed under the Community Specification License 1.0 available
  at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

.. index:: single: Application Messaging

Application Messaging and Configuration
---------------------------------------

|geisa-adm-hdr|

GEISA LwM2M Object ``/3600`` provides messaging between the EMS and Edge
Applications through separate Server to Client and Client to Server resources.
Each Object Instance represents one application messaging scope identified by
resource ``4050`` AppID and, where applicable, a managed application instance.

Object ``/3600`` carries application-message payloads, configuration, and
transport metadata.

Server to Client messages are written to resource ``0`` Server Message. They
typically carry app-facing configuration, commands, or other application
payloads from an authorized Vendor Application Server, EMS, or operator
workflow to the Edge Application. An ADM-conformant Platform receiving a
Server Message SHALL route the message payload and associated message metadata
to the application or application instance identified by resource ``4050`` AppID
through the corresponding GEISA Server to Client application-message API,
subject to authorization, routing policy, application lifecycle state, and
platform policy.

Client to Server messages are exposed through resource ``1`` Client Message
and are typically consumed by the EMS or other authorized endpoints. They
typically carry command results, status, events, alarms, application data,
telemetry, or effective configuration state sent by the Edge Application.
An ADM-conformant EMS MUST obtain these messages and their associated metadata
using the applicable LwM2M mechanisms.

Vendor Application Server to Edge Application
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

An ADM-conformant EMS MUST provide a ReST API that allows an authorized Vendor
Application Server to submit a message for delivery to an Edge Application.
All EMS ReST APIs, including the required application-message POST endpoint and
any additional operations, MUST use HTTPS.
The request MUST identify the target using its provisioned
:ref:`operator-identifier <operator-identifier>`
and AppID. The EMS obtains or maps ``operator-identifier`` from its
managed-device and provisioning context; the Edge Application does not need to
include this identifier in the application message.

An ADM-conformant EMS MUST accept POST requests at:

.. code-block:: text

   POST /geisa/adm/v1/devices/{operator-identifier}/apps/{appid}/messages

Requests MUST use HTTP ``Content-Type: application/json``. The request body
MUST conform to ``schemas/geisa-app-message-req-schema.json`` and carry the
GEISA application-message envelope, including ``payload-base64`` for the opaque
application payload. The envelope's ``content-type`` describes the application
payload; the HTTP Content-Type describes the JSON request.

The EMS MUST preserve ``request-id`` for correlation and synchronously indicate
whether it accepted or rejected the message for delivery. Acceptance does not
mean the Edge Application received, processed, accepted, or acted on the
message.

The EMS MUST return the following HTTP response codes as applicable:

.. list-table:: POST response status codes
   :header-rows: 1
   :widths: 18 24 58

   * - Status
     - Name
     - Meaning
   * - ``202``
     - Accepted
     - The EMS accepted responsibility for delivery
   * - ``400``
     - Bad Request
     - The request is malformed or its JSON body does not conform to the message schema
   * - ``401``
     - Unauthorized
     - Authentication is missing or invalid
   * - ``403``
     - Forbidden
     - The authenticated caller lacks permission
   * - ``404``
     - Not Found
     - The target Edge Device or application was not found
   * - ``405``
     - Method Not Allowed
     - The HTTP method is unsupported for the requested endpoint; the EMS MUST
       include an ``Allow`` header listing supported methods
   * - ``413``
     - Content Too Large
     - The request exceeds the applicable size limit
   * - ``415``
     - Unsupported Media Type
     - The HTTP request media type is unsupported
   * - ``429``
     - Too Many Requests
     - An applicable request rate or request quota limit was exceeded
   * - ``500``
     - Internal Server Error
     - An unexpected EMS failure prevents request processing
   * - ``503``
     - Service Unavailable
     - The EMS is temporarily unable to accept the message

For resources whose existence is sensitive, the EMS MUST NOT distinguish
unauthorized access from nonexistence and MAY return ``404`` for either.

EMS implementations MAY provide additional ReST operations. POST is the only
operation required for GEISA interoperability at this time.

Message Priority values are:

.. list-table::
   :header-rows: 1
   :widths: 12 20 68

   * - Value
     - Priority
     - Description
   * - ``0``
     - Unspecified
     -
   * - ``1``
     - Urgent
     - highest priority; send immediately when possible
   * - ``2``
     - Immediate
     - high priority; send as soon as possible
   * - ``3``
     - BestEffort
     - normal priority; send when resources are available
   * - ``4``
     - Latest
     - lowest priority; retain/send only the latest applicable message.  When a
       "Latest" message is received, older messages of the same type for the
       same AppID may be superseded/dropped.
   * - ``5`` through ``100``
     - Reserved
     - Reserved for future GEISA use
   * - ``101`` through ``254``
     - Reserved
     - Reserved for proprietary use
   * - ``255``
     - Reserved
     -

Message Type values are:

.. list-table::
   :header-rows: 1
   :widths: 12 20 68

   * - Value
     - Type
     - Description
   * - ``0``
     - ``UNSPECIFIED``
     - message type is not specified or not yet classified
   * - ``1``
     - ``CONFIG``
     - app-facing desired or effective configuration state
   * - ``2``
     - ``COMMAND``
     - action request to perform work now or soon
   * - ``3``
     - ``COMMAND_RESULT``
     - result of a ``COMMAND`` execution, distinct from transport-level response acceptance
   * - ``4``
     - ``STATUS``
     - current state, lifecycle, readiness, mode, or policy/quota state
   * - ``5``
     - ``EVENT``
     - operationally meaningful occurrence worth recording or routing
   * - ``6``
     - ``ALARM``
     - actionable, high-severity, security, safety, or policy condition
       requiring prompt attention or special handling
   * - ``7``
     - ``APP_DATA``
     - supplemental application-specific data that intentionally does not fit
       ``CONFIG``, ``COMMAND``, ``STATUS``, ``EVENT``, ``ALARM``,
       ``COMMAND_RESULT``, or ``TELEMETRY``
   * - ``8``
     - ``TELEMETRY``
     - measurement-oriented numeric or structured observations, usually
       time-series, snapshot, interval, or resource metrics
   * - ``9`` through ``100``
     - Reserved
     - Reserved for future GEISA use
   * - ``101`` through ``254``
     - Reserved
     - Reserved for proprietary use
   * - ``255``
     - Reserved
     -

Each app message is associated with Message Priority, Message Type, Message
TTL, Content Type, Request ID, and Message Timestamp metadata. These resources
describe the current application message; they do not provide durable message
history. The Platform and EMS use this metadata to classify, schedule, route,
retain, expire, correlate, and interpret app-message payloads exchanged through
resource ``0`` or resource ``1``.

For the GEISA application-message envelope, ``request_id``, ``priority``,
``message_type``, ``timestamp_us``, ``ttl_seconds``, and ``content_type`` map to
resources ``6``, ``2``, ``3``, ``7``, ``4``, and ``5``, respectively. The
``payload`` bytes appear once in resource ``0`` for Server to Client or resource
``1`` for Client to Server; the complete envelope is not encoded inside the
opaque message Resource.

Object ``/3600`` carries Edge Application configuration between the Edge
Application and authorized Vendor Application Servers or operator systems. A
Server to Client message with Message Type ``CONFIG`` may carry desired
application configuration, or request current configuration. A Client to
Server message with Message Type ``CONFIG`` or
``STATUS`` may carry application-reported effective configuration,
configuration status, or configuration-related state.

Object ``/3600`` does not define the internal schema of an application
configuration payload. The payload format is identified by Content Type and is
interpreted according to the application, operator, or deployment contract.
Acceptance of a Server Message by the ADM path does not by itself prove that
the application accepted or applied the configuration. Application-level
acceptance, rejection, effective state, or error detail should be reported
through an appropriate app message, status, event, alarm, or durable record.

Manifest and deployment policy define what an application is allowed to do;
Object ``/3600`` carries app-facing configuration payloads within those
permissions and platform policies.

.. list-table::
   :header-rows: 1
   :widths: 10 18 12 15 45

   * - Resource ID
     - Name
     - Operation
     - Data Type
     - Description
   * - ``4050``
     - AppID
     - ReadWrite
     - Unsigned Integer
     - System-unique identifier for the logical application within the applicable management domain.
   * - ``4051``
     - Software Instance
     - Read
     - Objlnk
     - Link to the corresponding LwM2M Software Management ``/9`` instance.
   * - ``0``
     - Server Message
     - Write
     - Opaque
     - Server to Client app-message payload.
   * - ``1``
     - Client Message
     - Read
     - Opaque
     - Client to Server app-message payload.
   * - ``2``
     - Message Priority
     - ReadWrite
     - Unsigned Integer
     - Per-message priority for ordering, scheduling, throttling, or delivery.
   * - ``3``
     - Message Type
     - ReadWrite
     - Unsigned Integer
     - Per-message payload classification.
   * - ``4``
     - Message TTL
     - ReadWrite
     - Unsigned Integer
     - Per-message time-to-live, in seconds.
   * - ``5``
     - Content Type
     - ReadWrite
     - String
     - Media type for the app-message payload encoding.
   * - ``6``
     - Request ID
     - ReadWrite
     - String
     - Sender-assigned identifier preserved across application-message transport.
   * - ``7``
     - Message Timestamp
     - ReadWrite
     - Unsigned Integer
     - UTC epoch timestamp, in microseconds, when the sender created the message.

.. figure:: app-messaging-data.*

  Edge App Message Reporting

.. figure:: app-messaging-config.*

  Edge App Message Delivery

|geisa-pyramid|
