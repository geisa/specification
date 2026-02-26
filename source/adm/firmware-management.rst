
..
  Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
  Security Alliance (GEISA), a Series of LF Projects, LLC
  This file is licensed under the Community Specification License 1.0
  available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

Firmware Management
-------------------

Firmware management is the process of updating the core operating system for an
ADM compliant GEISA platform.

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

  Firmware Over-the-Air Push Update

.. _fota-push-activate:
.. figure:: fota-push-activate.*

  Firmware Over-the-Air Manual Activate

The second example, as shown in :numref:`fota-pull-initiate`, demonstrates the
PULL of the firmware image from the URL set by the EMS into ``/5/0/1 Package
URI``.  As shown in :numref:`fota-pull-automatic`, the ADM conformant GEISA
platform automatically executes the upgrade after the download per the EMS
setting ``/5/0/14 Automatic Upgrade = True``.

.. _fota-pull-initiate:
.. figure:: fota-pull-initiate.*

  Firmware Over-the-Air Pull Image Initiate

.. _fota-pull-automatic:
.. figure:: fota-pull-automatic.*

  Firmware Over-the-Air Pull Automatic Download and Update


|geisa-pyramid|
