Package/r8169-firmware = $(call Package/firmware-default,RealTek RTL8169 firmware)
define Package/r8169-firmware/install
	$(INSTALL_DIR) $(1)/lib/firmware/rtl_nic
	$(CP) \
		$(PKG_BUILD_DIR)/rtl_nic/* \
		$(1)/lib/firmware/rtl_nic
endef
$(eval $(call BuildPackage,r8169-firmware))

Package/rtl8188eu-firmware = $(call Package/firmware-default,RealTek RTL8188EU firmware)
define Package/rtl8188eu-firmware/install
	$(INSTALL_DIR) $(1)/lib/firmware/rtlwifi
	$(CP) \
		$(PKG_BUILD_DIR)/rtlwifi/rtl8188eufw.bin \
		$(1)/lib/firmware/rtlwifi
endef
$(eval $(call BuildPackage,rtl8188eu-firmware))

Package/rtl8192ce-firmware = $(call Package/firmware-default,RealTek RTL8192CE firmware)
define Package/rtl8192ce-firmware/install
	$(INSTALL_DIR) $(1)/lib/firmware/rtlwifi
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/rtlwifi/rtl8192cfw.bin $(1)/lib/firmware/rtlwifi
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/rtlwifi/rtl8192cfwU.bin $(1)/lib/firmware/rtlwifi
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/rtlwifi/rtl8192cfwU_B.bin $(1)/lib/firmware/rtlwifi
endef
$(eval $(call BuildPackage,rtl8192ce-firmware))

Package/rtl8192cu-firmware = $(call Package/firmware-default,RealTek RTL8192CU firmware)
define Package/rtl8192cu-firmware/install
	$(INSTALL_DIR) $(1)/lib/firmware/rtlwifi
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/rtlwifi/rtl8192cufw.bin $(1)/lib/firmware/rtlwifi
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/rtlwifi/rtl8192cufw_A.bin $(1)/lib/firmware/rtlwifi
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/rtlwifi/rtl8192cufw_B.bin $(1)/lib/firmware/rtlwifi
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/rtlwifi/rtl8192cufw_TMSC.bin $(1)/lib/firmware/rtlwifi
endef
$(eval $(call BuildPackage,rtl8192cu-firmware))

Package/rtl8192de-firmware = $(call Package/firmware-default,RealTek RTL8192DE firmware)
define Package/rtl8192de-firmware/install
	$(INSTALL_DIR) $(1)/lib/firmware/rtlwifi
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/rtlwifi/rtl8192defw.bin $(1)/lib/firmware/rtlwifi
endef
$(eval $(call BuildPackage,rtl8192de-firmware))

Package/rtl8192eu-firmware = $(call Package/firmware-default,RealTek RTL8192EU firmware)
define Package/rtl8192eu-firmware/install
	$(INSTALL_DIR) $(1)/lib/firmware/rtlwifi
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/rtlwifi/rtl8192eu_nic.bin $(1)/lib/firmware/rtlwifi
endef
$(eval $(call BuildPackage,rtl8192eu-firmware))

Package/rtl8192se-firmware = $(call Package/firmware-default,RealTek RTL8192SE firmware)
define Package/rtl8192se-firmware/install
	$(INSTALL_DIR) $(1)/lib/firmware/rtlwifi
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/rtlwifi/rtl8192sefw.bin $(1)/lib/firmware/rtlwifi
endef
$(eval $(call BuildPackage,rtl8192se-firmware))

Package/rtl8192su-firmware = $(call Package/firmware-default,RealTek RTL8192SU firmware)
define Package/rtl8192su-firmware/install
	$(INSTALL_DIR) $(1)/lib/firmware/rtlwifi
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/rtlwifi/rtl8712u.bin $(1)/lib/firmware/rtlwifi
endef
$(eval $(call BuildPackage,rtl8192su-firmware))

Package/rtl8723au-firmware = $(call Package/firmware-default,RealTek RTL8723AU firmware)
define Package/rtl8723au-firmware/install
	$(INSTALL_DIR) $(1)/lib/firmware/rtlwifi
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/rtlwifi/rtl8723aufw_A.bin $(1)/lib/firmware/rtlwifi
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/rtlwifi/rtl8723aufw_B.bin $(1)/lib/firmware/rtlwifi
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/rtlwifi/rtl8723aufw_B_NoBT.bin $(1)/lib/firmware/rtlwifi
endef
$(eval $(call BuildPackage,rtl8723au-firmware))

Package/rtl8723bu-firmware = $(call Package/firmware-default,RealTek RTL8723BU firmware)
define Package/rtl8723bu-firmware/install
	$(INSTALL_DIR) $(1)/lib/firmware/rtlwifi
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/rtlwifi/rtl8723bu_nic.bin $(1)/lib/firmware/rtlwifi
endef
$(eval $(call BuildPackage,rtl8723bu-firmware))

Package/rtl8821ae-firmware = $(call Package/firmware-default,RealTek RTL8821AE firmware)
define Package/rtl8821ae-firmware/install
	$(INSTALL_DIR) $(1)/lib/firmware/rtlwifi
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/rtlwifi/rtl8821aefw.bin $(1)/lib/firmware/rtlwifi
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/rtlwifi/rtl8821aefw_wowlan.bin $(1)/lib/firmware/rtlwifi
endef
$(eval $(call BuildPackage,rtl8821ae-firmware))
