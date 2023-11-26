
include $(TOPDIR)/rules.mk

LUCI_TITLE:=SetupWizard support for Fau2Dev mesh devices
LUCI_DEPENDS:=+luci-mod-admin-full
PKG_NAME:=luci-fau2ui-setupWizardTab
LUCI_PKGARCH:=all
PKG_VERSION:=1.0

define Package/$(PKG_NAME)
	$(call Package/luci/webtemplate)
	TITLE:=$(LUCI_TITLE)
	DEPENDS:=$(LUCI_DEPENDS)
endef

define Package/$(PKG_NAME)/postinst
#!/bin/sh
rm -rf /tmp/luci-indexcache
rm -rf /tmp/luci-modulecache/
exit 0
endef

include $(TOPDIR)/feeds/luci/luci.mk

$(eval $(call BuildPackage,$(PKG_NAME)))
