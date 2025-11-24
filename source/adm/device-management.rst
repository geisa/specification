
..
  Copyright 2025, Contributors to the Grid Edge Interoperability & Security Alliance (GEISA) a Series of LF Projects, LLC  
  This file is licensed under the Community Specification License 1.0 available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

Device Management
-------------------------------

Device management within GEISA allows system operators to track, updated,
restart, and reset edge environments.  As discussed under :doc:`registration`,
when a GEISA ADM conformant device starts, it registers with the GEISA Edge
Management System (EMS).  Following the LWM2M protocol, devices will reregister
when their registration lifetime expires.  This process allows the system
operator to use the EMS to track the general status of the edge device fleet.

Device management is also used to perform platform-level firmware updates.
Firmware updates are performned using LWM2M Object 5, Firmware Update.

ADM conformant GEISA devices shall support device reboots as well as device
factory resets, using LWM2M Object 3.  Factory resets of an ADM conformant
device shall remove all installed applications and any associated application
data.

The LwM2M Device Management and Service Enablement interface exposes the
facility to perform device, application, and network management operations on
an ADM conformant GEISA platform:


* **Discover** – Used by a LwM2M Management Server to retrieve the list of Resources instantiated in each Object instance. Data (Resource Values) is not returned.
* **Read** – Used by an EMS to retrieve Resource data values (e.g., sensor reading). Reading may be performed at various levels: Resource Instance, entire Resource, Object Instance, entire Object
* **Read-Composite** – Used by an EMS to retrieve multiple Resources/Objects in single CoAP request.
* **Write** – Used by an EMS to modify Device configuration. 


  * CoAP PUT is used to Replace the Object Instance or Resource(s) with the new values provided.
  * CoAP POST is used for Partial Update to update the Resources with the new values provided, leaving other existing Resources unchanged.


* **Write-Composite** - Used by an EMS to update multiple Resources/Objects in single CoAP request.
* **Execute** – Used by an EMS to invoke commands on the platform (e.g., Factory Reset, Activate Edge App).
* **Create** – Used by an EMS to create new Object Instances on the LwM2M Client of the platform.
* **Delete** – Used by an EMS to delete Object Instances on the LwM2M Client of the platform.
* **Write-Attributes** – Used by an EMS to set Notification triggers for an Observe of a Resource/Object (e.g., Only send a Notification every two hours, only send a Notification if the observed value has changed by more than X).

There operations are performed using the following CoAp methods:

================ ========================= =============================================== ==================== ==================================
Operation        CoAp Method               Path                                            Success              Failure
================ ========================= =============================================== ==================== ==================================
Read             GET                       /{Object ID}/{Object Instance ID}/{Resource ID} 2.05 Content         4.00 Bad Request, 
                 Accept: Content Format ID                                                                      4.01 Unauthorized,
                                                                                                                4.04 Not Found,
                                                                                                                4.05 Method Not Allowed,
                                                                                                                4.06 Not Acceptable
Discover         GET                       /{Object ID}/{Object Instance ID}/{Resource ID} 2.05 Content         4.00 Bad Request,
                 Accept:                                                                                        4.01 Unauthorized,
                 application/link-format                                                                        4.04 Not Found,
                                                                                                                4.05 Method Not Allowed,
Write            PUT                       /{Object ID}/{Object Instance ID}/{Resource ID} 2.04 Changed         4.00 Bad Request,
                 Content Format:                                                           2.31 Continue        4.01 Unauthorized,
                                                                                                                4.04 Not Found,
                                                                                                                4.05 Method Not Allowed,
                                                                                                                4.06 Not Acceptable
                                                                                                                4.08 Request Entity Incomplete
                                                                                                                4.13 Request Entity Too Large
Write            POST                      /{Object ID}/{Object Instance ID}               2.04 Changed         4.00 Bad Request,
                 Content Format:                                                           2.31 Continue        4.01 Unauthorized,
                                                                                                                4.04 Not Found,
                                                                                                                4.05 Method Not Allowed,
                                                                                                                4.06 Not Acceptable
                                                                                                                4.08 Request Entity Incomplete
                                                                                                                4.13 Request Entity Too Large
Write-Attributes PUT                       /{Object ID}/{Object Instance ID}/{Resource ID} 2.04 Changed         4.00 Bad Request,
                                           ?pmin={minimum period}&pmax={maximum period}                         4.01 Unauthorized,
                                           &gt={greater than}&lt={less than}&st={step}                          4.04 Not Found,
                                                                                                                4.05 Method Not Allowed,
Execute          POST                      /{Object ID}/{Object Instance ID}/{Resource ID} 2.04 Changed         4.00 Bad Request,
                                                                                                                4.01 Unauthorized,
                                                                                                                4.04 Not Found,
                                                                                                                4.05 Method Not Allowed,
Create           POST                      /{Object ID}                                    2.01 Created         4.00 Bad Request,
                 Content Format:                                                                                4.01 Unauthorized,
                                                                                                                4.04 Not Found,
                                                                                                                4.05 Method Not Allowed,
                                                                                                                4.06 Not Acceptable
Delete           DELETE                    /{Object ID}/{Object Instance ID}               2.02 Deleted         4.00 Bad Request,
                                                                                                                4.01 Unauthorized,
                                                                                                                4.04 Not Found,
                                                                                                                4.05 Method Not Allowed,
================ ========================= =============================================== ==================== ==================================

.. figure:: device-management-operations.*

  Device Management Operations

.. figure:: object-creation-deletion.*

  Object Creation and Deletion


|geisa-pyramid|

