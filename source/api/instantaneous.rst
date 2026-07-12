
..
  Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
  Security Alliance (GEISA), a Series of LF Projects, LLC
  This file is licensed under the Community Specification License 1.0
  available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

.. _api-instantaneous-data:

Instantaneous Data
------------------

|geisa-api-hdr|

Summary
========
Instantaneous data provides a continuous stream of scalar metrological data as
provided by the host device, with data being pushed at least once a second.
Platforms MAY push data more frequently; however, data push periodicity MUST be
consistent. The instantaneous data push periodicity MUST be reported in the
:doc:`/api/discovery` transaction.

When supported by the platform, instantaneous data is available to authorized
applications without a separate activation transaction. There is no need to
specifically request or activate it; applications can simply subscribe to the
topic.

This API carries scalar metered quantities and remains distinct from the
high-rate waveform API.

Profiles and Required Values
============================

The base GEISA metered-quantities schema is capability-tolerant so it can
support different device and platform architectures. A field being defined by
the base schema does not make it mandatory for every platform, and applications
MUST tolerate absent standardized values unless another applicable requirement
or profile makes them mandatory.

Profiles define required subsets appropriate to specific device or capability
classes. The GEISA AC Meter Profile defines the current minimum required scalar
AC metrology baseline for implementations of that profile.

Note that this baseline is intentionally conservative for the current
specification version, and GEISA expects the base profile set and
profile-required metered quantities to expand in future specification
versions as implementation experience and application requirements mature.

The current AC Meter Profile directly requires the ``phase-a`` and ``system``
objects. Additional phases may be required according to meter form, phase
count, Platform Discovery, and conformance logic. Platforms not claiming the AC
Meter Profile may expose a different applicable subset when permitted by
another profile or capability model.

Scalar metered quantities remain separate from waveform frame delivery.
Billing quantities use separate metered-quantities payloads and profile
definitions and are not part of the instantaneous scalar profile.

AC Meter Profile Required Fields
================================

The following two tables list the current AC Meter Profile required
instantaneous fields. Every row shown here is required for the AC Meter
Profile. Additional phase objects may also be required according to meter
form, phase count, Platform Discovery, etc.

.. list-table:: Required Outer Payload and phase-a Fields
   :header-rows: 1
   :widths: 12 22 18 48

   * - Scope
     - Field
     - Encoding / Unit
     - Meaning / Applicability
   * - Outer payload
     - ``message-version``
     - uint32 integer
     - Top-level message version
   * - Outer payload
     - ``timestamp-us``
     - uint64 UTC Unix epoch microseconds
     - Top-level timestamp
   * - phase-a
     - ``message-version``
     - uint32 integer
     - Phase message version
   * - phase-a
     - ``phase``
     - String enum ``PHASE_A`` | ``PHASE_B`` | ``PHASE_C`` | ``PHASE_N``
     - Phase selector; AC Meter Profile uses PHASE_A here.
   * - phase-a
     - ``voltage-micro-v``
     - int64 fixed-point microvolts
     - Phase RMS voltage
   * - phase-a
     - ``current-micro-a``
     - int64 fixed-point microamps
     - Phase RMS current
   * - phase-a
     - ``active-power-micro-w-sum``
     - int64 fixed-point microwatts
     - Phase active power sum
   * - phase-a
     - ``reactive-power-micro-var-sum``
     - int64 fixed-point microvars
     - Phase reactive power sum
   * - phase-a
     - ``apparent-power-micro-va-sum``
     - int64 fixed-point microvolt-amperes
     - Phase apparent power sum
   * - phase-a
     - ``power-factor``
     - double ratio 0.0 to 1.0
     - Phase power factor magnitude
   * - phase-a
     - ``current-angle-deg``
     - double degrees
     - Phase current angle
   * - phase-a
     - ``voltage-angle-deg``
     - double degrees
     - Phase voltage angle
   * - phase-a
     - ``current-thd-percent``
     - double percent
     - Phase current THD
   * - phase-a
     - ``voltage-thd-percent``
     - double percent
     - Phase voltage THD
   * - phase-a
     - ``current-tdd-percent``
     - double percent
     - Phase current TDD

.. list-table:: Required System Fields
   :header-rows: 1
   :widths: 12 22 18 48

   * - Scope
     - Field
     - Encoding / Unit
     - Meaning / Applicability
   * - system
     - ``message-version``
     - uint32 integer
     - System message version
   * - system
     - ``timestamp-us``
     - uint64 UTC Unix epoch microseconds
     - System timestamp
   * - system
     - ``frequency-hz``
     - double hertz
     - System frequency
   * - system
     - ``active-power-micro-w-sum``
     - int64 fixed-point microwatts
     - System active power sum
   * - system
     - ``reactive-power-micro-var-sum``
     - int64 fixed-point microvars
     - System reactive power sum
   * - system
     - ``apparent-power-micro-va-sum-arithmetic``
     - int64 fixed-point microvolt-amperes
     - System arithmetic apparent power sum; required as the profile aggregate apparent power baseline
   * - system
     - ``power-factor-arithmetic``
     - double ratio 0.0 to 1.0
     - System arithmetic power factor magnitude

Additional Standardized Instantaneous Quantities
================================================

The base metered-quantities schema standardizes additional instantaneous
fields beyond the current AC Meter Profile baseline. These fields remain
interoperable when present, but applications MUST tolerate their absence unless
another applicable requirement or future profile makes them mandatory.

Additional phase objects may be present when supported by the platform and may
become required according to meter form, phase count, Platform Discovery, and
conformance logic even though the current AC Meter Profile directly requires
only the ``phase-a`` and ``system`` objects.

.. csv-table:: Additional Standardized Optional Instantaneous Fields
  :header-rows: 1
  :widths: 14 20 18 14 34
  :file: /api/instantaneous-optional.csv

Value Semantics
===============

- JSON schema and profile documents currently use hyphenated field names while
  the protobuf source uses an underscore naming convention
- Electrical integer values use the fixed-point micro-unit identified by the
  field name
- ``timestamp-us`` is UTC Unix epoch time in microseconds
- Proto3 optional presence distinguishes an absent or unsupported value from a
  valid zero
- Power factor is an unsigned magnitude in the range ``0.0`` through ``1.0``
- Directional and quadrant context comes from applicable active and reactive
  power fields and angles rather than power factor sign
- THD, TDD, and second-harmonic percentage fields use ``0`` through ``100``
  percentage semantics
- Measurement metadata describes averaging or integration windows and is not
  the publication cadence
- Arithmetic aggregate apparent power and power factor are required by the
  current AC Meter Profile
- Optional vectorial aggregate values may also be published; arithmetic and
  vectorial values are not mutually exclusive

.. note::

   Some jurisdictions, including Canada, may prefer or require vectorial
   calculations for selected aggregate metered quantities. The GEISA
   metered-quantities schema distinguishes arithmetic and vectorial aggregate
   values using separate field names where both calculation methods are
   defined. The current AC Meter Profile requires arithmetic aggregate apparent
   power and power factor as the baseline; vectorial aggregate values may also
   be published when supported by the platform. Applications that require
   vectorial aggregate values must tolerate their absence unless another
   applicable profile or requirement makes them mandatory.

MQTT Details
============
- QoS: 0 / Unacknowledged
- Topic: ``geisa/api/instantaneous/data``

API Permissions
===============

- Application:

  - Subscribe: ``geisa/api/instantaneous/data``

- Platform:

  - Publish: ``geisa/api/instantaneous/data``


Transaction Data
================

- ``GeisaInstantaneousQuantities``

As defined in |geisa-schemas-repo|


|geisa-pyramid|
