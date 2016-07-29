# kvm-vmi

KVM-based Virtual Machine Instrospection.

# Description

This project add virtual machine introspection to the KVM hypervisor source code
to monitor a running virtual machine without a guest agent.
It allows you to trap and receive all syscalls generated during the execution.

This project is divided into 2 components:
- a modified version of the KVM source code.
- a userland component which receive and displays events.

# Setup

Unfortunately, it is not possible to compile the KVM modules as an `out-of-tree`
build. You will have to compile and install a new kernel along with the new modules.

# References

Based on the work of `Jonas Pfoh`:
- [Nitro: Hardware-based System Call Tracing for Virtual Machines](https://www.sec.in.tum.de/assets/staff/pfoh/PfohSchneider2011a.pdf)
- [Nitro - VMI Extensions for Linux/KVM](http://nitro.pfoh.net/)
