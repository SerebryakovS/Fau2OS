#
# MT7628 Profiles
#

define Device/mt7628
  DTS := MT7628
  BLOCKSIZE := 64k
  IMAGE_SIZE := $(ralink_default_fw_size_4M)
  DEVICE_TITLE := MediaTek MT7628 EVB
  DEVICE_PACKAGES := kmod-usb2 kmod-usb-ohci kmod-usb-ledtrig-usbport
endef
TARGET_DEVICES += mt7628

define Device/miwifi-nano
  DTS := MIWIFI-NANO
  IMAGE_SIZE := $(ralink_default_fw_size_16M)
  DEVICE_TITLE := Xiaomi MiWiFi Nano
  DEVICE_PACKAGES := kmod-usb2 kmod-usb-ohci kmod-usb-ledtrig-usbport
endef
TARGET_DEVICES += miwifi-nano

define Device/vocore2
  DTS := VOCORE2
  IMAGE_SIZE := $(ralink_default_fw_size_16M)
  DEVICE_TITLE := VoCore VoCore2
  DEVICE_PACKAGES := kmod-usb2 kmod-usb-ohci kmod-usb-ledtrig-usbport \
    kmod-sdhci kmod-sdhci-mt7620
endef
TARGET_DEVICES += vocore2

define Device/wl-wn575a3
  DTS := WL-WN575A3
  IMAGE_SIZE := $(ralink_default_fw_size_8M)
  DEVICE_TITLE := Wavlink WL-WN575A3
endef
TARGET_DEVICES += wl-wn575a3

define Device/wrtnode2p
  DTS := WRTNODE2P
  IMAGE_SIZE := $(ralink_default_fw_size_16M)
  DEVICE_TITLE := WRTnode 2P
  DEVICE_PACKAGES := kmod-usb2 kmod-usb-ohci kmod-usb-ledtrig-usbport
endef
TARGET_DEVICES += wrtnode2p

define Device/duzun-dm06
  DTS := DUZUN-DM06
  DEVICE_TITLE := DuZun DM06
  DEVICE_PACKAGES := kmod-usb2 kmod-usb-ohci kmod-usb-ledtrig-usbport
endef
TARGET_DEVICES += duzun-dm06

define Device/mac1200r-v2
  DTS := MAC1200RV2
  DEVICE_TITLE := Mercury MAC1200R v2.0
endef
TARGET_DEVICES += mac1200r-v2

define Device/wcr-1166ds
  DTS := WCR-1166DS
  BUFFALO_TAG_PLATFORM := MTK
  BUFFALO_TAG_VERSION := 9.99
  BUFFALO_TAG_MINOR := 9.99
  IMAGES += factory.bin
  IMAGE/sysupgrade.bin := trx | pad-rootfs | append-metadata
  IMAGE/factory.bin := \
	trx -M 0x746f435c | pad-rootfs | append-metadata | \
	buffalo-enc WCR-1166DS $$(BUFFALO_TAG_VERSION) -l | \
	buffalo-tag-dhp WCR-1166DS JP JP | buffalo-enc-tag -l | \
	buffalo-dhp-image
  DEVICE_TITLE := Buffalo WCR-1166DS
endef
TARGET_DEVICES += wcr-1166ds
