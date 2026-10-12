
..
  Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
  Security Alliance (GEISA), a Series of LF Projects, LLC
  This file is licensed under the Community Specification License 1.0
  available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

.. index:: single: API Architecture

API Architecture
----------------

|geisa-api-hdr|

Rather than provide an interface library, and in the process potentially 
restricting or specifying which languages are suitable for use with GEISA, 
GEISA intentionally provides a message bus API allowing for additional 
implementor flexibility.

.. index:: single: Message Bus Communication

Message Bus Communication
^^^^^^^^^^^^^^^^^^^^^^^^^

GEISA uses `MQTT <https://mqtt.org>`_ as its reference message bus.  A GEISA
platform SHALL provide a MQTT broker and daemon(s) that GEISA applications
interact with.  GEISA applications MAY interact with the GEISA MQTT broker
using the MQTT client library that best suits their application's programming
language and architecture.  MQTT client libraries exist for many programming
languages and developers MAY make use of one provided by the GEISA EE
|geisa-ee-globe| (see :doc:`/lee/base-libraries` and
:doc:`/vee/base-libraries`) or bundle their own with their application.

APIs are either Request/Response (R/R) type messages from Application
to Platform and back, or published data from the Platform to all interested
Applications.  The architecture of the platform daemons that both respond to R/R
messages and post periodic and event data to the MQTT broker is platform-dependent.
Request/Response (R/R) type and published data type messages are also possible
between Applications using the :doc:`/api/app-to-app` capability.

GEISA API conformant platforms SHALL:

- provide an MQTT broker version 5 or later.
- support all API transactions listed as mandatory within this specification
- use `Protocol Buffers <https://protobuf.dev>`_ (``syntax=proto3``) for message payloads
- use the MQTT topics indicated for the API transactions
- support the Protobuf definitions indicated for the API transactions found 
  at |geisa-schemas-repo| according the version of the specification.

.. Note::

   GEISA uses git tags to track which protobuf schemas are associated with a
   given version of the specification.  Schemas referenced by this version of
   the specification are tagged with |geisa-spec-version|.

The GEISA API is designed as an **internal** API within the platform.  It is 
not intended to be exposed to a general network environment.  For security 
reasons, platform implementations MUST not expose the GEISA API MQTT 
implementation via external network interfaces.  

.. Note::

  Platforms or applications running in a GEISA-complaint COE MAY choose to 
  provide external MQTT implementations separate from the GEISA API MQTT 
  implementation.

|geisa-pyramid|

.. index:: single: Message Bus Credentials

Message Bus Connection and Credentials
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Conformant platforms SHALL provide the GEISA API over IP or unix domain
socket.  Conformant platforms MAY provide both.

When connecting over local IP, the GEISA API SHALL use MQTT standard port 1883.
GEISA API transactions are not sent over external network interfaces or shared
network interfaces.  GEISA API transactions SHALL NOT require the use of TLS.
IP based connections to the GEISA API MQTT implementation may only be exposed
via ``localhost`` or via virtual interfaces to GEISA application containers.

When connecting over a unix domain socket, the platform shall provide a socket
path that the edge application can use as is to establish a socket connection.

To enable authentication, GEISA EE |geisa-ee-globe| conformant applications
SHALL be assigned a unique user ID and token by the platform.  Applications use 
the credentials to authenticate with the MQTT message broker providing the 
GEISA API.

The platform SHALL generate and manage application user ID and tokens locally
on-device. User IDs and tokens MUST be alphanumeric printable strings,
restricted to the UTF8 character set.  Implementations should avoid quotation
marks, equals signs and backslashes, as these may complicate parsing of the
configuration file.  Tokens MUST contain a minimum of twelve (12) bytes of
random data.  Sixteen (16) bytes is preferred.  User ID values persist for the
life of the application's installation and tokens persist for at least the life
of an application's execution, but may persist longer.  Tokens SHOULD be a
sequence of random characters, rather than a predictable value.

.. Note::

  It is possible for a platform to use other means to determine which application
  instance is connecting to the message broker and pass authorization information
  out-of-band, and skip authentication entirely.  Such an approach, while 
  possible, requires platform vendors to customize or otherwise modify the MQTT 
  broker.  This simplified approach of passing authentication credentials to 
  the application as part of its local configuration enables the light-weight 
  authentication of applications to the broker to be appropriate for a closed 
  environment, without requiring unwanted customizations.  It is understood that 
  this approach is wholly inappropriate in a general network context.

|geisa-pyramid|

.. index:: single: Message Bus Topics

.. index:: single: Topics

.. index:: single: Message Bus Reliability

Message Bus Topics and Reliability
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

API requests SHALL be sent at MQTT QoS level 1, *At least once*, with 
acknowledged delivery.  The GEISA API MQTT broker shall acknowledge API requests.
GEISA API responses are sent at the QoS level indicated for the transaction, 
but most messages are QoS level 0, *At most once* and unacknowledged.  

MQTT topics used by the API are listed within each subsequent section.

|geisa-pyramid|

.. index:: single: Non-Message Bus Communication

Non-Message Bus Communication
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

While most application to platform communication is performed over the MQTT 
message bus, there are a few exceptions:

In order for an application to establish a connection to the MQTT message
bus, the address of the listener (either host and port or socketpath) and per-application credentials are
provided out-of-band from platform to application. GEISA applications determine
how to connect to the broker from this data.

For GEISA LEE |geisa-lee-tux|, this information SHALL be available at the
well-known location ``/etc/geisa/mqtt.conf`` within the application
container environment.

For GEISA VEE |geisa-vee-cloud|, this information SHALL be available in the
file ``mqtt.conf`` which shall be available in the working path of the edge
application.

The format of the ``mqtt.conf`` file shall be key/value pairs separated by an
equals sign.  The file shall contain at least an entry for ``SOCKET`` or
entries for both ``HOST`` and ``PORT``.  Platforms that support both IP and
unix domain sockets should include all three.  Edge applications MUST support
both ways of connecting.

.. code-block:: console
   :caption: Sample mqtt.conf file

        $ cat /etc/geisa/mqtt.conf
        HOST=localhost
        PORT=1883
        SOCKET=/tmp/broker
        USERID=AppUserId001
        PASSWORD=7DkXPCFD5fgQ+Kto4lwi

.. Note::

  As a reminder, each LEE |geisa-lee-tux| application is run within its own
  isolated environment enabling this data to be placed within a fixed
  well-known location and remain unencrypted accessible only to a single
  instance of a single application.

  Similarly, VEE |geisa-vee-cloud| implementations must ensure that each
  application has a unique ``mqtt.conf`` that is not accessible by any other
  application.

Because of the potentially very high-volumes of data involved in accessing
metrology :doc:`/api/waveform`, it is intentionally handled as a special case.
The API transactions over the message bus allow applications to obtain the
frame format and platform specific details regarding the waveform data (e.g.
sampling rate, sample resolution, etc.) and to request that the waveform data
stream is activated (or deactivated), but the waveform data itself is provided
as a raw-binary data structure pushed from the platform to any target
application containers using a socket and data format as described in
:doc:`/api/waveform`.

|geisa-pyramid|



