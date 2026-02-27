
..
  Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
  Security Alliance (GEISA), a Series of LF Projects, LLC
  This file is licensed under the Community Specification License 1.0
  available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

Instantaneous Data
------------------

|geisa-api-hdr|

Summary
=======
Instantaneous data provides a continuous stream of metrological data as provided 
by the host device, with data being pushed at least once a second.  Platforms 
MAY push data more frequently; however, data push periodicity MUST be consistent.  
The instantanous data push periodicity MUST be reported in the :doc:`/api/discovery` 
transaction.

Instantaneous data is always available to authorized applications.  There is no 
need to specifically request or activate it; applications can simply subscribe 
to the topic.

To enable application developers to have a consistent environment, the 
instantaneous data message includes many mandatory measurements. 

Simultaneously, GEISA recognizes that data which may be appropriate to require 
from every AC electric meter may be problematic to obtain from DC meters or fault 
indicators, load tap changers or other devices.  To address this, GEISA uses the 
concept of a *device type*.  The device type must be reported as part of the :doc:`/api/discovery`.

The specific values required to be published by a GEISA API conformant platform 
will depend on the device type.   
Presently, GEISA offers two device types: AC electric meter and unspecified.
Additional device types may be defined in the future.

.. csv-table:: Instantaneous Data
  :header-rows: 1
  :file: /api/instantaneous.csv

.. note:: 

  Some jurisdictions such as Canada, prefer to use vectorial calculations rather 
  than arithmetic calculations for generating metered quantities.  Rather than 
  having the instantaneous data feed provide both, a single stream of data is 
  offered.  Whether the platform is providing arithmetic or vectorial values is
  indicated by the :doc:`/api/discovery` transaction.

MQTT Details
============
- QoS: 0 / Unacknowledged
- Topic: ``geisa/api/instantaneous-data``

API Permissions
===============

- Application:

  - Subscribe: ``geisa/api/instantaneous-data``

- Platform:

  - Publish: ``geisa/api/instantaneous-data``


Transaction Data
================

- ``GeisaInstantaneousQuantities``

As defined in |geisa-schemas-repo|


|geisa-pyramid|
