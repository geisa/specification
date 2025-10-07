Platform and App Status
-----------------------

|geisa-api-hdr|

While the :doc:`/api/enumeration` data is fixed and does not change during the life of the application, the platform uses the message bus to distribute status to all running applications.  Notifications are grouped into 2 topics: application-specific or non-application-specific.


Runtime Mode
^^^^^^^^^^^^

Devices may be changed between an normal operating mode, test modes, and similar states.  These states may not apply to a specific GEISA application, but applications can use these notifications to enable or disable their own modes, suppress errors and alarms, or connect to different cloud resources (ex: test vs production).  Runtime mode is non-application-specific.

GEISA defines the following runtime modes:

- Manufacturing
- Unprovisioned
- Normal
- Test


Urgent Platform Updates
^^^^^^^^^^^^^^^^^^^^^^^

If the platform encounters an error or edge condition it can inform GEISA applications so they can take appropriate actions. For some conditions, a GEISA application may be able to directly determine the same error or condition, but a platform notification allows for a consistent method of notification and can reduce duplication of effort between platform and applications.

A GEISA compliant implementation MUST provide at a minimum non-application-specific notifications for:

- Over temperature
- Over CPU usage
- Low Memory
- Power Degraded (individual phase loss, under voltage, etc...)
- Power Loss (running on backup power)
- Reboot Scheduled


Application Updates
^^^^^^^^^^^^^^^^^^^

GEISA applications should be made aware of their resource utilization and any events or alarms specific to their application instance.

A GEISA compliant implementation MUST provide at a minimum application-specific notifications for:

- Resource usage periodically (at least once every 15 seconds)

  - CPU usage
  - Memory usage
  - Persistent storage usage
  - Non-persistent storage usage

Connectivity Updates
^^^^^^^^^^^^^^^^^^^^

A GEISA compliant implementation MUST provide at a minimum non-application-specific notifications for:

- Message based communication:

  - status: disabled, enabled-down, or enabled-up

- Operator based IP communication:

  - status: disabled, enabled-down, or enabled-up
  - protocol: ipv4, ipv6, or both
  - latency: real-time, delayed

- Internet based IP communication:

  - status: disabled, enabled-down, or enabled-up
  - protocol: ipv4, ipv6, or both
  - latency: real-time, delayed

- Local based IP communication:

  - status: disabled, enabled-down, or enabled-up
  - protocol: ipv4, ipv6, or both
  - latency: real-time, delayed

A GEISA compliant implementation MUST provide at a minimum application-specific notifications for:

- Time of next daily volume reset

- Message based communication:

  - Previous day messages used
  - Daily messages used & remaining

- Operator based IP communication:

  - Volume state: zero, metered, unlimited
  - Previous day volume used while unlimited
  - Previous day volume used while metered
  - Daily volume used while unlimited
  - Daily volume used & remaining while metered

- Internet based IP communication:

  - Volume state: zero, metered, unlimited
  - Previous day volume used while unlimited
  - Previous day volume used while metered
  - Daily volume used while unlimited
  - Daily volume used & remaining while metered

- Local based IP communication:

  - Volume state: zero, metered, unlimited
  - Previous day volume used while unlimited
  - Previous day volume used while metered
  - Daily volume used while unlimited
  - Daily volume used & remaining while metered

MQTT Details
=============
- QoS: 0 / Unacknowledged
- Topic: ``geisa/api/app-status/<userid>``
- Topic: ``geisa/api/platform-status``

API Permissions
================

- Application:

  - Subscribe: ``geisa/api/app-status/<userid>``
  - Subscribe: ``geisa/api/platform-status``

- Platform:

  - Publish: ``geisa/api/app-status/<userid>``
  - Publish: ``geisa/api/platform-status``


Transaction Data
=================

.. warning:: 
  
  Need to add reference to content within |geisa-schemas-repo| here.




|geisa-pyramid|
