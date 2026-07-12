
..
  Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
  Security Alliance (GEISA), a Series of LF Projects, LLC
  This file is licensed under the Community Specification License 1.0
  available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

Network Security
^^^^^^^^^^^^^^^^

For a full discussion on how edge applications can access network interfaces
within an edge environment, please see :doc:`/api/networking`.  This section
is specifically focused on how the system facilitates access control.
Implementers should review both sections for a fulsome understanding of how
network access is exposed and controlled.


Interface Access
~~~~~~~~~~~~~~~~

Application access to network interfaces is controlled through the Application
Manifest (see
https://github.com/geisa/schemas/blob/main/geisa-application-manifest-schema.json),
through the communications object.  Applications may be given access to the
Field Area Network (FAN) interface, the Home Area Network (HAN) interface, or
the messaging interface.  Access to each is independent.  System operators may
grant access to any, all, or none of these interfaces.  

Generally, the FAN interface is the operator-facing network.  This is
potentially an AMI mesh network, a private cellular network or a public carrier
network.  The HAN interface (if present) may very depending on the type of
device hosting the GEISA platform.  In AMI meters, this is likely to be a Wi-Fi
network, provided by the utility consumer where the meter is deployed.  For
distribution automation, this could potentially be a local Ethernet network
allowing access to other local device.

For messaging, the system operator must indicate a daily allowed message count
and grant the application access to the messaging API (see :doc:`/security/API`)

For the HAN and FAN interfaces, the system operator must grant access to the
desired interfaces.  When access has been granted, the platform will configure
the AII to provide the appropriate virtual network interfaces allowing the
application to send and receive packets using traditional network APIs (e.g.
Unix network sockets).

Network Permissions
~~~~~~~~~~~~~~~~~~~

Granting access to the interface does *not* grant any rights to send or receive
packets.  The system operator must also grant access to specific class of
network communications (operator, internet, or local), an allowed number of
bytes per day, and the allowed protocol/address/port combination.

GEISA takes a deny-by-default approach to network access.  Without the HAN or
FAN permission, applications will not be presented a virtual NIC at all.
Without the network access permission, applications will not have the firewall
permissions necessary to exchange messages.

The communication classes are as follows:

- operator:  GEISA devices can send and receive packets over the FAN network to
  any valid and approved address.

- local:  GEISA devices can send and receive packets over the HAN network to
  any valid and approved address local to the HAN interface.  Off-network
  traffic is not allowed.

- internet:  GEISA devices can send and receive packets over the HAN network to
  any valid and approved address on the internet, via the HAN interface.
  On-network traffic is not allowed.

.. note::

   Applications that need both local and internet access can be granted both.

.. note::

   Communication classes are superior to access tuples.  For example, if an
   application was granted access to the local network communication class with
   a network access tuple that was not local, access would still be denied.
   Platforms MUST enforce this behavior.

Communcations class assignments must include both an allowed number of bytes
per day, and at least one inbound or outbound network access tuple.  Inbound
network access tuples allow edge applications to listen on a port.  Outbound
network access tuples allow edge applications to send data to a destination.

The network access tuple is composed of the transport, address, and port,
separated by colons.  For example:

.. code::

  tcp:192.168.101.30:502
  udp::5540
  tcp:23.185.0.4:443

Transport and address may be omitted.  Port is always required.  Both IPv4
and IPv6 addresses are acceptable.  Only raw IP addresses are supported in this
version of the specification, not domain names.  This version of the
specification only allows TCP and UDP as transports.

Platforms MUST translate these tuples into appropriate firewall rules to
inbound and/or outbound traffic as indicated.  Communication classes may have
multiple network access tuple entries.  


|geisa-pyramid|

