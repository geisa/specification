
..
  Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
  Security Alliance (GEISA), a Series of LF Projects, LLC
  This file is licensed under the Community Specification License 1.0
  available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

Hardware Expectations
---------------------

The GEISA specification is written to align with the hardware
already in use by platform vendors serving electric utilities.
This version of the specification refers to hardware *expectations*,
rather than hardware *requirements*, because it does not require
binary compatibility. [#]_  Neverthless, it is important to define
the expected hardware deployment platform, as it informs a variety
of design decisions.

A full GEISA conformant platform, including ADM, API, and LEE or VEE 
interoperability conformance, should be realizable on:

- ARMv7 CPU with NEON extensions
- 512 MB of RAM
- 1 GB of Flash
- One (or more) network interfaces
- One (or more) metrology interfaces

.. note::

    For the LEE, as this version of the specification does *not* require binary 
    compatibility, but is limited to source-code compatibility only for LEE 
    GEISA applications, platform implementers MAY choose to use alternate CPUs 
    and/or fewer resources for the LEE.
    
Platform implementers should be aware that:

- It MAY NOT be possible to implement a fully conformant (ADM, API, and EE) 
  platform on a device with fewer resources
- If GEISA is extended to include binary compatibility in the future, alternate
  architectures will likely create additional management work for end users 
  (VEE GEISA applications are agnostic to underlying CPU architecture, but are
  source-code compatible only in GEISA 1.0.)

The vision is that the GEISA EE |geisa-ee-globe| runs on a wide range of 
hardware platforms with various capabilities:

- Device types such as smart meters, load switches, EV chargers, etc.
- Single and multi-core CPUs
- Support for processor extensions and coprocessors such as GPUs  
- RAM sizes greater than the minimum 512MB target
- Storage sizes greater than the minimum 1 GB target
- Multiple networking interfaces such as mesh, Wi-Fi, cellular, etc.
- Metrology interfaces to provide voltage, current, etc.
- Actuators such as relays and contactors
- Sensors including temperature, humidity, location, vibration and more
- Hardware watchdogs
- Generic hardware interfaces such as GPIO, ADC, SPI, etc.

Platform providers offering a GEISA EE |geisa-ee-globe| MUST provide a 
toolchain which allows application developers to build applications written for 
the GEISA EE. [#]_


Metrology
^^^^^^^^^

GEISA specifically addresses edge computing enviroments used by electric 
utilities.  It is assumed there is a source of metrological data available on 
GEISA devices.  The GEISA API |geisa-api-gear| provides a mechanism for GEISA 
applications to obtain details regarding the metrological capabilities of the 
device (see :doc:`api/discovery`)

.. note::

    The GEISA API is not expected to provide metrological information when used 
    on a non-metrological device; however, some platforms without local 
    metrology MAY support providing remote metrological data through their 
    local GEISA API

Metrological hardware, at a minimum, should be able to provide: [#]_

- Instantaneous RMS Voltage Reading
- Instantaneous RMS Current Reading
- Frequency

When coupled with a billing register, metrological hardware may also be able 
to provide derived quantities such as demand values, cummulative values, and 
interval values.

Metrological hardware may also be able to provide waveform data.  See 
:doc:`api/waveform` for additional details.  

When waveform data is provided, at a miminum, it SHALL provide:

- 128 samples per cycle (7.68 kHz at 60 Hz AC frequency)
- 16 bits per sample

Platforms may provide higher sampling rates (e.g. 128, 256, 512, 16,384 samples 
per cycle or more) and greater sampling resolution (e.g. 32 bits per sample).

Depending on the device, waveform data may be provided for voltage, current, or 
both.  Waveform data may be split-phase, phase-to-phase, or phase-to-neutral.  
The GEISA API allows applications to obtain details about the waveform data 
available on the platform so that they can correctly interpret the information 
the platform exposes through the API.

Sensors
^^^^^^^

A GEISA platform MAY optionally provide access to one or more sensors.
Sensors are exposed through the GEISA API |geisa-api-gear|.

Examples of sensors that may be provided include:

- Temperature Sensor
- Humidity Sensor
- Switch Sensor
- GPS
- Vibration / accelerometer

Actuators
^^^^^^^^^

A GEISA platform MAY optionally provide one or more actuators.  Actuators are 
exposed through the GEISA API |geisa-api-gear|.

Examples of actuators that may be provided include:

- Service disconnect switch
- DER disconnect switch
- Demand response relay

|geisa-pyramid|

.. [#] Future versions of the GEISA specification may require binary 
    compatibility, though it is likely this will only be done in conjunction 
    with a GEISA community reference implementation.

.. [#] GEISA LEE specifically assumes a GNU/Linux environment 
   (see :doc:`lee/operating-system`), such that it is likely that the tool chain 
   in use is open-source.  If a vendor is using a commercial tool chain, there 
   is no requirement that the platform vendor provide a license; however, they 
   MUST provide information regarding where third parties can purchase the 
   necessary tool chain and the version of the tool chain in use, and they must 
   provide any supporting files required to allow the tool chain to be used to 
   compile applications for their platform.

.. [#] Note: inductively powered devices, such a remote fault indicators, may 
   lack a ground reference and thus may be unable to provide voltage data.  
   Similarly, some devices may lack a current sensor and may thus be limited 
   to voltage only.  Electric meters are expected to be able to provide both.

|geisa-pyramid|


