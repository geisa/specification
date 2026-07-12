
..
  Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
  Security Alliance (GEISA), a Series of LF Projects, LLC
  This file is licensed under the Community Specification License 1.0
  available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md


.. _threat_model:

Threat Model
^^^^^^^^^^^^
The GEISA threat model identifies the assets requiring protection, the trust
boundaries across which the GEISA Common Operating Environment (COE) operates,
and representative threat scenarios that conformant implementations should be
designed to mitigate. It is not exhaustive and is intended to be a living
framework that evolves alongside the threat landscape. It provides implementers
with a baseline set of threats to consider when evaluating their specific
implementations.

Implementers SHOULD extend this model to reflect their operational context, 
inclusive of, but not limited to, their deployment, regulatory, and operational
environments and identify additional threats applicable to their specific 
circumstances.

Unlike traditional IT systems, compromise of grid-edge devices and resources may
create direct reliability impacts to the electrical grid or to individual
service locations. Therefore, prioritizing a defense-in-depth approach is 
essential. Additionally, the potential for physical access to grid-edge 
devices creates a need for robust physical security controls and/or tamper 
resistance.

The GEISA specification is designed to enable implementers to meet these needs
through the design of the COE and the control levers it provides to enforce
deployment-specific security policy.

Software Provenance and Deployment Authorization
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
GEISA deployments rely on verifiable software provenance and explicit operator
authorization. Trust decisions may involve multiple independent signing or
credential authorities, including application providers, utilities/operators,
and, where implemented, device or platform providers.

The following roles are referenced in this section:

* *Application Publisher*: the entity responsible for producing, signing,
  and asserting provenance of an application or workload artifact.
* *Device/Platform Provider*: the entity responsible for the hardware or
  platform on which the COE executes, when such identity is represented.

.. NOTE::
   Review whether the PKI governance language below reflects current
   consensus regarding operator authority and interoperability.  In
   particular, hw impact and compute needed for the more frequent 
   validation checks. 

GEISA does not mandate a specific PKI hierarchy; however, cryptographic
identity, signing, and validation are REQUIRED capabilities.

Implementations shall be capable of interoperating with operator-selected
utility, vendor, or industry PKI systems. Conformant implementations shall not
require exclusive use of a proprietary trust infrastructure controlled solely
by the implementer.

The utility or operator retains final authority over trust anchors,
certificate hierarchies, and approval of credential authorities.

Conformant implementations shall support operator-selected trust anchors and
credential authorities and shall not constrain the operator to a single
implementer-controlled trust infrastructure.

Support for operator-selected trust configurations shall be provided in a
manner that preserves the verification and enforcement capabilities described
herein.

Conformant implementations must provide mechanisms enabling:

* Validation of application provenance (e.g., verification that an application
  artifact corresponds to the bits produced by an identified vendor or
  publisher).
* Validation of operator authorization prior to deployment or activation (e.g.,
  the utility/operator explicitly approves whether a given application is
  permitted in a target environment, device class, or operational mode).
* Verification of authenticity and authorization in both:

  - application lifecycle workflows (e.g., package intake, cataloging, approval,
    deployment orchestration), and
  - on-device enforcement prior to install, activation, or execution within the
    COE.
* Support for both centralized deployment orchestration and authorized local
  provisioning workflows (e.g., field tool installation by authorized personnel).

Device or platform identity mechanisms (e.g., hardware vendor certificates or
attestation) may be used to strengthen trust in the executing environment.
GEISA does not mandate such mechanisms; however, if implemented they must
integrate with the above validation and enforcement model.

Validation performed by centralized or upstream lifecycle management systems
shall not be considered sufficient on its own. The COE must enforce verification
of software authenticity and authorization locally on the device prior to
installation, activation, or execution.  This ensures that software running 
within the COE is trustworthy even in the event of compromised upstream systems 
or supply chain attacks that may attempt to introduce unauthorized or malicious 
software.

The COE is the final technical enforcement point on the device itself.
Operational authority remains with the utility/operator (or delegated
operational systems) that define policy and authorization; the COE ensures 
those decisions are enforced locally and cannot be bypassed by external systems. 
External lifecycle or orchestration systems may request deployment actions, but 
shall not be able to bypass local verification, authorization, or policy enforcement.

