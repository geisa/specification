Bootstrapping
-------------------------

As discussed in the LWM2M core specification [LWM2M-Core]_ section 6.1, there
are four ways to bootstrap a device so that it knows how to contact its LWM2M
server for management:

- Factory Bootstrap
- Bootstrap from Smartcard
- Client Initiated
- Server Initiated

As noted in [LWM2M-Core] GEISA ADM conformant devices SHALL support Client
Initiated bootstrapping.  GESIA ADM conformant devices MAY support other
bootstrapping methods.  For mass deployed devices, like smart meters, Factory
Bootstrapping may be preferred by many system operators.

GEISA ADM conformant devices SHALL provide accessible out-of-band
mechanism which allows the system operator to preprovision the URL of the CoAp
Bootstrap-Server, the Bootstrap-Server Account credentials, and any other data
needed to complete the boostrapping process (e.g. certificates, keys, etc.).
GEISA ADM conformant edge management systems SHALL provide a Bootstrap-Server
implementation.

.. Note::

  ToDo:  LWM2M Bootstrapping can include an endpoint client name.  This is optional if
  the identifier provided in the security protocol is sufficient.  We need to
  agree on the security mechanism and discuss whether the identifiers it provides
  are sufficient.


