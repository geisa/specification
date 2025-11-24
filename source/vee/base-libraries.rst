
..
  Copyright 2025, Contributors to the Grid Edge Interoperability & Security Alliance (GEISA) a Series of LF Projects, LLC  
  This file is licensed under the Community Specification License 1.0 available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

Virtual Base Libraries
-----------------------------------

|geisa-vee-hdr|

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
