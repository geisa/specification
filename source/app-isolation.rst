Application Isolation
---------------------

GEISA applications shall be isolated from each other
for the following reasons:

- To ensure that one application cannot impact another application.
- To ensure that one application cannot see the artifacts of another application.

.. note::

    Other than specifiying that application that **isolation** shall be provided,
    it is not clear that the GEISA 1.0 specification should specify the
    isolation technology.

    One vendor/utility may have an existing implmentation with Linux Containers (LXC),
    while another may have an existing implementation with systemd.

    It may be useful to make this an “after 1.0” GEISA release requirement,
    or a future GEISA Extension.

    The most immediate need is for GEISA apps to run on multiple platforms from multiple vendors/utilities,
    perhaps using isolation techniques that are already used by existting vendor.


Reguardless of container implmeentation (e.g. LXC, systemd, etc.),
an **authenticated appllication manifest** shall control access
to the following:

- Permissions
- Performance
- System Control
- Networking Control
- API Control


Permissions
^^^^^^^^^^^

Most if not all of the bullets below are achieved by having each app in it's own isolated conainer.

- Apps should run in independent processes
- Apps must run with least privilege
- Apps access permissions should be deny by default
- App-to-app communication will be denied by default (**NOTE** perhaps hold off on app communication until after GEISA 1.0.0)
- Apps cannot access other apps memory or other resources
- Apps should not know about other apps unless explicitly informed
- Apps access to the local file-system will be isolated/restricted

Performance
^^^^^^^^^^^

GEISA isolation must meet these performance requirements:

- Apps cannot impact the performance of the system
- Apps cannot impact the stability of the system
- Apps cannot impact the performance of other apps
- Apps cannot impact the stability of other apps
- Apps cannot create denial-of-service situations

System Control
^^^^^^^^^^^^^^

The system (the container) shall control every aspect of an GEIA app, including:

- CPU (how much CPU allowed)
- Memory (how much RAM memory allowed)
- Persistent Storage (how mush Flash storae allowed)
- Non-Persistent Storage (how much tmpfs allowed)
- Networking (what networking interfaces and ports allowed)

Addition system control:

- App-to-app communication (**NOTE** perhaps hold off on app communication until after GEISA 1.0.0)
- Inspect and control application packet flows

Networking Control
^^^^^^^^^^^^^^^^^^

These permissions relate to controlling app access to the network.

By default, apps are not given any network access.

- Which network interfaces (none by default)
- Which network ports (none by default)
- Instantaneous Bandwidth
- Average network volume over a period (e.g. 1 hour, 24 hours)
- Direct versus Indirect Access
- Allowed destination addresses
- Allowed destination ports

API Control
^^^^^^^^^^^

These permissions realte to controlling app access to the network.

- Metrology Acccess (e.g. 1-second RMS, Waveforms)
- Actuator Access (if present)
- Sensor Access (if present)
- Hardware Access (GPIO, I2C, SPI, etc.)
- Inter-App Communication (**NOTE** perhaps hold off on app communcation until after GEISA 1.0.0)
- Device-to-Device Communcation (**NOTE** hold off until after GEISA 1.0.0)

Container Resource Management
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Container resource limits shall include the following:

- CPU limit (% of CPU)
- Memory Limit (in 1K units)
- Persistent Storage Limit (in 1K units)
- Non-Persistent Storage Limit (in 1K units)
- Allowed Network Bandwidth (in 1K units)

    - Ongoing Limit Outbound
    - Ongoing Limit Inbound
    - Burst Limit Outbound

- Allowed networking interfaces

    - HAN
    - LAN
    - FAN

- Define Container Access Levels

    - Level 0 - Read and Control - Core Features - Immutable
    - Level 1 - Read and Control - Utility
    - Level 2 - Read only

