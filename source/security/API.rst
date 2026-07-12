
..
  Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
  Security Alliance (GEISA), a Series of LF Projects, LLC
  This file is licensed under the Community Specification License 1.0
  available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

API
^^^

GEISA provides a message based API via MQTT.  Conformant implementations will
provide the application a local port via the :term:`AII` wherein they can
connect to the MQTT broker.  This is discuss in more detail in
:doc:`/api/architecture`.


API Authentication and Encryption
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Several highlights of API Authentication and Encryption are repeated here:

* Connections are over localhost or virtual network links between the
  application isolation implementations (i.e. containers, virtual machines,
  virtual execution enviroments, etc.) and the broker.

* The broker MUST not be exposed to any external network interface.  Doing so
  is a violation of this specification.

* Encryption is NOT used for this link.  While the industry has generally moved
  to requiring encryption everywhere, GEISA has chosen not to do this because:

  - The links are already completely isolated through the AII.

  - Doing so would introduce an internal key management or certificate management
    requirement. 

  - Encryption would add unnessary overhead on a constrained embedded device.

  - The GEISA threat model already addresses attacks against the API via
    other means.

As discussed in :doc:`../api/architecture`, platforms are responsible for issuing
applications their login credentials to access the broker.  The userid and
password (referred to as a token), MUST be printable alphanumeric characters.
The userid MUST be unique to the application instance and persist for the life
the application installation.  The recommended length of the application userid
is eight (8) characters.  The recommended length of the login token (password)
is sixteen (16) random characters.


API Access Control and Authorization
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The Application Manifest (see
https://github.com/geisa/schemas/blob/main/geisa-application-manifest-schema.json)
allows the :term:`System Operator` to determine which APIs an application is
allowed to access.  As of this version of the GEISA specification, the
deployment manifest supports six API controls:

- actuator-status: Allows applications to read the status of actuators

- actuator-control: Allows applications to control actuators

- instantaneous: Allows applications to obtain instantaneous readings & billing
  data.  (These may be split into separate permissions in future versions of the
  specification).

- messaging: Allows applications to send and receive application messages
  (limited by the application's message allocation)

- sensor: Allows applications to read sensor data

- waveform: Allows applications to read waveform data

Applications always have access to the :doc:`../api/discovery` and :doc:`../api/status` APIs.

Access to specific network interfaces is also controlled via the Application
Manifest.  Please see :doc:`../security/network` for details.

Platform implementations MUST enforce the API permissions granted by the
application manifest.

|geisa-pyramid|
