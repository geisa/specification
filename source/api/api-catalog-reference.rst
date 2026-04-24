..
  Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
  Security Alliance (GEISA), a Series of LF Projects, LLC
  This file is licensed under the Community Specification License 1.0
  available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

API Catalog Reference
=====================

|geisa-api-hdr|

This section is not intended to be read as a narrative description of system
behavior, but to serve as a structured reference for developers
implementing or integrating with the GEISA API.

It serves as a comprehensive catalog of all defined API calls, including:

- MQTT topic structures
- Required and optional parameters
- Message payload formats
- Expected responses
- Error conditions, where applicable

GEISA APIs are implemented using MQTT topic hierarchies. Each API call is
defined by:

- The MQTT topic structure
- The direction of message flow
- The associated request and response payload definitions
- References to relevant sections of the GEISA specification that define
  relevant behavior and constraints

API Topic and Permission Catalog
--------------------------------

.. note::

   In the topic definitions below, ``<userid>`` refers to the platform-local
   identifier of the requesting GEISA application instance (see
   :doc:`/glossary`).

+--------------------------------------------------+-----------------------------------------------+------------+-------------------+------------------+-------------------------------------------+--------------+
| Category                                         | Topic                                         | Role       | Action            | Direction        | Message Name                              | Message Type |
+==================================================+===============================================+============+===================+==================+===========================================+==============+
| :doc:`Discovery <../api/discovery>`              |                                               |            |                   |                  |                                           |              |
+--------------------------------------------------+-----------------------------------------------+------------+-------------------+------------------+-------------------------------------------+--------------+
|                                                  | ``geisa/api/platform/discovery/req/<userid>`` | Application| Publish           | App → Platform   | ``GeisaPlatformDiscovery_Req``            | Request      |
+--------------------------------------------------+-----------------------------------------------+------------+-------------------+------------------+-------------------------------------------+--------------+
|                                                  | ``geisa/api/platform/discovery/rsp/<userid>`` | Application| Subscribe         | Platform → App   | ``GeisaPlatformDiscovery_Rsp``            | Response     |
+--------------------------------------------------+-----------------------------------------------+------------+-------------------+------------------+-------------------------------------------+--------------+
|                                                  | ``geisa/api/app/manifest/req/<userid>``       | Application| Publish           | App → Platform   | ``GeisaApplicationDeploymentManifest_Req``| Request      |
+--------------------------------------------------+-----------------------------------------------+------------+-------------------+------------------+-------------------------------------------+--------------+
|                                                  | ``geisa/api/app/manifest/rsp/<userid>``       | Application| Subscribe         | Platform → App   | ``GeisaApplicationDeploymentManifest_Rsp``| Response     |
+--------------------------------------------------+-----------------------------------------------+------------+-------------------+------------------+-------------------------------------------+--------------+
|                                                  | ``geisa/api/platform/discovery/req/#``        | Platform   | Wildcard Subscribe| App → Platform   | ``GeisaPlatformDiscovery_Req``            | Request      |
+--------------------------------------------------+-----------------------------------------------+------------+-------------------+------------------+-------------------------------------------+--------------+
|                                                  | ``geisa/api/platform/discovery/rsp/<userid>`` | Platform   | Publish           | Platform → App   | ``GeisaPlatformDiscovery_Rsp``            | Response     |
+--------------------------------------------------+-----------------------------------------------+------------+-------------------+------------------+-------------------------------------------+--------------+
|                                                  | ``geisa/api/app/manifest/req/#``              | Platform   | Wildcard Subscribe| App → Platform   | ``GeisaApplicationDeploymentManifest_Req``| Request      |
+--------------------------------------------------+-----------------------------------------------+------------+-------------------+------------------+-------------------------------------------+--------------+
|                                                  | ``geisa/api/app/manifest/rsp/<userid>``       | Platform   | Publish           | Platform → App   | ``GeisaApplicationDeploymentManifest_Rsp``| Response     |
+--------------------------------------------------+-----------------------------------------------+------------+-------------------+------------------+-------------------------------------------+--------------+
| :doc:`Platform Status <../api/status>`           |                                               |            |                   |                  |                                           |              |
+--------------------------------------------------+-----------------------------------------------+------------+-------------------+------------------+-------------------------------------------+--------------+
|                                                  | ``geisa/api/platform/status``                 | Application| Subscribe         | Platform → App   | ``GeisaPlatformToAppStatus``              | Broadcast    |
+--------------------------------------------------+-----------------------------------------------+------------+-------------------+------------------+-------------------------------------------+--------------+
|                                                  | ``geisa/api/platform/app/status/<userid>``    | Application| Subscribe         | Platform → App   | ``GeisaPlatformToAppStatus``              | Directed     |
+--------------------------------------------------+-----------------------------------------------+------------+-------------------+------------------+-------------------------------------------+--------------+
|                                                  | ``geisa/api/app/platform/status/<userid>``    | Application| Publish           | App → Platform   | ``GeisaAppToPlatformStatus``              |              |
+--------------------------------------------------+-----------------------------------------------+------------+-------------------+------------------+-------------------------------------------+--------------+
|                                                  | ``geisa/api/platform/status``                 | Platform   | Publish           | Platform → App   | ``GeisaPlatformToAppStatus``              | Broadcast    |
+--------------------------------------------------+-----------------------------------------------+------------+-------------------+------------------+-------------------------------------------+--------------+
|                                                  | ``geisa/api/platform/app/status/<userid>``    | Platform   | Publish           | Platform → App   | ``GeisaPlatformToAppStatus``              | Directed     |
+--------------------------------------------------+-----------------------------------------------+------------+-------------------+------------------+-------------------------------------------+--------------+
|                                                  | ``geisa/api/app/platform/status/#``           | Platform   | Wildcard Subscribe| App → Platform   | ``GeisaAppToPlatformStatus``              | Directed     |
+--------------------------------------------------+-----------------------------------------------+------------+-------------------+------------------+-------------------------------------------+--------------+
| :doc:`Networking <../api/networking>`            |                                               |            |                   |                  |                                           |              |
+--------------------------------------------------+-----------------------------------------------+------------+-------------------+------------------+-------------------------------------------+--------------+
|                                                  | ``geisa/api/message/req/<userid>``            | Application| Publish           | App → Platform   |                                           |              |
+--------------------------------------------------+-----------------------------------------------+------------+-------------------+------------------+-------------------------------------------+--------------+
|                                                  | ``geisa/api/message/rsp/<userid>``            | Application| Subscribe         | Platform → App   |                                           |              |
+--------------------------------------------------+-----------------------------------------------+------------+-------------------+------------------+-------------------------------------------+--------------+
|                                                  | ``geisa/api/message/req/#``                   | Platform   | Wildcard Subscribe| App → Platform   |                                           |              |
+--------------------------------------------------+-----------------------------------------------+------------+-------------------+------------------+-------------------------------------------+--------------+
|                                                  | ``geisa/api/message/rsp/<userid>``            | Platform   | Publish           | Platform → App   |                                           |              |
+------------------------------------------------------+-----------------------------------------------+--------+-------------------+------------------+-------------------------------------------+--------------+
| :doc:`Instantaneous Data <../api/instantaneous>` |                                               |            |                   |                  |                                           |              |
+--------------------------------------------------+-----------------------------------------------+------------+-------------------+------------------+-------------------------------------------+--------------+
|                                                  | ``geisa/api/instantaneous/data``              | Application| Subscribe         | Platform → App   | ``GeisaInstantaneousQuantities``          | Broadcast    |
+--------------------------------------------------+-----------------------------------------------+------------+-------------------+------------------+-------------------------------------------+--------------+
|                                                  | ``geisa/api/instantaneous/data``              | Platform   | Publish           | Platform → App   | ``GeisaInstantaneousQuantities``          | Broadcast    |
+--------------------------------------------------+-----------------------------------------------+------------+-------------------+------------------+-------------------------------------------+--------------+
| :doc:`Waveform Data <../api/waveform>`           |                                               |            |                   |                  |                                           |              |
+--------------------------------------------------+-----------------------------------------------+------------+-------------------+------------------+-------------------------------------------+--------------+
|                                                  | ``geisa/api/waveform/req/<userid>``           | Application| Publish           | App → Platform   | ``GeisaWaveform_Req``                     | Request      |
+--------------------------------------------------+-----------------------------------------------+------------+-------------------+------------------+-------------------------------------------+--------------+
|                                                  | ``geisa/api/waveform/rsp/<userid>``           | Application| Subscribe         | Platform → App   | ``GeisaWaveform_Rsp``                     | Response     |
+--------------------------------------------------+-----------------------------------------------+------------+-------------------+------------------+-------------------------------------------+--------------+
|                                                  | ``geisa/api/waveform/req/#``                  | Platform   | Wildcard Subscribe| App → Platform   | ``GeisaWaveform_Req``                     | Request      |
+--------------------------------------------------+-----------------------------------------------+------------+-------------------+------------------+-------------------------------------------+--------------+
|                                                  | ``geisa/api/waveform/rsp/<userid>``           | Platform   | Publish           | Platform → App   | ``GeisaWaveform_Rsp``                     | Response     |
+--------------------------------------------------+-----------------------------------------------+------------+-------------------+------------------+-------------------------------------------+--------------+
| :doc:`Sensors <../api/sensors>`                  |                                               |            |                   |                  |                                           |              |
+--------------------------------------------------+-----------------------------------------------+------------+-------------------+------------------+-------------------------------------------+--------------+
|                                                  | ``geisa/api/sensor``                          | Application| Subscribe         | Platform → App   | ``GeisaSensorReading``                    | Broadcast    |
+--------------------------------------------------+-----------------------------------------------+------------+-------------------+------------------+-------------------------------------------+--------------+
|                                                  | ``geisa/api/sensor-req/<userid>``             | Application| Publish           | App → Platform   | ``GeisaSensorReadings_Req``               | Request      |
+--------------------------------------------------+-----------------------------------------------+------------+-------------------+------------------+-------------------------------------------+--------------+
|                                                  | ``geisa/api/sensor-rsp/<userid>``             | Application| Subscribe         | Platform → App   | ``GeisaSensorReadings_Rsp``               | Response     |
+--------------------------------------------------+-----------------------------------------------+------------+-------------------+------------------+-------------------------------------------+--------------+
|                                                  | ``geisa/api/sensor``                          | Platform   | Publish           | Platform → App   | ``GeisaSensorReading``                    | Broadcast    |
+--------------------------------------------------+-----------------------------------------------+------------+-------------------+------------------+-------------------------------------------+--------------+
|                                                  | ``geisa/api/sensor-req/#``                    | Platform   | Wildcard Subscribe| App → Platform   | ``GeisaSensorReadings_Req``               | Request      |
+--------------------------------------------------+-----------------------------------------------+------------+-------------------+------------------+-------------------------------------------+--------------+
|                                                  | ``geisa/api/sensor-rsp/<userid>``             | Platform   | Publish           | Platform → App   | ``GeisaSensorReadings_Rsp``               | Response     |
+--------------------------------------------------+-----------------------------------------------+------------+-------------------+------------------+-------------------------------------------+--------------+

Sensor Payload Notes
~~~~~~~~~~~~~~~~~~~~

Sensor descriptors are represented by ``GeisaSensorDescriptor`` and are
exposed through Platform Discovery rather than Sensor runtime topics.

Published sensor readings use ``GeisaSensorReading``. Each reading
contains ``sensor_id``, ``timestamp_ms``, and one or more
``GeisaSensorValue`` entries in the repeated ``values`` field.

A sensor reading may contain multiple values. Each value is represented
by one ``GeisaSensorValue`` entry, and each entry contains exactly one
scalar field: ``double_value``, ``int64_value``, ``bool_value``, or
``string_value``.

Explicit read requests use ``GeisaSensorReadings_Req`` with a repeated
``sensor_id`` field. Explicit read responses use
``GeisaSensorReadings_Rsp`` with ``status`` and repeated ``readings``
fields.

|geisa-pyramid|


