
..
  Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
  Security Alliance (GEISA), a Series of LF Projects, LLC
  This file is licensed under the Community Specification License 1.0
  available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

.. _api-networking:

Off-Device Communication
------------------------

|geisa-api-hdr|


GEISA allows applications to make use of 2 types of off-device communications:
Message based, and IP socket based.

GEISA distinguishes between platform-mediated message-based communication
and application-managed IP socket communication. These are separate
communication mechanisms. Applications do not use GEISA app-message
request and response payloads to perform IP socket communication. For
ADM-conformant platforms, app-message transport uses the GEISA ADM LwM2M over
CoAP path, carried by platform-controlled IP communication outside of the
application execution environment. Applications remain unaware of those ADM
transport details.  Applications that require both mechanisms must request both
in their manifest, and platforms enforce each according to the approved 
deployment policy.


Message-based via LwM2M
^^^^^^^^^^^^^^^^^^^^^^^

This type of communication is available on every device with :doc:`/adm` and uses
the administrative LwM2M connection for transport.

This type of communication is bi-directional and messages may be sent unsolicited
by either side.  Messages can be sent from the application (upstream) and to the
application (downstream).

Applications use the message bus to send and receive these messages to/from the
platform which in turn makes use of LwM2M to transport them.  The applications
themselves are unaware of any LwM2M details.

Delivery of messages under some circumstances may be significantly delayed or
lost. The :doc:`/adm` is responsible for queuing these messages in both directions.

For upstream messages, the queue contents may be long-lived due to delivery delays
or network outages.  The messages in the queue SHALL be persistent across device
reboots, power cycles, or application restarts, and if undeliverable beyond a
timeout period a failure status is reported to the sender.

.. note::

   Message queue persistence, retention, retry behavior, and recovery pacing
   are platform-managed behaviors subject to operator policy. This version of
   the specification does not define interoperable configuration mechanisms for
   these behaviors. Future versions may define standard configuration and
   observability mechanisms for platform-managed message queues.

Platforms SHOULD avoid creating a burst of delayed traffic when connectivity
is restored. Appropriate mechanisms may include message expiration, priority
handling, backoff, rate limiting, queue limits, or other platform-controlled
delivery controls.

A message-specific time-to-live value, when present, indicates the
sender's requested maximum useful lifetime for that message. The platform
MAY apply an implementation-defined maximum queued-message retention
period and SHOULD expire the message when either the applicable time-to-live
or retention period is reached.

.. note::

   This version of the specification does not define an interoperable operator
   override mechanism for storm conditions, network congestion, FAN outages, or
   other traffic management events. Such controls may exist as
   platform-specific or operator-specific capabilities and may be defined in a
   future version of this specification.

This version of the specification does not mandate fallback or transfer of
queued messages across destination classes or communication mechanisms.
For example, a platform is not required to transfer queued message-based
communication to an application IP socket communication path, or to
transfer failed application IP socket communication to message-based
communication. Applications that require cross-mechanism fallback are
responsible for implementing that behavior within the permissions approved
by the deployment policy.

For downstream messages, the queue contents are usually short-lived if the
application is running. If an application is not running, or does not
acknowledge message delivery over the message bus, the :doc:`/adm` is still
responsible for queuing these messages and, if undeliverable beyond a timeout
period, reporting a failure status to the sender.

If an application is uninstalled while its messages are in the queue, a delivery
failure status SHALL be sent back upstream for each queued downstream message,
and the queue then purged.

.. note::

  Messages that the application sends are deposited into an operator-run system
  for retrieval by the operator and/or application developer using APIs to the
  operator's cloud services.  The operator or application developer can also
  initiate messages to the application in bulk or individually.


IP socket based to local devices, private clouds, or public clouds
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Applications can also make use of traditional IP socket based real-time
communications on devices equipped with cellular, Wi-Fi, or other IP connectivity.
Applications MUST specify the endpoints they need to communicate to (IP/Port)
in their Application Deployment Manifest so that those policies can be approved
 by operators and implemented in the platform using firewall rules.

Applications MUST also specify the expected volume of data per day per
destination class.

