# External ADM / OMA references

This directory contains external references used by the GEISA specification build
and review process.

## `lwm2m-registry`

Pinned git submodule for the OMA LightweightM2M registry branch used for GEISA
LwM2M Object review and alignment.

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
- **3600 — GEISA Application Messaging** (`lwm2m-registry/3600.xml`):
  Application message transport and delivery state model.
- **3601 — GEISA Host Monitoring** (`lwm2m-registry/3601.xml`): Host/platform
  resource and health monitoring for GEISA-capable devices.
- **3602 — GEISA Application Accounting** (`lwm2m-registry/3602.xml`):
  Per-application accounting, quota, and policy-state reporting.
- **3604 — GEISA Application Communication Accounting**
  (`lwm2m-registry/3604.xml`): Communication accounting and traffic counters for
  GEISA applications.
- **3605 — GEISA Platform Monitoring** (`lwm2m-registry/3605.xml`):
  Platform-level monitoring and operational state.
- **3606 — GEISA Platform Configuration** (`lwm2m-registry/3606.xml`): Platform
  configuration and policy exposure for GEISA-capable devices.

Supporting standard OMA objects such as `/3` Device, `/4` Connectivity
Monitoring, `/5` Firmware Update, `/6` Location, `/7` Connectivity Statistics,
and `/9` Software Management remain part of the broader LwM2M baseline. The
list above identifies the GEISA-specific or GEISA-extended object set that
should be checked first when updating this submodule pin.
