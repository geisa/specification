
..
  Copyright 2025, Contributors to the Grid Edge Interoperability & Security Alliance (GEISA) a Series of LF Projects, LLC  
  This file is licensed under the Community Specification License 1.0 available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

OMA Lightweight M2M
-------------------------------------

GEISA Application & Device Management uses the Open Mobile Alliance Lightweight M2M
[LWM2M]_ protocol for application management.  Specifically,

* ADM conformant platforms and Edge Management Systems (EMS) SHALL support
  LwM2M protocol version 1.2 as defined by approved revision 1.2.2 of the
  LwM2M Core and Transport specifications. [LWM2M-Core]_
  [LWM2M-Transport]_
* ADM conformant platforms and EMS are required to support only the LwM2M
  interfaces, operations, Objects, Resources, features, and behaviors made
  applicable by the GEISA specification. GEISA does not require every optional
  LwM2M feature or every Object in the OMA registry.
* ADM conformant platforms and EMS MAY support later LwM2M protocol or Object
  versions, provided they continue to support the GEISA-pinned baseline and do
  not require later-version behavior for GEISA interoperability.
* ADM conformant platforms and EMS SHALL support CoAP over UDP for
  message transport. [LWM2M-Transport]_
* ADM conformant platforms and EMS SHALL support DTLS for CoAP security.
* ADM conformant platforms and EMS SHALL support Certificate mode with EST as
  per [LWM2M-Transport]_ 5.2.4.
* ADM conformant platforms and EMS SHALL support EST over CoAP per [RFC9148]_
* ADM conformant platforms and EMS SHALL support the Bootstrap, Registration,
  Device Management and Information Reporting interfaces.
* ADM conformant platforms and EMS SHALL support the applicable Resources and
  behaviors of the required LwM2M Objects at the versions in the fixed GEISA
  ADM Object-version baseline below.
* ADM conformant EMS shall support the following LWM2M Objects


  * ID 0 -- Security
  * ID 1 -- Server
  * ID 3 -- Device
  * ID 4 -- Connectivity Monitoring
  * ID 5 -- Firmware Update
  * ID 6 -- Location
  * ID 9 -- Software Management
  * ID 10 -- Cellular Network Connectivity
  * ID 11 -- APN Connection Profile
  * ID 12 -- WLAN Connectivity
  * ID 13 -- Bearer Selection
  * ID 20 -- Event Log
  * ID 504 -- Remote SIM Provisioning
  * ID 3600 -- GEISA App Messaging
  * ID 3601 -- GEISA Host Monitoring
  * ID 3602 -- GEISA App Accounting
  * ID 3603 -- GEISA Wi-SUN Radio Management
  * ID 3604 -- GEISA App Monitoring
  * ID 3605 -- GEISA Platform Monitoring
  * ID 3606 -- GEISA Platform Configuration

* ADM conformant platforms shall support the following LWM2M Objects

  * ID 0 -- Security
  * ID 1 -- Server
  * ID 3 -- Device
  * ID 4 -- Connectivity Monitoring
  * ID 5 -- Firmware Update
  * ID 9 -- Software Management
  * ID 20 -- Event Log
  * ID 3600 -- GEISA App Messaging
  * ID 3601 -- GEISA Host Monitoring
  * ID 3602 -- GEISA App Accounting
  * ID 3604 -- GEISA App Monitoring
  * ID 3605 -- GEISA Platform Monitoring
  * ID 3606 -- GEISA Platform Configuration

* ADM conformant platforms with 3GPP network interfaces SHALL support the
  following LWM2M Objects:

  * ID 10 -- Cellular Network Connectivity
  * ID 11 -- APN Connection Profile
  * ID 13 -- Bearer Selection
  * ID 504 -- Remote SIM Provisioning

* ADM conformant platforms with WLAN interfaces SHALL support the
  following LWM2M Objects:

  * ID 12 -- WLAN Connectivity

* ADM conformant platforms with GNSS interfaces SHALL support the
  following LWM2M Objects:

  * ID 6 -- Location

* ADM conformant platforms with Wi-SUN interfaces SHALL support the
  following LWM2M Objects:

  * ID 3603 -- Wi-SUN Radio Management

GEISA ADM Object-version baseline
=================================

The following Object versions form the fixed GEISA 1.0 ADM baseline. Where an
updated definition is available, the XML link identifies the pinned definition
audited for this baseline. Pending definition updates are identified below.

