
..
  Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
  Security Alliance (GEISA), a Series of LF Projects, LLC
  This file is licensed under the Community Specification License 1.0
  available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

Certificates
^^^^^^^^^^^^

GEISA relies on x.509 certificates for device authentication and for validating
signatures.  This section discusses expectations for certificate management
within the GEISA COE.

Signing Certificates
~~~~~~~~~~~~~~~~~~~~

As discussed in :doc:`/security/signatures` GEISA requires signatures on
applications, application manifests, and firmware images.  Signing certificates
are to be provided to the System Operator as x.509 certificates (see [X509]_).
Certificates SHOULD be provided in text (:code:`.pem`) or binary (:code:`.cer`
/ :code:`.der`) format.  ADM conformant EMS must support importing certificates
in both formats.

.. 
  For discussion:  Do we need to cover things like the EMS automatically
  attempting to retrieve a certification chain?


Bootstrapping Certificates
~~~~~~~~~~~~~~~~~~~~~~~~~~

As per :doc:`/adm/bootstrap/`, GEISA clients must support Client initiated
bootstrap (required of all LwM2M devices) as well as Factory Bootstrap.  GEISA
devices MUST include an initial IDevID (see [IEEE8021AR]_ for definitions)
issued by the manufacturer.  This IDevID is used during the initial
authentication process.  

The initial bootstrap follows the process shown below:

.. figure:: ESTBootstrap.*

   Enrollment over Secure Transport triggered by Client-Initiated Bootstrap

This is a basic two-certificate model in which the IDevID is used for initial
authentication and then an LDevID issued as an operational certificate for
session authentication (i.e. mDTLS).  Sometime this model refers to the IDevID
as a "birth certificate," and the LDevID as a"driver's license".  The birth
certificate is used to obtain a driver's license which is used for subsequent
session establishment until it expires or is renewed.  If the LDevID needs to
be replaces, the device returns to the IDevID to reauthenticate.

This process facilitates a transition from a manufacturer provided IDevID to an
operator provided LDevID, but it does not address concerns of key sovereignty.
Specifically, many utilities have policies that do not allow on-going use of
externally provided certificates or keys for authentication.  If the device
reboots and needs to reauthenticate, typically it will return to its IDevID to
reauthenticate.  

Many utilities require a three certificate model.  In this model the IDevID is
used to obtain a long-lived LDevID which effectively replaced the IDevID.  This
long-loved LDevID is used to obtain a short-lived LDevID which is used for
ongoing session establishment and is periodically replaced.  In this model, the
device never returns to its IDevID unless it goes through a full factory reset.
The utility will typically configure the system to reject any subsequent device
reauthentication using the IDevID once the long-lived LDevID is issued,
flagging any attempts as potential attacks needing investigation.

The primary reason for this approach is that the utility does not have any
control over the manufacturer's certificate authority (CA).  It is possible that the
CA would be compromised, misused etc.  It is just not acceptable to have an
on-going dependencies on an external CA.

One analogy to this approach is a birth certificate, citizenship, driver's
license model.  The IDevID (birth certificate) is used to complete a one-time
"naturalization" process in which a device is issued the long-lived LDevID
(naturaliation).  Once this is complete, long-lived LDevID (the naturalization
papers) is used to obtain the short-lived LDevID (the driver's license), which
is used as needed for session establishment.  The short-lived LDevID is subject
to expiration and is replaced periodically.

This extended bootstrap follows the process shown below:

.. figure:: TwoPassESTBootstrap.*

   Enrollment over Secure Transport triggered by Client-Initiated Bootstrap
   with long-lived and short-lived LDevIDs.


.. 
   Need to discuss how the long-lived LDevID and the short-lived LDevID are
   distinguished in an interoperable way.

GEISA conformant ADM clients must support having their IDevID replaced with a
long-lived LDevID issued by the system operator, which is used for subsequent
reauthentication.  GEISA conformant EMS must support issuing a long-lived
LDevID and then using that LDevID for to obtain short-lived LDevIDs.  The
system operator will determine whether they choose to use this feature.  Some
system operators may accept using an IDevID on an on-going basis.

..
   Need to discuss use of DNS, DNS-SD, and SNI.


|geisa-pyramid|

