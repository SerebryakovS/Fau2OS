#!/bin/sh
insmod mtd-rw.ko i_want_a_brick=1
Filepath="old_factory"
dd if=/dev/mtd2 of=$Filepath
DefaultMAC=$( dd if=$Filepath bs=1 skip=$((0xe000)) count=6 | xxd -p );
RandomPart=$( dd if=/dev/urandom bs=1 count=3 | xxd -p );
NewMAC="${DefaultMAC::-6}$RandomPart"
echo "Rewriting $DefaultMAC --> $NewMAC"
echo -n "$NewMAC" | xxd -r -p | dd of=$Filepath bs=1 seek=$((0xe000)) conv=notrunc;
mtd -r write $Filepath factory
