
..
  Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
  Security Alliance (GEISA), a Series of LF Projects, LLC
  This file is licensed under the Community Specification License 1.0
  available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

.. _api-platform-discovery:
.. index:: single: Platform Discovery

Platform Discovery
------------------

|geisa-api-hdr|

Different hardware platform implementers may choose to offer different
capabilities.  With this in mind, the GEISA API provides a mechanism for
describing or enumerating the specific hardware platform's capabilities.  This
platform discovery capability allows the application to discover what a given
platform offers in order to potentially adjust behavior, or just for logging
and awareness purposes.

The Platform Discovery data is typically constant and is not expected to
change during an application's runtime execution.  It SHOULD be retrieved
by a GEISA application during startup after the application becomes
operational.  Although the Platform Discovery content is platform-wide rather than
application-specific, it is retrieved using application-instance request/response
topics so that each running application instance can obtain the current
discovery snapshot for its device without broadcasting responses to other 
applications that may still be subscribed.

After receiving this data, an application MAY unsubscribe from the Platform
Discovery response topic for the remainder of that execution instance, as the
data will not change during runtime.

Applications MUST re-run Platform Discovery on each startup; if platform
capabilities change, the platform will restart applications so they retrieve
an updated snapshot during startup.

Dynamic updates and state are provided in :doc:`/api/status`.

Platform Discovery metadata may be truly static, where a platform implementer
generates the platform metadata as part of a build process.  This may be true,
for example, for a fixed function device with no installation variants.  It is
also possible that a platform vendor may dynamically generate the platform
metadata at the time of device installation or first boot.  This may be true if
the GEISA platform is hosted on an edge card that needs to be married to a
device, or a device whose realized capabilities may be activated as part of the
installation process.  How the platform metadata is generated is outside the
scope of GEISA.  However, because platform metadata is expected to be static,
GEISA platforms MUST facilitate restarting all running applications in the event
that the platform metadata changes; applications will be shut down by the platform
and subsequently started with the updated Platform Discovery responses, so on startup
applications are again aware of any changes/current platform capabilities.


Hardware, Firmware, and Platform Software
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The Platform Discovery API includes the following data so applications are able to
determine the realized hardware and software environment available on the device:

- Device Type - returns the type of the device or module, e.g. electric meter,
  EV charger, etc.
- Device Info - returns manufacturer name, model, revision, serial number(s)
- Device Firmware - returns a list of the device platform/OS firmware versions
  (including notable libraries and firmware and versions)
- Platform Software Environment - returns notable platform software and runtime
  components and their versions
- Operator Information - if provisioned, the operator name and operator-assigned
  device identifier.  If the device is not provisioned to an operator, the
  Operator Information MAY be omitted from the Platform Discovery response.

.. note::

   The platform vendor determines what information is included in the Device
   Firmware information. However, GEISA mandates that it MUST include, at a
   minimum, the versions of:

   #. the base host OS/RTOS
   #. the GEISA API implementation
   #. the GEISA execution environment(s) in use (LEE, VEE, or both), where implemented

|geisa-pyramid|

Application Information
^^^^^^^^^^^^^^^^^^^^^^^

Because an application's Deployment Manifest may differ from the Vendor
Application Manifest originally supplied by the application vendor,
applications MUST be able to retrieve their own current Application Deployment
Manifest as described in :doc:`/adm/manifests`.

|geisa-pyramid|

.. index:: single: Metrology Hardware

Metrology Hardware
^^^^^^^^^^^^^^^^^^

For Meter type devices, the platform MUST provide at a minimum:

- Meter Rating/Class
- Meter Form
- Number of Phases and if Neutral is connected
- Nominal Phase Angle
- Nominal Frequency
- Nominal Phase-to-Phase and Phase-to-Neutral Voltage (when applicable)

|geisa-pyramid|

.. index:: single: Sensor Hardware

Sensor Hardware
^^^^^^^^^^^^^^^

A GEISA EE conformant platform can optionally provide one or more sensors.

Some example sensors that may be provided include:

- Temperature Sensor and Alarm
- Humidity Sensor
- Switch Sensor
- Orientation or Motion/Vibration Sensor
- GNSS

Note this list is not exhaustive, and specific sensor types and accuracy will
be device-dependent.

Platform Discovery MAY include a list of available sensor descriptors so that
applications can enumerate which sensors exist on the platform at startup.
Runtime sensor readings and application-directed sensor queries are defined by
the Sensors API (:doc:`/api/sensors`).

|geisa-pyramid|

.. index:: single: Network Hardware

Network Hardware
^^^^^^^^^^^^^^^^

This version of the GEISA specification provides information
regarding the network interfaces supported by the platform, but only at an
abstract level.  Details like maximum transmission units, data rates, or
specific technologies are not provided.  GEISA network discovery provides
details on the class of network, the owner of the network, and the type of
technology.  These may be useful for applications to tune the type and/or
volume of data that they transmit over interfaces they been granted permission
to use.

