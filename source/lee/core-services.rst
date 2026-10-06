
..
  Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
  Security Alliance (GEISA), a Series of LF Projects, LLC
  This file is licensed under the Community Specification License 1.0
  available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

Core Services
-------------

GEISA LEE |geisa-lee-tux| implementations MUST provide:

-   ``/dev/log`` services
-   Network communications (when authorized to an application via its
    application manifest -- see doc:`/adm/manifests`)
-   GEISA MQTT API |geisa-api-gear| services (when offering a GEISA API 
    conformant implementation) as per :doc:`/api`

``/dev/log`` should allow applications running within the LEE AII to submit
data to the local ``/dev/log`` for persistence.  LEE implementations that are
also ADM conformant |geisa-adm-baton| should expose application logs via LwM2M
Object ``/20``.

IP network communications MUST be supported by the LEE.  The LEE SHOULD support
IPv4 and/or IPv6, in alignment with whatever IP stack(s) is used by the
underlying platform.  The platform MAY proxy IP communications for the LEE over
a non-IP network; however, this is not a preferred solution, as it may create
communications interoperability challenges.

GEISA LEE implementations MAY also provide:

-   Domain Name Services
-   Multicast Domain Name Services
-   DNS Service Discovery

.. Note::

   This version of the GEISA specification does not require implementations to
   offer DNS, mDNS, or DNS-SD.  Applications written to this version should be
   able to gracefully fallback to using direct IP addresses if DNS services are
   available.


