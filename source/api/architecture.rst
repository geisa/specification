API Architecture
--------------------

|geisa-api-hdr|

Rather than provide an interface library, and in the process potentially 
restrict which languages are suitable for use with GEISA, GEISA provides
a message bus API.


GEISA uses `MQTT <https://mqtt.org>`_ as its message bus.  A GEISA platform SHALL
provide a MQTT broker and daemon(s) that GEISA applications interact with.
APIs are either Request/Response (R/R) type messages from Application
to Platform and back, or published data from the Platform to all interested
Applications.  The architecture of the platform daemons that both respond to R/R
messages and post periodic and event data to the MQTT broker is platform dependent.

GEISA applications MAY interact with the GEISA MQTT broker using the MQTT client library
that best suites their application's programming language and architecture.  MQTT
client libraries exist for many programming languages and developers MAY make use of
one provided by the GEISA EE |geisa-ee-globe| (see :doc:`/lee/base-libraries` and :doc:`/vee/base-libraries`) or bundle
their own with their application.

GEISA API conformant platforms SHALL:

- provide an MQTT version 5 broker.
- support all API transactions listed as mandatory within this specification
- use `Protocol Buffers <https://protobuf.dev>`_ (edition=2023) for message payload
- use the MQTT topics indicated for the API transactions
- support the Protobuf definition indicated for the API transactions found at |geisa-schemas-repo|

Because of the potentially very high-volumes of data involved in accesssing metrology 
:doc:`/api/waveform`, it is handled as a special case.  
The waveform data transaction allows applications to obtain the frame format and 
platform specific details regarding the waveform data (e.g. sampling rate, sample resolution, etc.)
and to request that the waveform data stream is activated (or deactivated),
but the waveform data itself is provided as a raw-binary data structure pushed
from the platform to any target application containers using a socket and data format
as described in :doc:`/api/waveform`.

The GEISA API is designed as an **internal** API within the platform.  
It is not intended to be exposed to a general network environment.  
For security reasons platform implementations MUST not expose the 
GEISA API MQTT implementation via external network interfaces.  

The GEISA API MQTT implementation may only be exposed via ``localhost``
or via virtual interfaces to GEISA app containers.  GEISA applications determine how
to connect to the broker from data in a local configuration file `/opt/geisa/config.binpb`
within the Application container environment.

.. Note::

  Platforms or applications running on a GEISA application MAY provide
  externally MQTT implementations separate from the GEISA API MQTT implementation

The GEISA API SHALL use MQTT standard port 1883. GEISA API transactions
are not sent over external network interfaces or shared network interfaces.
GEISA API transactions SHALL NOT require the use of TLS.

To enable authentication, GEISA EE |geisa-ee-globe| conformant applications
SHALL be assigned a unique user ID and token by the platform.  Applications use the
credentials to authenticate with the MQTT message broker providing the GEISA API.

The platform SHALL generate and manage application user ID and tokens locally
on-device. User IDs and tokens MUST be alphanumeric printable strings.
Tokens MUST contain random data of sufficient length.  User ID values persist for
the life of the application's installation and tokens persist for at least the life of
application's execution.

.. Note::

  It is possible for a platform to use other means to determine which application
  instance is connecting to the message broker and pass authorization information
  out-of-band, and skip authentication entirely.  Such an approach, while possible,
  requires platform vendors to customize or otherwise modify the MQTT broker.  
  This simplified approach of passing authentication credentials to the application
  as part of its local configuration enables the light-weight authentication 
  of applications to the broker appropriate for a closed environment, without 
  requiring unwanted customizations.  It is understood that this approach is wholly
  inappropriate in a general network context.

API requests SHALL be sent at MQTT QoS level 1, At least once / acknowledged delivery.
The GEISA API MQTT broker shall acknowledge API requests.
GEISA API responses are sent at the QoS level indicated for the transaction, but
most messages are QoS level 0, At most once / unacknowledged.  

MQTT topics used by the API are listed within each section that follows.

|geisa-pyramid|



