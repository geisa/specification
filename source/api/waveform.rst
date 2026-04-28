..
   Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
   Security Alliance (GEISA), a Series of LF Projects, LLC

   This file is licensed under the Community Specification License 1.0
   available at:
   https://github.com/geisa/specification/blob/main/LICENSE.md or
   https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

.. _api-waveform-data:

Waveform Data
=============

|geisa-api-hdr|

The GEISA Waveform Data API provides access to higher-volume waveform data such
as voltage and current samples. Because of the potentially high data rates
involved, waveform data is handled differently than lower-rate APIs such as
sensors. The request/response messages exchanged over MQTT are used to request
access to a waveform stream and to provide the metadata needed to decode the
returned waveform frames. The waveform samples themselves are not transported as
MQTT payloads.

Applications publish waveform requests to
``geisa/api/waveform/req/<userid>`` and subscribe for responses on
``geisa/api/waveform/rsp/<userid>``. On a successful subscribe request, the
platform returns a per-application ``AF_UNIX`` ``SOCK_SEQPACKET`` socket path.
The application then consumes waveform frames from that socket.

Applications are not expected to infer electrical topology, meter form, or
device classification from waveform stream identifiers. Stream identifiers are
used to select among the waveform streams offered by the platform. Device Type,
metrology hardware characteristics, meter form, number of phases, nominal
frequency, and similar platform-wide details are provided through Platform
Discovery.

Baseline Stream Requirement
---------------------------

Platforms that support waveform data SHALL expose a baseline waveform stream
with the identifier ``waveform-base``.

The ``waveform-base`` stream represents the baseline interoperable waveform
stream for GEISA applications. Platforms MAY expose additional waveform streams
with different identifiers to provide alternate representations such as reduced,
decimated, filtered, or otherwise specialized waveform data.

Applications SHALL use waveform metadata to determine stream characteristics.
Applications SHALL NOT infer waveform structure or platform characteristics by
parsing the ``stream-id`` value.

If present, waveform stream ``name`` and ``description`` values are
platform-supplied informational metadata intended for display, diagnostics, or
logging. Applications SHALL NOT rely on these fields for interoperability
behavior.

Device Capabilities
-------------------

A platform MAY provide zero or more waveform streams. When waveform data is
supported, Platform Discovery SHALL indicate the presence of waveform support
and SHALL expose the descriptor metadata for each available waveform stream.

A waveform stream descriptor SHALL include:

- A platform-defined ``stream-id``.
- Optional human-readable ``name`` and ``description`` fields.
- The waveform ``sample-type``.
- The number of voltage channels present in each sample time step.
- The number of current channels present in each sample time step.
- The total number of channels present in each sample time step. This SHALL
  equal voltage-channel-count plus current-channel-count.
- The waveform ``sample-rate-hz``.
- The waveform ``samples-per-cycle`` when applicable.
- The waveform ``nominal-frequency-hz`` when applicable.
- Whether frames are ``cycle-aligned``.
- Whether frames are ``zero-crossing-aligned``.
- Optional integer-sample ``voltage-scale`` and ``current-scale`` values.
- The expected frame delivery period in milliseconds.

Platforms that provide waveform data SHALL provide, at a minimum:

- 128 samples per nominal AC cycle where AC cycle semantics apply.
- 16-bit sample resolution.
- Frame delivery at least every 200 ms for the baseline stream.
- Metadata indicating whether the stream is cycle-aligned and whether it is
  zero-crossing-aligned.
- For zero-crossing-aligned polyphase data, alignment to the Phase A voltage
  zero crossing.

Platforms MAY offer alternate sample rates, resolutions, filters, channel
counts, or specialized waveform views as additional streams. For convenience,
binary multiples for samples per cycle are preferred but not required, such as
128, 256, 512, and 16,384 samples per cycle.

Different devices will have different numbers of capture channels, each
typically sampling a single voltage or current input. The total number of
channels and how those channels are assigned may not be known at application
build time and are discoverable through Platform Discovery metadata.

