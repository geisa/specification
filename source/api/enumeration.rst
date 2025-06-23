Platform Enumeration 
---------------------

Different platform implementers may choose to offer different hardware
capabilities.  With this in mind, the GEISA API provides a mechanism
for describing or enumerating the hardware platform's capabilities.

Metrology Hardware
^^^^^^^^^^^^^^^^^^

Minimal **static** metrology information:

- Number of Phases
- Meter Rating
- Meter Form
- Base Frequency
- Serial Number

Minimal **dynamic RMS values** information:

- Voltage Reading, RMS
- Current Reading, RMS
- Frequency

Minimal **dynamic waveform** information:

- Voltage Reading, ADC
- Voltage Scaling, ADC
- Current Reading, ADC
- Current Scaling, ADC
- Samples/Cycle, 16, 64, 128, 256, 512, etc.
- Resolution per sample, e.g. 16-bits
- Wall Clock Time
- Monotinic Time

Sensor Hardware
^^^^^^^^^^^^^^^

A GEISA EE compliant platform can optionally
provide one or more sensors.

Some example sensors that may be provided include:

- Temperature Sensor
- Humidity Sensor
- Switch Sensor
- GPS

Hardware Enumeration
^^^^^^^^^^^^^^^^^^^^

The GEISA EE provides an API so that GIESA compliant applications
can query the hardware resources available:

- Device Info - returns device info, e.g. meter, ev charger, etc.
- CPU Info - return CPU info such as arch, number of cores, etc.
- RAM Info - return memory available to GEISA EE applciation
- Persistent Storage Info - return persistent storage info for GEISA EE application
- Non-Persistent Storage Info - return non-persistent storage info for GEISA EE application
- Network Info
- Metrology Info



