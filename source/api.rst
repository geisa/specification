Application Programming Interface (API)
-----------------------------------------

|geisa-api-hdr|

For GEISA applications to be interoperable across multiple platforms,
the GEISA specification establishes a well-defined set of APIs between the
application and the platform implementation.  
:doc:`/api/architecture` discusses the mechanics of the API.

The GEISA API offers the transactions sets for the following purposes:

- :doc:`/api/enumeration`

    Provide the capabilities of platform, including the device type and platform 
    capabilities (e.g. available sensors, actuators, interfaces etc.)

- :doc:`/api/status`

    Provide the current status of the platform, including meter mode (normal, test, alt), 
    communications status, power status (powered, outage), and resource availability.

- :doc:`/api/instantaneous`

    Streaming one second (or better) metrology data for applications that need to 
    continuously monitor conditions, without consuming and analyzing waveform data directly.

- Billing Data

    Billing quantities generated a meter register 
    (e.g. kWh interval data, peak demand, etc.).
    These are the same values that a host meter would typically share over
    a meter-to-cash protocol like ANSI C12.18/21/22 or DLMS/COSEM.

- :doc:`/api/waveform`

    Allows applications to obtain the details on the waveform data frame definition and to 
    activate or detactivate waveform data streaming.

- Other Metering Data

    Specialized metering quantities that meters may record and that applications
    may request, but that are not so widely used as to be included in the
    Instantaneous Data transaction definition.

- Actuator Status & Control

    Allows applications to query the status of actuators, such as a remote disconnect
    switch, secondary contactor, and auxiliary relays, and, if permitted by the 
    application deployment manifest, control them.  

- :doc:`/api/sensors` 

    Exposes sensor data such as temperature, humidity, location, seismic data, vibration,
    acceleration, and light / insolation.

- Event Data

- System Messaging


.. note::

  Additional transaction sets may be added in future versions of the GEISA specification.

.. toctree::
   api/architecture
   api/enumeration
   api/status
   api/instantaneous
   api/waveform
   api/sensors

|geisa-pyramid|

