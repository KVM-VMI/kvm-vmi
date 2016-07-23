init:
	cd kvm && \
		make olddefconfig && \
		make prepare && \
		make scripts

modules:
	cd kvm && \
		make SUBDIRS=arch/x86/kvm modules

reload:
	sudo modprobe -r kvm_intel kvm irqbypass
	sudo modprobe irqbypass
	cd kvm && \
		sudo insmod arch/x86/kvm/kvm.ko
	cd kvm && \
		sudo insmod arch/x86/kvm/kvm-intel.ko
