Operating System
----------------

|geisa-lee-hdr|

GEISA LEE SHALL use Linux as the core operating system.
The LEE platform implementer SHOULD use a Linux 6.x or greater kernel. A LEE platform
may use an older version if needed, but it MUST provide the needed application isolation
requirements.

The attack surface and size of the Linux kernel and base libraries provided MUST be
minimized. A LEE platform implementation SHOULD remove unnecessary components and
libraries providing the application the needed functionality but not a full Linux
distribution experience.

There is no requirement for the underlying Linux kernel
to support real-time features,
and no real-time features are exposed to GEISA applications.
Applications, however, do specify their needed CPU and memory resources in their
Application manifest and operators SHOULD consider the finite resources available
when deploying Applications.  Applications SHOULD receive, over time, their
resource allotment and not be starved to the point where metrological and
waveform data is lost.

|geisa-pyramid|



