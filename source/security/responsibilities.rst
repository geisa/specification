
..
  Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
  Security Alliance (GEISA), a Series of LF Projects, LLC
  This file is licensed under the Community Specification License 1.0
  available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md


Responsibilities
^^^^^^^^^^^^^^^^

GEISA is intended to support multi-vendor application ecosystems across
heterogeneous hardware platforms, and is designed to support deployment across
utilities and operators with differing regulatory obligations, risk tolerances,
and operational practices. Accordingly, the specification separates capability
definition from policy enforcement.

The Common Operating Environment (COE) provides mechanisms that enable
security, privacy, and operational policies to be configured by the
deploying utility or operator. GEISA does not mandate uniform policy settings,
nor should implementations hard-code assumptions about allowable access,
connectivity, or application behavior.

The COE is not a single software component or runtime environment. It is the
logical collection of execution environments, system services, control
interfaces, policy enforcement mechanisms, and lifecycle management functions
defined by GEISA that together provide a governed platform for applications at
the grid edge.

The COE may include one or more execution environments (e.g. native Linux or 
virtual runtimes), but is defined by the security, isolation, authorization, 
and operational controls it enforces rather than by any specific
implementation technology.

This approach ensures that:

* Utilities and operators retain authority over what functionality is enabled.
* Policy decisions may be adapted to local regulatory or operational needs as
  required.
* Interoperability across vendors (hardware and software as applicable) is 
  maintained without constraining governance.

Implementations shall expose the configuration and control interfaces necessary
for operator-defined policy to govern behavior within the COE.

The following are the minimum criteria needed for success of the GEISA
specification and for the implementor.

* Clear expectations must be illustrated outlining what responsibilities fall
  to the GEISA team vs the entities or individuals implementing the
  specification. This will be referred to as the "Shared Responsibility
  Model".
* The specification must enable implementers to comply with applicable
  standards, frameworks, certifications, or regulatory requirements.

Shared Responsibility Model
~~~~~~~~~~~~~~~~~~~~~~~~~~~
GEISA cannot feasibly account for every implementer’s operational context,
architecture, governance model, policy requirement, or business process.
Accordingly, responsibilities are divided between GEISA and those entities
implementing or operating solutions based on the specification.

The GEISA specification is architected according to established security design
principles; however, as a specification it defines required capabilities and
interfaces rather than prescribing specific implementations. It provides the
mechanisms and flexibility needed for implementers and operators to apply their
own policies, controls, and technology choices appropriate to their
environment.

GEISA is therefore not responsible for the final design, implementation, or
operation of security controls within a specific implementation or deployment.
The specification is not tailored to implementation-specific requirements and
does not mandate particular components, libraries, or platforms. It is
intentionally implementation-agnostic so that conformant solutions may adapt to
evolving technologies, regulatory landscapes, and operational priorities while
maintaining interoperability.

GEISA also recognizes that Implementers and Operators adopting the 
specification may have varying definitions of data classification and policy
statements surrounding those classifications. The specification is designed 
to allow for the application of policy and controls appropriate to a variety 
of needs and requirements. As such, it and does not mandate specific 
classifications or associated controls. Instead, GEISA makes capabilities 
available to Implementers and Operators such that they may apply their own 
classifications and controls as needed to meet their requirements.

GEISA Responsibilities
~~~~~~~~~~~~~~~~~~~~~~
..
   Note - added COE to current glossary. We do want to be sure that is still the
   standard term that captures the entirety of the GEISA environment.

* Making available to an implementer a baseline specification for a Common
  Operating Environment(COE) with levers needed to provide the implementer the
  ability to meet their applicable security and privacy requirements.
* Identifying the minimum system requirements in order to run the GEISA
  specification and testing against those system requirements to prove out a
  reference implementation in support of implementers.
* Implementing processes to ensure that contributions to the GEISA
  specification are properly vetted and carried out by individuals free of
  malicious intent.
* Defining and maintaining a baseline :ref:`threat_model` to identify risks,
  and where deemed appropriate, aligning system design to either mitigate those
  risks or allow for mitigation of those risks by an implementer using
  mechanisms available within the COE.

Implementer Responsibilities
~~~~~~~~~~~~~~~~~~~~~~~~~~~~
You as the implementer are best suited and equipped to understand the
architecture and environment that you are implementing within, the parties
involved, additional/specific policy requirements and risk appetites, etc. and,
as such, the following responsibilities have been identified:

Responsible for:

- Identifying the applicable laws, regulations, required security and privacy
  controls or other security and privacy-oriented requirements that individual
  specific entities must satisfy, assessing the GEISA specification for
  suitability to meet those requirements, and then implementing those
  requirements.
- Identifying the underlying hardware, choosing a compatible operating system
  they wish to use and at their discretion any additional software or system
  services deemed necessary beyond what is defined in the GEISA specification.
- Once implemented, keeping the operating system and any other software current
  with updates as they are released to fix published bugs, defects,
  vulnerabilities, etc.
- Defining their own shared responsibility model with any third parties that
  they may allow to access or provide components to the architecture they
  implement inclusive of the GEISA specification. This may include but is not
  limited to first or third-party application developers, system operators,
  etc.
- Defining and maintaining a threat model, which may take into account the
  GEISA baseline threat model, and identifying applicable risks as well as any
  appropriate action(s) required in order to mitigate those risks.
- Ensuring achievement of any/all implementation-specific control requirements
  spanning any/all relevant Security and Privacy domains.
- The GEISA specification may assist the implementer with achieving certain
  baseline implementation requirements but it is not responsible for the final
  design, implementation and/or operation of controls defined by the implementer
  nor is the GEISA specification required to meet implementation-specific
  requirements.

The following threat model establishes the risk framework used to derive the
security capability expectations defined by this specification.

|geisa-pyramid|

