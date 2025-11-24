
..
  Copyright 2025, Contributors to the Grid Edge Interoperability & Security Alliance (GEISA) a Series of LF Projects, LLC  
  This file is licensed under the Community Specification License 1.0 available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

Application & Device Management
-----------------------------------

|geisa-adm-hdr|

GEISA provides a uniform mechanism for managing edge devices and the
applications that run on top of them.  ADM conformant devices from different
platform vendors can be managed by a single ADM conformant edge management system.
See :doc:`system-architecture` for more discussion of the general concept.

ADM conformance devices support a set of standard transactions using OMA
Specworks Lightweight M2M [LWM2M]_ transaction definitions, over the IEFT CoAP
[RFC7252]_ protocol.  ADM conformant platform implementations MUST support the
LWM2M transactions detailed in this chapter and the supporting device behaviors
described.  ADM conformant edge management systems MUST support the LWM2M
transactions detailed in this chapter and the supporting edge management system
behaviors described.

.. Note::

  ADM conformance does not preclude platforms or edge management systems from
  supporting additional or supplementary management protocols.

.. Note::

  Platform vendors may offer an ADM conformant device without offering an ADM
  conformant edge management system or an ADM conformant edge management system
  without offering an ADM conformant device.

As described in the GEISA :doc:`api`, GEISA provides a default :doc:`adm/messaging`
mechanism.  ADM conformant platforms transport these messages over CoAP.  ADM
conformant edge management systems expose these messages over a local ReST API,
allowing other systems to easily consume messages sent by edge applications or
to send messages to edge applications.

.. toctree::
  :hidden:

  adm/lwm2m
  adm/bootstrap
  adm/registration
  adm/manifests
  adm/device-management
  adm/firmware-management
  adm/app-management
  adm/messaging

