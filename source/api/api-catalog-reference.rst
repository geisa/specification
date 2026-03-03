..
  Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
  Security Alliance (GEISA), a Series of LF Projects, LLC
  This file is licensed under the Community Specification License 1.0
  available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

API Catalog Reference
=====================

|geisa-api-hdr|

This section is not intended to be read as a narrative description of system
behavior, but to serve as a structured reference for developers
implementing or integrating with the GEISA API.

It serves as a comprehensive catalog of all defined API calls, including:

- MQTT topic structures
- Required and optional parameters
- Message payload formats
- Expected responses
- Error conditions, where applicable

GEISA APIs are implemented using MQTT topic hierarchies. Each API call is
defined by:

- The MQTT topic structure
- The direction of message flow
- The associated request and response payload definitions
- References to relevant sections of the GEISA specification that define
  relevant behavior and constraints

Discovery APIs
--------------

This section defines the GEISA Discovery-related API calls.

MQTT Characteristics
~~~~~~~~~~~~~~~~~~~~

+----------------------+----------------------------------------------+
| Property             | Value                                        |
+======================+==============================================+
| QoS                  | ``1`` (acknowledged)                         |
+----------------------+----------------------------------------------+
| Retained             | No                                           |
+----------------------+----------------------------------------------+
| Clean Session        | Implementation defined                       |
+----------------------+----------------------------------------------+

Topics
~~~~~~

+-------------------------------+-----------------------------------------------+------------------+
| Function                      | Topic                                         | Direction        |
+===============================+===============================================+==================+
| Platform Discovery Request    | ``geisa/api/platform-discovery-req``          | App → Platform   |
+-------------------------------+-----------------------------------------------+------------------+
| Platform Discovery Response   | ``geisa/api/platform-discovery-rsp``          | Platform → App   |
+-------------------------------+-----------------------------------------------+------------------+
| Application Manifest Request  | ``geisa/api/app-manifest-req/<userid>``       | App → Platform   |
+-------------------------------+-----------------------------------------------+------------------+
| Application Manifest Response | ``geisa/api/app-manifest-rsp/<userid>``       | Platform → App   |
+-------------------------------+-----------------------------------------------+------------------+

Permissions
~~~~~~~~~~~

