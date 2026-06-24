..
  Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
  Security Alliance (GEISA), a Series of LF Projects, LLC
  This file is licensed under the Community Specification License 1.0
  available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

Actuator Status & Control
=========================

|geisa-api-hdr|

Summary
-------

The actuator API allows authorized applications to query actuator state and
request actuator state changes.

Actuators are optional and platform/device-specific. Examples include a service
switch, DER switch, and load-control or auxiliary relays.

Permission and safety model
---------------------------

Access to actuator status and control is governed by deployment manifest policy
and platform policy.

A platform MUST reject unauthorized actuator requests.

A platform MAY reject otherwise well-formed requests if the actuator is
unavailable, unsupported, malfunctioning, unsafe to operate, interlocked,
administratively disabled, or otherwise denied by policy.

This API defines message structure and request/response behavior. It does not
define detailed utility switching workflows, sequencing, tariff behavior,
customer notice behavior, or physical interlock behavior.

Actuator targets
----------------

This version names the following actuator targets:

- service switch
- DER switch
- load-control relays 0-3

Platforms may expose only a subset of these targets.

Future versions of this specification may add additional actuator types as
appropriate, especially as GEISA is expanded to support distribution automation
devices.

Getting actuator status
-----------------------

The application publishes ``GeisaActuatorGet_Req`` on:

``geisa/api/actuator/get/req/<userid>``

The platform responds with ``GeisaActuatorGet_Rsp`` on:

``geisa/api/actuator/get/rsp/<userid>``

The response includes ``GeisaStatus`` and ``GeisaActuatorStatus`` values.

Setting actuator state
----------------------

The application publishes ``GeisaActuatorSet_Req`` on:

``geisa/api/actuator/set/req/<userid>``

The request may include one or more desired actuator settings.

The platform responds with ``GeisaActuatorSet_Rsp`` on:

``geisa/api/actuator/set/rsp/<userid>``

The response status indicates request outcome. A set response does not by
itself guarantee completed physical motion; applications should query current
status after a request when confirmation of state is required or desired.

MQTT Details
------------

QoS: 1 / Acknowledged R/R

Get:

- request: ``geisa/api/actuator/get/req/<userid>``
- response: ``geisa/api/actuator/get/rsp/<userid>``

Set:

- request: ``geisa/api/actuator/set/req/<userid>``
- response: ``geisa/api/actuator/set/rsp/<userid>``

.. note::

   In the topic definitions, ``<userid>`` refers to the platform-local
   identifier of the requesting GEISA application instance (see :doc:`/glossary` for
   additional information).

API Permissions
---------------

Application permissions:

- Publish ``geisa/api/actuator/get/req/<userid>``
- Publish ``geisa/api/actuator/set/req/<userid>``
- Subscribe ``geisa/api/actuator/get/rsp/<userid>``
- Subscribe ``geisa/api/actuator/set/rsp/<userid>``

Platform permissions:

- Wildcard Subscribe ``geisa/api/actuator/get/req/#``
- Wildcard Subscribe ``geisa/api/actuator/set/req/#``
- Publish ``geisa/api/actuator/get/rsp/<userid>``
- Publish ``geisa/api/actuator/set/rsp/<userid>``

Transaction Data
----------------

Actuator payloads are defined by:

- ``GeisaActuatorGet_Req``
- ``GeisaActuatorGet_Rsp``
- ``GeisaActuatorSet_Req``
- ``GeisaActuatorSet_Rsp``
- ``GeisaActuatorStatus``

``GeisaActuatorStatus`` includes discrete state and optional position fields.
Position is meaningful only for actuator types and platforms that support a
position or analog setting. Where position is not present, applications should
rely on discrete state and response status.

Note that JSON examples and JSON schema are human-readable schema 
representations, while runtime API payloads are protobuf.

Reference: defined in |geisa-schemas-repo|

Notes
-----

Actuator visibility and availability are platform specific and 
deployment-specific.

|geisa-pyramid|
