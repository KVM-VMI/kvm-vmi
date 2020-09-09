This Wiki page will help you setup KVM-VMI.

# Overview

To remove any ambiguity with the naming, you are going setup the `KVMi` (KVM introspection subsystem) version of KVM-VMI.

This repository contains 2 different/incompatible VMI patches for KVM:
- `Nitro`
- `KVMi`

KVM-VMI started with VMI patches from a project called [`Nitro`](https://www.sec.in.tum.de/assets/staff/pfoh/PfohSchneider2011a.pdf).

`Nitro` is not maintained anymore, and a new set of patches (with a completely different API) has been developed by BitDefender and proposed on the official KVM mailing list.
This new version is named `KVMi`.
The review and integration of the patches is still ongoing at this point.

Note: A submodule named `nitro` is still versioned in [KVM-VMI](https://github.com/KVM-VMI/kvm-vmi/tree/kvmi), but it is not used.

# Cloning the sources

First let's make sure that we have the repository, on the right branches.

If you **haven't** cloned `KVM-VMI` yet, use the following command:
~~~
$ git clone https://github.com/KVM-VMI/kvm-vmi.git --recursive --branch kvmi
~~~

If you have a already cloned the main repo, let's make sure everyone is one the `kvmi` branch

~~~
$ cd kvm-vmi
$ git checkout kvmi
$ git submodule update
~~~

This setup will help you configure 3 components:
- `KVM`
- `QEMU`
- `LibVMI`

# Setup Option 1: Vagrant - Virtual Machine based setup

[Vagrant](https://www.vagrantup.com/) is tool that helps create reproductible dev environment.
A Vagrant setup is available for KVM-VMI, and it will configure and install all the components
as well as a test virtual machine for you.

Go to `kvm-vmi/vagrant` and follow the instructions there.

Otherwise, keep reading

# Setup Option 2: Bare-metal setup

## KVM

You will have to compile and install an entire kernel.
It is not possible to compile the KVM modules using an "out-of-tree" build.

First we need to install the kernel build dependencies
~~~
$ sudo apt-get install bc fakeroot flex bison libelf-dev libssl-dev ncurses-dev
~~~

Let's configure the kernel
~~~
$ cd kvm-vmi/kvm
$ make olddefconfig
$ make menuconfig
~~~

Apply the following configuration:
~~~
CONFIG_KVM=m
CONFIG_KVM_INTEL=m
CONFIG_KVM_AMD=m
CONFIG_KSM=n
CONFIG_REMOTE_MAPPING=y
CONFIG_KVM_INTROSPECTION=y
~~~

Build and install the kernel
~~~
$ make -j4 bzImage
$ make -j4 modules
$ sudo make modules_install
$ sudo make install
~~~

Reboot.
Run `uname -a`
You should be on kernel `5.0.0-rc7` (`kvmi v6`)


## QEMU

Dependencies
~~~
$ sudo apt-get install libpixman-1-dev pkg-config zlib1g-dev libglib2.0-dev dh-autoreconf libspice-server-dev
~~~

Configure, build and install QEMU
~~~
$ cd kvm-vmi/qemu
$ ./configure --target-list=x86_64-softmmu --enable-spice --prefix=/usr/local
$ make -j4
$ sudo make install
~~~

Your modified QEMU has been installed at `/usr/local/bin/qemu-system-x86_64`

Remember this path.

## Preparing a domain

Choose a Virtual Machine to be inspected, import it in `libvirt`, and modify the XML configuration as the following.

~~~XML
<domain type='kvm' xmlns:qemu='http://libvirt.org/schemas/domain/qemu/1.0'>
    <qemu:commandline>
      <qemu:arg value='-chardev'/>
      <qemu:arg value='socket,path=/tmp/introspector,id=chardev0,reconnect=10'/>
      <qemu:arg value='-object'/>
      <qemu:arg value='secret,id=key0,data=some'/>
      <qemu:arg value='-object'/>
      <qemu:arg value='introspection,id=kvmi,chardev=chardev0,key=key0'/>
      <qemu:arg value='-accel'/>
      <qemu:arg value='kvm,introspection=kvmi'/>
  </qemu:commandline>
  ...
  <devices>
      <emulator>/usr/local/bin/qemu-system-x86_64</emulator>
~~~

Note that you need to **add** `xmlns:qemu='http://libvirt.org/schemas/domain/qemu/1.0'`.

Validate the new configuration and start the domain.

## libkvmi

[`libkvmi`](https://github.com/bitdefender/libkvmi) is a wrapper over the low-level KVMi API (ioctls)
You should use this library to build your applications.

~~~
$ git clone https://github.com/bitdefender/libkvmi --branch kvmi-v6
$ ./bootstrap
$ ./configure
$ make
$ sudo make install
~~~

## Libkvmi examples

Run the example provided by libkvmi: `hookguest-libkvmi`
~~~
$ cd libkvmi/examples
$ ./hookguest-libkvmi /tmp/introspector
~~~

Give it at least `10` seconds (waiting on QEMU to connect to the socket `/tmp/introspector`) and you should see some output ! :tada: 

## LibVMI

Dependencies
~~~
$ sudo apt-get install build-essential gcc libtool cmake pkg-config check libglib2.0-dev libvirt-dev flex bison libjson-c-dev
~~~

Build and install
~~~
$ cd kvm-vmi/libvmi
$ mkdir build
$ cd build
$ cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local -DENABLE_KVM=ON -DENABLE_XEN=OFF -DENABLE_BAREFLANK=OFF -DVMI_DEBUG='(VMI_DEBUG_KVM | VMI_DEBUG_DRIVER)'
$ make -j2
$ sudo make install
~~~

Go to [LibVMI](https://github.com/libvmi/libvmi) for the rest of the documentation.
