
..
  Copyright 2025, Contributors to the Grid Edge Interoperability & Security Alliance (GEISA) a Series of LF Projects, LLC  
  This file is licensed under the Community Specification License 1.0 available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

Bootstrapping
-------------------------

As discussed in the LWM2M core specification [LWM2M-Core]_ section 6.1, there
are four ways to bootstrap a device so that it knows how to contact its LWM2M
server for management:

- Factory Bootstrap
- Bootstrap from Smartcard
- Client Initiated
- Server Initiated

In Factory Bootstrap, devices are provisioned during manufacturing with
security credentials and Management Server (edge management system) information.
Upon field installation, devices connect directly to their Management Server
(edge management system) to perform registration.  

In Client-Initiated Bootstrap, shown below in :numref:`bootstrap`, devices are
provisioned during manufacturing with Bootstrap Server (BS) information. Upon
field installation, devices initiate connection to the Bootstrap Server for the
provisioning of Security credentials (object 0) and Management Server
information.

.. _bootstrap:
.. figure:: client-bootstrap.*

  Client Bootstrap

As noted in [LWM2M-Core], GEISA ADM conformant devices SHALL support Client
Initiated bootstrapping.  GESIA ADM conformant devices MAY support other
bootstrapping methods.  For mass deployed devices, like smart meters, Factory
Bootstrapping is usually preferred by system operators.

GEISA ADM conformant devices SHALL provide an accessible out-of-band
mechanism which allows the system operator to preprovision the URL of the CoAp
Bootstrap-Server, the Bootstrap-Server Account credentials, and any other data
needed to complete the boostrapping process (e.g. certificates, keys, etc.).

.. Note::

  GEISA ADM Conformant EMS are not required to provide a Bootstrap Server.  If a
  platform provider ships devices set to use client intiated bootstrap, it is
  expected that they will inform the purchaser in advance or provide a bootstrap
  server.


.. Note::

  ToDo:  LWM2M Bootstrapping can include an endpoint client name.  This is optional if
  the identifier provided in the security protocol is sufficient.  We need to
  agree on the security mechanism and discuss whether the identifiers it provides
  are sufficient.


