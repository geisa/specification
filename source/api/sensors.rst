..
  Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
  Security Alliance (GEISA), a Series of LF Projects, LLC
  This file is licensed under the Community Specification License 1.0
  available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

Sensors
-------

|geisa-api-hdr|

The GEISA Sensors API provides access to non-streaming, lower-rate
sensor data available to edge applications. It supports both
request/response for explicit reads and platform-driven
publish/subscribe updates.

High-frequency or streaming sensor data is handled separately by the
:doc:`Waveform <../api/waveform>` API.

GEISA maintains clear boundaries between APIs while allowing for future
sensor types to be integrated as needed. The Sensors API is intended for
discrete or periodic measurements, while higher-frequency data is handled
by other APIs.

The GEISA platform exposes available sensors through 
:doc:`Platform Discovery <../api/discovery>`.  Applications typically retrieve
discovery information once during startup after becoming operational. Discovery
information is treated as static for the lifetime of an application instance. 
If the platform's sensor inventory or sensor capabilities change, the platform 
restarts applications so they may repeat the discovery process and adapt if 
needed to the new environment.

For Sensors API topics that include ``<userid>``, ``<userid>`` is a
platform-local identifier for the deployed GEISA application instance.
It is used for topic routing and local correlation and is not a human
user identifier. See :doc:`/glossary`.

The Sensors API supports two interaction patterns:

#. request/response, for explicit read or refresh of one or more sensor
   values
#. publish/subscribe, for platform-driven publication of current sensor
   observations to authorized subscribers

Reporting cadence for published sensor data is determined by platform
and sensor policy, not independently by each subscribing application.

Sensor data access is subject to platform policy, including topic and
message-bus access control.

Scope
=====

The Sensors API covers lower-rate, semantically typed sensor observations. It
does not include waveform or high-frequency streaming sensor types.

Sensor descriptors are discovery-oriented metadata. Runtime readings are
transported separately from descriptors. A generic runtime value model enables
support for unknown or future sensors without defining a separate GEISA API for
every sensor class.

Sensor Discovery Model
----------------------

This specification defines GEISA sensor types for interoperability.
Platforms shall use a GEISA-defined sensor type whenever an applicable
type exists.

The GEISA platform exposes available sensors through
:doc:`Platform Discovery <../api/discovery>`.

Each sensor descriptor is represented by ``GeisaSensorDescriptor`` and
includes:

- ``sensor_id`` (required): platform-local unique identifier for the
  sensor
- ``sensor_type`` (required): GEISA-defined interoperable sensor type
- ``custom_sensor_type`` (conditional): required when ``sensor_type`` is
  ``GEISA_SENSOR_TYPE_CUSTOM``
- ``sensor_subtype`` (optional): platform-specific refinement of the
  sensor type
- ``unit`` (required): engineering unit used for reported values
- ``supports_read`` (required): whether explicit read is supported
- ``supports_publish`` (required): whether platform-driven publication is
  supported (the platform is capable of pushing sensor data without
  explicit read requests; updates may be periodic or event-driven;
  configuration of publishing behavior is implementation-specific as 
  of this version of the specification)
- ``min_report_period_ms`` (optional): minimum reporting period
- ``max_report_period_ms`` (optional): maximum reporting period
- ``model`` (optional): model identifier, useful for troubleshooting
- ``name`` (optional): platform-defined display name
- ``description`` (optional): platform-defined description
- ``manufacturer`` (optional): manufacturer name, useful for
  troubleshooting
- ``geolocation`` (optional): geospatial metadata for the sensor or
  hosting device

The ``unit`` field defines the engineering unit used for reported values. For
sensors that return a single value, it is the expected unit for that value
unless overridden in the runtime reading. For sensors that return multiple
values in a single reading, ``unit`` applies only when all returned values
share the same unit as of this version of the specification. When multiple 
values have different meanings or units, the interpretation SHALL be defined 
by the sensor descriptor, sensor subtype, or platform-specific documentation. 
This may be revised in a future specification version.

Platforms shall use a GEISA-defined sensor type whenever an applicable type
exists. If no applicable GEISA-defined sensor type exists, a platform may use
``GEISA_SENSOR_TYPE_CUSTOM`` together with ``custom_sensor_type``.

Optional platform-specific refinements, such as ``sensor_subtype`` or other
descriptive metadata, does not replace the GEISA sensor type.

