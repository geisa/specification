
..
  Copyright 2025, Contributors to the Grid Edge Interoperability & Security Alliance (GEISA) a Series of LF Projects, LLC  
  This file is licensed under the Community Specification License 1.0 available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

Application Messaging and Configuration
---------------------------------------

GEISA LwM2M object 3600 provides a bi-directional messaging facility for applications, with distinct resources defined for 
Client to Server messaging and Server to Client messaging. Object 3600 SHALL be used by ADM compliant platforms and EMS 
for sensor data reporting on the uplink (Client to Server) and edge app configuration on the downlink (Server to Client).

An ADM compliant EMS MAY *Observe* resource 1 to receive asynchronous LwM2M Notifications (containing app data) whenever the 
platform writes to resource 1 on behalf of the edge app.

An ADM compliant platform will receive asynchronous callbacks from its LwM2M Client whenever the EMS writes to resource 0 
to reconfigure an edge app, and the platform SHALL forward that resource 0 payload (containing an app configuration) via 
GEISA API to the app identified in resource 4050.

===========  ================  =========  =========  ==================================================================
Resource ID  Name              Operation  Data Type  Description
===========  ================  =========  =========  ==================================================================
0            Server Message    Write      Opaque     Server to Client message used for edge app configuration.
1            Client Message    Read       Opaque     Client to Server message used for edge app data reporting.
2            Message Priority  ReadWrite  Integer    Priority: 0=Immediate, 1=BestEffort, 2=Latest
3            Message Desc      ReadWrite  Integer    Description: 0=AppConfiguration, 1=AppData
4050         AppID             ReadWrite  Integer    ID of the edge app using this object instance.
===========  ================  =========  =========  ==================================================================
