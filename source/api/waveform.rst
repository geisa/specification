
..
  Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
  Security Alliance (GEISA), a Series of LF Projects, LLC
  This file is licensed under the Community Specification License 1.0
  available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

.. _api-waveform-data:

Waveform Data
-------------

|geisa-api-hdr|

The GEISA API exposes over the GEISA API message bus :doc:`/api/architecture`
the details on the waveform data frame definition and the ability to activate
or deactivate waveform data streaming.

Once activated, an application will receive waveform data via a dedicated
socket between the platform implementation outside of the isolated environment
and the application within the isolated environment.


Device Capabilities
^^^^^^^^^^^^^^^^^^^

GEISA applications MUST be able to query the platform to understand what forms
of waveform data are supported.  Platforms that provide waveform data MUST, at
a minimum provide:

- 128 samples per cycle (e.g 7.68kHz for 60 Hz AC or 6.4kHz for 50 Hz AC)
- 16-bit sample resolution
- data MUST be pushed at least every 200 ms
- data MUST indicate whether it is zero-crossing aligned or not
- zero-crossing aligned data MUST be aligned to the zero cross of Phase A on
  Polyphase Devices

Platforms MAY offer alternate sample rates and resolutions.
For convenience, binary multiples for samples per cycle are preferred but not
required:

- 128, 256, 512, and 16,384 samples per cycle
  (e.g. ~8 kHz, ~16 kHz, ~32 kHz, and ~1MHz, respectively)
- 32-bit sample resolution

Different devices will have a different number of capture channels, each
typically sampling a single voltage or current input.  The total number of
channels and how those are assigned may not be known at application build time
and are discoverable by querying the GEISA API message bus.

Data for all channels MUST be time-aligned to one another.  An individual sample
in channel 1 MUST have been sampled at the same time that the corresponding
samples in other channels (i.e., 2, 3, etc.) were.


.. Note::

  Devices MAY expose different waveform stream choices to applications if they
  support multiple capture frequencies or channel counts.  In this case, an
  application MUST be able to activate one or more streams simultaneously if
  desired.

.. _waveform_metadata:

Metadata
^^^^^^^^

Platform Discovery (:doc:`/api/discovery`) describes available waveform
streams and their static or semi-static characteristics. The metadata below
is provided via Platform Discovery except for application-specific runtime
access details (e.g., socket path), which are returned in the Waveform
activation response.

- The path to the data socket (returned in the Waveform activation response; not part of Platform Discovery)
- The type of data: one of int16, int32, float32, or float64
- The number of voltage channels
- The number of current channels
- The total number of channels (typically the sum of 2 items above, but MAY be larger)
- The sampling frequency in Hz
  ``sample-rate-hz`` is the authoritative samples-per-second value.
  ``samples-per-cycle`` is a nominal descriptor and applications SHALL
  interpret it together with the stream alignment fields and platform
  metadata.
- If the frames are AC cycle aligned or not (see Alignment Definitions below)
- If data type is integer, the voltage scaling factor to convert to volts
- If data type is integer, the current scaling factor to convert to amps
- The expected data frame frequency (ex: 200msec)

Alignment Definitions
^^^^^^^^^^^^^^^^^^^^^

A waveform stream is *cycle-aligned* when each frame contains an integer number
of nominal AC cycles.

A waveform stream is *zero-crossing-aligned* when frame boundaries are aligned
to a phase reference, typically the Phase A voltage zero crossing on polyphase
devices.

A stream MAY be cycle-aligned without being zero-crossing-aligned.
Zero-crossing-aligned implies a phase-reference boundary, while cycle-aligned
only describes frame duration.


Data Format
^^^^^^^^^^^

Once activated via the GEISA API, applications can then open and start receiving
data frames from a dedicated ``AF_UNIX`` family ``SOCK_SEQPACKET`` type socket.
This socket MUST be provisioned into the application's isolated environment using
a path provided in the activation API response.

``SOCK_SEQPACKET`` type sockets provide the application in-order delivery of
data that honors message boundaries and provide the sender connection-oriented
semantics.
Each socket message SHALL contain exactly one complete waveform frame; partial
frames SHALL NOT be transmitted.

The sending process in the platform constructs data frames and sends them over
this socket without serialization/deserialization. The process is suitable for
receipt directly into native data buffers for processing by the application.

