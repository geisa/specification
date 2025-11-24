
..
  Copyright 2025, Contributors to the Grid Edge Interoperability & Security Alliance (GEISA) a Series of LF Projects, LLC  
  This file is licensed under the Community Specification License 1.0 available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

Registration
-----------------------

GEISA ADM conformant devices SHALL attempt to register with a GEISA conformant
edge management system on startup.  Registration uses the LWM2M `registration
object`.

The LwM2M Registration process allows a GEISA ADM conformant platform to inform
the EMS of the device’s configuration and capabilities, and to request
management by the EMS.  It also informs the EMS of the current network address
of the device, which is likely dynamically assigned by the network.  During
Registration, the LwM2M Client in the platform reports to the Edge Management
System the list of LwM2M Objects supported by the EE and its currently
instantiated Object Instances.

Registration Update is a lightweight, empty Registration packet sent to the EMS for the following reasons:

* A periodic heartbeat from Client to Server to maintain the existing management session.
* If any previous Registration information changes, for example:


  * GEISA platform IP Address changes
  * The objects supported by the platform changes after a firmware upgrade

.. _registration:
.. figure:: client-registration.*

  LWM2M Registration and Registration Update

|geisa-pyramid|

