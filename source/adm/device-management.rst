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

