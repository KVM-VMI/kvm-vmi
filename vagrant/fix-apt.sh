#!/usr/bin/env bash
set -e

cat > /etc/apt/sources.list <<'EOF'
deb http://archive.debian.org/debian bullseye main
deb http://archive.debian.org/debian bullseye-updates main
# deb http://security.debian.org/debian-security bullseye-security main
EOF

apt-get update 
apt-get install -y ansible

mkdir -p /etc/ansible
printf '[defaults]\nstdout_callback = yaml\n' > /etc/ansible/ansible.cfg
