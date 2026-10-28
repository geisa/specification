..
  Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
  Security Alliance (GEISA), a Series of LF Projects, LLC
  This file is licensed under the Community Specification License 1.0
  available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

.. index:: single: Actuator Status

.. index:: single: Actuator Control

Actuator Status & Control
=========================

|geisa-api-hdr|

The actuator API allows authorized applications to query actuator state and
request actuator state changes.

Actuators are optional and platform/device-specific. Examples include a service
switch, DER switch, and load-control or auxiliary relays.

Permission and Safety Model
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

|geisa-pyramid|

Actuator Targets
----------------

This version names the following actuator targets:

- service switch
- DER switch
- load-control relays 0-3

Platforms may expose only a subset of these targets.

Future versions of this specification may add additional actuator types as
appropriate, especially as GEISA is expanded to support distribution automation
devices.

|geisa-pyramid|

Getting Actuator Status
-----------------------

The application publishes ``GeisaActuatorGet_Req`` on:

``geisa/api/actuator/get/req/<userid>``

The platform responds with ``GeisaActuatorGet_Rsp`` on:

``geisa/api/actuator/get/rsp/<userid>``

The response includes ``GeisaStatus`` and ``GeisaActuatorStatus`` values.

|geisa-pyramid|

Setting Actuator State
----------------------

The application publishes ``GeisaActuatorSet_Req`` on:

``geisa/api/actuator/set/req/<userid>``

The request may include one or more desired actuator settings.

The platform responds with ``GeisaActuatorSet_Rsp`` on:

``geisa/api/actuator/set/rsp/<userid>``

The response status indicates request outcome. A set response does not by
itself guarantee completed physical motion; applications should query current
status after a request when confirmation of state is required or desired.

|geisa-pyramid|

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

|geisa-pyramid|

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

|geisa-pyramid|

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

``GeisaActuatorStatus`` also includes an optional ``duration_s`` field, used
only in set requests. It gives the number of seconds the platform holds the new
setting before its normal control of the actuator resumes. When it is absent,
the platform holds the setting until it is changed. It is not reported in get
responses.

- A platform MUST reject a ``duration_s`` of zero with
  ``GEISA_STATUS_CODE_REQUEST_INVALID_ARGUMENT``.
- A platform that cannot hold a setting until it is changed MUST reject a
  setting without ``duration_s`` with ``GEISA_STATUS_CODE_REQUEST_UNSUPPORTED``.
- A platform that cannot hold a setting for a limited time MUST reject a setting
  with ``duration_s`` with ``GEISA_STATUS_CODE_REQUEST_UNSUPPORTED``.
- A platform MUST reject a ``duration_s`` longer than the actuator supports with
  ``GEISA_STATUS_CODE_REQUEST_OUT_OF_RANGE`` rather than shorten it.

Note that JSON examples and JSON schema are human-readable schema 
representations, while runtime API payloads are protobuf.

Reference: defined in |geisa-schemas-repo|

|geisa-pyramid|

Notes
-----

Actuator visibility and availability are platform specific and 
deployment-specific.

|geisa-pyramid|