``NetworkClass`` specifies whether a network is a ``local``, ``operator``, or
``internet`` network.  ``operator`` networks are assumed to be controlled by
the system operator (typically a utility or DSO).  ``local`` networks are local
to the deployed device and often used for interactions with other devices, such
as smart inverters or EVSE.  ``internet`` networks provide access to the public
internet, and may be useful for accessing cloud services.

``NetworkOwner`` specifies whether a network is owned by the system operator, a
consumer or a third party.  The distinction between system operator and third
party may be helpful so that applications can moderate their network usage on
public carrier networks which may have pay-per-byte rates or usage caps.
Similarly, applications may have logic to limit the volumes or types of data
sent over consumer networks.  

``NetworkTechnology`` specifies the general type of network technology is use.
These include:

-   Radio Frequency Mesh
-   Cellular
-   Ethernet
-   Fiber
-   WiFi
-   Power Line Carrier

Because these technologies can have quite different data rates,
``NetworkTechnology`` should not inform application behaviors with respect to
data rates.  Typically, the system operator will set appropriate per
application quotas in the application manifest, which the application should
use to determine its network communication strategy.  ``NetworkTechnology`` is
more useful for determining things like message retry strategies.

Each ``Network_Instance`` provided through :doc:`/api/discovery` also includes
whether the interface supports IPv4, IPv6, or both, as well as optional names
and descriptions for the available interfaces.

Implementations SHOULD NOT assume behavior, interfaces, or data structures
beyond what is explicitly defined in this specification.  Applications SHALL
assume that network permissions and volume restrictions described in its
Deployment Manifest are valid and realizable on the device. 

|geisa-pyramid|

.. index:: single: Waveform

Waveform Discovery
^^^^^^^^^^^^^^^^^^

Platform Discovery describes the available waveform streams and their
characteristics. Platforms that support waveform data SHALL expose a baseline
waveform stream with the identifier ``waveform-base``.

Discovery SHALL include only static metadata. Applications SHALL use waveform 
metadata to interpret a stream and SHALL NOT infer stream characteristics by 
parsing the stream identifier.

Runtime access details and application-specific state are defined by 
the :doc:`/api/waveform` API.

|geisa-pyramid|

.. index:: single: Application Manifest

Application Deployment Manifest
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Each GEISA application may retrieve its own Application Deployment Manifest.  This
manifest is also constant and not expected to change during runtime.

Like the Platform Discovery metadata, the Application Deployment Manifest may
be truly static; however, it is also possible that the operator of the platform
changes this data at runtime on an infrequent basis.

Because the Application Deployment Manifest content is expected to be static,
GEISA platforms MUST ensure a running application is restarted in the event of
a manifest change.

.. warning::

  Application designers should consider the impact of placing configuration-type data
  in their application manifest to minimize the occurences where an operator needs
  to change the manifest.  Frequently updated values or parameters should be sent
  over another mechanism such as the application message based communication with
  the ADM system.

|geisa-pyramid|

MQTT Details
============
- QoS: 1 / Acknowledged R/R
- Req Topic: ``geisa/api/platform/discovery/req/<userid>`` and ``geisa/api/app/manifest/req/<userid>``
- Rsp Topic: ``geisa/api/platform/discovery/rsp/<userid>`` and ``geisa/api/app/manifest/rsp/<userid>``

.. note::

   In the topic definitions, ``<userid>`` refers to the platform-local
   identifier of the requesting GEISA application instance (see :doc:`/glossary` for
   additional information).

   The MQTT topics for geisa/api/app/manifest/* are used to retrieve the
   Application Deployment Manifest for the requesting application instance.


API Permissions
===============

- Application:

  - Publish: ``geisa/api/platform/discovery/req/<userid>``
  - Subscribe: ``geisa/api/platform/discovery/rsp/<userid>``
  - Publish: ``geisa/api/app/manifest/req/<userid>``
  - Subscribe: ``geisa/api/app/manifest/rsp/<userid>``

- Platform:

  - Wildcard Subscribe: ``geisa/api/platform/discovery/req/#``
  - Publish: ``geisa/api/platform/discovery/rsp/<userid>``
  - Wildcard Subscribe: ``geisa/api/app/manifest/req/#``
  - Publish: ``geisa/api/app/manifest/rsp/<userid>``

Transaction Data
================

- ``GeisaPlatformDiscovery_Req``
- ``GeisaPlatformDiscovery_Rsp``
- ``GeisaAppDeploymentManifest_Req``
- ``GeisaAppDeploymentManifest_Rsp``

As defined in |geisa-schemas-repo|


|geisa-pyramid|
