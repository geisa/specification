<!--
Copyright 2025-2026, Contributors to the Grid Edge Interoperability &
Security Alliance (GEISA), a Series of LF Projects, LLC

Licensed under the Apache License, Version 2.0. See LICENSE.
-->

# Application manifest examples (JSON)

This directory includes JSON examples aligned to the GEISA application manifest
schema.

Current examples:

- vendor application manifest example:
  - `vendor-application-manifest-example.json`
- deployment/operator application manifest example:
  - `deployment-application-manifest-example.json`

For repository-level JSON validation/lint checks, run:

    npm run lint

# Signatures

The signatures in the manifests are valid.  It is possible to check these 
signatures by extracting the manifest block, formatting it in canonical form,
and using `gpg`.

To extract the manifest, the following command can be used:

`jq -c '.["geisa-application-manifest"].["manifest"]' \
 < deployment-application-manifest-example.json \
 > manifest-block.json `

The signatureValue element must be extracted and placed in a text file with 
the required "-----BEGIN PGP SIGNATURE-----" header.  This can be done with 
following commands:

`echo -e "-----BEGIN PGP SIGNATURE-----\n" > manifest-block.asc`

`jq -c '.["geisa-application-manifest"].["signatures"].[0].["signatureValue"]' \
 < deployment-application-manifest-example.json | sed s/\"//g >> manifest-block.asc`

`gpg --verify manifest-block.asc manifest-block.json`

Note: to complete the verification, the appropriate key must be loaded.  The 
`deployment-application-manifest-example.json` was signed using 
`system-operator-example.key`.  The `vendor-application-manifest-example.json`
was signed using `app-publisher-example.key`.  The public keys are available 
in the `examples` directory.


