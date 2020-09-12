# kvm-vmi

[![Slack](https://img.shields.io/badge/Slack-KVM--VMI-important)](https://kvm-vmi.slack.com)
![Slack_users](https://kvm-vmi.herokuapp.com/badge.svg)
[![Join](https://img.shields.io/badge/Slack-Join%20KVM--VMI-blue)](https://kvm-vmi.herokuapp.com)
[![badge_doc](https://img.shields.io/badge/-Documentation-green)](https://kvm-vmi.github.io/kvm-vmi/)

> KVM-based Virtual Machine Instrospection.

## Table of Contents

- [kvm-vmi](#kvm-vmi)
  - [Table of Contents](#table-of-contents)
  - [Overview](#overview)
    - [1 - KVMI](#1---kvmi)
    - [2 - Nitro (_legacy_)](#2---nitro-legacy)
  - [Installation](#installation)
  - [Presentations](#presentations)
  - [References](#references)
  - [Maintainers](#maintainers)
  - [Contributing](#contributing)
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

### 1 - KVMI

A complete set of VMI APIs proposed by [BitDefender](https://www.google.com/search?num=30&ei=fgH_W7mlKM39kwWpm7bQDQ&q=%22Guest+introspection%22+kvm+mailing+list&oq=%22Guest+introspection%22+kvm+mailing+list&gs_l=psy-ab.3...7670.8338..8580...0.0..0.187.187.0j1......0....1..gws-wiz.JoHSDKkCu_0)

This is where the current effort is focused on today.

[API overview](https://github.com/KVM-VMI/kvm/blob/528c2680bec46e9603126eec6506bc5da71d297b/tools/kvm/kvmi/include/kvmi/libkvmi.h)

~~~
git clone https://github.com/KVM-VMI/kvm-vmi.git --recursive --branch kvmi
~~~

Corresponding submodule branches:
- `kvm`: `kvmi`
- `qemu`: `kvmi`
- `nitro`: `kvmi`
- `libvmi`: `master`

Note: the `nitro` is a legacy component and not part of `kvmi`.

### 2 - Nitro (_legacy_)

This version of KVM-VMI has been deprecated.

For details regarding how it works, see the [Wiki page](https://github.com/KVM-VMI/kvm-vmi/wiki/Nitro-details-(legacy))

## Installation

Follow the [Setup guide](https://kvm-vmi.github.io/kvm-vmi/setup.html)

## Presentations

- [KVM Forum 2019: Advanced VMI on KVM - A Progress Report](https://static.sched.com/hosted_files/kvmforum2019/f6/Advanced%20VMI%20on%20KVM%3A%20A%20progress%20Report.pdf)
- [Hack.lu 2019: Leveraging KVM as a Debugging Platform](https://drive.google.com/file/d/1nFoCM62BWKSz2TKhNkrOjVwD8gP51VGK/view?usp=sharing)

## References

Based on `Jonas Pfoh`'s work:
- [Nitro: Hardware-based System Call Tracing for Virtual Machines](https://www.sec.in.tum.de/assets/staff/pfoh/PfohSchneider2011a.pdf)
- [Nitro - VMI Extensions for Linux/KVM](http://nitro.pfoh.net/)

## Maintainers

[@Wenzel](https://github.com/Wenzel)

## Contributing

PRs accepted.

Small note: If editing the Readme, please conform to the [standard-readme](https://github.com/RichardLitt/standard-readme) specification.

## License

[GNU General Public License v3.0](https://github.com/KVM-VMI/kvm-vmi/blob/master/LICENSE)
