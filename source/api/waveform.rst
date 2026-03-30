..
   Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
   Security Alliance (GEISA), a Series of LF Projects, LLC

   This file is licensed under the Community Specification License 1.0
   available at:
   https://github.com/geisa/specification/blob/main/LICENSE.md or
   https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

Waveform Data
=============

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
with the identifier ``waveform-full``.

The ``waveform-full`` stream represents the baseline interoperable waveform
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

Platform Discovery SHALL expose only static or semi-static waveform descriptor
metadata. Runtime access handles such as socket paths SHALL NOT be included in
Platform Discovery.

Metadata
--------

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

Data Format
-----------

The waveform data itself is delivered over the returned per-application socket
as a native binary frame format. The socket path is runtime state and SHALL NOT
be treated as static platform discovery metadata.

Each socket message SHALL contain exactly one complete waveform frame. Partial
frames SHALL NOT be transmitted.

Each frame SHALL provide sufficient information for an application to safely
consume and interpret the delivered samples without vendor-specific knowledge.

At a minimum, each frame SHALL include:

- A timestamp
- A sequence number
- A sample payload

The timestamp SHALL represent the time associated with the first sample in the
frame and SHALL be expressed as a signed 64-bit integer in nanoseconds since the
UNIX epoch (UTC).

A monotonically increasing sequence number SHALL be included to allow detection
of dropped or out-of-order frames.

The waveform sample encoding SHALL be one of:

- ``int16``
- ``int32``
- ``float32``
- ``float64``

The sample payload SHALL be encoded using the ``sample-type`` defined in the
waveform metadata.

Samples SHALL be packed in channel-interleaved order per time step. For each
sample index, all channel values SHALL be present, and channel ordering SHALL be
stable and consistent for a given stream.

For example, for a stream with 1 voltage channel and 2 current channels:

::

   [V0, I0, I1], [V0, I0, I1], ...

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