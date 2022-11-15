DESCRIPTION = "Linux Kernel for Intel SoCFPGA"
LICENSE = "GPL-2.0-only"


KERNEL_REPO ?= "git://github.com/altera-opensource/linux-socfpga.git"
KERNEL_PROT ?= "https"

# Kernel CONFIG_LOCALVERSION
LINUX_VERSION_EXTENSION ?= "-altera"

# Build branch name
LINUX_VERSION_PREFIX ?= "socfpga-"
LINUX_VERSION_SUFFIX ?= ""
LINUX_VERSION ?= "4.0"

SRCREV ?= "${AUTOREV}"
SRCREV_machine ?= "${AUTOREV}"
PV = "${LINUX_VERSION}${LINUX_VERSION_SUFFIX}"
PV:append = "+git${SRCPV}"

KBRANCH ?= "${LINUX_VERSION_PREFIX}${LINUX_VERSION}${LINUX_VERSION_SUFFIX}"

SRC_URI = "${KERNEL_REPO};protocol=${KERNEL_PROT};branch=${KBRANCH}"

require recipes-kernel/linux/linux-yocto.inc

KBUILD_DEFCONFIG ?= "socfpga_defconfig"
KCONFIG_MODE ?= "--alldefconfig"

FILESEXTRAPATHS:prepend := "${THISDIR}/config:"

SRC_URI:append:agilex_fm61 = " file://jffs2.scc file://gpio_sys.scc "
SRC_URI:append:agilex_fm87 = " file://jffs2.scc file://gpio_sys.scc "
SRC_URI:append:agilex_fm86 = " file://jffs2.scc file://gpio_sys.scc "
SRC_URI:append:stratix10 = " file://jffs2.scc file://gpio_sys.scc "
SRC_URI:append:arria10 = " file://lbdaf.scc "
SRC_URI:append:cyclone5 = " file://lbdaf.scc "
SRC_URI:append:arria5 = " file://lbdaf.scc "
SRC_URI:append:n5x = " file://jffs2.scc file://gpio_sys.scc "