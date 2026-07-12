..
  Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
  Security Alliance (GEISA), a Series of LF Projects, LLC
  This file is licensed under the Community Specification License 1.0
  available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

Common Response Status
----------------------

|geisa-api-hdr|

Summary
=======

GEISA request/response APIs that include ``GeisaStatus`` use it as a common
response status and error model. The common status is used for request/response
result handling and does not replace API-specific response fields that provide
additional context for a particular API.

This model is distinct from the Platform/App Status notification API described
in :doc:`/api/status`. Platform/App Status notifications report runtime platform
or application status over status topics; ``GeisaStatus`` reports the result of
a request/response transaction where the response message includes it.

Status Message Model
====================

``GeisaStatus`` contains:

- ``code``: a ``GeisaStatusCode`` machine-readable result that should drive
  application behavior.
- ``message``: a short human-readable explanation suitable for logs,
  diagnostics, or UI.
- ``details``: optional diagnostic text. Applications MUST NOT parse
  ``details`` for interoperable behavior.

``GEISA_STATUS_SUCCESS`` indicates success.

``GEISA_STATUS_CODE_UNSPECIFIED`` MUST NOT be treated as success unless an API
explicitly says otherwise.

Status Code Handling
====================

Applications should branch primarily on ``code``. Human-readable ``message``
and ``details`` values are for diagnostics and display, not interoperable
control flow.

.. list-table:: Status Code Handling
   :header-rows: 1
   :widths: 24 36 40

   * - Group
     - Codes
     - Expected application behavior
   * - Success
     - ``GEISA_STATUS_SUCCESS``
     - Treat the request as successful, subject to any API-specific response
       semantics.
   * - Request/protocol errors
     - ``GEISA_STATUS_CODE_REQUEST_*``
     - Fix the request before retrying; unchanged retries usually repeat the
       same error.
   * - Authorization/policy errors
     - ``GEISA_STATUS_CODE_AUTH_*``
     - Resolve permission or policy configuration; do not retry unchanged.
   * - Resource, limit, busy, or state errors
     - ``GEISA_STATUS_CODE_RESOURCE_*``
     - Retry only when appropriate, using bounded backoff or after the relevant
       platform state changes.
   * - Execution/platform/dependency errors
     - ``GEISA_STATUS_CODE_EXEC_*``
     - Treat as potentially transient or platform-side according to API
       context; log sufficient diagnostics for triage.
   * - Data quality or availability conditions
     - ``GEISA_STATUS_CODE_DATA_*``
     - Treat the response as completed, but handle data that may be unavailable,
       stale, incomplete, or otherwise limited.

API Usage
=========

The current schemas define ``GeisaStatus`` on these response messages:

- ``GeisaPlatformDiscovery_Rsp``
- ``GeisaWaveform_Rsp``
- ``GeisaActuatorSet_Rsp``
- ``GeisaActuatorGet_Rsp``
- ``GeisaSensorReadings_Rsp``

Some response messages include additional API-specific status or detail fields.
Those fields provide API-specific context in addition to the common status code;
they do not replace ``GeisaStatus`` where it is present.

``GeisaAppMessage_Rsp`` uses its own app-message response status field and is
not defined with ``GeisaStatus`` in the current schemas.

Implementation Guidance
=======================

Applications should branch primarily on the ``GeisaStatusCode`` value.
Applications should not parse ``message`` or ``details`` for interoperable
behavior.

Logs should include the status code and relevant request identifiers where
available. Applications should use bounded retry and backoff for retryable
conditions rather than tight retry loops.

Platforms should return the most specific applicable status code and include
human-readable diagnostics where useful. Platforms should not use success with
partial or invalid data unless the API explicitly defines partial-success
semantics.

Transaction Data
================

- ``GeisaStatus``
- ``GeisaStatusCode``

As defined in |geisa-schemas-repo|

|geisa-pyramid|
