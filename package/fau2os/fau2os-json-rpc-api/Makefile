
include $(TOPDIR)/rules.mk

PKG_NAME:=fau2os-json-rpc-api
PKG_VERSION=1.0

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
  TITLE:=API for managing and monitoring Mesh network
  CATEGORY:=Fau2
  MAINTAINER:=Stepan Serebryakov <serebryakov0906@gmail.com>
  DEPENDS:=+luci-mod-rpc +uhttpd +uhttpd-mod-ubus +speedtest-netperf
endef

define Build/Compile
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/
	$(CP) ./files/* $(1)/
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
