..
  Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
  Security Alliance (GEISA), a Series of LF Projects, LLC
  This file is licensed under the Community Specification License 1.0
  available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

Billing Data
------------

|geisa-api-hdr|

Summary
========
Billing Data defines meter-register-style metered quantities that are distinct
from the continuous Instantaneous Data stream and from Waveform Data. The
schema-level billing payload is ``GeisaBillingQuantities``.

Billing quantities cover accumulated summations and demand-oriented register
values used for billing or interval accounting use cases.

Billing Data Broadcast
======================

Platforms that support Billing Data publish billing snapshots on:

- ``geisa/api/billing/data``

The payload is ``GeisaBillingQuantities``. Billing Data is a platform-to-
application snapshot stream rather than a high-rate continuous feed.
Publication cadence is platform-specific and may reflect meter register update
timing, billing or interval windows, demand interval closure, or platform
policy.

Applications MUST use payload timestamps and measurement metadata to interpret
the billing window or demand interval. Applications MUST NOT infer billing
window boundaries solely from MQTT delivery time.

This version defines the Billing Data broadcast topic and payload. It does not
define a Billing Data request/response transaction, historical query,
application-selected billing interval, or socketed stream.

Billing Payload Model
=====================

``GeisaBillingQuantities`` is the outer billing payload. It contains:

- ``summation_total`` as ``GeisaBillingQuantities_Summation_Total``
- ``demand_total`` as ``GeisaBillingQuantities_Demand_Total``

``summation_total`` carries energy and related interval/window-qualified
billing quantities such as delivered, received, summed, net, reactive,
quadrant-qualified, and apparent-energy values where defined.

``demand_total`` carries maximum-demand style quantities using
``GeisaTypeMaxDemand``. Each max-demand value combines:

- ``max-demand-time-us`` for the recorded maximum-demand timestamp
- ``quantity`` for the fixed-point quantity value

The demand model is used for active, reactive, and apparent demand quantities
where defined by the schema.

Value Semantics
===============

- ``timestamp-us`` values use UTC Unix epoch time in microseconds.
- Electrical integer quantities use the fixed-point micro-unit encoded by each
  field name.
- ``GeisaTypeMeasurementMetadata`` describes the averaging or integration
  window and is not the publication cadence.
- Power factor values are unsigned magnitudes in the range ``0.0`` through
  ``1.0``.
- Direction and quadrant context comes from active/reactive quantities,
  power-factor angle fields, and quadrant-qualified field names rather than
  from power-factor sign.
- Reactive energy and reactive demand include Q1, Q2, Q3, Q4, and combined
  quadrant fields where defined.
- Apparent energy and apparent demand distinguish arithmetic and vectorial
  quantities where defined.
- Billing quantities remain separate from instantaneous scalar values and
  waveform data.

.. note::

   Some jurisdictions, including Canada, may prefer or require vectorial
   calculations for selected aggregate billing quantities. The GEISA billing
   payload uses explicit arithmetic and vectorial field names where both
   calculation methods are defined, so applications can distinguish the
   calculation basis from the field name rather than relying on a global
   stream-level setting.

Profile and Example
===================

The maintained schemas repository includes a billing profile overlay and
example payload for this model:

- ``profiles/geisa-metered-quantities-billing-profile.json``
- ``examples/metered-quantities-billing-profile-example.json``

The current billing profile requires a billing payload with both
``summation-total`` and ``demand-total`` sections. The required baseline
includes delivered active-energy summation, delivered active-power demand, and
``measurement-period-s`` metadata for both sections.

MQTT Details
============
- QoS: 0 / Unacknowledged
- Topic: ``geisa/api/billing/data``

API Permissions
===============

- Application:

  - Subscribe: ``geisa/api/billing/data``

- Platform:

  - Publish: ``geisa/api/billing/data``

Transaction Data
================

- ``GeisaBillingQuantities``
- ``GeisaBillingQuantities_Summation_Total``
- ``GeisaBillingQuantities_Demand_Total``
- ``GeisaTypeMaxDemand``
- ``GeisaTypeMeasurementMetadata``

As defined in |geisa-schemas-repo|


|geisa-pyramid|
