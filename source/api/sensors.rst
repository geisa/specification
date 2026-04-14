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

Sensor Discovery Model
----------------------

The GEISA platform exposes available sensors through
:doc:`Platform Discovery <../api/discovery>`.

Each sensor descriptor includes:

- a platform-local sensor identifier
- a GEISA-defined sensor type or category
- the engineering unit used for reported values
- whether the sensor supports explicit read
- whether the sensor supports platform-driven publication

This specification defines GEISA sensor types for interoperability.
Platforms shall use a GEISA-defined sensor type whenever an applicable
type exists.

Platforms may provide additional implementation-specific refinement,
such as subtype or other descriptive metadata, but such refinement does
not replace the GEISA sensor type.

If no applicable GEISA-defined sensor type exists, the platform may use
an implementation-specific custom type as defined by the corresponding
schema (see ``geisa-sensor-schema.json``) and protobuf definitions
(see ``sensor.proto``).

This approach preserves interoperability across platforms while still
allowing future and platform-specific sensors to be integrated into the
system.

If available, the platform may also provide identifying information
about the sensor such as manufacturer or model which are desired but not 
required to aid in troubleshooting and debugging purposes for both the 
application vendors and operators.

A platform implementation may also provide implementation-specific descriptive
metadata, such as a display name or reporting periodicity, as defined
by the corresponding message schema.

Runtime Data Model
~~~~~~~~~~~~~~~~~~

Runtime sensor messages carry current or recently observed values for
one or more sensors. A runtime sensor observation should include, at
minimum:

- the platform-local sensor identifier
- a timestamp indicating when the reading was generated
- the value of the observation
- the engineering unit associated with that value

The runtime value model is intentionally generic so that unknown or
future sensor types can be added without requiring a new GEISA API
for each sensor class.

Example Sensor Types
~~~~~~~~~~~~~~~~~~~~

This specification does not require a fixed exhaustive set of sensor
types. Implementations as well as specific devices may expose sensor 
types supported by the platform, provided they are represented through the 
generic sensor contract.

A temperature sensor is used as the primary example in this section.

Example platform-local identifiers include:

- ``board_temp1`` for internal board or electronics temperature
- ``ambient_temp1`` for ambient or enclosure temperature

For example, a platform may expose:

- ``board_temp1`` using engineering unit ``C``
- ``ambient_temp1`` using engineering unit ``C``

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

- ``GeisaSensorReadings_Req``
- ``GeisaSensorReadings_Rsp``
- ``GeisaSensorReading``

Notes
=====

- Sensor descriptors are exposed through :doc:`Discovery <../api/discovery>`
  rather than through the Sensor runtime topics
- Published sensor update frequency is determined by the platform and sensor
  policy, not independently by each subscribing application
- The current generic runtime value model is scalar. Some sensor types,
  such as geolocation, may require richer structured value support in future 
  versions of the GEISA specification

References
~~~~~~~~~~

- :doc:`Discovery <../api/discovery>`
- :doc:`Instantaneous Data <../api/instantaneous>`
- :doc:`Waveform Data <../api/waveform>`
- :doc:`Platform Status <../api/status>`