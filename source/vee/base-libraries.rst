
..
  Copyright 2025, Contributors to the Grid Edge Interoperability & Security Alliance (GEISA) a Series of LF Projects, LLC  
  This file is licensed under the Community Specification License 1.0 available at:
  https://github.com/geisa/specification/blob/main/LICENSE.md or
  https://github.com/CommunitySpecification/Community_Specification/blob/main/1._Community_Specification_License-v1.md

Virtual Base Libraries
----------------------

|geisa-vee-hdr|

GEISA  does  not specify which virtual runtime to use for the managed-code 
memory-safe languages.

For Java |reg|, a GEISA compliant VEE MUST support for the following class libraries:

 * java.io
 * java.lang
 * java.lang.annotation
 * java.lang.ref
 * java.lang.reflect
 * java.util
 * org.eclipse.paho.client.mqttv5
 * com.google.protobuf

Other libraries may be provided by platforms if desired.

For C and C++, a GEISA compliant VEE MUST provide support for standard libc C 
library with the exception of OS-specific or non-sandbox-friendly functions
such as ``fork()``/``exec()``, process control, signals. 

The following API MUST be supported:

* **FileSystem:** ``open``, ``fopen``, ``fdopendir``, ``close``, ``fclose``, 
  ``read``, ``write``, ``fread``, ``fwrite``, ``lseek``, ``stat``, ``fstat``, 
  ``readdir``, ``fstatat``, ``fileno``, ``fflush``, ``access``
* **Sockets:** ``send``, ``recv``, ``shutdown``, ``close``, ``socket``, 
  ``bind``, ``listen``, ``connect``
* **Clocks:** ``clock_getres``, ``clock_gettime``, ``gettimeofday``
* **Process:** ``exit``
* **StdIO:** ``printf``
* **Pthreads:** ``pthread_create``, ``pthread_join``, ``pthread_attr_init``, 
  ``pthread_attr_setstacksize``, ``pthread_attr_destroy``
* **Semaphores:** ``sem_wait``, ``sem_post``, ``sem_destroy``
* **C++ Standard Library**

.. note::
  
  While GEISA ADM |geisa-adm-baton| makes use of LWM2M for communication, GEISA
  Applications are unaware of this and do not require any LWM2M client
  libraries or knowledge.


|geisa-pyramid|