+------------+-------------------+-----------------------------------------------+
| Role       | Action            | Topic                                         |
+============+===================+===============================================+
| Application| Publish           | ``geisa/api/platform-discovery-req``          |
+------------+-------------------+-----------------------------------------------+
| Application| Subscribe         | ``geisa/api/platform-discovery-rsp``          |
+------------+-------------------+-----------------------------------------------+
| Application| Publish           | ``geisa/api/app-manifest-req/<userid>``       |
+------------+-------------------+-----------------------------------------------+
| Application| Subscribe         | ``geisa/api/app-manifest-rsp/<userid>``       |
+------------+-------------------+-----------------------------------------------+
| Platform   | Subscribe         | ``geisa/api/platform-discovery-req``          |
+------------+-------------------+-----------------------------------------------+
| Platform   | Publish           | ``geisa/api/platform-discovery-rsp``          |
+------------+-------------------+-----------------------------------------------+
| Platform   | Wildcard Subscribe| ``geisa/api/app-manifest-req/*``              |
+------------+-------------------+-----------------------------------------------+
| Platform   | Publish           | ``geisa/api/app-manifest-rsp/<userid>``       |
+------------+-------------------+-----------------------------------------------+

Message Types
~~~~~~~~~~~~~

+--------------------------------------+-----------+
| Message Name                         | Category  |
+======================================+===========+
| ``GeisaPlatformDiscovery_Req``       | Request   |
+--------------------------------------+-----------+
| ``GeisaPlatformDiscovery_Rsp``       | Response  |
+--------------------------------------+-----------+
| ``GeisaApplicationManifest_Req``     | Request   |
+--------------------------------------+-----------+
| ``GeisaApplicationManifest_Rsp``     | Response  |
+--------------------------------------+-----------+

Related
~~~~~~~

:ref:`Platform Discovery APIs <api-platform-discovery>`

Platform Status APIs
--------------------

This section defines the GEISA Platform Status–related API calls.


MQTT Characteristics
~~~~~~~~~~~~~~~~~~~~

+----------------------+----------------------------------------------+
| Property             | Value                                        |
+======================+==============================================+
| QoS                  | ``0`` (unacknowledged)                       |
+----------------------+----------------------------------------------+
| Retained             | No                                           |
+----------------------+----------------------------------------------+


Topics
~~~~~~

+--------------------------------------+-----------------------------------------------+------------------+
| Function                             | Topic                                         | Direction        |
+======================================+===============================================+==================+
| Platform Status Broadcast            | ``geisa/api/platform-status``                 | Platform → App   |
+--------------------------------------+-----------------------------------------------+------------------+
| Platform Application Status          | ``geisa/api/platform-app-status/<userid>``    | Platform → App   |
+--------------------------------------+-----------------------------------------------+------------------+
| Application Platform Status          | ``geisa/api/app-platform-status/<userid>``    | App → Platform   |
+--------------------------------------+-----------------------------------------------+------------------+


Permissions
~~~~~~~~~~~

+------------+-------------------+-----------------------------------------------+
| Role       | Action            | Topic                                         |
+============+===================+===============================================+
| Application| Subscribe         | ``geisa/api/platform-status``                 |
+------------+-------------------+-----------------------------------------------+
| Application| Subscribe         | ``geisa/api/platform-app-status/<userid>``    |
+------------+-------------------+-----------------------------------------------+
| Application| Publish           | ``geisa/api/app-platform-status/<userid>``    |
+------------+-------------------+-----------------------------------------------+
| Platform   | Publish           | ``geisa/api/platform-status``                 |
+------------+-------------------+-----------------------------------------------+
| Platform   | Publish           | ``geisa/api/platform-app-status/<userid>``    |
+------------+-------------------+-----------------------------------------------+
| Platform   | Subscribe         | ``geisa/api/app-platform-status/*``           |
+------------+-------------------+-----------------------------------------------+

Related
~~~~~~~
:ref:`Platform Status APIs <api-platform-status>`

Networking APIs
---------------

This section defines the GEISA Networking-related API calls.


MQTT Characteristics
~~~~~~~~~~~~~~~~~~~~

+----------------------+----------------------------------------------+
| Property             | Value                                        |
+======================+==============================================+
| QoS                  | ``1`` (acknowledged request/response)        |
+----------------------+----------------------------------------------+
| Retained             | No                                           |
+----------------------+----------------------------------------------+


Topics
~~~~~~

+---------------------------+-----------------------------------------------+------------------+
| Function                  | Topic                                         | Direction        |
+===========================+===============================================+==================+
| Message Request           | ``geisa/api/message-req/<userid>``            | App → Platform   |
+---------------------------+-----------------------------------------------+------------------+
| Message Response          | ``geisa/api/message-rsp/<userid>``            | Platform → App   |
+---------------------------+-----------------------------------------------+------------------+


Permissions
~~~~~~~~~~~

+------------+-------------------+-----------------------------------------------+
| Role       | Action            | Topic                                         |
+============+===================+===============================================+
| Application| Publish           | ``geisa/api/message-req/<userid>``            |
+------------+-------------------+-----------------------------------------------+
| Application| Subscribe         | ``geisa/api/message-rsp/<userid>``            |
+------------+-------------------+-----------------------------------------------+
| Platform   | Wildcard Subscribe| ``geisa/api/message-req/*``                   |
+------------+-------------------+-----------------------------------------------+
| Platform   | Publish           | ``geisa/api/message-rsp/<userid>``            |
+------------+-------------------+-----------------------------------------------+


Related
~~~~~~~

:ref:`Networking APIs <api-networking>`

Instantaneous Data APIs
-----------------------

This section defines the GEISA Instantaneous Data–related API calls.


MQTT Characteristics
~~~~~~~~~~~~~~~~~~~~

+----------------------+----------------------------------------------+
| Property             | Value                                        |
+======================+==============================================+
| QoS                  | ``0`` (unacknowledged)                       |
+----------------------+----------------------------------------------+
| Retained             | No                                           |
+----------------------+----------------------------------------------+


Topics
~~~~~~

+------------------------------+-------------------------------------------+------------------+
| Function                     | Topic                                     | Direction        |
+==============================+===========================================+==================+
| Instantaneous Data Broadcast | ``geisa/api/instantaneous-data``          | Platform → App   |
+------------------------------+-------------------------------------------+------------------+


Permissions
~~~~~~~~~~~

+------------+-----------+-------------------------------------------+
| Role       | Action    | Topic                                     |
+============+===========+===========================================+
| Application| Subscribe | ``geisa/api/instantaneous-data``          |
+------------+-----------+-------------------------------------------+
| Platform   | Publish   | ``geisa/api/instantaneous-data``          |
+------------+-----------+-------------------------------------------+


Message Types
~~~~~~~~~~~~~

+----------------------------------+-----------+
| Message Name                     | Category  |
+==================================+===========+
| ``GeisaInstantaneousQuantities`` | Broadcast |
+----------------------------------+-----------+

As defined in |geisa-schemas-repo|


Related
~~~~~~~

:ref:`Instantaneous Data APIs <api-instantaneous-data>`

Waveform Data APIs
------------------

This section defines the GEISA Waveform Data–related API calls.


MQTT Characteristics
~~~~~~~~~~~~~~~~~~~~

+----------------------+----------------------------------------------+
| Property             | Value                                        |
+======================+==============================================+
| QoS                  | ``1`` (acknowledged request/response)        |
+----------------------+----------------------------------------------+
| Retained             | No                                           |
+----------------------+----------------------------------------------+


Topics
~~~~~~

+-------------------+-------------------------------------------+------------------+
| Function          | Topic                                     | Direction        |
+===================+===========================================+==================+
| Waveform Request  | ``geisa/api/waveform-req/<userid>``       | App → Platform   |
+-------------------+-------------------------------------------+------------------+
| Waveform Response | ``geisa/api/waveform-rsp/<userid>``       | Platform → App   |
+-------------------+-------------------------------------------+------------------+


Permissions
~~~~~~~~~~~

+------------+-------------------+-------------------------------------------+
| Role       | Action            | Topic                                     |
+============+===================+===========================================+
| Application| Publish           | ``geisa/api/waveform-req/<userid>``       |
+------------+-------------------+-------------------------------------------+
| Application| Subscribe         | ``geisa/api/waveform-rsp/<userid>``       |
+------------+-------------------+-------------------------------------------+
| Platform   | Wildcard Subscribe| ``geisa/api/waveform-req/*``              |
+------------+-------------------+-------------------------------------------+
| Platform   | Publish           | ``geisa/api/waveform-rsp/<userid>``       |
+------------+-------------------+-------------------------------------------+


Message Types
~~~~~~~~~~~~~

+---------------------------+-----------+
| Message Name              | Category  |
+===========================+===========+
| ``GeisaWaveform_Req``     | Request   |
+---------------------------+-----------+
| ``GeisaWaveform_Rsp``     | Response  |
+---------------------------+-----------+

As defined in |geisa-schemas-repo|


Related
~~~~~~~

:ref:`Waveform Data APIs <api-waveform-data>`

|geisa-pyramid|