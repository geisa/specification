
..
  Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
  Security Alliance (GEISA), a Series of LF Projects, LLC
  This file is licensed under the Community Specification License 1.0
  available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

.. index:: single: Application Management

Application Management
----------------------

Application management is the process of deploying, activating, deactivating,
and decommissioning applications on a GEISA ADM conformant platform, for
execution within an execution environment.

Software Management
======================

The LwM2M ``/9/x Software Management`` object SHALL be used to manage the
software package lifecycle of containerized edge applications running in the
GEISA EE.  In contrast to the Firmware Update object, each instance of the
multi-instance Software Management object represents a distinct edge
application *Package* installed in the EE.  The format of the edge application
Package is defined in :doc:`/lee/file-layout` for LEE conformant |geisa-lee-tux| systems
and SHALL be composed of the following components:

*    X.509 Public Key Certificate used to verify the digital signature in the Package
*    Digital Signature across the Edge Application Manifest and Edge Application Image
*    :doc:`Edge Application Manifest </adm/manifests>`
*    Edge Application Image

To minimize edge application image sizes, applications are encouraged to
dynamically link against the libraries provided by the base GEISA environment
rather than providing their own.  Consideration for the management of the base
libraries and/or package dependencies will be deferred to a future release;  at
this time, no consideration is made for the use of LwM2M object ``14 Software
Component``.

.. index:: single: Application Installation

.. index:: single: Application Activation

**App Installation and Activation**

Similar to :doc:`Firmware Update </adm/firmware-management>`, the LwM2M spec
permits edge app packages can be transferred to the EE via either of the
following methods:

*    PUSH via *Write* of the opaque package to ``/9/x/2 Package``

*    PULL via *Write* to resource ``/9/x/3 Package URI`` for the GEISA platform
      to download as soon as practical

PULL downloads will attempt to use the protocol specified in the URI.  GEISA
ADM conformant EMS and GEISA ADM conformant platform implementations must
support CoAP transfers.  GEISA ADM conformant EMS must include the ability to
host firmware and application images for download via CoAP.  GEISA conformant
EMS MAY support alternate protocols (like HTTP) or specifying external URIs.

In contrast to Firmware Update, the ``Software Management object 9`` does not
support the concept of automatic Installation or Activation.  Both operations
of Installation and Activation are manually executed by the EMS, following
successful package download/verification and successful package install,
respectively.

The Software Management Object ``/9`` instance number is independent of
resource ``4050`` AppID. Resource ``4051`` Software Instance links a GEISA
application Object Instance to the corresponding ``/9`` instance.

The following example demonstrates GEISA conformant edge app installation and
      activation:

#.    PULL download of the edge app package from the URL set by the EMS into
      ``/9/x/3 Package URI``, shown in :numref:`software-update-trigger`.
#.    The EMS performing a manual *Execute* ``/9/x/4`` to trigger edge app
      Installation following successful app download and verification, shown in
      :numref:`software-update-install`.
#.    The EMS performing a manual *Execute* ``/9/x/10`` to trigger edge app
      Activation following successful app installation, shown in
      :numref:`software-update-install`.
#.    The EMS performing a manual *Execute* ``/9/x/6`` to trigger Uninstall of
      the edge app (not shown).

.. _software-update-trigger:
.. figure:: software-update-trigger.*

    Edge App Image Pull

.. _software-update-install:
.. figure:: software-update-install.*

    Edge App Install and Activate

**App Update**

ADM conformant platforms and EMS MUST support application updates using the
existing ``/9/x Software Management`` Object Instance and
``/9/x/6 Uninstall`` with argument ``1`` (``ForUpdate``).

When updating an installed edge application, the EMS SHALL use ``ForUpdate``.
The platform SHALL set ``/9/x/7 Update State`` to ``INITIAL`` and
``/9/x/9 Update Result`` to ``0``, and prepare to receive the replacement
package as defined by the Software Management Object.

Application updates MUST preserve persistent files in ``/home/geisa``.
Non-persistent files are not retained when the application filesystem is
reconstructed as part of the update.

If the operator does not wish to retain persistent application data when
moving to a newer version, they may instead use ``/9/x/22 Purge Data`` via the
EMS together with a normal ``/9/x/6 Uninstall`` and then perform a new
application installation. ``Purge Data`` remains an independent operation and
MAY also be used outside of an application replacement workflow.  Note that
``Purge Data`` MUST be supported as part of GEISA conformance.

Executing ``/9/x/6`` with no argument or argument ``0`` performs a normal
uninstall rather than an application update.

After ``ForUpdate``, the replacement package SHALL be transferred using
``/9/x/2 Package`` or ``/9/x/3 Package URI`` and follow the normal download,
verification, and ``/9/x/4 Install`` sequence. After successful installation,
the EMS MAY execute ``/9/x/10 Activate`` and, when application execution is
desired, ``/9/x/19 Start``.

The Software Management object Activation state machine defines the ability to use an app but does not address app execution state semantics:

* When the current state is set to ACTIVE, the installed software can be used by the LwM2M Client.
* When the current state is set to INACTIVE, the LwM2M Client MUST NOT use the installed software.


.. index:: single: Execution State

**App Execution State**

Version 1.1 of the Software Management object adds resources for an EMS to control the *Execution State*
of an edge application:

.. list-table::
   :header-rows: 1
   :widths: 12 15 15 58

   * - Resource ID
     - Operation
     - Data Type
     - Description
   * - 19
     - Execute
     -
     - Start Application. Only available when Activation State = Enabled.
   * - 20
     - Execute
     -
     - Stop Application. Only available when Activation State = Enabled.
   * - 21
     - Read
     - Integer
     - Execution Status. 0 = Stopped. 1 = Running.

.. index:: single: Application Purge

**App Purge**

Version 1.1 of the Software Management object adds an executable resource for
an EMS to remotely purge local data from an instance of an edge application
installation. Purge is independent of application update and uninstall
operations and MAY also be used when an operator requires a clean application
replacement without retaining persistent data:

.. list-table::
   :header-rows: 1
   :widths: 12 15 15 58

   * - Resource ID
     - Operation
     - Data Type
     - Description
   * - 22
     - Execute
     -
     - Purge Data. Deletes existing local application data without modifying the app installation/activation states.
