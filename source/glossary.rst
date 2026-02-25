
..
  Copyright 2025, Contributors to the Grid Edge Interoperability & Security Alliance (GEISA) a Series of LF Projects, LLC  
  This file is licensed under the Community Specification License 1.0 available at:
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

   API
    Applications Programming Interface

   CoAP
    Constrained Applications Protocol

   COE
    Common Operating Environment
    
    The COE is the software platform specification which defines the software components, 
    interfaces, and processes needed to implement a GEISA conformant platform.  
    The COE is designed to be flexible and modular, allowing for a variety of implementations 
    that can meet the needs of different use cases and environments.  The COE is intended to 
    provide a common foundation for GEISA implementations, while also allowing for customization 
    and innovation by implementers.

   DER
        Distributed Energy Resource

        Distributed Energy Resource is a generic term that typically includes
        photo-voltaics coupled with a smart inverter, battery energy storage systems,
        electric vehicles, demand response, and other dispatchable load or generation
        available on the electric distribution network.  DER is typically owned by
        consumers or businesses, rather than utilities or wholesale energy market participants.

   FAN
    Field Area Network

   EE
    Execution Environment

   EMA
    Edge Management Agent

    The EMA is the logical component of a GEISA ADM conformant platform
    which implements ADM support.

   EMS
    Edge Management System

    Note: with the electric utility industry, EMS often means
    *Energy* Management System.  Similarly, within the network management
    system EMS often means *Element* Management System.  
    Within this specification EMS is used exclusively for Edge 
    Management System.

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
     the aggregation of edge-determined conditions.  FOr example, a specific 
     edge application may determine some specific conditions locally, but also
     share data upstream to a cloud-based application to perform additional analysis
     to determine if other conditions may exist, or to determine if the 
     locally-determined conditions are part of a larger pattern of conditions.
   
   LAN
    Local Area Network

   LEE
    Linux Execution Environment

   MQTT
    `MQTT <https://en.wikipedia.org/wiki/MQTT>`_ 
    is a light-weight publish and subscribe protocol formerly
    known as Message Queueing Telemetry Transport. 


   OS
    Operating System

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
 
   VEE
    Virtual Execution Environment

|geisa-pyramid|


