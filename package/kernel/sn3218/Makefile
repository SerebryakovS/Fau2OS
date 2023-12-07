include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=sn3218
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define KernelPackage/sn3218
	SUBMENU:=Other modules
	TITLE:=SN3218 LED driver
	FILES:=$(PKG_BUILD_DIR)/sn3218.ko
	AUTOLOAD:=$(call AutoProbe,sn3218)
endef

define KernelPackage/sn3218/description
	This package contains the SN3218 LED driver for OpenWrt.
endef

EXTRA_KCONFIG:= \
	CONFIG_SN3218=m

EXTRA_CFLAGS:= \
	$(patsubst CONFIG_%, -DCONFIG_%=1, $(patsubst %=m,%,$(filter %=m,$(EXTRA_KCONFIG)))) \
	$(patsubst CONFIG_%, -DCONFIG_%=1, $(patsubst %=y,%,$(filter %=y,$(EXTRA_KCONFIG)))) \

MAKE_OPTS:= \
	$(KERNEL_MAKE_FLAGS) \
	SUBDIRS="$(PKG_BUILD_DIR)" \
	EXTRA_CFLAGS="$(EXTRA_CFLAGS)" \
	$(EXTRA_KCONFIG)

define Build/Compile
	$(MAKE) -C $(LINUX_DIR) $(MAKE_OPTS) M=$(PKG_BUILD_DIR) modules
endef

$(eval $(call KernelPackage,sn3218))
