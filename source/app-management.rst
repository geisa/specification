Application Management
----------------------

Application management is
the process of
deplying,
activating,
deactivating,
and decommissioning
applications in the GEISA EE.

Metadata
^^^^^^^^

GEISA's application management system
follows a model similar to
`Amazon IoT Greengrass <https://docs.aws.amazon.com/greengrass/v2/developerguide/what-is-iot-greengrass.html>`_
or
`Microsoft Azure IoT <https:learn.microsoft.com/en-us/azure/iot/iot-introduction>`_
in this applications have a
`recipe <https://docs.aws.amazon.com/greengrass/v2/developerguide/component-recipe-reference.html>`_,
`manifest <https://learn.microsoft.com/en-us/azure/iot-central/core/howto-manage-deployment-manifests-with-rest-api>`_,
or other set of meta-data
describing the
requirements
and
dependencies.

GEISA application meta-data shall include:

- Name
- Description
- Version
- Hash of the application image
    - The GEISA EE shall not activate an application unless the hash of the image matches the hash in the meta-data
- System Resources Required
- External Dependencies
    - GEISA applicaitons should be as self-contained as possible,

    with all necessary dependencies
    contained with the application artifacts
- Application Configuration
    - GEISA appliciations may need basic information to initialize
    
    such as the URL of a server.
    The system operator should be able to change the configuration
    information without needing to redeploy the application.
- Launch Strategy
    - Includes details such as whether the application should

    automatically be restarted if it fails,
    and how many failures with a given period of time constitues a permanent failure.

Here is an example of meta-data.

.. code-block:: json
    :linenos:

    {
      "geisa": {
        "com.example.HelloWorld": {
          "author": "Some Company",
          "version": "1.0.0",
          "arch" : "arm32",
          "clib" : "musl",
          "artifiacts": {
            "overlay" : "zip"
          }
        }
      },
      "geisa_sdk_version": "1.0.0"
    }


Application Artifacts
^^^^^^^^^^^^^^^^^^^^^

The GEISA Application artifacts includes all parts of the application
that are installed within the GEISA EE, including:

- Executables
- Libraries
- Configuration


Application Management Protocol
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. note:: 

    It is not clear this should be part of the GEISA 1.0 specification,
    especially given that a vendor/utility may already have protocols for app management.

    It may be useful ot make this an "after 1.0" GEISA release requirement,
    or a future GEISA Extension.

    The most immediate need is for GEISA apps to run on multiple platforms from multiple vendors/utilities,
    perhaps using deployment techniques that are already used by vendor/utilty.


GEISA needs to select a specific application management protocol to enable interoperability.
Give the scale of GEISA (millions of devices),
it is critical that the protocol be as lightweight as possible.

GEISA will use the
`OMA Specworks LWM2M <https://www.openmobilealliance.org/lwm2m/>`_
specification.

LWM2M originated with COAP,
and has been expanded to other protocols including
HTTP and MQTT.

