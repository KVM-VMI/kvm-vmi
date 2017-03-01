# kvm-vmi

KVM-based Virtual Machine Instrospection.

# Description

This project add virtual machine introspection to the KVM hypervisor source code
to monitor a running virtual machine without a guest agent.
It allows you to trap and receive all syscalls generated during the execution.

This project is divided into 2 components:
- a modified version of the KVM source code.
- a userland component which receive and displays events.
- you need to compile `QEMU` only if you intend to use `libvmi` (see `nitro/`)

# Setup

## Using Vagrant (recommended)

Go to the `vagrant/` sub-directory to install a development environement for `kvm-vmi`

## Manually

Unfortunately, it is not possible to compile the KVM modules as an `out-of-tree`
build. You will have to compile and install a new kernel along with the new modules.

- Start by compiling a new kernel in `kvm`
- Reboot
- Make sure you loaded the modified kernel module (`make reload`)
- Go to `nitro` to setup the userland component and intercept syscalls
- Compile the modified version of `qemu` if you intend to analyze syscall events with `libvmi`


# References

Based on the work of `Jonas Pfoh`:
- [Nitro: Hardware-based System Call Tracing for Virtual Machines](https://www.sec.in.tum.de/assets/staff/pfoh/PfohSchneider2011a.pdf)
- [Nitro - VMI Extensions for Linux/KVM](http://nitro.pfoh.net/)