Lifecycle Trust Enforcement
~~~~~~~~~~~~~~~~~~~~~~~~~~~
Trust within GEISA is not established at a single point in time. It is evaluated
and enforced across multiple lifecycle transitions, including application
ingest, approval, deployment, installation, activation, and execution.

Conformant implementations must ensure that trust assertions made by one system
or phase are independently verified at the point where enforcement occurs. Trust
shall not be implicitly inherited across lifecycle boundaries without validation.

This includes, but is not limited to:

* Verification of application integrity and publisher identity when software is
  introduced into lifecycle management systems (i.e. a GEISA ADM conformant
  Edge Management System).
* Confirmation of operator authorization prior to deployment to a device or
  environment.
* Independent validation performed by the COE prior to installation and at
  activation (including restarts of applications and/or workloads).

  .. NOTE::
     Need to discuss execution/runtime or periodic validations.
* Continued enforcement of policy, identity, and behavioral constraints during
  runtime operation.
* Runtime enforcement of operator-defined behavioral constraints, including the
  ability to detect, limit, or terminate workloads that violate policy or exceed
  authorized resource or communication profiles.
* Revocation of trust relationships when software is no longer authorized for 
  execution within the COE (e.g. due to compromise, policy change, or end of life).

This model ensures that compromise of any single lifecycle component does not
result in implicit trust of software or actions elsewhere in the system and helps 
to mitigate risks resulting in systemic compromise.

Trust Revocation and Credential Lifecycle
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   
GEISA defines mechanisms (revocation, update, policy change), but the System
Operator is responsible for monitoring, initiating, and governing these
actions, though some may be automated in vendor implementations.  GEISA
implementations and deployments must support the ability to modify or withdraw
previously established trust relationships throughout the operational lifecycle
of a device or application.

Conformant implementations shall provide mechanisms enabling:

* Revocation or invalidation of application, publisher, operator, or device
  credentials when trust can no longer be assured.
* Enforcement of operator-directed actions to disable, restrict, or remove
  software that is no longer authorized for execution within the COE.
* Update and rotation of trust anchors, certificates, and associated
  cryptographic material without requiring replacement of deployed devices.
* Local enforcement of revocation or policy changes even in environments with
  limited or intermittent connectivity to centralized management systems.

These capabilities ensure that trust established during provisioning or
deployment can be continuously evaluated and adjusted in response to evolving
security conditions, operational decisions, or cryptographic requirements.

Assets Requiring Protection
~~~~~~~~~~~~~~~~~~~~~~~~~~~
The GEISA specification is designed to protect the following asset classes:

* Integrity of grid-impacting control functions (e.g., service disconnect, DER
  coordination, or other local controls)
* Authenticity and integrity of telemetry, metrology, and status data
* Device identity and associated cryptographic credentials
* Availability of edge execution environments necessary for safe grid operation
* Application and Application Publisher identity as represented by
  associated credentials
* Isolation between workloads executing within the COE
* Application and device monitoring, behavioral logging, and alerting
  capabilities
* Customer data subject to privacy and/or regulatory protection
* Trust relationships with utility/operator systems
* Software and firmware integrity across the device lifecycle

Trust Boundaries and External Interfaces
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The GEISA Execution Environment operates across multiple security trust
boundaries. A trust boundary exists wherever administrative control, execution
privilege, or assurance level changes.

GEISA defines these boundaries to enable secure interoperability among
heterogeneous vendor solutions while preserving the operator’s ability to
enforce deployment-specific policy. The GEISA Common Operating Environment 
(COE) acts as the on-device enforcement point through which operators may 
permit, restrict, or condition interactions between applications, networks, 
and connected systems.

These enforcement functions exist regardless of whether applications execute
locally, participate in hybrid edge/cloud workflows, or are installed through
centralized lifecycle management systems.

All interactions crossing these boundaries shall be treated as untrusted unless
explicitly authenticated, authorized, and governed by operator-defined policy.
The boundaries listed below represent the primary attack surfaces considered by
this model. They are not exhaustive. Implementers shall evaluate their
deployment to determine whether additional boundaries are present.

Note that examples are illustrative and do not define required sensor types or
configurations.

