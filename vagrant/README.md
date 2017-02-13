# Vagrant

Here you will find a `Vagrantfile` to build a development environment for `kvm-vmi`.

# Requirements

- `vagrant`
- `vagrant-libvirt` plugin
- `ansible >= 2.2.1.0`

# Setup

Tune the Vagrantfile configuration to your needs.

Default config :
- `libvirt.memory = 4G` (at least `2G` is required)
- `libvirt.cpus = 2`

Update vagrant plugin to the latest version:
~~~
$ vagrant plugin update vagrant-libvirt
~~~

- Run `vagrant up --provider=libvirt`
- Once vagrant is done creating and provisioning the box, **reboot the box** (from libvirt) to
run the new kernel with the modified KVM modules, and run `vagrant ssh` to get a shell in the VM.
- Start the test vm with `virsh start nitro_win7x64` (or use `virt-manager` connection)
- go to `/data/kvm-vmi/nitro` and you can play with **Nitro** !

# Virt-manager

You can use `virt-manager` to view and manage VMs in the vagrant box.
SSH is open for password authentication.
Specify the `root` account with the password `vagrant`.

To have the graphical display working, you need to change the `Display Spice/VNC` configuration:
set `address` to `All interfaces`.

# Using NFS

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