Once a network interface is online, the Application may use outbound-initiated
AF_INET/AF_INET6 sockets from within the container environment to reach the
specified endpoints.

Approval of IP socket communication does not imply unmanaged or
application-selected network reachability. The System Operator remains
authoritative for which destination classes, endpoints, protocols, ports,
and volumes are allowed. Platform implementations MAY satisfy approved IP
socket communication using direct routing, NAT, firewall rules,
forwarding, transparent proxies, shared upstream connections, or other
platform-controlled mechanisms, provided the Application can use standard
socket APIs from within its execution environment and the approved policy
is enforced.

Approved IP socket communication may be satisfied through proxying, NAT,
forwarding, or shared upstream connectivity. Regardless of the platform
mechanism used, the Application remains responsible for its application-layer
security behavior. The operator remains responsible for the deployment policy,
operator-managed trust configuration, and operation of operator-managed
platform and EMS components. See Security considerations below.

Inbound connections towards the Application are only supported for the local
destination class defined below and disallowed from other destination classes.

.. note::

  Application-visible IP socket communication from within the Application
  execution environment is NOT REQUIRED by every GEISA device. ADM-conformant
  platforms still require IP connectivity for the ADM LwM2M over CoAP path, but
  that platform-managed IP connectivity is distinct from Application-managed IP
  socket access. Applications can be designed to require IP socket
  communication or, if it is not available, fall back to message-based
  communication functionality.

  Additionally, not all destination classes are REQUIRED by a GEISA device. An
  operator or device manufacturer may only support a subset depending on
  capabilities, deployment architecture, or security policy. The availability
  of an approved application IP communication path is not guaranteed.
  Applications may encounter intermittent or prolonged outages, or may run on
  devices where some or all destination classes are not provisioned.
  Applications approved for IP socket communication SHOULD be designed to
  handle these conditions, operate in a degraded mode where appropriate, avoid
  producing excessive alarms or logs, and fall back to message-based
  communication only when that behavior is implemented by the application and
  allowed by deployment policy.


Interface Types
^^^^^^^^^^^^^^^

The method of connectivity that a device provides can vary from a home Wi-Fi
device (e.g. router) providing Internet connectivity, to private Wi-Fi for
partner integrations, or to a variety of operator-maintained connectivity
options such as shared Wi-Fi hotspots, cellular, mesh, wired, or proprietary
interfaces.

Applications need to know which (or multiple) of these are available and online
for use at any given time; however, enumerating both the technology and the
allowable use cases that they can transport can become complex quickly.

Example types of network interfaces:

- Wi-Fi - Home (device is client)
- Wi-Fi - Meter (device is AP)
- Wi-Fi - Operator/Partner-Hotspot (device is client)
- Cellular - Internet APN
- Cellular - Private APN
- Ethernet - Home
- Ethernet - Private/Partner Devices
- Field Area Network

Other network interfaces that may be available (but out of scope of
*IP socket*-based communication in GEISA at this time) are:

- Bluetooth / Bluetooth LE
- IoT integrations via 802.15.4 technologies (Zigbee, Thread, etc.)
- Other wired connectivity or peripherals: RS232/485, USB connected devices, etc.


Destination Classes
^^^^^^^^^^^^^^^^^^^

The device may have zero, one, or multiple interfaces online at any given
time. Applications are not required to know these details but instead only
need to know if their desired endpoints are accessible under the approved
deployment policy and what volume limits are in place.

Each endpoint an application defines falls into one of these categories:

- Internet Endpoint (ex: Public Cloud)
- Operator Endpoint (ex: Private Cloud)
- Local Endpoint (something off-device, but on-net and private)
- Message based (LwM2M)

For each of these classes, applications have a defined volume limit for when
that class is metered.


Network State
^^^^^^^^^^^^^

For each destination class, applications have a network state that informs the
application if and what volume of communication is available as described in
:doc:`status`.

An application can request communication with more than one class of endpoint
and would need a network status indicator for each class separately.  For
example, it may communicate with both Internet Endpoints as well as Local
Endpoints.

Applications may observe a mismatch between reported network state and their
own communication attempts. This version of the GEISA specification does not
define a dedicated application-to-platform diagnostic reporting mechanism.
Implementations MAY expose troubleshooting, logging, or diagnostic
reporting through implementation-specific mechanisms or through future GEISA
status, logging, or messaging extensions.


