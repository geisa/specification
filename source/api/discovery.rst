
..
  Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
  Security Alliance (GEISA), a Series of LF Projects, LLC
  This file is licensed under the Community Specification License 1.0
  available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

.. _api-platform-discovery:

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
change during an application's runtime execution.  It MUST be retrieved
by a GEISA application during startup after the application becomes
operational.  Although the Platform Discovery content is platform-wide rather than
application-specific, it is retrieved using application-instance request/response
topics so that each running application instance can obtain the current
discovery snapshot for its device.

After receiving this data, an application MAY unsubscribe from the Platform
Discovery response topic for the remainder of that execution instance, as the
data is not expected to change during runtime.

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
applications are again aware of any changes/current platform capbilities.

.. warning::

  There may be exceptional cases where this data does change such as
  provisioning the device or placing it in or out of a test or development mode.
  During those events, all GEISA applications MUST be restarted so they will
  be made aware of any new platform data changes.  In this case, the platform
  environment is the one managing the shutdowns and subsequent application start.



Hardware, Firmware, and Platform Software
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The GEISA EE provides an API so that GEISA compliant applications are able to
query the realized hardware and software environment available on the device as
follows:

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

   #. the base host OS
   #. the GEISA API implementation
   #. the GEISA platform runtime environment in use, such as LEE or VEE where implemented

Application Information
^^^^^^^^^^^^^^^^^^^^^^^

Because an application's Deployment Manifest may differ from the Vendor
Application Manifest originally supplied by the application vendor,
applications MUST be able to retrieve their own current Application Deployment
Manifest as described in :doc:`/adm/manifests`.


Metrology Hardware
^^^^^^^^^^^^^^^^^^

For Meter type devices, the platform MUST provide at a minimum:

- Meter Rating/Class
- Meter Form
- Number of Phases and if Neutral is connected
- Nominal Phase Angle
- Nominal Frequency
- Nominal Phase-to-Phase and Phase-to-Neutral Voltage (when applicable)


Sensor Hardware
^^^^^^^^^^^^^^^

A GEISA EE compliant platform can optionally provide one or more sensors.

Some example sensors that may be provided include:

- Temperature Sensor and Alarm
- Humidity Sensor
- Switch Sensor
- Orientation or Motion/Vibration Sensor
- GPS

Note this list is not exhaustive, and specific sensor types and accuracy will
be device-dependent.

Network Hardware
^^^^^^^^^^^^^^^^

.. admonition:: Status: Reserved for Future Definition
   :class: tbd-section

   This section is intentionally incomplete as of this version of the GEISA
   specification. The requirements and definitions associated with this section
   remain under review and will be defined in a future revision of this
   specification.

   Implementations SHALL NOT assume any behavior, interface, or data structure
   beyond what is explicitly defined elsewhere in this specification.

Waveform Discovery
------------------

Platform Discovery describes available waveform streams and their
characteristics. Platforms that support waveform data SHALL expose a baseline 
waveform stream with the identifier ``waveform-full``.  Discovery SHALL 
include only static or semi-static metadata.
Runtime access details and application-specific state are not included here and
are defined by the Waveform Data API.

Waveform Data
^^^^^^^^^^^^^

See Metadata section in :doc:`/api/waveform`.


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

  - Subscribe: ``geisa/api/platform/discovery/req/<userid>``
  - Publish: ``geisa/api/platform/discovery/rsp/<userid>``
  - Wildcard Subscribe: ``geisa/api/app/manifest/req/#``
  - Publish: ``geisa/api/app/manifest/rsp/<userid>``

Transaction Data
================

- ``GeisaPlatformDiscovery_Req``
- ``GeisaPlatformDiscovery_Rsp``
- ``GeisaApplicationDeploymentManifest_Req``
- ``GeisaApplicationDeploymentManifest_Rsp``

As defined in |geisa-schemas-repo|


|geisa-pyramid|
