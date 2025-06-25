Instantaneous Data
-------------------

|geisa-api-hdr|

Summary
=========
Instantaneous data is always available to authorized applications.  There is no need to
activate it or request.  Applications can simply subscribe to the topic.

Instantaneous data provides a continuous stream of metrological data as provided by the 
host device.  Data is pushed at least once a second.  Platforms MAY push data more frequently;
however, data push periodicity MUST be consistent.  The instantanous data push periodicity
MUST be reported in the :doc:`/api/enumeration` transaction.

To enable application developers to have a consistent environment, the instantaneous data
message includes many mandatory measurements.  
Simultaneously, GEISA recognizes that data which may be appropriate to require from every
AC electric meter may be problematic to obtain from DC meters or fault indicators, or 
load tap changers or other devices.  To address this, GEISA uses the concept of a
*device type*.  The device type must be reported as part of the :doc:`/api/enumeration`.

The specific values required to be published by a GEISA API conformant platform will depend
on the device type.  
Presently, GEISA offers two device types: AC electric meter and unspecified.
Additional device types may be define in the future.

.. csv-table:: Instantaneous Data
  :header-rows: 1
  :file: /api/instantaneous.csv

.. note:: 

  Some jurisdictions, like Canada, prefer to use vectorial calculations rather than
  arithmetic calculations for generating metered quantities.  Rather than having the
  instantaneous data feed provide both, a single stream of data is offered.  Whether
  the platform is providing arithmetic values or vectorial values is indicating
  by the :doc:`/api/enumeration` transaction.


MQTT Details
=============
- QoS: 0 / Unacknowledged
- Topic: ``geisa-stream``

API Permissions
================
- Read-only
- ``geisa-stream`` permission required to access

Transaction Data
=================

.. warning:: 
  
  Need to add protobuf stuff here.


|geisa-pyramid|
