
include $(TOPDIR)/rules.mk

PKG_NAME:=luci-app-fau2os-setup-wizard-prod
PKG_VERSION=1.0

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
  CATEGORY:=Fau2
  MAINTAINER:=Stepan Serebryakov <serebryakov0906@gmail.com>
  TITLE:=SetupWizard support for Fau2 mesh devices for production usage
  DEPENDS:= +luci-theme-fau2os-prod
endef

define Build/Compile
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/
	$(CP) ./files/* $(1)/
	$(CP) ./root/* $(1)/
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
