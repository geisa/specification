Operating System
----------------

|geisa-lee-hdr|

GEISA LEE shall use Linux as the core operating system.
GEISA SHOULD use a Linux 6.x or greater kernel.

 .. warning::

  TODO: The only technological requirement GEISA has placed on the kernel is containerision technology which has existed in much older kernel version than 6.x.  Also, many SoC and toolchain vendors are distributing 5.10, 5.4, or older kernels.  Perhaps we specify functionality not a specific version here.


The GEISA Linux kernel must minimize the attack surface and size.
This means removing all unnecessary components and extranous modules.
Whether the GEISA Linux kernel supports loadable kernel modules
or not is an implementation decision that is
invisible to a GEISA application; 
however, for security  and efficiency reasons, it is recommended that platform implementers
limit the use of loadable modules.

 .. warning::

  TODO: this seems out of place/scope.  loadable modules is a point concern among many security considerations a platform implementer may consider.  Move to security section or remove as out-of-scope?

There is no requirement for the underlying Linux kernel
to support real-time features,
and no real-time features are exposed to GEISA applications.
Applications, however, do specify their needed CPU and memory resources in their
Application manifest and operators SHOULD consider the finite resources available
when deploying Applications.  Applications SHOULD receive, over time, their
resource allotment and not be starved to the point where metrological and
waveform data is lost.

|geisa-pyramid|



