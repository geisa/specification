
..
  Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
  Security Alliance (GEISA), a Series of LF Projects, LLC
  This file is licensed under the Community Specification License 1.0
  available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

Digital Signatures
^^^^^^^^^^^^^^^^^^

Support Signature Algorithms
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

GEISA requires that application images, firmware images, and application
manifest be digitally signed.  Digital signatures for application images are
provided in the application manifest in the application artifact object (see
https://github.com/geisa/specification/blob/main/schemas/geisa-application-manifest-schema.json).
A full discussion of how signature are formatted within GEISA can be found in
:doc:`/adm/manifests`.

Generally, GEISA signatures are detached signature packets, as defined within
the OpenPGP standard, as defined in [RFC9580]_ and [RFC9980]_.  These standards
define a rich set of signing and encryption capabilities, of which GEISA uses
just a minor subset.

GEISA supports two digital signature schemas:

- ECDSA as per [FIPS186]_ and as operationalized in [RFC9580]_.
- MLDSA as per [FIPS204]_ and as operationalized in [RFC9980]_.

Spefically, conformant EMS and platform implementations MUST support

- ``ML-DSA-65+Ed25519`` (algorithm ID 31) 
- ``ECDSA`` (algorithm ID 19)

.. Note::

   The OpenPGP implementation of MLDSA is hybridized with EdDSA.

GEISA conformant EMS and platforms MUST support Version 6 signatures, as per
[RFC9580]_ and SHOULD support Version 6 signatures.

GEISA conformant EMS and platforms MUST support ECDSA using the P-521 curve
(see [NIST800-186]_) and MLDSA using ML-DSA-65 signatures.  ML-DSA-65
signatures are quite large (3309 bytes) compared to ECDSA signatures; however,
guidance from the NSA [CSNA20]_ indicates that systems should migrate to post
quantum cryptogpraphy no later than 2031.


Signature Validation
~~~~~~~~~~~~~~~~~~~~

To facilitate tranport of digital signatures in JSON files, signatures are
provided as base64 encoded text, based on [RFC9580]_ and the GEISA specific
guidance provided in :doc:`/adm/manifests`.

The [RFC9580]_ signature packet embeds within it the required metadata (e.g.
the algorithm, key identifier, etc.) to allow the signature to be matched to
the appropriate public key and the verification completed.  Implementers should
be able to use an appropriate OpenPGP compliant library to verify or generate
signatures as required.

The GEISA deployment manifest requires at least one signature per artifact and
at lease one signature per manifest.  Artifacts may have more than one
signature in the manifest.  When more than one signature is included,
conformant EMS and conformant platforms MUST validate every signature in the
manifest.  If any of the signatures do not validate, the manifest or artificat
MUST be rejected as having failed signature validation.  Support for multiple
signatures is provided to allow an optional certifier (see :doc:`/operations`)
to countersign images, manifests, or both.  To ensure artifacts provenance
publishers MUST always sign their artifacts, even if an artifact will be
submitted to an optional certifier.


.. To-Do

   Need to define the wrapper for firmware images.

.. To-Do

   Need to add discussion on zip files containing images and manifest.

|geisa-pyramid|

