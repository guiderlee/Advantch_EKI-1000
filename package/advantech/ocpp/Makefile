include $(TOPDIR)/rules.mk

PKG_NAME:=ocpp
PKG_VERSION:=1.6
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

define Package/ocpp
 SECTION:=Advantech
 CATEGORY:=Advantech software
 TITLE:=Advantech OCPP Application
 DEPENDS:=+librt +libc +lsqlite3
endef

define Package/ocpp/description
	advantech ocpp application
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

export TARGET_CC

define Build/Compile
	CFLAGS="$(TARGET_CPPFLAGS) $(TARGET_CFLAGS) -I$(PKG_BUILD_DIR)/include" LIBS="$(TARGET_LDFLAGS)" \
	$(MAKE) -C $(PKG_BUILD_DIR)
endef

define Build/Clean
	rm -rf $(PKG_BUILD_DIR)
endef

define Package/ocpp/install
	$(INSTALL_DIR) $(1)/usr/sbin
	chmod 744 $(PKG_BUILD_DIR)/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/ocpp1.6_WD $(1)/usr/sbin/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/config.json $(1)/usr/sbin/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/chargeingprofilem_v1.db $(1)/usr/sbin/
endef

$(eval $(call BuildPackage,ocpp))
