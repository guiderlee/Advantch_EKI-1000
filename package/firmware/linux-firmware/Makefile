#
# Copyright (C) 2014 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=linux-firmware
PKG_VERSION:=20210511
PKG_RELEASE:=1

PKG_SOURCE_URL:=@KERNEL/linux/kernel/firmware
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.xz
PKG_HASH:=2aa6ae8b9808408f9811ac38f00c188e53e984a2b3990254f6c9c02c1ab13417

PKG_MAINTAINER:=Felix Fietkau <nbd@nbd.name>

SCAN_DEPS = *.mk

include $(INCLUDE_DIR)/package.mk

define Package/firmware-default
  SECTION:=firmware
  CATEGORY:=Firmware
  URL:=http://git.kernel.org/cgit/linux/kernel/git/firmware/linux-firmware.git
  TITLE:=$(1)
  DEPENDS:=$(2)
endef

define Build/Compile
	cp ./usbusb8997_combo_v4.bin $(PKG_BUILD_DIR)/mrvl/
	cp ./sdsd8997_combo_v4.bin $(PKG_BUILD_DIR)/mrvl/
endef

include $(wildcard ./*.mk)
#$(eval $(call BuildPackage,linux-firmware))
