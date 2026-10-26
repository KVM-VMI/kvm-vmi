# Archived

## Nitro

`KVM-VMI` started as an improved fork of [Nitro](http://nitro.pfoh.net/), a set of VMI patches
for `QEMU/KVM` to intercept system calls and rebuild the execution context.

`Nitro` is the name of the userland component that will receive and interpret the syscalls,
as well as the name of the set of patches for `QEMU/KVM`.

A backup branch `nitro` is still available in the repo
~~~
git clone https://github.com/KVM-VMI/kvm-vmi.git --recursive --b nitro
~~~

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
