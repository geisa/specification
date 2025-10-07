
Application Manifests
_____________________

GEISA's application management system follows a model similar to `Amazon IoT
Greengrass <https://docs.aws.amazon.com/greengrass/v2/developerguide/what-is-iot-greengrass.html>`_
or `Microsoft Azure IoT <https:learn.microsoft.com/en-us/azure/iot/iot-introduction>`_ in that
applications have a `recipe
<https://docs.aws.amazon.com/greengrass/v2/developerguide/component-recipe-reference.html>`_,
`manifest <https://learn.microsoft.com/en-us/azure/iot-central/core/howto-manage-deployment-manifests-with-rest-api>`_,
or other set of metadata describing the requirements and dependencies.

GEISA handled application meta-data through by defining two manifests for each
application: a vendor manifest and an operator manifest.  

The vendor application manifest provides information about the application to
the operator and the edge management system, including any external
dependencies and minimum resouce requirements.  The vendor manifest is used by
a GEISA ADM conformant edge management system to inform the operator about the
application and to facilitate the secure import of the application.  

The operator application manifest provides information to the execution
environment as to what resources the system operator has allocated to the
application.

GEISA vendor and operator application manifests SHALL include:

- Vendor assigned Application ID

    - Vendor assigned application IDs use
      `https://en.wikipedia.org/wiki/Reverse_domain_name_notation Reverse DNS
      Name Notation`, similar to Java packages
    - GEISA recommends ``tld.companyname.geisa.appname`` for application IDs,
      for example, ``org.lfenergy.geisa.waveformanalyzer``.

- Name of the application
- Description of the application
- Version Number of the application
- Hash of the application image

    - The GEISA EE shall not activate an application unless the hash of the image matches the hash in the meta-data

GEISA vendor manifests SHALL include:

- Compatibility:

    - GEISA API Minimum Version
    - GEISA LEE Minimum Version (null for unsupported)
    - GEISA VEE Minimum Version (null for unsupported)
    - Waveform Access (boolean)

- System Resources Required:

    - CPU usage in percent
    - RAM in MiB
    - Persistent Storage in MiB
    - Non-persistent Storage in MiB
    - Max threads/processes

- Off-Device Communication

    - Each application that performs off-device communication MUST specify the
      classes, destinations, and daily volume of that communication.
    - See :doc:`/api/networking` for details.
    - Daily volumes are specified in KiB units, and daily messages are in message units.

.. Note::

  Application messaging is provided through the API and does not require direct
  access to a network interface.

- External Dependencies

    - GEISA applications should be as self-contained as possible, with all
      necessary dependencies contained with the application artifacts
    - GEISA does not provide a mechanism for loading arbitrary packages.  The
      external dependencies element in the manifest is used exclusively to
      indicate that one application depends on another.
    - Vendor assigned Application ID of the application this application
      depends on.

- Default Application Configuration

    - GEISA applications may need basic information to initialize such as the
      URL of a server, or settngs such as the frequency of reportng.  The
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


Here is an example of an vendor application manifest.

.. code-block:: json
  :linenos:

  {
    "geisa-vendor-app-manifest": {
      "org.lfenergy.geisa.HelloWorld": {
        "author": "Some Company",
        "name": "Hello World Application",
        "description": "Killer application that writes 'hello world' to the log",
        "version": "1.0.0",
        "artifacts": {
          "image-size": 748340,
          "uncompressed-size": 2494464,
          "image": "helloworld-1.tgz",
          "sha256": "00beeaeeca59f9177d88a13132f7c0686616fe728d85f20ddbd15352abd10988"
        },
        "compatibility": {
          "GEISA-API": "1.0.0",
          "GEISA-LEE": "1.0.0",
          "GEISA-VEE": null
        },
        "resources": {
          "app-cpu": 30,
          "app-ram": 40,
          "storage-persist": 20,
          "storage-nonpersist": 5,
          "threads": 50,
          "AMI": false,
          "HAN": true,
          "waveform": true
        },
        "communication": {
          "message": {
            "daily-messages": 30
          },
          "operator": {
            "daily-volume": 2048,
            "outbound": [
              "tcp:[3fff:421:32::/48]:443",
              "udp:[3fff:421:2:661::/64]:4242",
              "tcp:198.51.100.0/24:999"
            ]
          },
          "internet": {
            "daily-volume": 51200,
            "outbound": [
              "tcp:[2001:db8:44:12::/64]:443",
              "udp:203.0.113.66:2256"
            ]
          }
        },
        "external-dependencies": [
          null
        ],
        "default-configuration": {
          "knob": 36,
          "setting": "blue",
          "turbo encabulator active": true
        },
        "default-launch-strategy": {
          "auto-restart": true,
          "max restarts": 5,
          "restart period": 60
        }
      }
    }
  }
