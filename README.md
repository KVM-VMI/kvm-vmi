<h1 align="center">
  <br>KVM-VMI</br>
</h1>

<h3 align="center">
KVM-based Virtual Machine Instrospection.
</h3>

<p align="center">
  <a href="https://kvm-vmi.slack.com">
    <img src="https://img.shields.io/badge/Slack-KVM--VMI-important" alt="Slack">
  </a>
  <img src="https://kvm-vmi.herokuapp.com/badge.svg" alt="Slack_Users">
  <a href="https://kvm-vmi.herokuapp.com">
    <img src="https://img.shields.io/badge/Slack-Join%20KVM--VMI-blue">
  <a>
  <a href="https://kvm-vmi.github.io/kvm-vmi/">
    <img src="https://img.shields.io/badge/-Documentation-green">
  <a>
</p> 

## Table of Contents

- [Overview](#overview)
- [Installation](#installation)
- [Presentations](#presentations)
- [References](#references)
- [Maintainers](#maintainers)
- [License](#license)

## Overview

This project adds virtual machine introspection to the KVM hypervisor.

_Virtual Machine Introspection_ is a technology that aims to understand the guest's execution context, solely based on the VM's hardware state, for various purposes:

- Debugging
- Malware Analysis
- Live-Memory Analysis
- OS Hardening
- Monitoring
- Fuzzing

See the [presentations](#presentations) section for more information.

This project is divided into 4 components:
- `kvm`: linux kernel with _vmi_ patches for KVM
- `qemu`: patched to allow introspection
- `nitro` (legacy): userland library which receives events, introspects the virtual
  machine state, and fills the semantic gap
- `libvmi`: virtual machine instrospection library with unified API
  across `Xen` and `KVM`

At the moment, 2 versions of VMI patches are available for `QEMU/KVM`
in this repository:

## Installation

Follow the [Setup guide](https://kvm-vmi.github.io/kvm-vmi/setup.html)

## Presentations

- [Bringing Commercial Grade Virtual Machine Introspection to KVM](https://www.linux-kvm.org/images/7/72/KVMForum2017_Introspection.pdf)
- [KVM Forum 2019: Advanced VMI on KVM - A Progress Report](https://static.sched.com/hosted_files/kvmforum2019/f6/Advanced%20VMI%20on%20KVM%3A%20A%20progress%20Report.pdf)
- [Hack.lu 2019: Leveraging KVM as a Debugging Platform](https://drive.google.com/file/d/1nFoCM62BWKSz2TKhNkrOjVwD8gP51VGK/view?usp=sharing)
- [Advanced VMI on KVM: A Progress Report](https://static.sched.com/hosted_files/kvmforum2019/f6/Advanced%20VMI%20on%20KVM%3A%20A%20progress%20Report.pdf)

## References

The legacy VMI system contained in this repo (_Nitro_) is based on `Jonas Pfoh`'s work:
- [Nitro: Hardware-based System Call Tracing for Virtual Machines](https://www.sec.in.tum.de/assets/staff/pfoh/PfohSchneider2011a.pdf)
- [Nitro - VMI Extensions for Linux/KVM](http://nitro.pfoh.net/)

## Maintainers

[@Wenzel](https://github.com/Wenzel)

## License

[GNU General Public License v3.0](https://github.com/KVM-VMI/kvm-vmi/blob/master/LICENSE)
