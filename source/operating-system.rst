Operating System
----------------

GEISA shall use Linux as the core operating system,
based,
in part,
due to the requirment for application isolation.

.. note::

    It is not clear that GEISA 1.0.0 should specify an exact kernel since
    existing vendors/utilities are using various versions of the
    Linux kernel.

    If the focus on GEISA is on the EE, one can argue that the EE
    should be isolated from a given version of the kernel.

GEISA will use a Linux 6.x kernel (exact version TBD).

The GEISA Linux kernel must minimize the attack surface and size.
This means removing all unnecessary components and extranous modules.

Whether the GEISA Linux kernel supports loadable kernel modules
or not is an implementation decision that is
invisible to a GEISA application.

There is no requirement for the underlying Linux kernel
to support real-time features,
and no real-time features are exposed to GEISA applications.

