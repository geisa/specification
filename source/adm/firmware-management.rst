
..
  Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
  Security Alliance (GEISA), a Series of LF Projects, LLC
  This file is licensed under the Community Specification License 1.0
  available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md
  SPDX-License-Identifier: Community-Spec-1.0

Firmware Management
-------------------

|geisa-adm-hdr|

Manifests & Packages
~~~~~~~~~~~~~~~~~~~~

To ensure interoperability across systems, GEISA uses a defined firmware
package format.  The package format is the same as the application package
format (see :doc:`/adm/app-management`): a gzip compressed ``tar`` archive
containing the manifest, named ``manifest.json``, and all of the artifacts
listed in the manifest.  The format and contents of the firmware artifacts are
not defined by GEISA and are specific to the device they have been built for.
GEISA defines the package format and the manifest to allow an EMS to load and
transfer firmware for any device from any vendor and to ensure a consistent
and secure firmware transfer process.  The gzip compressed ``tar`` file is the
image that the EMS transfers to the device using the LwM2M mechanisms discussed
below.

The firmware manifest format is provided in
``geisa-firmware-manifest-schema.json``.  The format is substantially similar
to the application manifest (see :doc:`/adm/manifests`); however, it only
includes artifacts, compatibility meta-data and signatures, omitting resource
allocations and permissions.  Critically, the firmware manifest uses the LwM2M
Object ``3`` ``manufacturer`` and ``model-number`` fields to determine whether
the firmware package is compatible with the target device.  The
``firmware-version`` field allows the EMS to understand whether a package is an
upgrade or a downgrade.

Firmware manifests and the incorporated artifacts MUST be signed by the
publisher.  Firmware manifests in deployment packages MAY be countersigned by
the system operator.  Device manufacturers are free to include multiple
artifacts within a firmware package.  This capability can be used to provide
images for specific subcomponents within a device.  Manufacturers may use the
``image-name``, ``image-type`` or both to distinguish between different
artifacts.  The EMS MUST preserve the ``manifest`` value within
``geisa-firmware-manifest`` without any changes.  Only the manifest's
``signatures`` block MAY be updated by the EMS.  Typically, this is
done to allow system operator to counter-sign a package.  The publisher
signature on the ``geisa-firmware-manifest`` MUST be retained, as it may be
required by the target device.


LwM2M Update Process
~~~~~~~~~~~~~~~~~~~~

Firmware management is the process of updating the core operating system for an
ADM conformant GEISA platform.

The LwM2M singleton object ``/5/0 Firmware Update`` represents the firmware
update *process*, not simply the firmware image stored on the device.  Object
``/5/0`` is advertised during initial Registration, and object ``/5/0`` is not
deleted by the GEISA platform client after an upgrade; only the ``/5/0/3
State`` and ``/5/0/5 Update Result`` resources are reset after an upgrade to
reflect the new baseline.

The multi-step Firmware Update transaction typically involves the EMS *Observe*
``/5/0/3 State`` so that the GEISA platform client will provide asynchronous
updates of client state changes to the EMS, after which the EMS will proceed with
subsequent steps in the transaction.  Although it is technically possible to
*Observe* resources ``/5/0/3`` and ``/5/0/5`` following initiation of the update
transaction, in order to avoid transaction dead locks or inconsistent state due
to race conditions, and to provide optional support for resource ``/5/0/14
Automatic Upgrade at Download``, a GEISA ADM conformant EMS SHALL perform the
following:

*  *Observe* ``/5/0/3 State`` when object ``/5/0`` is advertised during GEISA
   platform Registration
*  *Read* ``/5/0/5 Update`` Result after Notification that ``/5/0/3 State = Idle``


Depending on EMS capabilities, LwM2M allows either of the following methods
for firmware image distribution to the GEISA platform:

* **PUSH** (CoAP block-wise transfer) via the *Write* operation of the opaque
  binary image to resource ``/5/0/0`` (Package)

* **PULL** via the *Write* operation to resource ``/5/0/1`` (Package URI),
  allowing the GEISA platform to download via CoAP or HTTP as soon as practical.

The following sequence diagrams provide two examples of GEISA conformant
upgrades of the platform firmware.  The first example demonstrates PUSH of the
firmware image to ``/5/0/0 Package``, as shown in :numref:`fota-push-image`
followed by the EMS performing a manual *Execute* ``/5/0/2`` to trigger the
upgrade in :numref:`fota-push-activate`.

.. _fota-push-image:
.. figure:: fota-push-image.*
   :width: 70 %

   Firmware Over-the-Air Push Update

.. _fota-push-activate:
.. figure:: fota-push-activate.*
   :width: 70 %

   Firmware Over-the-Air Manual Activate

The second example, as shown in :numref:`fota-pull-initiate`, demonstrates the
PULL of the firmware image from the URL set by the EMS into ``/5/0/1 Package
URI``.  As shown in :numref:`fota-pull-automatic`, the ADM conformant GEISA
platform automatically executes the upgrade after the download per the EMS
setting ``/5/0/14 Automatic Upgrade = True``.

.. _fota-pull-initiate:
.. figure:: fota-pull-initiate.*
   :width: 70 %

   Firmware Over-the-Air Pull Image Initiate

.. _fota-pull-automatic:
.. figure:: fota-pull-automatic.*
   :width: 90 %

   Firmware Over-the-Air Pull Automatic Download and Update


|geisa-pyramid|
