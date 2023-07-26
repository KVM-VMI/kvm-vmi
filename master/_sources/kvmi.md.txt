# KVMi subsystem for KVM

This page tracks the new versions of the `KVMi` subsystem for KVM.

## Description

The KVM introspection subsystem provides a facility for applications
running on the host or in a separate VM, to control the execution of
other VMs (pause, resume, shutdown), query the state of the vCPUs (GPRs,
MSRs etc.), alter the page access bits in the shadow page tables (only
for the hardware backed ones, eg. Intel's EPT) and receive notifications
when events of interest have taken place (shadow page table level faults,
key MSR writes, hypercalls etc.). Some notifications can be responded
to with an action (like preventing an MSR from being written), others
are mere informative (like breakpoint events which can be used for
execution tracing).  With few exceptions, all events are optional. An
application using this subsystem will explicitly register for them.

The use case that gave way for the creation of this subsystem is to
monitor the guest OS and as such the ABI/API is highly influenced by how
the guest software (kernel, applications) sees the world. For example,
some events provide information specific for the host CPU architecture
(eg. `MSR_IA32_SYSENTER_EIP`) merely because its leveraged by guest software
to implement a critical feature (fast system calls).

At the moment, the target audience for KVMI are security software authors
that wish to perform forensics on newly discovered threats (exploits)
or to implement another layer of security like preventing a large set
of kernel rootkits simply by "locking" the kernel image in the shadow
page tables (ie. enforce `.text` `r-x`, `.rodata` `rw-` etc.). It's the latter
case that made KVMI a separate subsystem, even though many of these
features are available in the device manager. The ability to build a
security application that does not interfere (in terms of performance)
with the guest software asks for a specialized interface that is designed
for minimum overhead.

## v1

- Publication: **16th June 2017**
- [Mailing list](https://www.spinics.net/lists/kvm/msg151508.html)

## v2

- Publication: **7th July 2017**
- [Mailing list](https://www.spinics.net/lists/kvm/msg152567.html)

**Changes since** `v1`

- add documentation and ABI [Paolo, Jan]
- drop all the other patches for now [Paolo]
- remove KVMI_GET_GUESTS, KVMI_EVENT_GUEST_ON, KVMI_EVENT_GUEST_OFF,
  and let libvirt/qemu handle this [Stefan, Paolo]
- change the license from LGPL to GPL [Jan]
- remove KVMI_READ_PHYSICAL and KVMI_WRITE_PHYSICAL (not used anymore)
- make the interface a little more consistent

## v3

- Publication: **11th September 2017**
- [Mailing list](https://lore.kernel.org/kvm/20170911153637.30326-1-alazar@bitdefender.com/)

**Changes since** `v2`:

- make small changes to the wire protocol (eg. use kvmi_error_code
  with every command reply, a few renames, etc.)
- removed '_x86' from x86 specific structure names. Architecture
  specific structures will have the same name.
- drop KVMI_GET_MTRR_TYPE and KVMI_GET_MTRRS (use KVMI_SET_REGISTERS)
- drop KVMI_EVENT_ACTION_SET_REGS (use KVMI_SET_REGISTERS)
- remove KVMI_MAP_PHYSICAL_PAGE_TO_GUEST and KVMI_UNMAP_PHYSICAL_PAGE_FROM_GUEST
  (to be replaced by a token+hypercall pair)
- extend KVMI_GET_VERSION with allowed commnd/event masks
- replace KVMI_PAUSE_GUEST/KVMI_UNPAUSE_GUEST with KVMI_PAUSE_VCPU
- replace KVMI_SHUTDOWN_GUEST with KVMI_EVENT_ACTION_CRASH
- replace KVMI_GET_XSAVE_INFO with KVMI_GET_CPUID
- merge KVMI_INJECT_PAGE_FAULT and KVMI_INJECT_BREAKPOINT
  in KVMI_INJECT_EXCEPTION
- replace event reply flags with ALLOW/SKIP/RETRY/CRASH actions
- make KVMI_SET_REGISTERS work with vCPU events only
- add EPT view support in KVMI_GET_PAGE_ACCESS/KVMI_SET_PAGE_ACCESS
- add support for multiple pages in KVMI_GET_PAGE_ACCESS/KVMI_SET_PAGE_ACCESS
- add (back) KVMI_READ_PHYSICAL/KVMI_WRITE_PHYSICAL
- add KVMI_CONTROL_VE
- add cstar to KVMI_EVENT
- add new events: KVMI_EVENT_VCPU_PAUSED, KVMI_EVENT_CREATE_VCPU, 
  KVMI_EVENT_DESCRIPTOR_ACCESS, KVMI_EVENT_SINGLESTEP
- add new sections: "Introspection capabilities", "Live migrations",
  "Guest snapshots with memory", "Memory access safety"
- document the hypercall used by the KVMI_EVENT_HYPERCALL command
  (was KVMI_EVENT_USER_CALL)

## v4

- Publication: **18th December 2017**
- [Mailing list](https://lore.kernel.org/kvm/20171218190642.7790-1-alazar@bitdefender.com/)

**Changes since** `v3`:

- move the accept/handshake worker to QEMU
- extend and use the 'page_track' infrastructure to intercept page
  accesses during emulation
- remove the 0x40000000-0x40001fff range from monitored MSR-s
- make small changes to the wire protocol (error codes, padding, names)
- simplify KVMI_PAUSE_VCPU
- add new commands: KVMI_GET_MAP_TOKEN, KVMI_GET_XSAVE
- add pat to KVMI_EVENT
- document KVM_HC_MEM_MAP and KVM_HC_MEM_UNMAP hypercalls

## v5

- Publication: **20th December 2018**
- [Mailing list](https://www.spinics.net/lists/kvm/msg179441.html)
- Kernel: `4.20.0-rc7`

**Changes since** `v4`:

- move the new and improved remote mapping code to the mm/ tree
- add two VM events (in addition to vCPU events) - KVMI_EVENT_CREATE_VCPU
      and KVMI_EVENT_UNHOOK - controlled by KVMI_CONTROL_VM_EVENTS
- add KVM_INTROSPECTION_UNHOOK ioctl to support suspend, snapshot
      and live migration
- use KVMI_PAUSE_ALL_VCPUS instead of KVMI_PAUSE_VCPU (temporarily)
- fix the reinjection of guest breakpoints
- add single-stepping
- extend KVMI_EVENT_PF to support single-stepping and to reduce
      the number of events on REP prefixed instructions
- allow the guest to update A/D bits when the page tables are tracked
      (write protected)
- extend page tracking to pass the gva in addition to gpa
- make small changes to the wire protocol (error codes, padding, names)
- extend struct kvm_introspection (ioctl KVM_INTROSPECTION) with the guest's uuid
- change the maximum message size to 4K (from 64K)
- fix more bugs

## v6

- Publication: **9th August 2019**
- [Patches on the mailing list](https://lore.kernel.org/kvm/20190809160047.8319-1-alazar@bitdefender.com/)
- Kernel: `5.0-rc7`

**Changes since** `v5`:

- small changes to the protocol, but enough to make it backward
incompatible with v5
- fix CR3 interception (thanks to Mathieu Tarral for reporting the issue)
- add SPP support (thanks to Weijiang Yang)
- add two more ioctls in order to let userspace/QEMU control
the commands/events allowed for introspection
- extend the breakpoint event with the instruction length
- complete the descriptor table registers interception
- add new instructions to the x86 emulator
- move arch dependent code to arch/x86/kvm/
- lots of fixes, especially on page tracking, single-stepping, exception
injection and remote memory mapping
- the guests are much more stable (on pair with our introspection
products using Xen)
- speed improvements (the penalty on web browsing actions is 50% lower,
at least)

## v7

- Publication: **7th February 2020**
- [Mailing list](https://lore.kernel.org/kvm/20200207181636.1065-1-alazar@bitdefender.com/)
- Kernel: `5.4.24`

**Changes since** `v6`:

- this is a subset of the previous version, as Sean and Paolo suggested,
  keeping "only" the basic introspection capabilities
- add a x86_64 test in tools/testing/selftests/kvm [Paolo]
- simplify the requests/replies handling [Paolo]
- add a new ioctl (PREHOOK) to notify the introspection tool to unhook
  [Paolo, Sean]
- add two new commands KVMI_VCPU_CONTROL_SINGLESTEP
  and KVMI_VCPU_TRANSLATE_GVA [Mathieu]
- restore the status of MSRs, CR3, descriptors access interception
  and prevent conflicts with userspace [Sean]
- other fixes for allmost all the issues pointed in the previous
  code review [Sean, Paolo]

## v8

- Publication: **30th March 2020**
- [Mailing list](https://lore.kernel.org/kvm/20200330101308.21702-1-alazar@bitdefender.com/)

**Changes since** `v7`:

- remove the RFC tag
- KVMI_EVENT_SINGLESTEP and KVMI_EVENT_TRAP doesn't have to
  be enabled. These events are sent after a specific command
  (KVMI_VCPU_CONTROL_SINGLESTEP/KVMI_VCPU_INJECT_EXCEPTION), as it is
  the case with KVMI_VCPU_PAUSE/KVMI_EVENT_PAUSE.
- add kvm_x86_ops.desc_ctrl_supported()
- fix the descriptor-table and MSR events on AMD
- drop KVMI_EVENT_REPLY (use KVMI_EVENT instead; as we do with the commands)
- other small changes (code refactoring, message validation, etc.).

## v9

- Publication: **22nd Jul 2020**
- [Mailing list](https://lore.kernel.org/kvm/20200721210922.7646-1-alazar@bitdefender.com/)
- Kernel: `5.8`

**Changes since** `v8`:

- rebase on 5.8
- fix non-x86 builds (avoid including the UAPI headers from kvmi_host.h)
- fix the clean-up for KVMI_VCPU_SINGLESTEP [Mathieu]
- extend KVMI_VM_SET_PAGE_ACCESS with the 'visible' option
- improve KVMI_VM_GET_MAX_GFN (skip read-only, invalid or non-user memslots)
- add KVMI_VM_CONTROL_CLEANUP [Tamas, Mathieu]
- add KVMI_VCPU_GET_XCR and KVMI_VCPU_SET_XSAVE (SSE emulation)
- move KVM_REQ_INTROSPECTION in the range of arch-independent requests
- better split of x86 vs arch-independent code
- cover more error codes with tools/testing/selftests/kvm/x86_64/kvmi_test.c
- remove more error messages and close the introspection connection
  when an error code can't be sent back or it doesn't make sense to send it
- other small changes (code refactoring, message validation, etc.).

## v10

- Publication: **25th November 2020**
- [Mailing list](https://lore.kernel.org/kvm/20201125093600.2766-1-alazar@bitdefender.com/)
- Kernel: `5.10`

**Changes since** `v9`:

- rebase on 5.10 from 5.8
- complete the split of x86 and arch-independent code
- split the VM and vCPU events
- clean up the interface headers (VM vs vCPU messages/events)
- clean up the tests
- add a new exit code (for the CRASH action) instead of killing
  the vCPU threads [Christoph]
- other small changes (code refactoring, message validation, etc.).

## v11

- Publication: **7th December 2020**
- [Mailing list](https://lore.kernel.org/kvm/20201207204622.15258-1-alazar@bitdefender.com/)
- Kernel: `5.10`

Changes since v10:

- fix the event reply validation
- fix the compile-time warnings reported by "kernel test robot <lkp@intel.com>"
- send the error code (KVM_ENOMEM) when the memory allocation fails
  while handling the KVMI_VCPU_GET_XSAVE command

## v12

- Publication: **6th October 2021**
- [Mailing list](https://lore.kernel.org/kvm/20211006173113.26445-1-alazar@bitdefender.com/)
- Kernel: `5.15`

Changes since v11:

- rebase to 5.15 (from 5.10)
- remove patches no longer needed
- remove kvm_get_max_gfn()/KVMI_VM_GET_MAX_GFN (a couple of tests are needed to see
  if it is better to send the memory size from QEMU, during handshake)

## Debugging

Enable CONFIG_DYNAMIC_DEBUG, CONFIG_FTRACE and CONFIG_FUNCTION_TRACER and rebuild the kernel.

Use the following commands to read the output of all `trace_kvmi_...()` functions:
```
mount -t tracefs nodev /sys/kernel/tracing
echo 'kvmi:*' > /sys/kernel/tracing/set_event
cat /sys/kernel/tracing/trace_pipe
```

Use the following commands to enable the output from `kvm_debug()` calls for specific files:
```
mount -t debugfs none /sys/kernel/debug
echo 8 > /proc/sys/kernel/printk
echo "file kvmi_msg.c +p" >> /sys/kernel/debug/dynamic_debug/control
echo "file kvmi.c +p" >> /sys/kernel/debug/dynamic_debug/control
```

## How to add new events/commands

Follow what Arash Eslami did for KVMI_EVENT_CPUID - https://github.com/KVM-VMI/kvm/pull/41/files

Read [the documention](https://github.com/KVM-VMI/kvm/blob/kvmi-v7/Documentation/virt/kvm/kvmi.rst) especially the [Events section](https://github.com/KVM-VMI/kvm/blob/kvmi-v7/Documentation/virt/kvm/kvmi.rst#events) if you add an event.

Find the proper place in the KVM system and place the function call (that will send the new event).
Write the implementation in `arch/x86/kvm/kvmi.c` and the event in `arch/x86/include/uapi/asm/kvmi.h` (if it is a x86 architecture specific event), otherwise in `virt/kvm/introspection/kvmi.c` and `include/uapi/linux/kvmi.h`.

Add the event to `KVMI_KNOWN_VCPU_EVENTS` or `KVMI_KNOWN_VM_EVENTS` macro.

Don't forget to update the documentation and to add a new test in `tools/testing/selftests/kvm/x86_64/kvmi_test.c`. Once you reboot with the new kernel, this will be the easiest way to test your changes.

```
make -C tools/testing/selftests/kvm TEST_GEN_PROGS_x86_64=x86_64/kvmi_test run_tests DEBUG=1
```

If you get a `madvise failed` error message, run the following command and rebuild `kvmi_test`
```
sed -i '/madvise failed/s/== 0,/== 0 \|\| errno == EINVAL,/' tools/testing/selftests/kvm/lib/kvm_util.c
```

For a new command, you must add the command handling function to `msg_vm[]` or `msg_vcpu[]` array,
the new id to `KVMI_KNOWN_COMMANDS` macro and the new structures to `arch/x86/include/uapi/asm/kvmi.h` or `include/uapi/linux/kvmi.h`. Don't forget the documentation and selftest.

Once you've tested the kernel side, add the event/command to userspace:
 - [libkvmi](https://github.com/bitdefender/libkvmi)
 - [libvmi](https://github.com/kvm-VMI/libvmi)
