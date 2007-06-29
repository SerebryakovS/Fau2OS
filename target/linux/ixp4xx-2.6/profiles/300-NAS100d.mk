#
# Copyright (C) 2006 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

define Profile/NAS100d
  NAME:=Iomega NAS 100d
  PACKAGES:=kmod-ixp4xx-npe kmod-pata-artop kmod-usb2
endef

define Profile/NAS100d/Description
	Package set optimized for the Iomega NAS 100d
endef
$(eval $(call Profile,NAS100d))