+----------------------------+---------------------------------------------+------------------------------+
| Boundary                   | Description                                 | Examples                     |
+============================+=============================================+==============================+
| Field Devices              | Physically accessible deployment            | Enclosure access, debug      |
|                            | environment where attackers may gain        | ports                        |
|                            | hardware access. This includes attempts     |                              |
|                            | to tamper with the device, extract          |                              |
|                            | sensitive material, or conduct side-channel |                              |      
|                            | to observe, influence, or bypass normal     |                              |
|                            | system protections.                         |                              |
+----------------------------+---------------------------------------------+------------------------------+
| Local Provisioning /       | Interfaces used during installation or      | Field tools, Bluetooth,      |
| Maintenance                | maintenance that may introduce temporary    | serial                       |
|                            | elevated trust.                             |                              |
+----------------------------+---------------------------------------------+------------------------------+
| Sensors                    | Data originating from instrumentation whose | Metrology, temperature,      |
|                            | acquisition and integrity are governed by   | accelerometer, GNSS, other   |
|                            | the COE device itself.                      | directly-attached sensors    |
+----------------------------+---------------------------------------------+------------------------------+
| Customer Networks          | Communications over networks not managed    | Home/Business Wi-Fi, HAN,    |
|                            | by the utility/operator and therefore not   | LAN, Thread                  |
|                            | inherently trusted.                         |                              |
+----------------------------+---------------------------------------------+------------------------------+
| Workload (e.g.             | Separation between the COE platform and     | GEISA COE APIs, resource     |
| Applications)              | hosted workloads enabling operator control  | allocation, storage,         |
|                            | over resource and network access. This      | permission models            |
|                            | boundary exists even when all code is local |                              |
|                            | due to multi-tenancy, privilege separation, |                              |
|                            | and differing lifecycles.                   |                              |
+----------------------------+---------------------------------------------+------------------------------+
| External Device / Control  | Interfaces to autonomous systems not        | Inverters, Matter devices,   |
|                            | governed by GEISA lifecycle or assurance    | thermostats, gateways,       |
|                            | controls. Includes third-party devices or   | controllable loads, local    |
|                            | subsystems that may have grid or local      | data sources                 |
|                            | impact if compromised.                      |                              |
+----------------------------+---------------------------------------------+------------------------------+
| Operational Integration    | Exchange of operational data with upstream  | AMI backhaul, DERMS,         |
|                            | systems, including utility or non-utility   | analytics platforms,         |
|                            | infrastructure outside the COE trust domain.| monitoring systems, hybrid   |
|                            |                                             | edge/cloud applications      |
+----------------------------+---------------------------------------------+------------------------------+
| Lifecycle Management       | Authority to deploy, configure, approve,    | Application deployment,      |
|                            | restrict, update, or revoke software and    | update orchestration,        |
|                            | policy governing the COE.                   | policy/config distribution   |
+----------------------------+---------------------------------------------+------------------------------+

Utility-operated networks and systems are considered external to the COE trust
domain and are therefore modeled within the Operational Integration or
Lifecycle Management boundaries depending on function.

Devices communicating via customer-managed ecosystems (e.g., Wi-Fi, Thread,
Matter, or similar technologies) are not considered part of the Sensor
Boundary, even when providing measurement data. Such devices operate with
independent identity, firmware, and lifecycle control and are therefore treated
as External Devices whose communications traverse the Customer Network Boundary.

Threat Actors Considered
~~~~~~~~~~~~~~~~~~~~~~~~
The GEISA threat model considers a range of potential threat actors with varying
levels of access, capability, and intent. These actors may operate
independently or in coordination and may target individual devices, aggregated
infrastructure, or upstream systems.

The following categories are considered within scope:

