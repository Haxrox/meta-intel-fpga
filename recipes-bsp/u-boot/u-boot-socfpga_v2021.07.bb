require u-boot-socfpga-common.inc

DEPENDS:append:agilex += "arm-trusted-firmware bash"
DEPENDS:append:stratix10 += "arm-trusted-firmware bash"
DEPENDS:append:n5x += "arm-trusted-firmware bash"

COMPILE_PREPEND_FILES:stratix10 += " bl31.bin Image linux.dtb "
COMPILE_PREPEND_FILES:agilex += " bl31.bin Image linux.dtb "
COMPILE_PREPEND_FILES:n5x += " bl31.bin Image linux.dtb "
COMPILE_PREPEND_FILES:arria10 += " Image "

DEPLOY_APPEND_FILES:agilex += " kernel.itb "
DEPLOY_APPEND_FILES:stratix10 += " kernel.itb "
DEPLOY_APPEND_FILES:n5x += " kernel.itb "

LIC_FILES_CHKSUM = "file://Licenses/README;md5=5a7450c57ffe5ae63fd732446b988025"

UBOOT_VERSION = "v2021.07_RC"

SRCREV = "7340de195483ea7faa2c740150aa1058d2666731"
