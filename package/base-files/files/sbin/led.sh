#!/bin/sh
# (C) 2008 openwrt.org

. /etc/functions.sh
ACTION=$1
NAME=$2
do_led() {
	local name
	local sysfs
	config_get name $1 name
	config_get sysfs $1 sysfs
	[ "$name" == "$NAME" -a -e "/sys/class/leds/${sysfs}" ] && {
		[ "$ACTION" == "set" ] &&
			echo 1 >/sys/class/leds/${sysfs}/brightness \
			|| echo 0 >/sys/class/leds/${sysfs}/brightness
		exit 0
	}
}

[ "$1" == "clear" -o "$1" == "set" ] &&
	[ -n "$2" ] &&{
		config_load system
		config_foreach do_led
		exit 1
	}
