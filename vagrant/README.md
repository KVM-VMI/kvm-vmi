<img src="https://media.licdn.com/mpr/mpr/AAEAAQAAAAAAAAdYAAAAJGMyOGY0NTA1LWFiOTAtNDE3Yi1iYWRkLTM0MjczNGQ3MzdhNA.png" align="right" width="30%" height="30%"/>

# Vagrant

Here you will find a `Vagrantfile` to build a development environment for `kvm-vmi`.

# Requirements

- `vagrant`
- [`vagrant-libvirt`](https://github.com/vagrant-libvirt/vagrant-libvirt) plugin
  (Optional: required to use `KVM`)
- [`vagrant-vbguest`](https://github.com/dotless-de/vagrant-vbguest) plugin
  (Optional: required to use `VirtualBox`
- [`vagrant-reload`](https://github.com/aidanns/vagrant-reload) plugin
- `ansible >= 2.2.1.0`

# Setup

Example setup on Debian Buster
~~~
$ sudo apt-get install -y vagrant ruby-dev
$ vagrant plugin install vagrant-reload
~~~

## libvirt provider

~~~
$ vagrant plugin install vagrant-libvirt
~~~

## virtualbox provider

~~~
$ vagrant plugin install vagrant-vbguest
~~~

## Vagrantfile

Tune the Vagrantfile configuration to your needs.

## Build the environment

- Run `vagrant up --provider=libvirt` or `vagrant up --provider=virtualbox`
- Once the provisioning via `Ansible` is done, ssh into the box with `vagrant ssh`


# Troubleshooting

## NFS

You need to open your firewall for `NFS`. The following commands should make it work for a `Vagrant` box
to access your host `NFS` server:

~~~
firewall-cmd --permanent --add-service=nfs
firewall-cmd --permanent --add-service=rpc-bind
firewall-cmd --permanent --add-service=mountd
firewall-cmd --reload
~~~

# Note: Virt-manager

You can use `virt-manager` to view and manage VMs in the vagrant box.

SSH is open for password authentication.
- username: `root`
- password: `vagrant`

To have the graphical display working, you need to change the follwing setting:

`Display Spice/VNC` `->` `Address` `->` `All interfaces`.
