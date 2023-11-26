#! /bin/sh

# The tap interfaces will be created with access rights for the current user.
# This allows the qemu instance to start up without being root.

USER="$(whoami)"
BRIDGE=br-qemu
NUM_SESSIONS=$1

sudo ip link add "${BRIDGE}" type bridge
for i in $(seq 1 "${NUM_SESSIONS}"); do
    sudo ip tuntap add dev tap$i mode tap user "$USER"
    sudo ip link set tap$i up
    sudo ip link set tap$i master "${BRIDGE}"
done

sudo ip link set "${BRIDGE}" up
sudo ip addr replace 192.168.251.1/24 dev "${BRIDGE}"
