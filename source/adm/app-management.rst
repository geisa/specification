Application Management
----------------------

Application management is the process of deplying, activating, deactivating,
and decommissioning applications on a GEISA ADM compliant platform, for
execution within an execution environment.

Software Management
======================

The LwM2M ``/9/x Software Management`` object SHALL be used to manage the
Installation and Activation of containerized edge applications running in the
GEISA EE.  In contrast to the Firmware Update object, each instance of the
multi-instance Software Management object represents a distinct edge
application *Package* installed in the EE.  The format of the edge application
Package is defined for LEE conformant |geisa-lee-tux| systems in
:doc:`/lee/file-layout` and SHALL be composed of the following components:

*    X.509 Public Key Certificate used to verify the digital signature in the Package
*    Digital Signature across the Edge Application Manifest and Edge Application Binary
*    :doc:`Edge Application Manifest </adm/manifests>`
*    Edge Application Binary

To minimize edge app container sizes, applications are encouraged to
dynamically link against the libraries provided by the base GEISA environment
rather than providing their own.  Consideration for the management of the base
libraries and/or package dependencies will be deferred to a future release;  at
this time, no consideration is made for the use of LwM2M object ``14 Software
Component``.

Similar to :doc:`Firmware Update </adm/firmware-management>`, the LwM2M spec permits edge app
packages can be transferred to the EE via either of the following methods:

*    PUSH via *Write* of the opaque package to ``/9/x/2 Package`` 
*    PULL via *Write* to resource ``/9/x/3 Package URI`` for the GEISA platform to download via CoAP/HTTP as soon as practical

In contrast to Firmware Update, the ``Software Management object 9`` does not
support the concept of automatic Installation or Activation.  Both operations
of Installation and Activation are manually executed by the EMS, following
successful package download/verification and successful package install,
respectively. 

The following example demonstrates GEISA compliant edge app installation and activation:

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
