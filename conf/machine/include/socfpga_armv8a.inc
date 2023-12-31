require conf/machine/include/arm/arch-armv8a.inc

KERNEL_PROVIDER ?= "linux-socfpga"
PREFERRED_PROVIDER_virtual/kernel ?= "${KERNEL_PROVIDER}"
KERNEL_IMAGETYPE ?= "Image"
MACHINE_EXTRA_RRECOMMENDS:append = " kernel-modules"

KBUILD_DEFCONFIG ?= "defconfig"

PREFERRED_PROVIDER_virtual/bootloader ?= "u-boot-socfpga"
PREFERRED_PROVIDER_u-boot ?= "u-boot-socfpga"

SPL_BINARY ?= "spl/u-boot-spl-dtb.hex"
UBOOT_SUFFIX ?= "img"
UBOOT_BINARY ?= "u-boot.img"
UBOOT_ELF ?= "u-boot"

# UBOOT_IMAGE = "u-boot-${MACHINE}-${PV}-${PR}.${UBOOT_SUFFIX}"

IMAGE_FSTYPES ?= "cpio ext3 tar.gz"
do_image_wic[depends] += "mtools-native:do_populate_sysroot dosfstools-native:do_populate_sysroot virtual/bootloader:do_deploy virtual/kernel:do_deploy"