Volume Limits
^^^^^^^^^^^^^

Each destination class may be metered depending on which underlying technology
transports the data.  A Home Wi-Fi network would normally be considered unlimited
whereas a cellular connection would be metered in order to keep the device under a
monthly volume limit.

An application developer MUST define volume limits per destination class in
their Application Vendor Manifest.  These limits may be overridden by the
operator at deployment time when converting the Application Vendor Manifest
into a Deployment Manifest.

These volume limits are specified as a per day (24 hour period) limit in
bytes. For interoperability, application-visible volume accounting is based
on application payload bytes. For IP socket communication, this is measured
at the application socket boundary. For message-based communication, this
is measured at the GEISA app-message payload boundary. Both transmit and
receive application payload bytes count toward the application's limit.

Operators may account for expected protocol, security, encapsulation,
tunnel, or lower-layer overhead when setting limits. The platform MAY
separately measure or estimate interface-level bytes, including protocol
and lower-layer overhead, for operator visibility, network planning,
analysis, audit, and subsequent adjustment of limits.

The daily rollover mechanism and reset period are deployment and platform
policy. This version of the specification does not define an
application-visible transaction for configuring those policy values. The
application obtains the remaining volume limits and the next reset time via
:doc:`/api/status`.

If an application exhausts its metered volume quota for one or more
destination classes, the policy for those classes remains *metered* and
the remaining metered byte count is reported as zero until the next reset
or operator adjustment. Exhaustion of a metered quota does not change the
policy to *zero*.

The *zero* policy indicates that the Application currently has no usable
allocation for that destination class, such as where access is not approved
by deployment policy. Volume limits do not apply to destination classes
when the policy is *unlimited*.


Security considerations
^^^^^^^^^^^^^^^^^^^^^^^

For message based communications, the operating environment will provide
encryption and authentication for data passed between the device and head-end
via LwM2M, applications MAY perform further encryption and/or authentication on
top of what :doc:`/adm` provides.

For IP socket based communications, the application is responsible for encryption
and authentication of data passed between the device and its endpoints where
needed.

Applications MUST NOT assume that approved IP socket communication provides
the same security, queuing, retry, or store-and-forward behavior as
GEISA message-based communication unless those behaviors are explicitly
provided by the application protocol or deployment environment.

When a platform uses proxying, forwarding, NAT, tunneling, or shared
upstream connectivity, application-layer security remains the
responsibility of the relevant communication design. Network-layer
mediation can preserve end-to-end application TLS or mTLS semantics.
Applications MAY use certificate pinning, client authentication, or other
application-layer trust mechanisms where supported by their protocol.

.. note::

  This version of the specification does not define an interoperable mechanism
  for an Application vendor to declare whether TLS inspection, explicit
  proxying, or operator-mediated re-origination of application-layer security is
  supported. Operators and platform implementations that use such mechanisms
  are responsible for ensuring that the behavior is compatible with the
  Application, its configured trust material, and the deployment policy. A
  future version may define manifest fields or policy controls for this
  behavior.

Connectivity
^^^^^^^^^^^^

The operating environment is responsible for providing network connectivity
between each Application container environment and network interfaces.

The platform is responsible for implementing policy (by firewall and forwarding
rules), accounting (volume limits), and providing underlying connectivity and
routing between these components.

.. note::

  GEISA does not mandate a specific technology that the implementer of the
  operating environment must use to accomplish this, but does recommend the use
  of Linux network namespaces, veth interfaces, and iptables/nftables for
  filtering, NAT, and accounting.  The implementer may also make use of
  on-device transparent proxies if desired, however the Application must be
  able to use AF_INET/AF_INET6 sockets from within the container environment
  with any encoding and protocol within.

The operating environment MUST provide a local lo interface within the container
environment for each application. The local lo interface must be up and configured
with both 127.0.0.1 and ::1 addresses.

The apparent address, route, or connection path visible to an Application
inside its container environment is not required to correspond one-to-one
with the physical interface, upstream session, or operator network path
used by the platform. Applications should treat the socket interface as
the approved local execution-environment abstraction and rely on Platform
and App Status for communication availability and quota state.


