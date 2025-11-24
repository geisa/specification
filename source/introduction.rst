
..
  Copyright 2025, Contributors to the Grid Edge Interoperability & Security Alliance (GEISA) a Series of LF Projects, LLC  
  This file is licensed under the Community Specification License 1.0 available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

Introduction
------------

The Grid Edge Interoperability and Security Alliance (GEISA) Specification addresses 
interoperability for edge computing environments used by electric utilities.  These
edge environments are often found in `Advanced Metering Infrastructure 
<https://en.wikipedia.org/wiki/Smart_meter#Advanced_metering_infrastructure>`_ (AMI) meters, but
may also be present in Distribution Automation (DA) devices, customer gateways, or other
utility owned devices.

The goal of the GEISA specification is to address end-to-end interoperability for edge environments.
Within the GEISA specification, interoperability is be broken down into four areas:

* Application and Device Mangement (ADM)
* Application Programming Interface (API)
* Linux Execution Environment (LEE)
* Virtual Execution Environment (VEE)

Vendor implementations of the GEISA specificiation may not support interoperability in all areas. 
For example, it is likely that most platform vendors will support either a Linux execution environment,
or a virtual execution environment, but not both; though there is nothing in the specification that precludes supporting both. 
For clarity, this specification uses icons for each aspect of interoperability 
so it is clear which requirements apply to a given 
type of conformance.  The icons are:

|geisa-adm-logo| |geisa-api-logo| |geisa-lee-logo| |geisa-vee-logo| |geisa-ee-logo|

Throughout this specification there are blocks associated with each aspect of interoperability.  
In this introduction, the blocks explain, at a high level, the interoperability behaviors 
a given aspect supports.  Blocks which discuss specific aspects of interoperability close 
with a GEISA pyramid icon (|geisa-pyramid|).

|geisa-adm-hdr|

Application and Device Management interoperability allows utilities to use a single management
system to manage ADM conformant devices from multiple vendors using an ADM conformant management
system.  ADM defines the behaviors and protocols necessary to register and manage edge devices
and the applications which run on them.

When this documentation notes something that is ADM related, there may be an orchestrator's baton icon 
|geisa-adm-baton| to highlight it.

|geisa-pyramid|

|geisa-ee-hdr|

While GEISA defines two specific execution environments (discussed below), ocassionaly there are requirements
common to both.  

When this specification discusses execution environments in general, there may be a globe icon 
|geisa-ee-globe| to highlight it.

|geisa-pyramid|

|geisa-lee-hdr|

Linux Execution Environment interoperability allows software developers to have a consistent embedded
Linux environment for running programs.  
LEE conformant devices provide a standard set of base libraries, a consistent file 
system layout, and other details which ensure app developers do not have to manage variations across
platform implementations.

When this specification notes something that is LEE related, there may be a Tux icon
|geisa-lee-tux| to highlight it.

|geisa-pyramid|

|geisa-vee-hdr|

Virtual Execution Environment interoperability allows software developers to have a consistent virtual
machine environment for running programs.
VEE conformant devices provide the ability to run programs that rely on standard Java |reg| class libraries.

When this specification notes something that is VEE related, there may be a connected cloud icon 
|geisa-vee-cloud| to highlight it.


|geisa-pyramid|


|geisa-api-hdr|

Application Programming Interface interoperability allows software developers to interact with grid
edge environment specific capabilities, like meter readings, waveform data, sensors, and actuators in
a consistent manner.  GEISA uses a message-bus based API so that application developers are not 
constrained to a specific programming language.

When this specification notes something that is API related, there may be a gear icon 
|geisa-api-gear| to highlight it.

|geisa-pyramid|

The goal of this specification is  
that two vendors working from the specification alone
can create an implementation
such that a GEISA conformant application
can run on a GEISA conformant platform without modification.
Similarly, a vendor providing a GEISA conformant management system
should be able to management a GEISA conformant platform without modification.

This specification currently addresses:

- :doc:`design-principles` 
- :doc:`system-architecture`
- :doc:`conformance`
- :doc:`hardware`
- :doc:`adm` |geisa-adm-baton| 
- :doc:`app-isolation` 
- :doc:`linux-environment` |geisa-lee-tux|
- :doc:`virtual-environment` |geisa-vee-cloud|
- :doc:`api` |geisa-api-gear| 
- :doc:`security` 

This specification follows [RFC2119]_ conventions, using "MUST", "MAY", and "SHOULD" to 
indicate what is expected from a conformant implementation.  

Please note that conformance 
for each of GEISA defined aspects of interoperability (ADM |geisa-adm-baton|, 
API |geisa-api-gear|, LEE |geisa-lee-tux| & VEE |geisa-vee-cloud|) is considered independently.

|geisa-pyramid|
