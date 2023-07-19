# Copyright (c) 2014, AllSeen Alliance. All rights reserved.
#
#    Permission to use, copy, modify, and/or distribute this software for any
#    purpose with or without fee is hereby granted, provided that the above
#    copyright notice and this permission notice appear in all copies.
#
#    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
#    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
#    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
#    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
#    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
#    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
#    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=u-boot-at91
PKG_VERSION:=1.0.0
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

define Package/u-boot-at91
 SECTION:=Advantech
 CATEGORY:=Advantech software
 TITLE:=u-boot from AT91
 DEPENDS:=+librt +libc 
endef

define Package/u-boot-at91/description
	 advantech u-boot application 
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

export TARGET_CC

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) sam9x60ek_eki1000_defconfig 
	$(MAKE) -C $(PKG_BUILD_DIR) CROSS_COMPILE=$(TARGET_CROSS)
endef

define Build/Clean
	rm -rf $(PKG_BUILD_DIR)
endef

define Package/u-boot-at91/install
	$(INSTALL_DIR) $(BIN_DIR)/u-boot-at91
	$(CP) $(PKG_BUILD_DIR)/u-boot.bin $(BIN_DIR)/u-boot-at91/u-boot.bin
endef

$(eval $(call BuildPackage,u-boot-at91))
