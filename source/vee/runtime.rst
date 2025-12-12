
..
  Copyright 2025, Contributors to the Grid Edge Interoperability & Security Alliance (GEISA) a Series of LF Projects, LLC  
  This file is licensed under the Community Specification License 1.0 available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

Virtual Execution Runtime
-------------------------

|geisa-vee-hdr|

The VEE Runtime is composed of a lightweight execution engine that abstracts 
the underlying hardware and operating system to provide a trusted and secure, 
multi-application environment for embedded applications to run on cost-effective 
devices.


Processing Unit
^^^^^^^^^^^^^^^

The GEISA VEE Runtime MUST feature a Processing Unit, which acts as a virtual 
CPU executing a compact and hardware-agnostic virtual instruction set. 
Instead of running native machine code directly on the microcontroller or 
microprocessor, applications are compiled into optimized virtual bytecode. 
This bytecode is then executed by the Processing Unit using a deterministic, 
low-latency execution model tailored for embedded systems. 
Because the instruction set is independent from the underlying processor 
architecture (ARM, RISC-V, x86, etc.) and and also independent from the 
operating system (Linux, Zephyr, bare metal), the Processing Unit provides a
stable abstraction layer that guarantees the same behavior for any binary 
application across any physical GEISA devices.

Scheduler
^^^^^^^^^

Along with the Processing Unit, the VEE Runtime MUST have a strict pre-emptive
priority-based scheduler with consistent thread management, ensuring that 
various applications collaborate and execute with the same behavior on every 
target, independent of the underlying OS/RTOS. 
The GEISA VEE scheduler MUST provide:

- Application-level thread scheduling independent of OS scheduling
- Fair resource allocation among running sandboxed applications
- Prevention of thread starvation across applications
- Consistent scheduling behavior across heterogeneous hardware platforms

Java Language Support
^^^^^^^^^^^^^^^^^^^^^

A GEISA-compliant VEE MUST support the Java language specification version 7 or
later.
The GEISA VEE MUST implement:

- Core Language Features

  - All Java primitives (byte, short, int, long, float, double, boolean, char)
  - Object-oriented features (classes, interfaces, inheritance, polymorphism)
  - Exception handling (try, catch, finally, throw)
  - Reflection API for class inspection and instantiation (Class.forName(), 
    Class.getName(), Class.getSimpleName(), and Class.newInstance())
  - Generic types

- Garbage Collector

  - The garbage collector MAY implement various collection strategies (generational, 
    concurrent, incremental) provided they maintain predictable embedded system behavior.
  - The VEE MUST include a garbage collector to automatically manage memory. 
    The garbage collector MUST provide:

    - Deterministic collection of unreachable objects
    - Minimal impact on application latency suitable for embedded devices
    - Configurable collection policies per sandbox to respect resource constraints
  
C/C++ Language Support
^^^^^^^^^^^^^^^^^^^^^^

A GEISA VEE MUST support the C and C++ programming languages. 
Applications MAY be written entirely in C/C++, or mixed-language applications MAY
combine Java and C/C++ components within the same application. 
The VEE runtime MUST prevent C/C++ code from bypassing sandbox isolation, accessing
other applications' memory, or circumventing security controls through unsafe
pointer operations or direct hardware access.

Multi-Sandbox Execution Control
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The VEE Runtime MUST include a Multi-Sandbox semantic that provides a dynamic
loader for application loading, while enforcing strict isolation between
applications at runtime. 

The GEISA VEE MUST enforce resource limits per resource (using a Resource Manager): 

- Compute Resources: CPU allocation with fair scheduling among running applications, 
  and criticality level between applications
- Memory Resources: Heap size limits per application
- Network Resources: Bandwidth throttling and volume limits

The GEISA VEE MUST provide a Kernel responsible for the minimal core services
organized and accessible through a registry of Services.  
The multi-sandboxed Kernel manages the lifecycle of applications, enforces
access control to resources through a Security Manager.
The Kernel is responsible for reliable, trusted execution and cannot be
modified by applications.

Each application is optional, potentially untrusted, and may be unreliable; 
however, applications can be installed, started, stopped, and uninstalled
without jeopardizing the kernel's stability or the execution of other
applications. 
The Kernel controls the life cycle of the various loaded applications. 
An application can be installed, started, stopped and uninstalled at any time
independent of the system state (particularly, an application never depends on
another Application to be stopped). 

The multi-sandboxed kernel MUST implement the application life cycle as 
described below:

- Installed: The Application has been successfully linked to the kernel, but is 
  not running. 
- Started: The Application has been started and is running.
- Stopped: The Application has been stopped and all threads are terminated. 
- Uninstalled: The application has been unlinked from the Kernel.

Security Manager 
^^^^^^^^^^^^^^^^

A security policy allows the Kernel to prevent an Application from accessing
resources or calling specific APIs. 
GEISA VEE multi-sandboxed kernel MUST implement a security manager.


|geisa-pyramid|
