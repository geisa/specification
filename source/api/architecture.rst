API Architecture
--------------------

|geisa-api-hdr|

Rather than provide an interface library, and in the process potentially 
restrict which languages are suitable for use with GEISA, GEISA provides
a message bus API.  GEISA applications can make requests over a message
bus and receive data back.  Libraries for accessing the message bus from
C (and languages that can consume Linux C libraries directly) are provided
by the GEISA EE |geisa-ee-globe| (see :doc:`/base-libraries`).  
Programming languages that are better served with other libraries can 
include the necessary libraries to access the message bus in their container image.

GEISA uses `MQTT <https://mqtt.org>`_ as its message bus.  Message definitions are provided for 
each supported transaction.  These definitions indicate exactly what messages
must be sent to make a request of the API, and what messages must be send in response.
GEISA transaction messages are serialized and deserialized 
using `Protocol Buffers <https://protobuf.dev>`_.  
GEISA uses `Protobuf Editions, 2023 <https://protobuf.dev/programming-guides/editions/>`_.
GEISA provides .proto files in its github schema repository, https://github.com/geisa/schemas.

GEISA API conformant platforms SHALL:

- provide an MQTT version 5 broker.
- support all API transactions listed as mandatory within this specification
- use Protocol Buffers (edition=2023) 
- use the MQTT topics indicated for the API transactions
- support the Protobuf definition indicated for the API transactions

Because of the potentially very high-volumes of data involved in accesssing metrology 
:doc:`/api/waveform`, it is handled as a special case.  
The waveform data transaction allows applications to obtain the frame format and 
platform specific details regarding the waveform data (e.g. sampling rate, sample resolution, etc.)
and to request that the waveform data stream is activated (or deactivated),
but the waveform data itself is provided as a raw-binary data structure pushed
from the platform to any target application containers using 

.. admonition:: To-Do

  Need to determine if we are using raw sockets or zeroMQ.

The GEISA API is designed as an **internal** API within the platform.  
It is not intended to be exposed to a general network environment.  
For security reasons platform implementations MUST not expose the 
GEISA API MQTT implementation via external network interfaces.  
The GEISA API MQTT implementation may only be exposed via ``localhost``
or via virtual interfaces to GEISA app containers.

.. Note::

  Platforms or applications running on a GEISA application MAY provide
  externally MQTT implementations separate from the GEISA API MQTT implementation

The GEISA API SHALL use MQTT standard port 1883. GEISA API transactions
are not sent over external network interfaces or shared network interfaces.
GEISA API transactions SHALL NOT require the use of TLS.
To enable authentication, GEISA EE |geisa-ee-globe| conformant applications
SHALL obtain a unique user ID and password assigned to the local application
installation by the platform, from a local configuration file, and use those
credentials to authenticate with the MQTT message broker providing the GEISA API.

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

The GEISA API SHALL receive API requests on the "geisa-req" topic.
API requests SHALL be sent at MQTT QoS level 1, At least once / acknowledged delivery.
The GEISA API MQTT broker shall acknowledge API requests.
GEISA API responses are sent at the QoS level indicated for the transaction, but
most messages are QoS level 0, At most once / unacknowledged.  

|geisa-pyramid|