Policy Rules
^^^^^^^^^^^^

The :doc:`/adm/manifests` include a set of Endpoints the Application is expecting
to communicate with.  The application must list every endpoint that it wishes
to communicate with per destination class.

DNS
^^^

.. warning::

  TODO: should we forgo DNS for GEISA 1.0?

While policy rules are defined using IP addresses, Applications may use DNS
queries to avoid hard-coded IP literals within their application source or
configuration files.

The Operating Environment and Network Manager must provide DNS services for
applications to use, however the scope of resolution may be limited particularly
for devices that are not or are poorly Internet connected.

GEISA highly recommends that the Operating Environment implement a caching
local resolver that honors TTL to reduce network traffic off-device due to
repeated application lookups for the same name.

The application must be able to reach DNS services from within the container
environment by using standard Linux libraries (i.e., libnss/resolvconf/etc.)

DNS in a multi-tenant and multi-interface environment can get quite complex.
For example, an operator may implement their Operator Endpoints using a
dedicated private TLD and configure the resolver to direct DNS lookups for that
TLD over their private network where other TLDs for Internet Endpoints use a
home Wi-Fi or Internet-connected Cellular provider's supplied DNS.


Local Endpoint Considerations
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Local Endpoints are defined to allow an Application access to local resources
on a connected network.  Typically this would be for purposes of local device
integrations such as EVSE, Solar Inverter and battery storage equipment, smart
plugs and similar devices.  This class is typically only available for devices
that are connected to a home or Meter hosted Wi-Fi, or wired connection, for
example.

Unlike the operator and Internet destination classes, the local destination
class allows additional functionality:

- Inbound access, including multicast and broadcast
- Outbound multicast and broadcast

As the IP addressing of the connected network are not known and not static
between devices, the Application Manifest cannot list destination/source IP
addresses for policy rules, but instead only protocol/port and multicast groups.

An application requesting inbound access in its manifest requires that the
platform create that inbound mapping from the appropriate local interface (such
as a WiFi interface) into the application container environment.  When
requesting a port mapping, both IPv4 and IPv6 MUST be mapped if the local
interface supports both.

Many common local device protocols use multicast or broadcast for discovery and
registration.  Applications SHOULD be able to both send to IP multicast groups
and register IP multicast groups for receipt.  If specified in the application
manifest, the platform will register those addresses on the appropriate local
interface and forward received packets that match both the multicast/broadcast
address and the inbound protocol/port into the application container environment.

Multiple applications MAY register the same IP multicast group at the same time;
however, they MUST NOT register the same protocol/port.  The platform and/or ADM
system MUST arbitrate inbound protocol/port requests in each application manifest
to prevent multiple applications from requesting the same inbound protocol/port
combination.


MQTT Details
============

- QoS: 1 / Acknowledged R/R
- Req Topic: ``geisa/api/message/upstream/req/<userid>``
- Rsp Topic: ``geisa/api/message/upstream/rsp/<userid>``
- Req Topic: ``geisa/api/message/downstream/req/<userid>``
- Rsp Topic: ``geisa/api/message/downstream/rsp/<userid>``

.. note::

   In the topic definitions, ``<userid>`` refers to the platform-local
   identifier of the requesting GEISA application instance (see :doc:`/glossary` for
   additional information).


API Permissions
===============

- Application:

  - Publish: ``geisa/api/message/upstream/req/<userid>``
  - Publish: ``geisa/api/message/downstream/rsp/<userid>``
  - Subscribe: ``geisa/api/message/upstream/rsp/<userid>``
  - Subscribe: ``geisa/api/message/downstream/req/<userid>``

- Platform:

  - Wildcard Subscribe: ``geisa/api/message/upstream/req/#``
  - Wildcard Subscribe: ``geisa/api/message/downstream/rsp/#``
  - Publish: ``geisa/api/message/upstream/rsp/<userid>``
  - Publish: ``geisa/api/message/downstream/req/<userid>``


Transaction Data
================

.. warning::

  Need to add refererence to content within |geisa-schemas-repo| here.




|geisa-pyramid|
