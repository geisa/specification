OMA Lightweight M2M
-------------------------------------

GEISA Application & Device Management uses OMA Specworks' Lightweight M2M
[LWM2M]_ as for application management.  Specifically,

* ADM conformant platforms and Edge Management Systems (EMS) SHALL support LWM2M
  v1.2. [LWM2M-Core]_
* ADM conformant platforms and EMS MAY support LWM2M
  versions greater than v1.2; however, they MUST retain compatibility with
  v1.2.
* ADM conformant platforms and EMS SHALL support CoAP over UDP for
  message transport. [LWM2M-Transport]_
* ADM conformant platforms and EMS SHALL support DTLS for CoAp security.
* ADM conformant platforms and EMS SHALL support the Bootstrap, Registration,
  Device Management and Information Reporting interfaces.
* ADM conformant EMS shall support the following LWM2M Objects

  * ID 0 -- Security
  * ID 1 -- Server
  * ID 3 -- Device
  * ID 4 -- Connectivity Monitoring
  * ID 5 -- Firmware Update
  * ID 6 -- Location
  * ID 9 -- Software Management
  * ID 10 -- Cellular Network Connectivity
  * ID 11 -- APN Connection Profile
  * ID 12 -- WLAN Connectivity
  * ID 13 -- Bearer Selection
  * ID 19 -- Binary App Container
  * ID 20 -- Event Log
  * ID 504 --Remote SIM Provisioning

* ADM conformant platforms shall support the following LWM2M Objects

  * ID 0 -- Security
  * ID 1 -- Server
  * ID 3 -- Device
  * ID 4 -- Connectivity Monitoring
  * ID 5 -- Firmware Update
  * ID 9 -- Software Management
  * ID 19 -- Binary App Container
  * ID 20 -- Event Log

* ADM conformant platforms with 3GPP network interfaces SHALL support the
  followng LWM2M Objects:

  * ID 10 -- Cellular Network Connectivity
  * ID 11 -- APN Connection Profile
  * ID 12 -- WLAN Connectivity
  * ID 13 -- Bearer Selection
  * ID 504 --Remote SIM Provisioning

* ADM conformant platforms with GPS interfaces SHALL support the
  followng LWM2M Objects:

  * ID 6 -- Location


