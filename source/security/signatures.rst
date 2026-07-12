
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
https://github.com/geisa/schemas/blob/main/geisa-application-manifest-schema.json).  

GEISA supports two digital signature schemas:

- ECDSA as per [FIPS186]_
- MLDSA as per [FIPS204]_

Additional signature schemes (e.g EdDSA, FNDSA, etc.) maybe added if there is
demand.

GEISA conformant EMS and platforms MUST support ECDSA using the P-521 curve
(see [NIST800-186]_) and MLDSA using ML-DSA-65 signatures.  ML-DSA-65
signatures are quite large (3309 bytes) compared to ECDSA signatures; however,
guidance from the NSA [CSNA20]_ indicates that systems should migrate to post
quantum cryptogpraphy no later than 2031.


Signature Validation
~~~~~~~~~~~~~~~~~~~~

To facilitate tranport of digital signatures in JSON files, signatures are
provided as hexadecimal text.  While this approach is not as efficient as
Base64 and other denser encoding it is very simple to implement and it avoids
requiring escape sequences.  Encoding and decoding in C can be done with
:code:`printf("%x",signature)` or :code:`scanf("%x",signature)`.

The application manifest schema requires expected length of the signature (in
bytes) be included.  This acts as a simple integrity check.  Given the
hexadecimal encoding, the signature length should always be half the number of
characters in the signature string.

The application manifest schema also includes a signatureReference field.  This
field is the SubjectName of the x.509 signature that can be used to validate
the signature.  While this field is not required, publishers SHOULD include it
when providing an application manifest so that the GEISA EMS can easily
identify which certificate should be used.

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


.. admonition:: To-Do

   Need to define the wrapper for firmware images.

.. admonition:: To-Do

   Need to add discussion on zip files containing images and manifest.

|geisa-pyramid|