The data frame is formatted as follows (example C language structure)::

   struct geisa_waveform_frame
   {
     int64_t    timestamp;       /* in millisec */
     uint32_t   sequence_num;    /* unspecified starting value, incremented every frame */
     uint32_t   reserved;
     union {
       /* variable length array of 1 of 4 data types */
       int16_t  i16[0];
       int32_t  i32[0];
       float    f32[0];
       double   f64[0];
     } data;
   };

The starting value is unspecified and the sequence number MAY reset on platform
restart or when an application re-subscribes. Applications SHALL tolerate
resets and gaps.

Notably absent from the data frame is the :ref:`waveform_metadata` listed above
as well as the frame length which is obtained from the ``recv()`` or similar
syscall.

The ``timestamp`` field MUST be the timestamp for the first sample in the frame.

The ``data`` union represents a variable length array of one of the four
supported data types.  The array size is computed as
``sample_count * total_channel_count``.

Samples within the data array MUST be ordered as follows:

- Time 0

  - All voltage channels
  - All current channels

- Time 1

  - All voltage channels
  - All current channels

- Time 2

  - All voltage channels
  - All current channels

- ... continuing for any additional time samples in the frame


A standard split phase 2S [#ansiforms]_ meter with one voltage and two current
channels (three total channels) would report its data as follows:

- Voltage Phase AB, Time 0
- Current Phase A, Time 0
- Current Phase B, Time 0
- Voltage Phase AB, Time 1
- Current Phase A, Time 1
- Current Phase B, Time 1


A standard split phase 12S meter with two voltage and two current channels
(four total channels) would report its data as follows:

- Voltage Phase A, Time 0
- Voltage Phase B, Time 0
- Current Phase A, Time 0
- Current Phase B, Time 0
- Voltage Phase A, Time 1
- Voltage Phase B, Time 1
- Current Phase A, Time 1
- Current Phase B, Time 1


For example, a polyphase meter with three voltage and three current channels
(six total channels) would report its data as follows:

- Voltage Phase A, Time 0
- Voltage Phase B, Time 0
- Voltage Phase C, Time 0
- Current Phase A, Time 0
- Current Phase B, Time 0
- Current Phase C, Time 0
- Voltage Phase A, Time 1
- Voltage Phase B, Time 1
- Voltage Phase C, Time 1
- Current Phase A, Time 1
- Current Phase B, Time 1
- Current Phase C, Time 1


A polyphase with neutral meter with three voltage and four current channels
(seven total channels) would report its data as follows:

- Voltage Phase A, Time 0
- Voltage Phase B, Time 0
- Voltage Phase C, Time 0
- Current Phase A, Time 0
- Current Phase B, Time 0
- Current Phase C, Time 0
- Current Neutral, Time 0
- Voltage Phase A, Time 1
- Voltage Phase B, Time 1
- Voltage Phase C, Time 1
- Current Phase A, Time 1
- Current Phase B, Time 1
- Current Phase C, Time 1
- Current Neutral, Time 1


MQTT Details
============

- QoS: 1 / Acknowledged R/R
- Req Topic: ``geisa/api/waveform/req/<userid>``
- Rsp Topic: ``geisa/api/waveform/rsp/<userid>``


API Permissions
===============

- Application:

  - Publish: ``geisa/api/waveform/req/<userid>``
  - Subscribe: ``geisa/api/waveform/rsp/<userid>``

.. note::

   In the topic definitions, ``<userid>`` refers to the platform-local
   identifier of the requesting GEISA application instance (see :doc:`/glossary` for
   additional information).


- Platform:

  - Wildcard Subscribe: ``geisa/api/waveform/req/#``
  - Publish: ``geisa/api/waveform/rsp/<userid>``


Transaction Data
================

- ``GeisaWaveform_Req``
- ``GeisaWaveform_Rsp``

As defined in |geisa-schemas-repo|

References
==========

.. [#ansiforms] ANSI defines a series of standard meter "forms" for the North
   American market in the ANSI C12.1 standard
   (`Code for Electricity Metering <https://webstore.ansi.org/standards/nema/ansic122024>`__).

   Each form has specific physical and electrical characteristics.

|geisa-pyramid|
