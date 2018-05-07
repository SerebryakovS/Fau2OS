#
# Copyright (C) 2011 OpenWrt.org
#

PART_NAME=firmware

platform_check_image() {
	local board=$(board_name)
	local magic="$(get_magic_word "$1")"
	local magic_long="$(get_magic_long "$1")"

	[ "$#" -gt 1 ] && return 1

	case "$board" in
	"ubnt,unifi")
		[ "$magic" != "2705" ] && {
			echo "Invalid image type."
			return 1
		}

		return 0
		;;
	esac

	echo "Sysupgrade is not yet supported on $board."
	return 1
}

platform_do_upgrade() {
	local board=$(board_name)

	case "$board" in
	*)
		default_do_upgrade "$ARGV"
		;;
	esac
}
