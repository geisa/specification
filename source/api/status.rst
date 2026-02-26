
..
  Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
  Security Alliance (GEISA), a Series of LF Projects, LLC
  This file is licensed under the Community Specification License 1.0
  available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

Platform and App Status
-----------------------

|geisa-api-hdr|

While the :doc:`/api/discovery` data is fixed and does not change during the
life of the application, the platform uses the message bus to distribute status
to all running applications.  Notifications are grouped into 2 topics:
application-specific or non-application-specific.


Runtime Mode
^^^^^^^^^^^^

Devices may be changed between a normal production operating mode, test modes, and 
similar states.  These states may not apply to a specific GEISA application, but 
applications can use these notifications to enable or disable their own modes or
behaviors, suppress errors and alarms, or connect to different cloud resources 
(e.g., connect to test vs production service instances).  Runtime mode is 
non-application-specific and determined solely by the device.

GEISA defines the following runtime modes:

- Manufacturing
- Unprovisioned
- Normal
- Test


Urgent Platform Updates
^^^^^^^^^^^^^^^^^^^^^^^

If the platform encounters an error or edge condition it can inform GEISA 
applications so they can take appropriate actions. For some conditions, a GEISA 
application may be able to directly determine the same error or condition, but 
a platform notification allows for a consistent method of notification and can 
reduce duplication of effort between platform and applications.

A GEISA compliant implementation MUST provide at a minimum non-application-specific 
notifications for:

- Over temperature
- High CPU usage
- Low Memory
- Power Degraded (individual phase loss, under voltage, etc...)
- Power Loss (running on backup power)
- Reboot Scheduled
- Shutdown Scheduled

When an application receives one of these updates it MAY take an action but 
SHALL continue operating until a separate application shutdown request is 
received, if any.  The platform will send these updates periodically (at least 
once per minute) for as long as the condition persists.  The platform SHOULD 
send a notification at least once after all events are cleared.


Application Updates
^^^^^^^^^^^^^^^^^^^

GEISA applications should be made aware of their own resource utilization and 
any events or alarms or commands specific to their application instance.

A GEISA-compliant implementation MUST provide at a minimum application-specific 
notifications for:

- Resource usage periodically (at least once every 15 seconds)

  - CPU usage
  - Memory usage
  - Persistent storage usage
  - Non-persistent storage usage

- Commands for the application to perform

  - Send status to platform immediately
  - Shut down application cleanly
  - Clear PII from application memory, persistent, and non-persistent storage, if any

The platform MAY send a message to the application to start a shutdown over the 
message bus, OR it MAY invoke the stop command described in the application 
manifest.  These two methods are considered equivalent and the platform SHOULD 
invoke one or the other.  In either case, this request is advisory giving the 
application the ability to cleanly shutdown such as saving state or data to 
persistent storage, closing open network connections, flushing logs, etc.  
Once ready for termination, the application responds with a status message (if 
the shutdown request was made via message), or the stop command will complete 
(if the shutdown request was made via stop command).


Application Status
^^^^^^^^^^^^^^^^^^

GEISA platforms expect to know the status and health of each application in 
order to manage their lifecycle and availability.

A GEISA-compliant implementation MUST accept at a minimum application-specific 
messages for:

- Notification that an application startup is complete and now operating
- Current application status (running, shutting down)
- Notification that an application is shut down (due to a shutdown request) 
  and ready for termination
- Request from an application to terminate itself then restart
- Request from an application to terminate itself without restart

Upon startup of the application, it MUST send a notification to the platform 
that it is now operating and its status is RUNNING. In this message, the 
application MAY specify if it requires the platform to implement a 
keepalive/watchdog mechanism.  If so, the application SHALL also send its 
application status periodically (at a period specified in the most recent 
message).  If the application does not require a keepalive/watchdog mechanism, 
it MAY omit a timeout value.

If the platform does not receive a status message within the specified timeout 
period it MUST take the following corrective actions:

- Send a message to the application requesting its status
- If the application does not respond within a second timeout period, run the 
  stop command specified in the application manifest
- If the stop command itself times out (as defined in the application manifest), 
  terminate the application
- Restart the application using the start command as defined in the application 
  manifest



Connectivity Updates
^^^^^^^^^^^^^^^^^^^^

A GEISA compliant implementation MUST provide at a minimum non-application-specific 
notifications for:

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

A GEISA compliant implementation MUST provide at a minimum application-specific 
notifications for:

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
============
- QoS: 0 / Unacknowledged
- Topic: ``geisa/api/platform-status``
- Topic: ``geisa/api/platform-app-status/<userid>``
- Topic: ``geisa/api/app-platform-status/<userid>``

API Permissions
===============

- Application:

  - Subscribe: ``geisa/api/platform-status``
  - Subscribe: ``geisa/api/platform-app-status/<userid>``
  - Publish: ``geisa/api/app-platform-status/<userid>``

- Platform:

  - Publish: ``geisa/api/platform-status``
  - Publish: ``geisa/api/platform-app-status/<userid>``
  - Subscribe: ``geisa/api/app-platform-status/*``


Transaction Data
================

.. warning:: 
  
  Need to add reference to content within |geisa-schemas-repo| here.




|geisa-pyramid|