The platform may provide identifying information such as manufacturer
or model to aid in troubleshooting and debugging.

A platform implementation may also provide implementation-specific descriptive
metadata, such as a display name or reporting periodicity, as defined
by the corresponding message schema.

This approach preserves interoperability across platforms while still
allowing future and platform-specific sensors to be integrated into the
system.

Geolocation Metadata
====================

``GeisaGeolocation`` is an optional descriptor metadata field for a sensor or 
hosting device. It contains:

- ``latitude``
- ``longitude``
- ``altitude_m``: optional altitude in meters

This geolocation metadata represents the device or sensor position in the field 
and is distinct from service point address, customer address, or any
PII-associated data.

Geolocation is descriptor metadata only. It is not currently used as a runtime
sensor value payload in this version of the specification. Runtime geolocation
sensor readings may require a structured value model extension in a future
version of the GEISA specification.

Sensor Type Enumeration
=======================

The ``GeisaSensorType`` enumeration defines the following GEISA-defined sensor types for
interoperability:

+----------------------------------------+-------+-----------------------------------------------+
| Name                                   | Value | Notes                                         |
+========================================+=======+===============================================+
| ``GEISA_SENSOR_TYPE_UNSPECIFIED``      | 0     | Unspecified sensor type                       |
+----------------------------------------+-------+-----------------------------------------------+
| ``GEISA_SENSOR_TYPE_TEMPERATURE``      | 10    | Environmental / physical measurement          |
+----------------------------------------+-------+-----------------------------------------------+
| ``GEISA_SENSOR_TYPE_HUMIDITY``         | 20    | Environmental / physical measurement          |
+----------------------------------------+-------+-----------------------------------------------+
| ``GEISA_SENSOR_TYPE_PRESSURE``         | 30    | Environmental / physical measurement          |
+----------------------------------------+-------+-----------------------------------------------+
| ``GEISA_SENSOR_TYPE_VOLTAGE``          | 40    | Electrical measurement, non-meter             |
+----------------------------------------+-------+-----------------------------------------------+
| ``GEISA_SENSOR_TYPE_CURRENT``          | 50    | Electrical measurement, non-meter             |
+----------------------------------------+-------+-----------------------------------------------+
| ``GEISA_SENSOR_TYPE_POWER``            | 60    | Electrical measurement, non-meter             |
+----------------------------------------+-------+-----------------------------------------------+
| ``GEISA_SENSOR_TYPE_ENERGY``           | 70    | Electrical measurement, non-meter             |
+----------------------------------------+-------+-----------------------------------------------+
| ``GEISA_SENSOR_TYPE_CONTACT_STATE``    | 80    | State / event-oriented sensor                 |
+----------------------------------------+-------+-----------------------------------------------+
| ``GEISA_SENSOR_TYPE_TAMPER``           | 90    | State / event-oriented sensor                 |
+----------------------------------------+-------+-----------------------------------------------+
| ``GEISA_SENSOR_TYPE_TILT``             | 100   | Motion / physical condition                   |
+----------------------------------------+-------+-----------------------------------------------+
| ``GEISA_SENSOR_TYPE_VIBRATION``        | 110   | Motion / physical condition                   |
+----------------------------------------+-------+-----------------------------------------------+
| ``GEISA_SENSOR_TYPE_GEOLOCATION``      | 120   | May require structured runtime value support  |
+----------------------------------------+-------+-----------------------------------------------+
| ``GEISA_SENSOR_TYPE_MICRO_ARC``        | 130   | Generic first-pass classification             |
+----------------------------------------+-------+-----------------------------------------------+
| ``GEISA_SENSOR_TYPE_SEISMIC``          | 140   | Generic first-pass classification             |
+----------------------------------------+-------+-----------------------------------------------+
| ``GEISA_SENSOR_TYPE_CUSTOM``           | 500   | Use only when no GEISA-defined type applies   |
+----------------------------------------+-------+-----------------------------------------------+

Runtime Data Model
==================

Runtime sensor messages carry current or recently observed readings. A
runtime sensor reading is represented by ``GeisaSensorReading`` and
includes:

- ``sensor_id`` (required): sensor identifier, matching a discovered
  descriptor
- ``timestamp_ms`` (required): UTC epoch time in milliseconds when the
  reading was generated
- ``values`` (required): one or more ``GeisaSensorValue`` entries for the
  observation
- ``unit`` (optional): unit override for the reading
- ``quality`` (optional): quality indicator
- ``status`` (optional): status text, such as ``OK`` or ``WARNING``

