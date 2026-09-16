<!--
Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
Security Alliance (GEISA), a Series of LF Projects, LLC

Licensed under the Apache License, Version 2.0. See LICENSE.
-->

# GEISA Profile Schemas

This directory contains profile schemas for GEISA device and capability
profiles. For example,
`geisa-metered-quantities-ac-meter-profile.json` defines the GEISA 0.9
AC meter profile for scalar metered quantities, and
`geisa-metered-quantities-billing-profile.json` defines the GEISA 0.9
billing profile.

Base schemas define capability-tolerant message structures. Profile schemas add
required fields or field families for specific device types or capability
classes without implying that all GEISA devices implement all APIs or expose
all measurements/values.

Profile schemas are intended for profile-specific validation by examples,
implementations, test tooling, and conformance tooling. A validator can select
profiles from Platform Discovery metadata such as device type, metrology
capability, meter form, phase count, and advertised API support.

## Profile Evolution

The GEISA 0.9 profiles are initial validation overlays for common metrology
and billing expectations. They are intentionally narrower than the full
set of capabilities likely to be needed by edge-intelligence-capable
devices as GEISA engagement with utilities, vendors, and application
developers continues.

Future GEISA releases are expected to expand these profiles and may add
additional profiles for other platform classes, such as gateways or compute
modules that provide GEISA conformant capabilities but may not expose
direct local metrology. Profile expansion may also tighten selected optional
fields into mandatory profile requirements where interoperability experience
shows a common baseline is needed for applications spanning DER, local
control, safety, load disaggregation, power quality, and other edge intelligence
use cases.

Profiles do not replace the base schema. The base schema remains
capability-tolerant and acts as the superset of possible attributes and the wire
contract for these payloads; profiles define stronger validation expectations
for specific platform or capability classes.

Later specification versions may add additional profiles. Implementers may also
provide device or application-specific validation profiles for operator use,
but GEISA 0.9 does not require per-application profiles.
