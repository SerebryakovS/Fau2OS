#! /bin/bash

BOOTARGS=()
if [ -z "${STY}" ]; then
    echo "must be started inside a screen session" >&2
    exit 1
fi

SHARED_PATH="$(pwd)"
NUM_SESSIONS=3
BASE_IMG=openwrt-malta-le-root.qcow2
KERNEL_IMG=openwrt-malta-le-vmlinux.elf
BOOTARGS+=("-serial" "chardev:charconsole0")

for i in $(seq 1 "${NUM_SESSIONS}"); do
    if [ ! -e "/sys/class/net/tap${i}" ]; then
        echo "hub script must be started first to create tap$i interface" >&2
        exit 1
    fi
done

for i in $(seq 1 "${NUM_SESSIONS}"); do
    normalized_id="$(echo "$i"|awk '{ printf "%02d\n",$1 }')"
    twodigit_id="$(echo $i|awk '{ printf "%02X", $1 }')"

    qemu-img create -b "${BASE_IMG}" -f qcow2 -F qcow2 root.cow$i
    screen qemu-system-mipsel -M malta \
        -hda root.cow$i \
        -kernel "${KERNEL_IMG}" \
        -nographic \
        -append "root=/dev/sda console=ttyS0" \
        -nic tap,ifname=tap$i,script=no,downscript=no,model=virtio,mac=02:ba:de:af:fe:"${twodigit_id}" \
        -nic user,model=virtio,mac=06:ba:de:af:fe:"${twodigit_id}" \
	-chardev stdio,id=charconsole0,mux=on,signal=off \
    	-mon chardev=charconsole0,mode=readline \
        -gdb tcp:127.0.0.1:$((23000+$i)) \
        "${BOOTARGS[@]}"
    sleep 1
done
