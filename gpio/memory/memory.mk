################################################################################
#
# memory
#
################################################################################

MEMORY_VERSION = 1.0
MEMORY_SITE = $(TOPDIR)/package/memory/memory_src_make
MEMORY_SITE_METHOD = local
MEMORY_DEPENDENCIES = libgpiod
define MEMORY_BUILD_CMDS
   $(MAKE) $(TARGET_CONFIGURE_OPTS) memory -C $(@D)
endef
define MEMORY_INSTALL_TARGET_CMDS 
   $(INSTALL) -D -m 0755 $(@D)/memory $(TARGET_DIR)/usr/bin 
endef
MEMORY_LICENSE = Proprietary


$(eval $(generic-package))
