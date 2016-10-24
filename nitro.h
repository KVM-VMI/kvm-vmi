#ifndef NITRO_H_
#define NITRO_H_

#include <linux/ioctl.h>
#include <linux/kvm.h>
#include <linux/types.h>

#define NITRO_MAX_VCPUS 64

enum syscall_direction {
    ENTER,
    EXIT
};

enum syscall_type {
    SYSENTER,
    SYSCALL
};

struct event {
    bool present;
   enum syscall_direction direction;
   enum syscall_type type;
};

struct nitro_vcpus{
  int num_vcpus;
  int ids[NITRO_MAX_VCPUS];
  int fds[NITRO_MAX_VCPUS];
};

//events
#define KVM_NITRO_EVENT_ERROR			1
#define KVM_NITRO_EVENT_SYSCALL			2
#define KVM_NITRO_EVENT_SYSRET			3

//KVM functions
#define KVM_NITRO_NUM_VMS  	_IO(KVMIO, 0xE0)
#define KVM_NITRO_ATTACH_VM  	_IOW(KVMIO, 0xE1, pid_t)

//VM functions
#define KVM_NITRO_ATTACH_VCPUS	_IOR(KVMIO, 0xE2, struct nitro_vcpus)
#define KVM_NITRO_SET_SYSCALL_TRAP _IOW(KVMIO, 0xE3, bool)

//VCPU functions
#define KVM_NITRO_GET_EVENT	_IOR(KVMIO, 0xE5, struct event)
#define KVM_NITRO_CONTINUE	_IO(KVMIO, 0xE6)

#define KVM_NITRO_GET_REGS              _IOR(KVMIO,  0xE7, struct kvm_regs)
#define KVM_NITRO_SET_REGS              _IOW(KVMIO,  0xE8, struct kvm_regs)
#define KVM_NITRO_GET_SREGS             _IOR(KVMIO,  0xE9, struct kvm_sregs)
#define KVM_NITRO_SET_SREGS             _IOW(KVMIO,  0xEA, struct kvm_sregs)

#endif //NITRO_H_
