..
  Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
  Security Alliance (GEISA), a Series of LF Projects, LLC
  This file is licensed under the Community Specification License 1.0
  available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

Conformance
-----------

The |GEISA| was established to advance interoperability within the utility
industry.  Interoperability exists in many forms.

To enable platform vendors, application developers, management system
providers, and utilities to evaluate a given system component against the
applicable requirements of this specification, |GEISA| provides an open source
conformance test framework.

This framework is licensed under the `Apache License`_ and is available in
the |GEISA| `github repository`_.

The framework is intended to be run in users' own environments to evaluate
an implementation's behavior against the applicable requirements of a
specific GEISA specification version for one or more GEISA interoperability
pillars:

.. list-table:: GEISA Conformance Pillars
   :widths: 10 35 55
   :header-rows: 1

   * - Pillar
     - Test domain
     - Broad scope
   * - ADM
     - GEISA platform/EMA, EMS, or both in their declared roles
     - LwM2M transactions, required objects, management and lifecycle behavior
   * - API
     - Platform-provided GEISA API implementation
     - Topics, payloads, request/response behavior, permissions, and platform/application interaction
   * - LEE
     - Platform execution environment
     - Linux environment, libraries, filesystem, isolation, and required execution behavior
   * - VEE
     - Platform virtual execution environment
     - Runtime, libraries, isolation, and defined managed execution behavior;
       automated conformance coverage is planned

Conformance is evaluated independently for ADM, API, LEE, and VEE. A
conformance result applies only to the implementation role, interoperability
pillar, specification version, target configuration, and tests identified in
the result. It does not imply conformance for untested pillars, roles, or
requirements.

The GEISA specification remains authoritative. The conformance test framework
provides evidence against its requirements; it does not define or modify
those requirements.

.. important::

   GEISA conformance testing evaluates observable implementation behavior
   against the applicable requirements of the GEISA specification. It does
   not constitute application certification, product certification, utility
   production approval, cybersecurity certification, safety certification,
   regulatory approval, or validation that an application performs its
   claimed business or analytic function.

   Passing the available tests provides evidence only for the scope actually
   tested. It does not establish broader conformance for requirements or
   interoperability pillars that were not evaluated.

Conformance testing is not intended to replace deeper product or application
certification processes. It provides an accessible mechanism for producing
pillar-specific evidence of GEISA specification and interoperability
conformance.

An application used by the conformance framework itself is a test tool;
successful use of that application does not certify it, or any other
production application.

A conformance result can inform procurement, integration, and deployment
decisions.  The System Owner or System Operator still determines whether a
particular platform, management system, application version, configuration,
and deployment is approved.  Conformance does not override utility policy or
risk acceptance.  Application approval and signed deployment manifests remain
operator-controlled workflows.

Conformance testing covers:

- Does this platform, EMS, API, LEE, or VEE implement the applicable GEISA
  requirements?
- Can independently developed components interact through the specified
  interfaces?
- Are required observable behaviors present?

Application certification may cover:

- Does this specific application artifact remain within acceptable behavioral
  and policy bounds?
- Is it safe or appropriate for a utility's deployment environment?
- Does its algorithm detect what it claims to detect?
- Are its accuracy, false-positive, performance, or operational claims valid?

Refer to :doc:`operations` for more on Application Certification.

Conformance Test Overview
^^^^^^^^^^^^^^^^^^^^^^^^^

The GEISA conformance test suite is Apache-2.0 licensed and:

- is intended for vendors, utilities, developers, and integrators to run
  themselves
- can produce repeatable test evidence and reports in machine-consumable or
  PDF output formats
- may be used in development, integration labs, procurement evaluation, and
  for regression testing or other related purposes

Validation Tools
^^^^^^^^^^^^^^^^

The GEISA conformance test suite uses Cukinia and pillar-specific test tooling
to execute conformance tests and produce results in JUnit XML and PDF formats.
The ADM tests are designed to work with compatible LwM2M server and client
implementations, rather than being tied to specific Leshan or Wakaama
versions.

Running the Conformance Tests
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The conformance test suite may be run manually from a Linux host or through
continuous integration using a configured runner and target. Detailed
information on installing, configuring, and running the test suite in a
user's environment is provided in the `Conformance README`_.

Conformance Test Coverage
^^^^^^^^^^^^^^^^^^^^^^^^^

As of this version of the specification, conformance-test coverage is not yet
complete. Framework coverage evolves alongside the specification and may not
exercise every applicable requirement or provide complete coverage across
every conformance pillar.

Lack of an automated test does not make a normative requirement optional, and
passing the available tests does not establish coverage beyond the tests
actually run.

The project intends to expand coverage across all pillars. At the time of
writing, LEE and API coverage are the most mature, followed by ADM. VEE
coverage is planned and remains the least complete at this time.

Contributing or Reporting Issues
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Contributions to the conformance test suite are welcome, and anyone may open a
pull request against the conformance repository.

If issues are encountered while running the suite, or if gaps or incorrect
behaviors are found, open an issue in `GitHub issues`_. Include the test-suite
version, pillar being evaluated, operating system and version, relevant system
configuration, and enough detail to reproduce the problem.

Other Resources
^^^^^^^^^^^^^^^

The GEISA project maintains example implementations for various pillar
elements that may be used to exercise conformance test cases. Note that
these are example implementations for testing purposes, not fully
operational production systems. Examples include:

- `GEISA LEE Mockup <https://github.com/geisa/lee-mockup>`_ — Example LEE
  environment with Yocto configuration
- `GEISA API Mockup <https://github.com/geisa/api-mockup>`_ — Example API
  implementation using MQTT
- `GEISA ADM Mockup <https://github.com/geisa/adm-mockup>`_ — Example ADM
  implementation using Leshan LwM2M Server and Wakaama LwM2M client

Others may also be of interest outside of the core conformance repo.  Browse
the other GEISA repositories at `GEISA GitHub`_.

The GEISA project is undergoing a repository consolidation. Starting with
the 1.1 release, the schemas repository will be included within the
specification repository, and the conformance repository will aim for
parity with the specification/schemas release cycle.

|geisa-pyramid|

.. _Apache License: https://www.apache.org/licenses/LICENSE-2.0
.. _github repository: |geisa-conformance-repo|
.. _Conformance README: https://github.com/geisa/conformance/blob/main/README.md
.. _GitHub issues: https://github.com/geisa/conformance/issues
.. _GEISA GitHub: https://github.com/geisa