Operating System
----------------

|geisa-lee-hdr|

GEISA LEE shall use Linux as the core operating system.
GEISA SHALL use a Linux 6.x or greater kernel.

The GEISA Linux kernel must minimize the attack surface and size.
This means removing all unnecessary components and extranous modules.
Whether the GEISA Linux kernel supports loadable kernel modules
or not is an implementation decision that is
invisible to a GEISA application; 
however, for security  and efficiency reasons, it is recommended that platform implementers
limit the use of loadable modules.

There is no requirement for the underlying Linux kernel
to support real-time features,
and no real-time features are exposed to GEISA applications.

|geisa-pyramid|