Data for all channels in a frame SHALL be time-aligned to one another. An
individual sample in one channel SHALL have been sampled at the same time as
the corresponding samples in other channels for that sample index.

.. note::

   Platforms MAY expose multiple waveform stream choices to applications if
   they support multiple capture frequencies, channel counts, filters, or
   alternate waveform views. In this case, an application MAY subscribe to one
   or more streams as permitted by the platform and application deployment
   policy.

Platform Discovery SHALL expose only static or semi-static waveform descriptor
metadata. Runtime access handles such as socket paths SHALL NOT be included in
Platform Discovery.

Metadata
--------

Platform Discovery (:doc:`/api/discovery`) describes available waveform
streams and their static or semi-static characteristics. This includes, for each
offered stream:

- The waveform stream identifier.
- Optional stream ``name`` and ``description`` values.
- The type of data: one of ``int16``, ``int32``, ``float32``, or ``float64``.
- The number of voltage channels.
- The number of current channels.
- The total number of channels.
- The sampling frequency in hertz.
- Whether frames are AC cycle aligned.
- Whether frames are zero-crossing aligned.
- Integer voltage and current scaling factors, when applicable.
- The expected data frame period.

Runtime access details, including the per-application socket path, are not part
of Platform Discovery and are returned by the Waveform request/response path.

The Waveform request/response path is used for runtime access control and
runtime decode metadata.

A waveform request includes:

- ``stream-id`` – the identifier of the waveform stream.
- ``request-type`` – either ``subscribe`` or ``unsubscribe``.

A waveform response includes:

- ``status`` – success or a defined error condition.
- ``stream-id`` – echo of the requested stream identifier.
- ``subscribed`` – whether the application instance is subscribed after the
  request is processed.
- ``socket-path`` – the returned per-application socket path when the
  application is subscribed.
- The waveform metadata needed to decode the returned frames.

The waveform response intentionally repeats metadata that may also be available
through Platform Discovery. This duplication is by design so that an authorized
application can immediately validate and decode waveform frames received on the
returned per-application socket without requiring a separate discovery
transaction.

A waveform subscribe request does not imply that an application controls the
underlying platform metrology hardware or the global lifecycle of waveform
capture. Rather, the request asks the platform to grant or deny access to a
waveform stream for the requesting application instance.

Per-Application Socket
~~~~~~~~~~~~~~~~~~~~~~

Each successful subscribe request SHALL result in a socket that is scoped to the
requesting application instance. The returned ``socket-path`` identifies a
per-application socket and SHALL NOT be shared across application instances.

Platforms MAY internally multiplex waveform delivery, but the externally
exposed socket semantics SHALL be per-application to allow independent access
control and isolation.

Alignment Definitions
~~~~~~~~~~~~~~~~~~~~~

A waveform stream is *cycle-aligned* when each frame contains an integer number
of nominal AC cycles.

A waveform stream is *zero-crossing-aligned* when frame boundaries are aligned
to a phase reference, typically the Phase A voltage zero crossing on polyphase
devices.

A stream MAY be cycle-aligned without being zero-crossing-aligned.
Zero-crossing-aligned implies a phase-reference boundary, while cycle-aligned
only describes frame duration.

The ``sample-rate-hz`` value is the authoritative samples-per-second value.
The ``samples-per-cycle`` value is a nominal descriptor and applications SHALL
interpret it together with the stream alignment fields and platform metadata.

Data Format
-----------

The waveform data itself is delivered over the returned per-application socket
as a native binary frame format. The socket path is runtime state and SHALL NOT
be treated as static platform discovery metadata.

``SOCK_SEQPACKET`` type sockets provide the application in-order delivery of
data that honors message boundaries and provide the sender connection-oriented
semantics. Each socket message SHALL contain exactly one complete waveform
frame. Partial frames SHALL NOT be transmitted.

Each frame SHALL provide sufficient information for an application to safely
consume and interpret the delivered samples without vendor-specific knowledge.

At a minimum, each frame SHALL include:

