
..
  Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
  Security Alliance (GEISA), a Series of LF Projects, LLC
  This file is licensed under the Community Specification License 1.0
  available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

Platform Discovery
------------------

|geisa-api-hdr|

Different hardware platform implementers may choose to offer different 
capabilities.  With this in mind, the GEISA API provides a mechanism for 
describing or enumerating the specific hardware platform's capabilities.  This
platform discovery capability allows the application to discover what a given
platform offers.

The Platform Discovery data is constant and is not expected to change during
runtime.  Dynamic updates and state are provided in :doc:`/api/status`.
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
that the platform metadata changes.

.. warning::

  There may be exceptional cases where this data does change such as 
  provisioning the device or placing it in or out of a test or development mode.  
  During those events, all GEISA applications MUST be restarted so they will 
  be made aware of any new platform data changes.

The Platform Discovery metadata is typically the first data that a GEISA
application requires upon startup.  A GEISA applicaion may unsubscribe from the
Platform Discovery MQTT topic once data is received post-startup as that data 
will not change during the lifetime of that GEISA application's specific execution 
runtime.


Hardware and Firmware
^^^^^^^^^^^^^^^^^^^^^

The GEISA EE provides an API so that GEISA compliant applications are able to 
query the hardware resources available as follows:

- Device Type - returns device type, e.g. meter, EV charger, etc.
- Device Info - returns manufacturer name, model, revision, serial number(s)
- Device Firmware - returns a list of the device platform/OS firmware versions 
  (including notable libraries and firmware)
- Operator Information - if provisioned, the operator name and operator serial 
  number or device identifier

.. note::

   The platform vendor determines what information is included in the Device
   Firmware information. However, GEISA mandates that it MUST include, at a
   minimum, the versions of:

   #. the base host OS
   #. the GEISA platform daemon/library

Application Information
^^^^^^^^^^^^^^^^^^^^^^^

Because an Application's Deployment Manifest may differ from the Application 
Manifest provided by the Application Vendor, Applications MUST be able to 
retrieve the Deployment Manifest as described in :doc:`/adm/manifests`.


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


Waveform Data
^^^^^^^^^^^^^

See Metadata section in :doc:`/api/waveform`.


Application Deployment Manifest
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Each GEISA application may retrieve its own application deployment manifest.  This
manifest is also constant and not expected to change during runtime.

Like the Platform Discovery metadata, the Application Deployment Manifest may 
be truly static; however, it is also possible that the operator of the platform 
changes this data at runtime on an infrequent basis.

Because the Application Deployment Manifest content is expected to be static, 
GEISA platforms MUST ensure a running application is restarted in the event of 
a manifest changes.

.. warning::

  Application designers should consider the impact of placing configuration-type data
  in their application manifest to minimize the occurances where an operator needs
  to change the manifest.  Frequently updated values or parameters should be sent
  over another mechanism such as the application message based communication with
  the ADM system.


MQTT Details
============
- QoS: 1 / Acknowledged R/R
- Req Topic: ``geisa/api/platform-discovery-req`` and ``geisa/api/app-manifest-req/<userid>``
- Rsp Topic: ``geisa/api/platform-discovery-rsp`` and ``geisa/api/app-manifest-rsp/<userid>``

API Permissions
===============

- Application:

  - Publish: ``geisa/api/platform-discovery-req``
  - Subscribe: ``geisa/api/platform-discovery-rsp``
  - Publish: ``geisa/api/app-manifest-req/<userid>``
  - Subscribe: ``geisa/api/app-manifest-rsp/<userid>``

- Platform:

  - Subscribe: ``geisa/api/platform-discovery-req``
  - Publish: ``geisa/api/platform-discovery-rsp``
  - Wildcard Subscribe: ``geisa/api/app-manifest-req/*``
  - Publish: ``geisa/api/app-manifest-rsp/<userid>``

Transaction Data
================

- ``GeisaPlatformDiscovery_Req``
- ``GeisaPlatformDiscovery_Rsp``
- ``GeisaApplicationManifest_Req``
- ``GeisaApplicationManifest_Rsp``

As defined in |geisa-schemas-repo|


|geisa-pyramid|