.. list-table:: GEISA 1.0 ADM Object versions
   :header-rows: 1
   :widths: 10 40 15 35

   * - Object
     - Name
     - Version
     - Linked XML definition
   * - ``/0``
     - LwM2M Security
     - 1.2
     - :download:`0.xml <external/lwm2m-registry/0.xml>`
   * - ``/1``
     - LwM2M Server
     - 1.2
     - :download:`1.xml <external/lwm2m-registry/1.xml>`
   * - ``/3``
     - Device
     - 1.2
     - :download:`3.xml <external/lwm2m-registry/3.xml>`
   * - ``/4``
     - Connectivity Monitoring
     - 1.3
     - :download:`4.xml <external/lwm2m-registry/4.xml>`
   * - ``/5``
     - Firmware Update
     - 1.2
     - :download:`5.xml <external/lwm2m-registry/5.xml>`
   * - ``/6``
     - Location
     - 1.0
     - :download:`6.xml <external/lwm2m-registry/6.xml>`
   * - ``/9``
     - Software Management
     - 1.1
     - :download:`Current 9.xml <external/lwm2m-registry/9.xml>`
       (version 1.0; update pending)
   * - ``/10``
     - Cellular Network Connectivity
     - 1.1
     - :download:`10.xml <external/lwm2m-registry/10.xml>`
   * - ``/11``
     - APN Connection Profile
     - 1.1
     - :download:`11.xml <external/lwm2m-registry/11.xml>`
   * - ``/12``
     - WLAN Connectivity
     - 1.1
     - :download:`12.xml <external/lwm2m-registry/12.xml>`
   * - ``/13``
     - Bearer Selection
     - 1.1
     - :download:`13.xml <external/lwm2m-registry/13.xml>`
   * - ``/20``
     - Event Log
     - 3.2
     - :download:`20.xml <external/lwm2m-registry/20.xml>`
   * - ``/504``
     - Remote SIM Provisioning
     - 1.0
     - :download:`504.xml <external/lwm2m-registry/504.xml>`
   * - ``/3600``
     - GEISA App Messaging
     - 1.1
     - :download:`3600.xml <external/lwm2m-registry/3600.xml>`
   * - ``/3601``
     - GEISA Host Monitoring
     - 1.0
     - :download:`3601.xml <external/lwm2m-registry/3601.xml>`
   * - ``/3602``
     - GEISA App Accounting
     - 1.0
     - :download:`3602.xml <external/lwm2m-registry/3602.xml>`
   * - ``/3603``
     - GEISA Wi-SUN Radio Management
     - TBD
     - Definition pending
   * - ``/3604``
     - GEISA App Monitoring
     - 1.0
     - :download:`3604.xml <external/lwm2m-registry/3604.xml>`
   * - ``/3605``
     - GEISA Platform Monitoring
     - 1.0
     - :download:`3605.xml <external/lwm2m-registry/3605.xml>`
   * - ``/3606``
     - GEISA Platform Configuration
     - 1.0
     - :download:`3606.xml <external/lwm2m-registry/3606.xml>`

The linked Software Management ``/9`` definition is version 1.0 and does not
yet represent the GEISA 1.0 baseline requirement for version 1.1, including
Resources 19 through 22. That linked definition must be updated before GEISA
1.0 release. The Wi-SUN Radio Management ``/3603`` definition and version are
pending coordination with the Wi-SUN work and must be resolved before release.

GEISA ADM Object Model
======================

GEISA ADM uses LwM2M as the interoperable management protocol and OMA
objects as the management resource model. LwM2M defines the mechanisms
used by an EMS and a GEISA platform to discover objects, read resources,
write configuration, execute operations, and observe resources for
notifications.

GEISA ADM conformance is separate from GEISA API, LEE, and VEE
conformance. ADM object requirements therefore apply in the context of
ADM conformance and the relevant platform capability. They do not imply
that every GEISA device implements every GEISA API, every execution
environment, or every optional hardware capability. ADM implementations MAY
provide alternate or additional mechanisms for device, platform, or application
management. Such mechanisms do not replace the GEISA ADM requirements; an
implementation claiming GEISA ADM conformance SHALL support the applicable
LwM2M interfaces, operations, Objects, Resources, and behaviors defined by
this specification.

The host is not the GEISA Platform. The GEISA Platform is not an
application. A conformant ADM system needs enough visibility into all
three scopes to manage the device, operate the platform, and monitor
applications consistently.

ADM implementations should keep these distinct:

* Host / Device

  The physical or logical device, including CPU, memory, storage,
  network interfaces, firmware, power, location, connectivity, and other
  device-level resources.

* GEISA Platform

  The platform implementation that enables GEISA behavior on the device,
  including the EMA or equivalent management functions, LwM2M client,
  GEISA API services, MQTT broker, app message bridge, local monitoring
  engine, event/log service, policy enforcement, and queue or spool
  handling.

* Application

  An edge application instance running inside the LEE or VEE and subject
  to manifest-driven permissions, resource limits, lifecycle controls,
  and application-specific state.

