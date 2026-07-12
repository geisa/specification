
..
  Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
  Security Alliance (GEISA), a Series of LF Projects, LLC
  This file is licensed under the Community Specification License 1.0
  available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

Application Programming Interface (API)
---------------------------------------

|geisa-api-hdr|

For GEISA applications to be interoperable across multiple hardware/device
platforms, the GEISA specification establishes a well-defined set of APIs
between the application and the device-specific portions of platform
implementation.
:doc:`/api/architecture` discusses the mechanics of the API.

:doc:`api/api-catalog-reference` provides a simple catalog of all current APIs.

The GEISA API defines APIs for the following purposes:

- :doc:`/api/discovery`

   Provides platform capabilities, including device type and available features
   (e.g., sensors, actuators, interfaces), etc.

- :doc:`/api/status`

    Provides the current status of the platform, including runtime mode (e.g.
    Manufacturing, Unprovisioned, Normal, Test), communications status, power
    status (powered, outage), and resource availability.

- :doc:`/api/response-status`

    Defines the common response status and error model used by GEISA
    request/response APIs that include ``GeisaStatus``. This model is distinct
    from the Platform/App Status notification API.

- :doc:`/api/instantaneous`

    Provides streaming metrology data at one-second intervals or better for
    applications that need to continuously monitor conditions, without
    consuming and analyzing waveform data directly.

- :doc:`/api/billing`

    Defines billing quantity payloads for meter-register-style summation and
    demand values using ``GeisaBillingQuantities``. Billing Data is distinct
    from the Instantaneous Data stream and from Waveform Data.

    This version defines the billing payload/profile structure and the
    platform-to-application Billing Data broadcast topic
    ``geisa/api/billing/data``.

    Note that this version of the specification does not define a Billing Data
    request/response transaction, historical query, or application-selected
    billing intervals.


- :doc:`/api/networking`

    Allows applications to communicate off-device via messaging or direct IP
    sockets.

- :doc:`/api/waveform`

    Allows applications to obtain waveform frame metadata and to subscribe or
    unsubscribe to waveform data streams.

- Other Metering Data

    This includes specialized metering quantities that meters may record and
    that applications may request, but that are not so widely used as to be
    included in the Instantaneous Data transaction definition.

    .. note::
       Reserved for expansion and definition in a future version of the
       specification.

- :doc:`/api/actuators`

    Allows authorized applications to query actuator status and request
    actuator control for platform-exposed actuators such as service switches,
    DER switches, and load-control relays.

- :doc:`/api/sensors`

    Exposes sensor data such as temperature, humidity, location, seismic data,
    vibration, acceleration, and light / solar radiation.  These are examples
    only; sensors are device/platform specific and other sensors may exist on
    a particular platform.

- Event Data

    .. note::
       Reserved for expansion and definition in a future version of the
       specification.

- System Messaging

    .. note::
       Reserved for expansion and definition in a future version of the
       specification.

.. note::

  Additional transaction sets may be added in future versions of the GEISA
  specification.

.. toctree::
   :hidden:

   api/architecture
   api/api-catalog-reference
   api/discovery
   api/status
   api/response-status
   api/instantaneous
   api/billing
   api/waveform
   api/actuators
   api/sensors
   api/networking


|geisa-pyramid|
