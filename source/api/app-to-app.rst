
..
  Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
  Security Alliance (GEISA), a Series of LF Projects, LLC
  This file is licensed under the Community Specification License 1.0
  available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

.. _api-app-to-app:

App-to-App Communication
------------------------

|geisa-api-hdr|


By default, each Application running within the GEISA EE does not know about the existence of and cannot communicate with other Applications running on the same device to enforce the Application Isolation Principal.  Applications generally communicate with and through the GEISA platform APIs not with other Applications.

There are, however, use cases where modularization, collaboration, system services, or other conditions require specific Applications to communicate with other specific Applications within the same device.

GIESA allows selective App-to-App communication within the same device if requested by an Application Publisher and approved for deployment by a System Operator.

GEISA conformant devices implementing the GIESA API pillar are required to implement Platform support for App-to-App communication.

.. note::

   App-to-App communication described in this section is for on-device communication only. Communication between Apps on separate Edge devices is not provided by this API.


Platform implementation
^^^^^^^^^^^^^^^^^^^^^^^^^

Each App installed on a device MUST not know about another App installed or running on the same device unless permission to communicate is given.

App-to-App messages use the GEISA API with the GEISA platform MQTT broker relaying messages between apps when permitted.

Both Request/Response and Publish/Subscribe style messages are supported. An Application MAY offer services to other Applications, it MAY use services of other Applications, or both.

Each Application offering services MUST provide a service name for each service.  A service name MAY be the same as the Application's Vendor assigned Application ID as described in :doc:`../adm/manifests`, or it MAY be a separate name describing the service.  In either case, like the Application ID a service name MUST be in Reverse DNS Name Notation.  A single Application MAY offer more than 1 service to provide users of those service different functionality.

An Application Vendor SHOULD consider a service name for their offered services that is separate from the Application ID to preserve flexibility if they wish to rename, re-purpose, or replace their applications in the future while preserving the same offered services to other Applications, however the vendor MAY use a service name that is identical to the Application ID.

GEISA recommends ``tld.companyname.geisa.servicename`` for services offered by Applications, for example, ``com.example.geisa.summaryservice``.


Application Manifest
^^^^^^^^^^^^^^^^^^^^

If an Application supports sending and/or receiving of App-to-App messages, that capability SHALL be listed in the Application Manifest.

Up to 4 types of communication are listed in a Manifest describing what services that Application provides and consumes:

- Receiving and responding to unsolicited R/R messages from other Apps
- Sending R/R request messages to other Apps
- Publishing messages to other interested Apps
- Subscribing to messages published by other Apps

If present in the Application Deployment Manifest, the GEISA Platform allows specific Apps to communicate with other specific Apps via the GIESA API using MQTT topic permissions.

.. note::

   Applications offering services (Publish or Respond) do not list in the Manifest what other Apps are allowed to use those services.  This means an Application Publisher offering services will not know what other apps MAY use those services at publication time.  The System Operator is encouraged to determine compatibility before deploying an Application that uses another Application's services.


An `app2app` section in the Manifest such as the examples below is added to each Application:

.. code-block:: json
  :linenos:

  "app2app": {
    "publish": [
      "com.example.geisa.fooservice",
     ],
    "subscribe": [
      "org.example.geisa.barservice",
      "net.example.geisa.barapp",
     ],
    "respond": [
      "com.example.geisa.fooservice",
     ],
    "request": [
      "org.example.geisa.bazapp",
     ],
  },


There are up to 4 sections in the Manifest.  `publish` and `respond` are service names this Application is offering, while `subscribe` and `request` are service names of other Applications that this Application will use.


Runtime and Dependency Considerations
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

A GEISA Application does not know about the existence and runtime status of another specific Application unless it can successfully communicate with that Application via approved messages.  If no messages are received from that other Application, the reason is unknown.

Dependencies are not enforced by the platform or ADM/EMS such as a requirement that App A can only be installed or run if it App B is also running.  Applications MUST detect and handle missing applications at runtime in this version of GEISA.


Security Considerations
^^^^^^^^^^^^^^^^^^^^^^^

If a System Operator grants permission for a set of Applications to communicate, they should consider the possible impact on information sharing between, proxying of permissions given, compromise of, or control of one application from another.

A GEISA platform implementation is not expected to inspect, limit, or alter the payloads of App-to-App communication.

When communication occurs at runtime, each Application will be aware of the peer's Application ID by examining the MQTT topic used.


MQTT Details
============

Both of the applications involved as well as the GEISA platform implementation must be able to generate MQTT topics based on the permissions in each App's manifest.  All App-to-App communication occurs within the MQTT hierarchy below the ``geisa/api/app2app/...`` topic.

In the samples below, App "A" is the App offering services (Publish or Respond) and App "B" is the App using the service (Subscribe or Request).

"SName" is App A's service name defined in its Manifest, "AppID-A" is App A's name, and "AppID-B" is App B's name.


- QoS: 0 / Unacknowledged
- Topic: ``geisa/api/app2app/pub/<SName>/<AppID-A>``


- QoS: 1 / Acknowledged R/R
- Req Topic: ``geisa/api/app2app/req/<SName>/<AppID-B>``
- Rsp Topic: ``geisa/api/app2app/rsp/<SName>/<AppID-B>/<AppID-A>``

.. note::

   The `<AppID-A>` suffix is informational.  Subscribing Apps SHALL use a wildcard subscribe at that level.


API Permissions
===============

- Application A 'publish' permission

  - Publish: ``geisa/api/app2app/pub/<SName>/<AppID-A>``

- Application B 'subscribe' permission

  - Wildcard Subscribe: ``geisa/api/app2app/pub/<SName>/#``

- Application A 'respond' permission

  - Wildcard Subscribe: ``geisa/api/app2app/req/<SName>/#``
  - Publish: ``geisa/api/app2app/rsp/<SName>/<AppID-B>/<AppID-A>``

- Application B 'request' permission

  - Wildcard Subscribe: ``geisa/api/app2app/rsp/<SName>/<AppID-B>/#``
  - Publish: ``geisa/api/app2app/req/<SName>/<AppID-B>``


Transaction Data
================

The payloads of each App-to-App message are opaque, It is up to the Application Vendors involved to mutually agree upon payload formats and contents for their Service Name(s).


|geisa-pyramid|
