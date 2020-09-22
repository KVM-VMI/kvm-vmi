# Overview

`KVM-VMI` is a community aiming at providing **Virtual Machine Introspection** (*VMI*) support
to the KVM hypervisor.

_Virtual Machine Introspection_ is a technology that aims to understand the guest's execution context, solely based on the VM's hardware state, for various purposes:

- Debugging
- Malware Analysis
- Live-Memory Analysis
- OS Hardening
- Monitoring
- Fuzzing

## Repository structure

`KVM-VMI` repository consists of multiple components:

- `kvm`: Linux's *Kernel-Based Virtual Machine* kernel [git tree](https://www.linux-kvm.org/page/Code#kernel_git_tree), with *VMI* extensions
- `qemu`: [QEMU](https://github.com/qemu/qemu) emulator, with *VMI* extensions
- `libvmi`: fork of [LibVMI], the *Simplified Virtual Machine Introspection Library*, with an KVM driver integration based on `KVM-VMI`
- `vagrant`: a [Vagrant](https://www.vagrantup.com/) based development environment to easily setup `KVM-VMI`
