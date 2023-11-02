#!/bin/bash

function simple(){
	sudo qemu-system-mipsel -M malta -hda openwrt-malta-le-root.ext4 -kernel openwrt-malta-le-vmlinux.elf -nographic -append "root=/dev/sda console=ttyS0";
}
screen
./virtual-network.sh
./run.sh

