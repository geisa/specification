Platform Enumeration 
---------------------

|geisa-api-hdr|

Different platform implementers may choose to offer different hardware
capabilities.  With this in mind, the GEISA API provides a mechanism
for describing or enumerating the hardware platform's capabilities.

The Platform Enumeration data is constant and not expected to change during
runtime. Dynamic updates and state are provided in :doc:`/api/status`.

.. warning::

  There may be exceptional cases where this data does change such as provisioning
  the device or placing it in or out a test mode.  During those events, all GEISA
  applications MUST be restarted so they will notice the new data.

.. note::

  Because the Platform Enumeration data is constant, the platform MUST make
  it available via a static file placed within the EE.  This allows the GEISA
  applications to read the data using normal file I/O calls instead of using the
  more complicated MQTT API R/R mechanism.


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

Because an Application's Deployment Manifest may differ from the Application Manifest provided by the Application Vendor, Applications MUST be able to retrieve the Deployment Manifest which includes:

.. warning::

  TBD: Need to add a section on Application Manifest and Deployment Manifest content.


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

TBD

MQTT Details
=============

- N/A.
- Applications retreive Platform Enumeration data by reading the file `/opt/geisa/platform.binpb` within the Application container environment.

API Permissions
================
- Application: Read-only


Transaction Data
=================

.. warning::

  Need to add refererence to content within |geisa-schemas-repo| here.

|geisa-pyramid|