+----------------------------+---------------------------------------------+
| Threat Actor               | Description                                 |
+============================+=============================================+
| Supply Chain Adversary     | Actor seeking to introduce malicious        |
|                            | components, firmware, or updates during     |
|                            | manufacturing or distribution stages.       |
+----------------------------+---------------------------------------------+
| Field-Level Physical       | Actor with physical access capable of       |
| Attacker                   | tampering, extraction, or hardware          |
|                            | manipulation to disrupt operation, alter    |
|                            | executable code outside authorized          |
|                            | lifecycle processes, or obtain data from    |
|                            | the device. This may include invasive       |
|                            | techniques (e.g., device/chip decapsulation |
|                            | ("decap"), probing, or unauthorized         |
|                            | reflashing) intended to bypass protections. |
+----------------------------+---------------------------------------------+
| Opportunistic Local        | Actor on a customer or shared network       |
| Network Attacker           | capable of interception, manipulation, or   |
|                            | disruption of communications or operations. |
+----------------------------+---------------------------------------------+
| Unauthorized Local Service | Individual attempting access via            |
| Actor                      | provisioning or maintenance interfaces      |
|                            | using unauthorized or stolen tools or       |
|                            | credentials.                                |
+----------------------------+---------------------------------------------+
| Remote Adversary           | External attacker using network access to   |
|                            | exploit exposed services, protocols, or     |
|                            | integrations.                               |
+----------------------------+---------------------------------------------+
| Coordinated Distributed    | Group or automated campaign capable of      |
| Actor                      | influencing behavior across many endpoints. |
+----------------------------+---------------------------------------------+
| Compromised Upstream       | Trusted operational or management system    |
| System                     | issuing valid-looking but malicious actions |
|                            | after being compromised.                    |
+----------------------------+---------------------------------------------+
| Compromised External       | Third-party or customer-managed device      |
| Device                     | providing malicious data or attempting      |
|                            | lateral influence on the COE.               |
+----------------------------+---------------------------------------------+
| Malicious or Negligent     | Individual with authorized access who may   |
| Insider                    | misuse privileges, attempt escalation,      |
|                            | alter policy, or exfiltrate information,    |
|                            | either intentionally or unintentionally.    |
+----------------------------+---------------------------------------------+

Representative Threat Scenarios
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The following scenarios illustrate representative ways in which identified
threat actors may attempt to exploit trust boundaries to impact protected
assets. These examples are not exhaustive but demonstrate the types of risks
implementations should be designed to address.

Implementations SHOULD address these risks using deployment-specific controls,
policies, and technologies consistent with the capabilities defined by the
GEISA specification.

Unauthorized Use of Local Service Interfaces
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
An Unauthorized Local Service Actor connects to provisioning or maintenance
interfaces using stolen credentials or unauthorized tools to modify
configuration, deploy software, or alter policy.

* Boundaries Involved: Local Provisioning / Maintenance, Lifecycle Management
* Potential Impact: Unauthorized deployment, policy manipulation, integrity
  loss, or unauthorized access to sensitive configuration or data.

Compromise of a Customer-Network Connected Device
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
A Compromised External Device (e.g., Matter or Wi-Fi system) provides falsified
telemetry or malformed data intended to influence processing performed locally
or by upstream systems participating in hybrid workflows.

* Boundaries Involved: External Device / Control, Customer Networks
* Potential Impact: Corrupted data, unintended control actions, incorrect
  operational conclusions, or propagation of misleading information into
  coordinated services.

Malicious or Altered Software Introduced During Update
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
A Supply Chain Adversary inserts malicious code into firmware, applications,
or update packages prior to deployment.

* Boundaries Involved: Lifecycle Management
* Potential Impact: Persistent compromise, unauthorized control, data exposure,
  or loss of software and device integrity across the lifecycle.

Remote Exploitation of Exposed Services
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
A Remote Adversary targets reachable services or protocols to gain unauthorized
access, manipulate data, or disrupt availability.

* Boundaries Involved: Operational Integration
* Potential Impact: Loss of availability, unauthorized command execution,
  unintended control actions, or compromise of data privacy.

Insider Abuse of Authorized Privileges
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
A Malicious or Negligent Insider misuses authorized access to escalate
privileges, alter logging or policy, access sensitive data, or deploy
unauthorized workloads.

* Boundaries Involved: Workload Boundary, Lifecycle Management
* Potential Impact: Policy bypass, unauthorized data access, compromise of data
  privacy, undetected system changes, or loss of operational integrity.

Coordinated Manipulation Across Multiple Devices
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
A Coordinated Distributed Actor attempts to influence many endpoints
simultaneously to create aggregate operational impact or to collect or
manipulate data at scale.

* Boundaries Involved: Operational Integration
* Potential Impact: Grid instability, synchronized disruption, large-scale data
  exposure, or propagation of misleading information into upstream systems.

The following capability expectations describe the security functions that
implementations must be able to realize in order to address the risks
identified in this threat model.

|geisa-pyramid|


