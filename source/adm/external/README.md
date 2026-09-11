# External ADM / OMA references

This directory contains external references used by the GEISA specification
build and review process.

## `lwm2m-registry`

Pinned git submodule for the OMA LightweightM2M registry branch used for GEISA
LwM2M Object review and alignment.  Note that this branch in the registry
is intended to be labeled across GEISA releases, and the submodule linkage
updated accordingly on GEISA releases.

- Upstream: `https://github.com/OpenMobileAlliance/lwm2m-registry`
- Branch: `GEISA-LwM2M-Objects`

The submodule is intentionally pinned by commit. Update the submodule pointer
when the agreed OMA registry branch advances.

Note as this content is provided via a git submodule, it is not populated by a
plain `git clone` and will appear empty.

To fetch it after cloning the geisa specification repo:
  <from repo root>
  git submodule update --init source/adm/external/lwm2m-registry

### GEISA-relevant OMA LwM2M objects

The pinned OMA LwM2M registry submodule contains the full OMA registry. The
following objects are the GEISA-relevant object set currently referenced for
GEISA ADM review, implementation alignment, and OMA submission tracking.

- **20 — Event Log** (`lwm2m-registry/20.xml`): Shared event, alarm, and
  operational log model used by GEISA devices and applications.  This is
  the standard / prior /20 Object with minor additions for GEISA and
  generic usage.
- **3600 — Application Messaging** (`lwm2m-registry/3600.xml`):
  Application message transport and delivery state model.
- **3601 — Host Monitoring** (`lwm2m-registry/3601.xml`): Host/platform
  resource and health monitoring for GEISA-capable devices.
- **3602 — Application Accounting** (`lwm2m-registry/3602.xml`):
  Per-application accounting, quota, and policy-state reporting.
- **3604 — Application Monitoring** (`lwm2m-registry/3604.xml`): App-scoped
  runtime monitoring, lifecycle, and health visibility.
- **3605 — Platform Monitoring** (`lwm2m-registry/3605.xml`):
  Platform-level aggregate monitoring and operational state.
- **3606 — Platform Effective Configuration** (`lwm2m-registry/3606.xml`):
  Platform effective configuration and policy exposure for GEISA-capable
  devices.
- **3607 — Platform Requested Configuration** (`lwm2m-registry/3607.xml`):
  Platform requested configuration and policy exposure for GEISA-capable
  devices.
- **3608 — Component Monitoring** (`lwm2m-registry/3608.xml`): Logical component
  monitoring state for individual Platform components for GEISA-capable
  platform functions, services, queues, APIs, and operational paths.

Supporting standard OMA objects such as `/3` Device, `/4` Connectivity
Monitoring, `/5` Firmware Update, `/6` Location, `/7` Connectivity Statistics,
and `/9` Software Management remain part of the broader LwM2M baseline. The
list above identifies the GEISA-specific or GEISA-extended object set that
should be checked first when updating this submodule pin.
