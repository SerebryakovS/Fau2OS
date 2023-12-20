
include $(TOPDIR)/rules.mk

PKG_NAME:=fau2os-conf-and-tools-cuman-ac12x
PKG_VERSION=1.0

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
  TITLE:=Set of utilities and config files for managing fmesh system
  CATEGORY:=Fau2
  MAINTAINER:=Stepan Serebryakov <serebryakov0906@gmail.com>
#   DEPENDS:=+wpad-mesh-wolfssl +wpa-cli +bmx7 +bmx7-iwinfo +bmx7-json +bmx7-sms +bmx7-table +bmx7-tun +bmx7-uci-config +lime-proto-batadv +bmx7-auto-gw-mode +lime-proto-bmx7 +lime-proto-anygw +shared-state +shared-state-dnsmasq_hosts +shared-state-dnsmasq_leases +shared-state-bat_hosts +wifi-unstuck-wa

endef

define Build/Compile
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/
	$(CP) ./files/* $(1)/
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
