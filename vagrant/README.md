<img src="https://media.licdn.com/mpr/mpr/AAEAAQAAAAAAAAdYAAAAJGMyOGY0NTA1LWFiOTAtNDE3Yi1iYWRkLTM0MjczNGQ3MzdhNA.png" align="right" width="30%" height="30%"/>

# Vagrant

Here you will find a `Vagrantfile` to build a development environment for `kvm-vmi`.

# Requirements

- `vagrant`
- `vagrant-libvirt` plugin
- `ansible >= 2.2.1.0`

# Setup

## Vagrantfile
Tune the Vagrantfile configuration to your needs.

Default hardware config:
- `libvirt.memory = 3G` (at least `2G` is required to run a nested VM)
- `libvirt.cpus = 2`
Other options:
- use `NFS` to mount `kvm-vmi` as a network shared folder (see below)

## Build the environment

- Run `vagrant up --provider=libvirt`
- Once vagrant is done provisioning the vm, run `vagrant reload` to reboot the box (to use the modified kernel)
- ssh into the box with `vagrant ssh`
- Start the test vm with `virsh start nitro_win7x64` (or use `virt-manager` connection)
- go to `/(data|vagrant)/kvm-vmi/nitro` and you can play with **Nitro** !


## Optional: use NFS

You can make use of Vagrant's `NFS` to mount the root of the repo in the vagrant box.
This gives you several advantages:
- the second partition where the kernel was cloned and compiled is not needed (30G)
- you can edit your files directly on your host, with your favorite IDE

You need to open you firewall for `NFS`. The following commands should make it work for a `Vagrant` box
to access your host `NFS` server:

~~~
firewall-cmd --permanent --add-service=nfs
firewall-cmd --permanent --add-service=rpc-bind
firewall-cmd --permanent --add-service=mountd
firewall-cmd --reload
~~~

To enable it, replace the value of `use_nfs` by `true` in the `Vagrantfile`:
~~~
use_nfs = true
~~~

# Produce Debian packages

You can produce debian packages for the modified linux kernel as well as
the modified `QEMU` by setting `gen_deb` to `true` in the `Vagrantfile`.
You have to use `NFS`.

# Virt-manager

You can use `virt-manager` to view and manage VMs in the vagrant box.
SSH is open for password authentication.
Specify the `root` account with the password `vagrant`.

To have the graphical display working, you need to change the `Display Spice/VNC` configuration:
set `address` to `All interfaces`.
