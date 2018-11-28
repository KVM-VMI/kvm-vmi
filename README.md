# kvm-vmi

[![Join the chat at https://gitter.im/kvm-vmi/Lobby](https://badges.gitter.im/trailofbits/algo.svg)](https://gitter.im/kvm-vmi/Lobby)
[![standard-readme compliant](https://img.shields.io/badge/readme%20style-standard-brightgreen.svg?style=flat-square)](https://github.com/RichardLitt/standard-readme)

[![Slack](https://maxcdn.icons8.com/Color/PNG/48/Mobile/slack-48.png)](https://kvm-vmi.slack.com)

> KVM-based Virtual Machine Instrospection.

## Table of Contents

- [Overview](#overview)
- [Install](#install)
    - [Vagrant](#vagrant-recommended)
    - [Manually](#manually)
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
- `nitro`: userland library which receives events, introspects the virtual
  machine state, and fills the semantic gap
- `libvmi`: virtual machine instrospection library with unified API
  across `Xen` and `KVM`

At the moment, 2 versions of VMI patches are available for `QEMU/KVM`
in this repository:

### 1 - Nitro (_legacy_)

`KVM-VMI` started as an improved fork of [Nitro](http://nitro.pfoh.net/), a set of VMI patches
for `QEMU/KVM` to intercept system calls and rebuild the execution context.

`Nitro` is the name of the userland component that will receive and interpret the syscalls,
as well as the name of the set of patches for `QEMU/KVM`.

Corresponding submodule branches:
- `kvm`: `vmi`
- `qemu`: `vmi`
- `nitro`: `master`
- `libvmi`: `nitro`

(Sorry for the confusing branches naming...)

Details:

Once the traps are set, the VM will be in a "_paused_" state and go back to the
hypervisor on every system call.
In details, the traps are working directly at the instruction level, on `syscall`
and `sysret`, which means that you can also stop the VM when the system call
returns from the kernel.

When the VM is "_paused_", some introspection can be done by reading or writing
into the memory. Therefore it is possible to reconstruct VM state and understand
the system call `context` (process name, system call name).

Furthermore, we are able to decode the system call
parameters and display what file is being created (in the case of `NtCreateFile`,
for `Windows` only).

A hooking API allows you to define `callbacks` on top of the system calls you intercept:

[NtCreateFile](https://msdn.microsoft.com/en-us/library/bb432380.aspx)
~~~Python
def enter_NtCreateFile(syscall):
    DesiredAccess = syscall.args[1]
    object_attributes = syscall.args[2]
    obj = ObjectAttributes(object_attributes, syscall.process)
    buffer = obj.ObjectName.Buffer
    access = FileAccessMask(DesiredAccess)
    syscall.hook = {
        'object_name': buffer,
        'access': access.rights
    }
~~~

Resulting in this output:

~~~JSON
[
    {
        "event": {
            "cr3": "0x76f9e000",
            "vcpu": 0,
            "rax": "0x52",
            "direction": "enter",
            "type": "syscall"
        },
        "name": "NtCreateFile",
        "process": {
            "pid": 2344,
            "name": "powershell.exe"
        },
        "hook": {
            "object_name": "\\??\\C:\\Program Files\\Windows Sidebar\\Gadgets\\PicturePuzzle.Gadget\\en-US\\gadget.xml",
            "access": [
                "SYNCHRONIZE",
                "GENERIC_READ",
                "FILE_READ_ATTRIBUTES"
            ]
        }
    },
]
~~~


### 2 - KVMI

A complete set of VMI APIs proposed by [BitDefender](https://www.google.com/search?num=30&ei=fgH_W7mlKM39kwWpm7bQDQ&q=%22Guest+introspection%22+kvm+mailing+list&oq=%22Guest+introspection%22+kvm+mailing+list&gs_l=psy-ab.3...7670.8338..8580...0.0..0.187.187.0j1......0....1..gws-wiz.JoHSDKkCu_0)

This is where the current effort is focused on.

Corresponding submodule branches:
- `kvm`: `kvmi`
- `qemu`: `kvmi`
- `nitro`: `kvmi`
- `libvmi`: `kvmi`

## Install

### Vagrant (recommended)

Go to the `vagrant/` sub-directory to install a development environment for `kvm-vmi`

### Manually

Unfortunately, it is not possible to compile the KVM modules as an `out-of-tree`
build. You will have to compile and install a new kernel along with the new modules.

This is only valid for the `Nitro` set of patches:

- Start by compiling a new kernel in `kvm`
- Reboot
- Make sure you loaded the modified kernel module (`make reload`)
- Go to `nitro` to setup the userland component and intercept syscalls
- Compile the modified version of `qemu` if you intend to analyze syscall events


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