Most sensors will likely provide a single value, but some sensors may provide
multiple related values at the same timestamp. When multiple values are
returned, their meaning and ordering SHALL be defined by the sensor descriptor,
sensor subtype, or platform-specific documentation until a future GEISA version
may define a richer structured model.

For single-value readings, ``unit`` overrides the descriptor unit. For
multi-value readings, ``unit`` is only appropriate when all values share the
same unit. Otherwise, unit interpretation SHALL be defined by the sensor
descriptor, sensor subtype, or platform-specific documentation.

The runtime value model is intentionally generic so that unknown or
future sensor types can be added without requiring a new GEISA API
for each sensor class.

Sensor Value Model
==================

``GeisaSensorValue`` is a generic scalar value model. Each value entry contains
exactly one of the following fields:

- ``double_value``
- ``int64_value``
- ``bool_value``
- ``string_value``

Each individual value remains scalar in this version. A reading may contain one
or more values. Future GEISA revisions may introduce richer structured types for
self-describing multi-value observations.

Informational mapping guidance:

- ``double_value``: temperature, humidity, pressure
- ``int64_value``: voltage, current, energy
- ``bool_value``: contact-state, tamper
- ``string_value``: fallback, vendor-defined, or custom values

Read Request and Response
=========================

``GeisaSensorReadings_Req`` requests one or more sensor readings. It
contains a repeated ``sensor_id`` field. An empty list MAY be interpreted
as a request for all readable sensors accessible to an application.

``GeisaSensorReadings_Rsp`` returns zero or more sensor readings. It
includes:

- ``status`` (required): ``GeisaStatus`` result status
- ``readings`` (required): zero or more ``GeisaSensorReading`` entries

--------------


Example Sensor Types
~~~~~~~~~~~~~~~~~~~~

This specification does not require a fixed exhaustive set of sensor
types. Implementations as well as specific devices may expose sensor 
types supported by the platform, provided they are represented through the 
generic sensor contract.

Example platform-local identifiers include:

- ``board_temp1`` for internal board or electronics temperature
- ``ambient_temp1`` for ambient or enclosure temperature

For example, a platform may expose:

- ``board_temp1`` with ``sensor_type`` set to
  ``GEISA_SENSOR_TYPE_TEMPERATURE`` and engineering unit ``C``
- ``ambient_temp1`` with ``sensor_type`` set to
  ``GEISA_SENSOR_TYPE_TEMPERATURE`` and engineering unit ``C``

MQTT Details
============

- QoS: 0 / Unacknowledged
- Topic: ``geisa/api/sensor``
- Topic: ``geisa/api/sensor-req/<userid>``
- Topic: ``geisa/api/sensor-rsp/<userid>``

.. note::

   In the topic definitions, ``<userid>`` refers to the platform-local
   identifier of the requesting GEISA application instance (see :doc:`/glossary`
   for additional information).

API Permissions
===============

- Application:

  - Subscribe: ``geisa/api/sensor``
  - Publish: ``geisa/api/sensor-req/<userid>``
  - Subscribe: ``geisa/api/sensor-rsp/<userid>``

- Platform:

  - Publish: ``geisa/api/sensor``
  - Subscribe: ``geisa/api/sensor-req/#``
  - Publish: ``geisa/api/sensor-rsp/<userid>``

Transaction Data
================

- ``GeisaSensorDescriptor``
- ``GeisaSensorValue``
- ``GeisaSensorReading``
- ``GeisaSensorReadings_Req``
- ``GeisaSensorReadings_Rsp``
- ``GeisaGeolocation``

as defined in |geisa-schemas-repo|

Notes
=====

- Sensor descriptors are exposed through :doc:`Discovery <../api/discovery>`
  rather than through the Sensor runtime topics.
- Published sensor update frequency is determined by the platform and sensor
  policy, not independently by each subscribing application.
- Runtime readings contain one or more scalar values. The meaning and ordering
  of multi-value readings are not yet self-describing in the schema.
- Some sensor types, such as geolocation, may require richer structured runtime
  value support in future versions of the GEISA specification.

References
==========

- :doc:`Discovery <../api/discovery>`
- :doc:`Instantaneous Data <../api/instantaneous>`
- :doc:`Waveform Data <../api/waveform>`
- :doc:`Platform Status <../api/status>`

|geisa-pyramid|
