
..
  Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
  Security Alliance (GEISA), a Series of LF Projects, LLC
  This file is licensed under the Community Specification License 1.0
  available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

Virtual Execution Environment
-----------------------------

|geisa-vee-hdr|

A Virtual Execution Environment is a multi-sandboxed applications container for
resource-constrained embedded devices running on microcontrollers or 
microprocessors.

It allows devices to run multiple and mixed managed code (Java |reg| compiled 
binary code, C/C++ compiled binary code, JavaScript code, etc.). 
A VEE is always based on a virtual execution engine that executes inside the
devices operating system as a process or a task, thus creating an isolated 
environment where code executes as virtual instruction independent from the 
operating system or the processor instruction set. 

The GEISA Virtual Execution Environment is one of two execution environments
defined within the GEISA specification.  The GEISA Virtual Execution Environment 
definitions allows platforms which support running applications in a virtual 
execution environment, rather than a full operating system, to do so in an 
interoperable way.

VEEs are used on a variety of platforms.  The GEISA VEE may run on top of the 
GEISA LEE, although this is not an obligation;  that is, the underlying system 
for a GEISA VEE can be any RTOS and not necessarily Linux.

VEEs rely on managed-code virtual runtime (typically a virtual machine): GEISA
VEEs MUST support both multi-thread managed C/C++ and (managed) Java |reg|. 
Support for other languages (Kotlin, Lua, Rust, ECMAScript, etc.) may be included 
in future versions of the specification but are not mandated or defined at this 
time.

In this version of the GEISA specification, the host operating system is Linux 
and the VEE SHOULD execute in userspace as a process. 
In a future version of the specification, it may be possible to consider Zephyr 
OS, in which case the VEE would execute as a task.

On top of this runtime sits a multi-application kernel that manages the 
lifecycle, scheduling, and isolation of multiple apps running concurrently. 
Each application executes inside its own sandbox with strict memory and API
boundaries, ensuring strong fault-containment, secure separation of logic, and
safe coexistence of third-party or field-updatable applications on the same
device.

VEE conformant platforms will provide a consistent:

* :doc:`vee/runtime`
* :doc:`vee/base-libraries`

.. toctree::
  :hidden:

  vee/runtime
  vee/base-libraries

|geisa-pyramid|
