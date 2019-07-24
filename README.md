# kvm-vmi

[![Join the chat at https://gitter.im/kvm-vmi/Lobby](https://badges.gitter.im/trailofbits/algo.svg)](https://gitter.im/kvm-vmi/Lobby)
[![standard-readme compliant](https://img.shields.io/badge/readme%20style-standard-brightgreen.svg?style=flat-square)](https://github.com/RichardLitt/standard-readme)

[![Slack](https://maxcdn.icons8.com/Color/PNG/48/Mobile/slack-48.png)](https://kvm-vmi.slack.com)

> KVM-based Virtual Machine Instrospection.

## Table of Contents

- [Overview](#overview)
    - [1 - KVMI](#1---kvmi)
    - [2 - Nitro (Legacy)](#2---nitro-legacy)
- [Setup](#setup)
- [References](#references)
- [Maintainers](#maintainers)
- [Contributing](#contributing)
- [License](#license)

## Overview

This project adds virtual machine introspection to the KVM hypervisor
to monitor a running virtual machine without a guest agent.

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
- `libvmi`: `kvmi`

Note: the `nitro` is a legacy component and not part of `kvmi`.

### 2 - Nitro (_legacy_)

This version of KVM-VMI has been deprecated.

For details regarding how it works, see the [Wiki page](https://github.com/KVM-VMI/kvm-vmi/wiki/Nitro-details-(legacy))

## Setup

Configuration and install instructions are detailed on the following Wiki page:

[KVM-VMI setup](https://github.com/KVM-VMI/kvm-vmi/wiki/KVM-VMI-setup)

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