The following list summarizes the GEISA-relevant LwM2M object model.
The list describes object purpose and boundaries only. The detailed
resource definitions, mandatory resource flags, data types, operations,
and versioning are defined by the corresponding OMA object XML files and
GEISA object definitions.

* ``/0`` Security

  Scope: ADM baseline

  Provides LwM2M security configuration and credentials required for
  secure ADM operation.

* ``/1`` Server

  Scope: ADM baseline

  Provides LwM2M server configuration, registration lifetime, binding,
  and related server behavior.

* ``/3`` Device

  Scope: Host / Device

  Provides device identity, firmware and hardware details, time, reboot,
  factory reset, storage/memory, and device-level error state. This
  object is for device-level information and controls, not application
  lifecycle, app messages, or app accounting.

* ``/4`` Connectivity Monitoring

  Scope: Host / Device

  Provides current network bearer and connectivity visibility. This
  object provides context for management connectivity and app-facing
  connectivity status, but it does not define application permissions or
  per-application quota state.

* ``/5`` Firmware Update

  Scope: Host / Device

  Provides the platform firmware update workflow. The application
  package lifecycle remains under Software Management ``/9`` and is not
  part of Firmware Update.

* ``/6`` Location

  Scope: conditional host / device capability

  Provides device or platform location when GPS, GNSS, or provisioned
  location is available through ADM.

* ``/9`` Software Management

  Scope: application lifecycle

  Provides application package download, install, activation, execution
  state where supported, uninstall, and purge behavior.

* ``/10`` Cellular Network Connectivity

  Scope: conditional network capability

  Provides cellular network and module behavior where cellular capability
  is present.

* ``/11`` APN Connection Profile

  Scope: conditional network capability

  Provides APN profile configuration and state. APN counters are bearer
  or profile-level data and do not replace GEISA per-application
  accounting.

* ``/12`` WLAN Connectivity

  Scope: conditional network capability

  Provides Wi-Fi interface configuration, state, and counters where WLAN
  capability is present.

* ``/13`` Bearer Selection

  Scope: conditional network capability.

  Provides bearer preference and selection policy where bearer selection
  is supported. This object does not replace GEISA app-message priority,
  TTL, or per-application accounting.

* ``/20`` Event Log

  Scope: durable records

  Provides durable event, log, audit, diagnostic, platform, and application
  records. Current state should be exposed through the relevant monitoring
  objects; durable history belongs here.

* ``/504`` Remote SIM Provisioning

  Scope: conditional network capability.

  Provides eSIM or eUICC profile lifecycle and remote SIM provisioning where
  supported.

* ``/3600`` GEISA App Messaging

  Scope: application / EMS bridge

  Provides an app-scoped messaging exchange and defaults surface for a specific
  application or application instance. It is intended for application-facing
  message configuration and transport metadata, not durable event history,
  accounting, runtime health, or platform configuration.

* ``/3601`` GEISA Host Monitoring

  Scope: Host / Device

  Provides host-level monitoring information used by the GEISA platform,
  including CPU, memory, storage, process, scheduler, and network interface
  observability. This object is not specific to the EMA or GEISA Platform
  services.

* ``/3602`` GEISA App Accounting

  Scope: application accounting

  Provides operations-facing application accounting and policy summary state
  for an application or application accounting scope. It exposes 
  current-period usage counters, quotas and limits, throttle, block, or
  disabled state, selected enforcement evidence, and operator or EMS/ADM action
  resources.

* ``/3603`` GEISA Wi-SUN Radio Management

  Scope: conditional network capability

  Provides Wi-SUN radio and interface management for Wi-SUN-capable platforms.

* ``/3604`` GEISA App Monitoring

  Scope: application runtime

  Provides app-scoped runtime monitoring and health visibility. It represents
  the platform view of one installed or running application instance, including
  operational health, lifecycle visibility, resource consumption, restart
  behavior, watchdog state, and platform actions.

* ``/3605`` GEISA Platform Monitoring

  Scope: GEISA Platform

  Provides platform-scoped monitoring state for GEISA-capable platform
  functions, components, services, queues, APIs, and operational paths.
  It provides an aggregate health instance, as well as allowance for
  individual component or sub-module reporting; for example, EMA and LwM2M
  client health, registration and bootstrap state, upstream reporting,
  API broker or service, or vendor-specific components.

* ``/3606`` GEISA Platform Configuration

  Scope: GEISA Platform

  Configures GEISA Platform behavior for local monitoring, reporting, logging,
  queueing, and app-message handling. It represents requested and effective
  behavior of the GEISA Platform for an edge device and is intended for
  operator or EMS-visible configuration state rather than current operational
  health. It does not carry app-domain configuration payloads; app-domain
  configuration uses the GEISA App Messaging object.
