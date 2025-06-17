Hardware Requirements
---------------------

.. note::

    The original text specified an ARMv7 platform with
    512MB or RAM and 1GB of flash. However the text
    below focused on the GEISA EE environment instead
    of the lower-layer hardware platform.

As a **source-code interoperabiilty** specification,
the underlying hardware must ensure
that that it supports the GEISA EE.

The vision is that GEISA EE runs on 
a wide range of hardware platforms with various capabilities:

- Device type such as smart meter, load switch, EV charger, etc.
- Processor architectures such as ARM32, ARM64, RV32, RV64, AMR64, etc.
- Single core and multi core
- RAM sizes from 512MB and higher
- Storage sizes from 1GB and higher
- Networking Interfaces such as mesh, Wi-Fi, celluar, etc.
- Metrology Interfaces to provide voltage, current, etc.
- Hardware Interfaces such as GPIO, ADC, SPI, etc.
- Hardware Watchdog

A given hardware platform must provide a tool-chain
for buidling the GEISA EE,
along with the necessary hardware resources.

Metrology Hardware
^^^^^^^^^^^^^^^^^^

One of the primary targets for the GEISA EE is on smart electric meters,
hence the need for a standardize interface to metrology information.

.. note::

    A GEISA EE environment is not expected to provide metrology info
    when used on a non-metrology device.

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



