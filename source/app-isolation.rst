
..
  Copyright 2025, Contributors to the Grid Edge Interoperability & Security Alliance (GEISA) a Series of LF Projects, LLC  
  This file is licensed under the Community Specification License 1.0 available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

Application Isolation
---------------------

.. note::

  :doc:`virtual-environment` are assumed to provide strong isolation 
  from the underlying operating system.  As a result, while VEE
  MUST support the permissions discussed in this chapter, many of the 
  technical details discussed in this chapter are specific to LEE.


GEISA applications shall be isolated from each other
for the following reasons:

- To ensure that one application cannot impact another application.
- To ensure that one application cannot see the artifacts, resources, or state of another application.

Regardless of application isolation implementation (e.g. LXC container, systemd, VEE, etc.),
an **authenticated application manifest** shall control access
to the following:

- Permissions
- Performance
- System Control
- Networking Control
- API Control


Permissions
^^^^^^^^^^^

Most if not all of the bullets below are achieved by having each app in its own isolated container.

- Apps should run in their own isolated and controlled environment, whether implemented as separate processes or sandboxes
- Apps must run with least privilege
- Apps access permissions should be deny by default
- App-to-app communication will be denied by default 
- Apps cannot access other apps memory or other resources
- Apps should not know about other apps unless explicitly informed
- Apps access to the local file-system will be isolated/restricted

Performance
^^^^^^^^^^^

GEISA isolation must meet these performance requirements:

- Apps cannot impact the performance of the system
- Apps cannot impact the stability of the system
- Apps cannot impact the performance of other apps
- Apps cannot impact the stability of other apps
- Apps cannot create denial-of-service situations
- System and non-GEISA components can have priority, but cannot consume all resources to the point of GEISA Apps starvation
- Operators MAY choose to oversubscribe CPU resources but not RAM and storage resources
- If oversubscribed, available resources must be fairly distributed between Apps

System Control
^^^^^^^^^^^^^^

The EE (LEE or VEE) shall control every aspect of an GESIA app, including:

- CPU (how much CPU allowed)
- Memory (how much RAM memory allowed)
- Persistent Storage (how mush Flash storage allowed)
- Non-Persistent Storage (how much tmpfs allowed)
- Networking (what networking interfaces and ports allowed)

Addition system control:

- App-to-app communication (**NOTE** perhaps hold off on app communication until after GEISA 1.0.0)
- Inspect and control application packet flows

Networking Control
^^^^^^^^^^^^^^^^^^

These permissions relate to controlling app access to the network.

By default, apps are not given any network access.

- Which network interfaces (none by default)
- Instantaneous Bandwidth
- Average network volume over a period (e.g. 1 hour, 24 hours)
- Direct versus Indirect Access
- Allowed destination addresses
- Allowed destination ports

API Control
^^^^^^^^^^^

These permissions relate to controlling app access to the platform.

- Metrology Access (e.g. 1-second RMS, Waveforms)
- Actuator Access (if present)
- Sensor Access (if present)
- Hardware Access (GPIO, I2C, SPI, etc.) (**NOTE** apps should almost never have hardware access except in the cases of dedicated accelerator or specific peripherals which must be passed through or proxied into the EE)
- Inter-App Communication (**NOTE** perhaps hold off on app communcation until after GEISA 1.0.0)
- Device-to-Device Communication (**NOTE** hold off until after GEISA 1.0.0)

EE Resource Management
^^^^^^^^^^^^^^^^^^^^^^

EE shall control the application's resource limits including the following:

- CPU limit (% of CPU)
- Memory Limit (in 1KiB units)
- Persistent Storage Limit (in 1KiB units)
- Non-Persistent Storage Limit (in 1KiB units)
- Allowed Network Bandwidth and Volume (in 1Kbit and 1KiB units respectively)

    - Ongoing Limit Outbound
    - Ongoing Limit Inbound
    - Burst Limit Outbound

- Allowed networking interfaces

    - HAN
    - LAN
    - FAN

- Define Application Access Levels

    - Level 0 - Read and Control - Core Features - Immutable
    - Level 1 - Read and Control - Utility
    - Level 2 - Read only

.. note::

  An Application or Deployment manifiest can be modified and re-deployed during
  an Application upgrade or administrative change.  Changes to the resource requirements
  SHOULD not require an Application restart, but an EE implementation MAY stop, modify,
  and restart an Application if necessary.

  All resource requirements can be changed including the persistent storage limit.  If
  that limit is increased, an implementation MUST honor that change and provide the
  application with a larger volume or limit without loss of persistent data.  If that
  limit is reduced, an implementation SHOULD attempt to honor that change and reduce
  the volume or limit, however if the Application is using more than the new limit
  an alarm or exception SHOULD be raised to the EMS and the action MUST be aborted
  leaving the Application running with the previous limit.
