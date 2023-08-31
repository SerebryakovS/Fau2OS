include $(TOPDIR)/rules.mk

PKG_NAME:=sn3218
PKG_VERSION:=1.0
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/sn3218
	SECTION:=Extra packages
	TITLE:=sn3218-control
	DEPENDS:=+kmod-i2c-core
endef

define Package/helloworld/description
	Simple program to control sn3218 LED controller using i2c interface
endef

# Package build instructions; invoke the target-specific compiler to first compile the source file, and then to link the file into the final executable
define Build/Compile
	$(TARGET_CC) $(TARGET_CFLAGS) \
		$(PKG_BUILD_DIR)/sn3218.c \
		$(PKG_BUILD_DIR)/i2c.c \
		$(PKG_BUILD_DIR)/meshLedController.c -o \
		$(PKG_BUILD_DIR)/meshLedController
endef

# Package install instructions; create a directory inside the package to hold our executable, and then copy the executable we built previously into the folder
define Package/sn3218/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/meshLedController $(1)/usr/bin
endef

$(eval $(call BuildPackage,sn3218))

