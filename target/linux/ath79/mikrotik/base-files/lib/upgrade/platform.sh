# Copyright (C) 2011 OpenWrt.org

PART_NAME=firmware

REQUIRE_IMAGE_METADATA=1
platform_check_image() {
	return 0
}

RAMFS_COPY_BIN='fw_printenv fw_setenv nandwrite'
RAMFS_COPY_DATA='/etc/fw_env.config /var/lock/fw_printenv.lock'

platform_do_upgrade_mikrotik_nand() {
	CI_KERNPART=none
	local fw_mtd=$(find_mtd_part kernel)
	fw_mtd="${fw_mtd/block/}"
	[ -n "$fw_mtd" ] || return
	mtd erase kernel
	tar xf "$1" sysupgrade-routerboard/kernel -O | nandwrite -o "$fw_mtd" -

	nand_do_upgrade "$1"
}

platform_do_upgrade() {
	local board=$(board_name)

	case "$board" in
	mikrotik,routerboard-922uags-5hpacd)
		platform_do_upgrade_mikrotik_nand "$1"
		;;
	*)
		default_do_upgrade "$1"
		;;
	esac
}
