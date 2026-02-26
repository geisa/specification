
..
  Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
  Security Alliance (GEISA), a Series of LF Projects, LLC
  This file is licensed under the Community Specification License 1.0
  available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

Operating System
----------------

|geisa-lee-hdr|

GEISA LEE SHALL use Linux as the core operating system.  The LEE platform 
implementer SHOULD use a Linux 6.x or greater kernel. A LEE platform may use 
an older version if needed, but it MUST provide the needed application isolation
requirements as defined within the GEISA specification.

The attack surface and size of the Linux kernel and base libraries provided 
MUST be minimized. A LEE platform implementation SHOULD remove unnecessary 
components and libraries providing the platform and applications the required 
functionalities while being cognizant and intentional on minimizing the overall 
packages and services and should not be similar to a full typical Linux 
distribution.

There is no requirement for the underlying Linux kernel to support real-time 
features, and no real-time features are exposed to GEISA applications.

Applications, however, do specify their needed CPU and memory resource 
requirements in their Application manifests and operators SHOULD consider the 
finite resources available when deploying Applications.  Applications SHOULD 
receive, over time, their resource allotment and not be starved to the point 
where metrological and waveform data is lost.

|geisa-pyramid|



