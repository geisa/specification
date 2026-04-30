
..
  Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
  Security Alliance (GEISA), a Series of LF Projects, LLC
  This file is licensed under the Community Specification License 1.0
  available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

Glossary
-----------------------------------------------

.. glossary::

   ADC
    Analog-to-digital conversion
    Analog-to-digital converter

   ADM
    Application and Device Management

   AMI
    Advanced Metering Infrastructure

   AII
    Application Isolation Implementation

   API
    Applications Programming Interface

   Application Certifier
    An organization acting in this role that may independently assess, test, 
    and/or countersign application artifacts for validation of behaviors 
    prior to deployment.  Optional in context of this version of the 
    Specification.

   Application Deployment Manifest
    Operator-approved deployment manifest that defines effective
    application deployment parameters for an Application for a target 
    environment.

   Application Publisher
    Organization or entity providing one or more Applications for Operator 
    Testing, Deployment or Certification. Provides a signed package, vendor 
    application manifest and associated collaterals.

   Application Vendor
    Role responsible for application production and publication
    responsibilities in a GEISA workflow.

   CoAP
    Constrained Applications Protocol

   COE
    Common Operating Environment

    The COE is the software platform specification which defines the software
    components, interfaces, and processes needed to implement a GEISA-conformant
    platform.  The COE is designed to be flexible and modular, allowing for a
    variety of implementations that can meet the needs of different use cases
    and environmental constraints.  The COE is intended to provide a common
    foundation for GEISA implementations, while also allowing for customization
    and innovation by implementers.

   DER
    Distributed Energy Resource

    Distributed Energy Resource is a generic term that typically includes
    photo-voltaics coupled with a smart inverter, battery energy storage
    systems, electric vehicles, demand response, and other dispatchable load
    or generation available on the electric distribution network.  DERs are
    typically owned by consumers or businesses, rather than utilities or
    wholesale energy market participants.

   DTLS
    Data Transport Layer Security

   FAN
    Field Area Network, generally owned/operated by the Utility or Operator.
    Sometimes referred to as AMI network.

   EE
    Execution Environment - one of LEE (Linux Execution Environment) or VEE
    (Virtual Execution Environment) which Edge Applications run on.

   EMA
    Edge Management Agent

    The EMA is the logical component of a GEISA ADM conformant platform
    which implements ADM capabilities on the edge device(s).

   EMS
    Edge Management System - the overall system implementing the set of
    capabilities of the ADM Pillar, which will include the LwM2M server and
    client typically but may also include other software and/or capabilities.

    Note: with the electric utility industry, EMS often means
    *Energy* Management System.  Similarly, within the network management
    system EMS often means *Element* Management System.
    Within this specification EMS is used exclusively for Edge
    Management System.

   Edge Application
    Workload running within a GEISA execution environment using
    GEISA platform services and API interfaces.

   GEISA
    `Grid Edge Interoperability and Security Alliance
    <https://lfenergy.org/projects/geisa/>`_

   GPIO
    General Purpose Input/Output

   GUI
    Graphical User Interface

   HAN
    Home Area Network

   Hybrid Application Model
     A hybrid application model in context of GEISA refers to an application
     which may use a combination of edge/local and cloud resources for
     determination of actual conditions, or additional upstream analysis on
     the aggregation of edge-determined conditions.  For example, a specific
     edge application may determine some specific conditions locally, but also
     share data upstream to a cloud-based application to perform additional
     analysis to determine if other conditions may exist, or to determine if
     the locally-determined conditions are part of a larger pattern of
     conditions.

   LAN
    Local Area Network

   LEE
    Linux Execution Environment

   LwM2M
    Lightweight Machine-to-Machine

   MQTT
    `MQTT <https://en.wikipedia.org/wiki/MQTT>`_
    is a light-weight publish and subscribe protocol formerly
    known as Message Queueing Telemetry Transport.

   OS
    Operating System

   Platform Provider
    Role responsible for supplying platform hardware, platform software,
    and associated platform trust material where applicable.

   PKI
    Public Key Infrastructure

   Platform Implementation
    A combination of hardware and software which provides one or more
    GEISA conformant interfaces (ADM, API, EE).

   POSIX
    `Portable Operating System Interface
    <https://en.wikipedia.org/wiki/POSIX>`_

   RMS
    Root Mean Square

   SPI
    Serial Peripheral Interface

   System Operator
    Role with deployment-environment authority for approving,
    configuring, authorizing, deploying, and operating GEISA-managed
    devices and applications.

   Vendor Application Manifest
    Publisher-supplied application manifest provided with an application
    artifact as input to operator deployment decisions.

   userid
    In context of GEISA MQTT APIs, this is a platform-local unique identifier
    assigned to a deployed GEISA application instance on that local device.  It
    is used for topic routing and message correlation within a device.
    Implementations may map this identifier to underlying platform or application
    constructs such as application manifest details, container identities, or
    other information in order to ensure local uniqueness.

    The userid is unique within the scope of a device but is not required to be
    globally unique (as of this specification version) and does not represent
    a human user.

    In this version of the GEISA specification, platforms are not required to 
    support concurrent execution of multiple instances of the same application 
    version on a single device.  Future revisions may expand this behavior.

   VEE
    Virtual Execution Environment

|geisa-pyramid|
