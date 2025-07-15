Virtual Execution Environment
-----------------------------------

|geisa-vee-hdr|

The GEISA Virtual Execution Environment definitions allows platforms
which support running applications in a virtual execution environment,
rather than a full operating system, to do so in an interoperable way.
VEEs are used on a variety of platforms.  Many rely on Java |reg| technology
or similar virtual runtime enviroments.

GEISA does not specify which virtual runtime is to be used; however, 
it does require that the VEE support the Java language specification version 7,
and that it provides support for the following class libraries:

 * java.io
 * java.lang
 * java.lang.annotation
 * java.lang.ref
 * java.lang.reflect
 * java.util
 * org.eclipse.paho.client.mqttv5

Other libraries may be provided by platforms if desired.

GEISA does not specify which language is used by VEE conformant applications,
though Java must be supported within the VEE.
Applications may include additional libraries as needed within their archive package.

.. note::
  
  The list of required class libraries needs to be updated based on input from
  working group members that are more familiar with VEE.


|geisa-pyramid|
