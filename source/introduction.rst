
..
  Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
  Security Alliance (GEISA), a Series of LF Projects, LLC
  This file is licensed under the Community Specification License 1.0
  available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

.. index:: single: Grid

Introduction
------------

The Grid Edge Interoperability and Security Alliance (GEISA) Specification 
addresses interoperability for edge computing environments used by electric 
utilities.  These edge environments are often found in `Advanced Metering Infrastructure 
<https://en.wikipedia.org/wiki/Smart_meter#Advanced_metering_infrastructure>`_ 
(AMI) meters, but may also be present in Distribution Automation (DA) devices, 
customer gateways, or other utility-owned devices.

.. figure:: images/electricity-grid-north-america.*
   :name: na_grid_figure
   :alt: Simplified North American Electricity Grid 

   Simplified North American Electricity Grid [#f1]_

:numref:`na_grid_figure`, above, shows a simplified view of North American
electricity grid.  Electricity grids in other parts of the world are generally
similar, though the voltage levels are often different.  While the GEISA
specification may be used to provide interoperable edge intelligence in any
device, GEISA is primarily focused on device that live in the distribution
network, shown in green in :numref:`na_grid_figure`.  Edge intelligence for
substations is likely better served by the LF Energy SEAPATH project, https://seapath.energy/.

Within the electricity distribution network, electric utilities or distribution
network operators deploy a variety of different devices to manage their
networks.  Smart electricity meters are used to record customer energy
consumption and serve as grid sensors, providing data on outages and other
events.  Load tap changers and capacitor bank controllers are used to ensure
that voltage stays within accepted tolerances.  Remote fault indicators help
network operators determine the physical location of grid failures.  Remote
intelligent switches and remote automatic reclosers support automatic recovery
from faults and allow reconfiguration of the distribution network without
sending personnel into the field.  

All of these devices could potentially benefit from the ability to deploy
applications on them.  GEISA allows utilities or distribution network operators
to deploy interoperable edge applications from different vendors on to devices
from different vendors and manage them all with a single management system.
This capability enables a much more flexible, capable distribution grid.
System operators can deploy apps where needed, enabling a variety of different
use cases from simple applications that enable flexible, site-specific
load-control (e.g. if load exceeds X, operate relay) to complex waveform
analysis and AI modeling.  

The goal of the GEISA specification is to address end-to-end interoperability 
for edge environments.  

Within the GEISA specification, interoperability is be broken down into three areas:

* Application and Device Mangement 
* Application Programming Interface 
* Execution Environment

.. raw:: latex

   \bigskip


|geisa-adm-hdr|

Application and Device Management (ADM) interoperability allows utilities to
use a single management system to manage ADM-conformant devices from multiple
vendors using an ADM-conformant management system.  ADM defines the behaviors
and protocols necessary to register and manage edge devices and the
applications which run on them.

When this documentation notes something that is ADM-related, there may be an 
orchestrator's baton icon |geisa-adm-baton| to highlight it.

|geisa-pyramid|

|geisa-api-hdr|

Application Programming Interface (API) interoperability allows software
developers to interact with grid edge device specific capabilities, such as
meter readings, waveform data, sensors, and actuators in a consistent manner.
GEISA uses a message-bus based API so that application developers are not
constrained to a specific programming language.

When this specification notes something that is API related, there may be a 
gear icon |geisa-api-gear| to highlight it.

|geisa-pyramid|

|geisa-ee-hdr|

Execution Environment (EE) interoperability defines the specific target
environment a GEISA platform supports for running applications.  This version
of the GEISA specification defines two specific execution environments: A Linux
Execution Environment and a Virtual Execution Environment.

Ocassionaly there are requirements common to both.  When this specification
discusses execution environments in general, there may be a globe icon
|geisa-ee-globe| to highlight it.

|geisa-pyramid|

|geisa-lee-hdr|

Linux Execution Environment (LEE) interoperability allows software developers
to have a consistent embedded Linux environment for running programs.
LEE-conformant devices provide an isolated per-application execution
environment containing a standard set of base libraries, a consistent
filesystem layout, and other details which ensure application developers do not
have to manage variations across different platform implementations.

When this specification notes something that is LEE related, there may be a Tux 
icon |geisa-lee-tux| to highlight it.

|geisa-pyramid|

|geisa-vee-hdr|

Virtual Execution Environment (VEE) interoperability allows software developers 
to have a consistent virtual execution environment for running programs.  
VEE-conformant devices provide the ability to run programs that rely on 
standard managed-code; that is, code executed under the supervision of a virtual 
machine that provides memory management, security, and isolation. The minimal 
supported languages for managed-code for GEISA VEE are C/C++ and Java, with 
their respective libraries.  

When this specification notes something that is VEE related, there may be a 
connected cloud icon |geisa-vee-cloud| to highlight it.

|geisa-pyramid|

Vendor implementations of the GEISA specification may not support 
interoperability in all areas. For example, some vendors may support either a 
Linux execution environment (LEE), or a virtual execution environment (VEE), 
while other vendors may choose to support both, with a VEE running on top of or 
along side of a LEE environment.  There is nothing in the specification that 
precludes supporting only one type of Execution Environment (LEE or VEE) or 
supporting both.

For clarity, this specification uses icons for each aspect of interoperability 
so it is clear which requirements apply to a given 
type of conformance.  The icons are:

|geisa-adm-logo| |geisa-api-logo| |geisa-lee-logo| |geisa-vee-logo| |geisa-ee-logo|

The goal of this specification is that two vendors working from the 
specification alone are able to create an implementation such that a 
GEISA-conformant application can run on nearly any GEISA-conformant platform 
without modification.  Similarly, a vendor providing a GEISA-conformant 
ADM / management system should be able to manage a GEISA conformant platform 
without modifications.

Throughout this specification there are blocks associated with each aspect of 
interoperability.  In this introduction, the blocks explain, at a high level, 
the interoperability behaviors a given aspect supports.   

This specification follows [RFC2119]_ conventions, such as "MUST", "MAY", and 
"SHOULD" to indicate what is expected from a conformant implementation.  

Please note that conformance for each of GEISA defined aspects of 
interoperability (ADM |geisa-adm-baton|, API |geisa-api-gear|, LEE |geisa-lee-tux| 
& VEE |geisa-vee-cloud|) is considered independently.

.. [#f1] Sourced via Wikimedia Commons from the United States Department of
   Energy.  See https://commons.wikimedia.org/wiki/File:Electricity_grid_simple-_North_America.svg 

|geisa-pyramid|
