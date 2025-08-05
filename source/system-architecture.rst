System Architecture
------------------------------

As discussed in :doc:`introduction`, the |GEISA| specification describes 
four types of interoperability: ADM, API, LEE, and VEE.  
These types of interoperability live in a general system context, which is shown below in
:numref:`geisa-architecture`.

.. _geisa-architecture:
.. figure:: /images/geisa-architecture.*

   GEISA Architecture

GEISA is focused on interoperability and security.  Where it is possible to maintain interoperability without specifying aspects of the implementation, details are left to the implementer.

|geisa-adm-hdr|

In a full implementation of the GEISA architecture, there is a GEISA Edge Management System (EMS) that 
implements the ADM interface described in :doc:`app-management`.  The EMS implements
a network protocol based interface and is able to use that protocol to interact with ADM interface
conformant GEISA platform implementations.  Internal details of the EMS are beyond
the scope of this specification.  GEISA simply requires that a conformant EMS expose the required
functions to the system operator in some meaningful way, and that it implements the specified network
protocol and transactions in response to user commands.  An EMS could provide a GUI, a command line 
interface, or an API and still be conformant.

Interacting with the GEISA EMS is one or more platform implementations.  An ADM conformant platform
interface will be able to communicate with the GEISA EMS using the ADM protocol and transactions.
In :numref:`geisa-architecture` above, the ADM conformant implementation is shown as the GEISA 
Edge Management Agent.  Implementation details are beyond the scope of this specification.
Implementers may provide a stand alone EMA within their platform, or integrate EMA functions within
other elements of their platform as they see fit.

GEISA ADM elements |geisa-adm-baton| are shown in red in :numref:`geisa-architecture` above.

|geisa-pyramid|

The system operator is able to use the GEISA EMS to deploy and activate GEISA edge applications
to GEISA platform implementations.  A fully conformant GEISA platform implementation will provide
both a GEISA conformant execution environment and a GEISA conformant application programming interface.

|geisa-ee-hdr|

GEISA defines two different execution environments: a Linux Execution Environment |geisa-lee-tux|
and a Virtual Execution Environmenti |geisa-vee-cloud|.
Platforms may offer one or both of these EE.  
While the GEISA API should be accessible from both EE, there is no expectation that code written
for one EE will work on the other without being ported. 


|geisa-lee-hdr|

LEE GEISA applications are provided as container images, as detailed in :doc:`app-isolation`. 
An LEE conformant GEISA implementation is able to mount a container image and grant that container
the rights the system operator permitted the application in the deployment manifest.
The container runtime used by the platform implementation is out of scope, but conformant implementations 
MUST be able to enforce the permissions and controls the GEISA specification requires.

An LEE conformant GEISA implementation must provide a set of :doc:`base-libraries` and :doc:`core-services`
to containers running in the environment.  The goal of GEISA LEE conformance is to provide a consistent
and efficient execution enviroment to edge applications running on the platform.  
Platform implementers may use any GNU/Linux variant they see fit, provided it meets the requirements
noted in :doc:`operating-system`; however, for security and efficiency reasons, implementers SHOULD NOT 
use full general purpose GNU/Linux operating systems.  Implementers SHOULD use distributions specifically
built for embedded enviroments and should excise any unnecessary system components.

GEISA LEE elements |geisa-lee-tux| are shown in blue in :numref:`geisa-architecture` above.

|geisa-pyramid|

|geisa-vee-hdr|

VEE GEISA applications are provided VEE archives, as detailed in :doc:`virtual-environment`.
A VEE conformant GEISA implementation is able to launch the archive in a VEE as necessary and grant the 
application the rights the system operatator permitted the application in the deployment manifest.
The VEE used by the platform implementation is out of scope, but conformant implementations MUST
be able to enforce the permissions and controls the GEISA specification requires, 
and support the GEISA required APIs.

GEISA VEE elements |geisa-vee-cloud| are not currently shown in :numref:`geisa-architecture` above.

|geisa-pyramid|

|geisa-api-hdr|

General operating system functions such as file system access, math libraries, and network socket APIs 
are provided by the GEISA LEE or VEE discussed above.  The GEISA API facilitates access to platform capabilities
that are not serviced by the LEE's or VEE's respective APIs.  The GEISA API is described in detail in :doc:`api`.
The GEISA API will provide access to metrological data, sensor data, billing data, actuators, and,
for GEISA ADM conformant implementations, message exchange with the EMS.

GEISA API conformant platform implementations MUST provide an implementation of the message bus 
described in :doc:`api` and MUST respond appropriately to all required API transactions.  
Connecting the GEISA API implementation to the underlying 
platform is out of scope for the GEISA specification.  
Platform implementers may use any supporting implementation they see fit; however, implementers
SHOULD consider the security implications of the implementation and ensure they are robust against
both unintended abuse and deliberate attacks.

GEISA API elements |geisa-api-gear| are shown in green in :numref:`geisa-architecture` above.

|geisa-pyramid|

