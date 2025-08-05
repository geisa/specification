Security
----------------

Security is fundamental to the GEISA specification,
so much so that it is included in the name itself: Grid Edge Interoperability and **Security** Allicance.

The following are the minimum criteria needed success of the GEISA specification and for the implementor.

- Clear expections must be illustrated
  outlining what responsibilities fall to the GEISA team
  vs the entities or individuals
  implementing the specification.
  This will be ferred to as the "Shared Responsiblity Model".
- The specification must affort an implementor the ability(ies) to
  comply with applicable standards,
  frameworks,
  certifications, etc.

GEISA Responsibilities
^^^^^^^^^^^^^^^^^^^^^^

It is important to note that GEISA can’t feasibly account for all implementer operational contexts, architectures, governance and policy requirements, processes, etc. and, as such, the below responsibilities have been identified given these circumstances.

Responsible for:

**# Noting that I use the "COE" abbreviation but don't see anything in the glossary. I want to be sure that is still the standard term that captures the entirety of the GEISA environment.**

- Making available to an implementer a baseline COE with levers needed to afford the implementer the ability to meet their applicable security and privacy requirements.
- Identifying the minimum system requirements in order to run the GEISA specification and testing against those system requirements to prove out a reference implementation in support of implementers.
- Implementing processes to ensure that contributions to the GEISA specification are properly vetted and carried out by individuals free of malicious intent.
- Defining and maintaining a baseline :ref:`threat_model` to identify risks, and where deemed appropriate, aligning system design to either mitigate those risks or allow for mitigation of those risks by an implementer using mechanisms available in the COE.


Implementer Responsibilities
^^^^^^^^^^^^^^^^^^^^^^^^^^^^
You as the implementer are best suited, and equipped, to understand the architecture that you are implementing within, the parties involved, the policy requirements and risk appetites, etc. and, as such, the following responsibilities have been identified given these circumstances.

Responsible for:

- Identifying the applicable laws, regulations, required security and privacy controls or other security and privacy-oriented requirements that they must satisfy and assessing the GEISA specification for suitability to meet those requirements and then implementing those requirements.
- Identifying the underlying hardware, choosing the compatible operating system they wish to use and at their discretion any additional software deemed necessary beyond what is defined in the GEISA specification.
- Once implemented keeping the operating system and any other software current with updates as they are released to fix published bugs, defects, vulnerabilities, etc.
- Defining their own shared responsibility model with any third parties that they may allow to access or provide components to the architecture they implement inclusive of the GEISA specification. For example, any application developers, system operators, etc.
- Defining and maintaining a threat model, which may take into account the GEISA baseline threat model, and identifying applicable risks as well as any appropriate action(s) to mitigate those risks.
- Ensuring achievement all implementer-specific control requirements spanning all relevant Security and Privacy domains.
- The GEISA specification may assist the implementer with achieving certain implementer requirements but it is not responsible for the final design, implementation and/or operation of controls defined by the implementer and required to meet certain implementer requirements.- 

.. _threat_model:
Threat Model
^^^^^^^^^^^^^^^^^^^^^^

The GEISA Execution Environment **inputs**:

- HAN Interface
 - Gateway
 - Smart Inverters
- LAN Interface
- Environmental Sensors
 - Temperature
 - Humidity
 - Accelerometer
 - Location (GPS)
- Meter Register
- Metrology Sensor
- Provisioning Interfaces
 - Bluetooth
 - Thread
 - HAN Interface. **# Would this technically be an input?**

GEISA Execution Environment **outputs**:

- HAN Interface
- LAN Interface
- Local Storage
- Disconnect Switch(es)

**Potential Threats and Causes**

- Malicious Firmware & Apps
 - Supply Chain Attack
 - Unpatched Components
 - Compromised Vendor
 - Compromised Staff Workstation
 - Compromised Management System
- Vulnerable Network Interface
 - Poor Programming Practices
 - Inadequate Testing
 - Unpatched Components
- Broken Firmware
- Poor Programming Practices
 - Incorrect Logic
 - Inadequate Testing
 - Unpatched Components
- Side Channel Attacks
- Malicious Inputs
 - Forged data from Smart Inverters
 - Forged data from EVSE
 - Attack on the Provisioning Interface
- Privilege Escalation
 - Unpatched Components
 - Poor system design
- Isolation Escape
 - Unpatched Components
 - Poor system design
- Direct Hardware Attack
 - Decap Chip
 - Access to programming interfaces
  - Replace Firmware
  - Retrieve and decompile firmware
 - Swap out the chip
- Resource Exhaustion
 - CPU
 - Memory 
 - Storage
 - HAN Communications
 - LAN Communications
- Denial of Service
 - HAN Communications
 - LAN Communications
- Peer-to-Peer Attacks

**Potential Attacker Objectives**

- Access to the Utility or Operator (e.g. Meter Maker) Internal Network
- Controlling the Remote Service Switch (or other actuator)
- Attacking devices within the Home
- Coordinated attacks across Homes
 - Note: there are papers which demonstrate that coordinated attacks on as little as 1% of the load can cause grid instability.
- Manipulating readings (typically for theft)
- Steal data (privacy, spying on customers etc.)
- Obtaining Key material to impersonate the meter.
- Turn devices into a botnet (e.g. Mirai, etc.)