- A timestamp
- A sequence number
- A sample payload

The native socket frame is not a protobuf message. The following C structure is
an illustrative native layout for the frame header and typed sample payload::

struct geisa_waveform_frame
{
  int64_t    timestamp_ns;    /* first sample time, ns since UNIX epoch UTC */
  uint32_t   sequence_num;    /* unspecified starting value */
  uint32_t   reserved;
  union {
    /* variable length array of one sample type */
    int16_t  i16[0];
    int32_t  i32[0];
    float    f32[0];
    double   f64[0];
  } data;
};

The timestamp SHALL represent the time associated with the first sample in the
frame and SHALL be expressed as a signed 64-bit integer in nanoseconds since the
UNIX epoch (UTC). This defines the timestamp representation and does not imply
that the platform clock is accurate to one nanosecond. Timestamp accuracy is
platform-dependent.

A monotonically increasing sequence number SHALL be included to allow detection
of dropped or out-of-order frames. The starting value is unspecified and the
sequence number MAY reset on platform restart or when an application
re-subscribes. Applications SHALL tolerate resets and gaps.

The waveform sample encoding SHALL be one of:

- ``int16``
- ``int32``
- ``float32``
- ``float64``

The sample payload SHALL be encoded using the ``sample-type`` defined in the
waveform metadata. The sample payload size is computed as
``sample_count * total_channel_count`` values.

Samples SHALL be packed in channel-interleaved order per time step. For each
sample index, all channel values SHALL be present, and channel ordering SHALL be
stable and consistent for a given stream.

Samples within the data array SHALL be ordered by sample time step. Within
each time step, voltage channels are listed first, followed by current channels,
using the stable channel ordering described by the stream metadata:

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

A polyphase meter with neutral current and three voltage and four current
channels (seven total channels) would report its data as follows:

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

All multi-byte numeric values SHALL be encoded using little-endian byte order.

For integer sample formats (``int16``, ``int32``), scaling factors SHALL be
applied as defined by the ``voltage-scale`` and ``current-scale`` metadata
values. For floating-point formats (``float32``, ``float64``), scaling factors
SHOULD be omitted or set to ``1.0``.

The waveform frame format SHALL be defined by this specification and SHALL be
sufficient to ensure interoperable decoding across conformant implementations.

The frame structure, including timestamp representation, sequence numbering,
sample encoding, channel ordering, and endianness, SHALL be defined such that an
application can decode waveform data using only the waveform metadata provided
and this specification, without requiring vendor-specific knowledge.

MQTT Details
------------

- QoS: 1 / Acknowledged R/R
- Req Topic: ``geisa/api/waveform/req/<userid>``
- Rsp Topic: ``geisa/api/waveform/rsp/<userid>``

API Permissions
---------------

- Application:

  - Publish: ``geisa/api/waveform/req/<userid>``
  - Subscribe: ``geisa/api/waveform/rsp/<userid>``

.. note::

   In the topic definitions, ``<userid>`` refers to the platform-local
   identifier of the requesting GEISA application instance. See
   :doc:`/glossary` for additional information.

- Platform:
  - Wildcard Subscribe: ``geisa/api/waveform/req/#``
  - Publish: ``geisa/api/waveform/rsp/<userid>``

Transaction Data
----------------

- ``GeisaWaveform_Req``
- ``GeisaWaveform_Rsp``

As defined in https://github.com/geisa/schemas

Examples
--------

Example files for waveform include:

- ``waveform-stream-example.json``
- ``waveform-subscribe-request-example.json``
- ``waveform-subscribe-response-example.json``
- ``waveform-unsubscribe-request-example.json``
- ``waveform-unsubscribe-response-example.json``

References
==========

.. [#ansiforms] ANSI defines a series of standard meter "forms" for the North
   American market in the ANSI C12.1 standard
   (`Code for Electricity Metering <https://webstore.ansi.org/standards/nema/ansic122024>`__).

   Each form has specific physical and electrical characteristics.

|geisa-pyramid|
