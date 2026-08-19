
..
  Copyright 2025-2026, Contributors to the Grid Edge Interoperability & 
  Security Alliance (GEISA) a Series of LF Projects, LLC  
  This file is licensed under the Community Specification License 1.0 available
   at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md


Application Manifests
_____________________

GEISA's application management system follows a model similar to `Amazon IoT
Greengrass <https://docs.aws.amazon.com/greengrass/v2/developerguide/what-is-iot-greengrass.html>`_
or `Microsoft Azure IoT <https:learn.microsoft.com/en-us/azure/iot/iot-introduction>`_ in that
applications have a `recipe
<https://docs.aws.amazon.com/greengrass/v2/developerguide/component-recipe-reference.html>`_,
`manifest <https://learn.microsoft.com/en-us/azure/iot-central/core/howto-manage-deployment-manifests-with-rest-api>`_,
or other set of metadata describing the requirements and dependencies.

GEISA handles application metadata by defining two manifests for each
application: a vendor manifest and an operator manifest.  

The vendor application manifest provides information about the application to
the operator and the edge management system, including any external
dependencies and minimum resource requirements.  The vendor manifest is used by
a GEISA ADM conformant edge management system to inform the operator about the
application and to facilitate the secure import of the application.  

The operator application manifest is based on the vendor application manifest 
allowing the operator to customize and tune the application permissions and 
resource allocations to match their execution environment, intended use case,
and security requirements prior to deployment to the execution environment.  

.. Warning::

   Overriding the vendor application manifest may prevent applications from
   running correctly.  If a system operator chooses to override the vendor
   recommendations, they take responsibility for any related application
   issues.  To enable operational flexibility, the GEISA specification requires
   that system operators be able to override vendor settings, but operators
   should be aware of the potential consequences.

GEISA vendor and operator application manifests SHALL include:

- Vendor assigned Application ID

    - Vendor assigned application IDs use
      `https://en.wikipedia.org/wiki/Reverse_domain_name_notation Reverse DNS
      Name Notation`, similar to Java packages
    - GEISA recommends ``tld.companyname.geisa.appname`` for application IDs,
      for example, ``com.example.geisa.waveformanalyzer``.

- Name of the application
- Description of the application
- Version Number of the application
- Hash of the application image

    - The GEISA EE shall not activate an application unless the hash of the image matches the hash in the metadata

GEISA vendor manifests SHALL include:

- Compatibility:

    - GEISA API Minimum Version
    - GEISA LEE Minimum Version (null for unsupported)
    - GEISA VEE Minimum Version (null for unsupported)
    - Waveform Access Required (boolean)
    - GEISA LEE CPU arch string as returned by the Linux arch command:

        - ARM 32-bit: armv7l, armv6l
        - ARM 64-bit: aarch64
        - RISC-V 32-bit: riscv32
        - RISC-V 64-bit: riscv64
        - x86 32-bit: i686
        - X86 64-bit: x86_64, amd64

    - GEISA LEE C library required:

        - glibc
        - musl
        - uClibc
        - uClibc-ng

    - For VEE, a string of the JVM version:

        - Java 8: java8
        - Java 11: java11
        - Java 17: java17
        - Java 21: java21


- System Resources Required:

    - CPU usage in percent
    - RAM in KiB
    - Persistent Storage in KiB
    - Non-persistent Storage in KiB
    - Max threads/processes

- Off-Device Communication

    - Each application that performs off-device communication MUST specify the
      classes, destinations, and daily volume of that communication.
    - See :doc:`/api/networking` for details.
    - Daily volumes are specified in Byte units, and daily messages are in message units.

.. Note::

  Application messaging is provided through the API and does not require direct
  access to a network interface.

.. Note::

   Requests for IP socket communication in a vendor manifest are subject to
   operator approval in the deployment manifest. Operators may approve,
   narrow, replace, or deny requested destination classes, endpoints, ports,
   and volume limits according to deployment policy.

- External Dependencies

    - GEISA applications should be as self-contained as possible, with all
      necessary dependencies, except for the base libraries provided by the EE, 
      contained with the application artifacts.
    - GEISA does not provide a mechanism for loading arbitrary packages.  The
      external dependencies element in the manifest is used exclusively to
      indicate that one application depends on another.
    - Vendor-assigned Application ID of the application this application
      depends on.  

- Default Application Configuration

    - GEISA applications may need basic information to initialize such as the
      URL of a server, or settngs such as the frequency of reporting.  The
      default application configuration provides an initial set of values that
      can be used by the system operator when creating the operator manifest.  

.. Note :: 
  
  The system operator should be able to change the configuration information
  without needing to redeploy the application.

- Default Launch Strategy

    - Includes details such as whether the application should automatically be
      restarted if it fails, and how many failures with a given period of time
      constitues a permanent failure.

      - Auto restart (boolean)
      - Max failures -- number of failures within the restart period after
        which the application will not be restarted
      - Restart period -- elasped time, in minutes, before the failure count is
        reset.  The first failure starts the timer.  If the configured maximum
        number of failures occurs before the restart period is over, the 
        application is not restarted.  Otherwise, the failure count is reset.

- Vendor Signature

    - Base64 Encoded Signature of the compact JSON encoding of the vendor
      application manifest.

.. Note::

    ToDo: Add details on the signature mechanism.


Here is an example of an vendor application manifest:

.. include:: vendor-application-manifest-example.rst


Here is an example of a deployment application manifest:

.. include:: deployment-application-manifest-example.rst

