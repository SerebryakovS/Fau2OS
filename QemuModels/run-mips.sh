#! /bin/bash

# emulation for mt76x8, according to "MIPS System emulator" qemu-system-mips description it supports a range of MIPS CPUs, default is the 24Kf
# The MT7628 CPU core is 24KEc




if [ -z "${STY}" ]; then
    echo "must be started inside a screen session" >&2
    exit 1;
fi;
# to kill screen session:
# $ screen -ls
# $ screen -XS <session-id> quit

SHARED_PATH="$(pwd)"
if [ -z "$1" ]; then
    echo "[err]: Please, specify count of virtual nodes you want to run";
    exit 1;
fi;
NUM_SESSIONS=$1;

IMG_NAME=openwrt-malta-le-root
KERNEL_IMG=openwrt-malta-le-vmlinux.elf
BOOTARGS+=("-serial" "chardev:charconsole0")

./virtual-network.sh $NUM_SESSIONS
for i in $(seq 1 "${NUM_SESSIONS}"); do
    if [ ! -e "/sys/class/net/tap${i}" ]; then
        echo "hub script must be started first to create tap$i interface" >&2
        exit 1
    fi
done

for i in $(seq 1 "${NUM_SESSIONS}"); do
    normalized_id="$(echo "$i"|awk '{ printf "%02d\n",$1 }')"
    twodigit_id="$(echo $i|awk '{ printf "%02X", $1 }')"
    qemu-img convert -f raw -O qcow2 $IMG_NAME.ext4 $IMG_NAME.qcow2
    qemu-img create -b $IMG_NAME.qcow2 -f qcow2 -F qcow2 root.cow$i
    screen qemu-system-mipsel -M malta \
        -hda root.cow$i \
        -cpu 24KEc -m 512M \
        -kernel "${KERNEL_IMG}" \
        -nographic \
        -append "root=/dev/sda console=ttyS0" \
        -nic tap,ifname=tap$i,script=no,downscript=no,model=virtio,mac=02:ba:de:af:fe:"${twodigit_id}" \
        -nic user,model=virtio,mac=06:ba:de:af:fe:"${twodigit_id}" \
        -gdb tcp:127.0.0.1:$((23000+$i)) \
        -virtfs local,path=${SHARED_PATH},mount_tag=host,security_model=none \
        -chardev stdio,id=charconsole0,mux=on,signal=off -mon chardev=charconsole0,mode=readline \
        "${BOOTARGS[@]}"
    sleep 1
done
