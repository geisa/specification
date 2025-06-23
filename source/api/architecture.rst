API Architecture
--------------------

|geisa-api-hdr|

Rather than provide an interface library, and in the process potentially 
restrict which languages are suitable for use with GEISA, GEISA provides
a message bus API.  GEISA applications can make requests over the message
bus and receive data back.  Libraries for accessing the message bus from
C (and languages that can consume Linux C libraries directly) are provided
by the GEISA EE |geisa-ee-globe| (see :doc:`/base-libraries`).  
Programming languages that are better served with other libraries can 
include the necessary libraries to access the message bus in their container image.

.. admonition:: To-Do

   Decide on message bus technology.  Current candidates are ZeroMQ and DBus.
   MQTT has also been suggested.


|geisa-pyramid|



