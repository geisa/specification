Platform Discovery
---------------------

|geisa-api-hdr|

Different platform implementers may choose to offer different hardware
capabilities.  With this in mind, the GEISA API provides a mechanism
for describing or enumerating the hardware platform's capabilities.  This
platform discovery capability allows the application to discover what a given
platform offers.

The Platform Discovery data is constant and not expected to change during
runtime.  Dynamic updates and state are provided in :doc:`/api/status`.
Platform Discovery metadata may be truly static, where a platform implementer
generates the platform metadata as part of a build process.  This may be true for
a fixed function device with no installation variants.  It is also possible
that a platform vendor would dynamically generate the platform metedata at time
of device installation or first boot.  This may be true if the GEISA platform
is hosted on an edge card that needs to be married to a device, or a device
whose realized capabilities may be activated as part of the installation
process.  How the platform metadata is generated is outside the scope of GEISA.
Because platform metadata is expected to be static, GEISA platforms MUST
facilitate restarting all applications if the platform metadata changes.

.. warning::

  There may be exceptional cases where this data does change such as provisioning
  the device or placing it in or out a test mode.  During those events, all GEISA
  applications MUST be restarted so they will notice the new data.

Because the Platform Discovery metadata is expected to be constant, the GEISA
platforms MUST make it available via a static file placed within the EE.  This
allows the GEISA applications to read the data using normal file I/O calls
instead of using the more complicated MQTT API Request / Response mechanism.  


Hardware and Firmware
^^^^^^^^^^^^^^^^^^^^^

The GEISA EE provides an API so that GIESA compliant applications
can query the hardware resources available:

- Device Type - returns device type, e.g. meter, ev charger, etc.
- Device Info - returns manufacturer name, model, revision, serial number(s)
- Device Firmware - returns a list of the device platform/OS firmware versions (including notable libraries and firmware)
- Operator Info - if provisioned, the operator name, and operator serial number or device identifier


.. note::

  The platform vendor determines what information is included in the Device Firmware, however GEISA mandates it MUST include at a minimum the versions of: 1) the base host OS, and 2) the GEISA platform daemon/library.


Application Information
^^^^^^^^^^^^^^^^^^^^^^^

Because an Application's Deployment Manifest may differ from the Application Manifest provided by the Application Vendor, Applications MUST be able to retrieve the Deployment Manifest as described in :doc:`/adm/manifests`.


Metrology Hardware
^^^^^^^^^^^^^^^^^^

For Meter type devices, the platform MUST provide at a minimum:

- Meter Rating/Class
- Meter Form
- Number of Phases and if Neutral connected
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


Network Hardware
^^^^^^^^^^^^^^^^

TBD


Waveform Data
^^^^^^^^^^^^^

See Metadata section in :doc:`/api/waveform`.


MQTT Details
=============

- Non Applicable.  Platform Discovery metadata is exposed through files that
  can be read using traditional file I/O processed. 
- Applications retrieve Platform Discovery metadata by reading the file `/etc/geisa/platform.binpb` within the Application container environment.
- Applications retrieve Deployment Manifest data by reading the file `/etc/geisa/manifest.json` within the Application container environment.

API Permissions
================
- Application: Read-only


Transaction Data
=================

.. warning::

  Need to add refererence to content within |geisa-schemas-repo| here.

|geisa-pyramid|
