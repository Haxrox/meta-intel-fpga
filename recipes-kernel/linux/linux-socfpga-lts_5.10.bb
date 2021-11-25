LINUX_VERSION = "5.10.60"
LINUX_VERSION_SUFFIX = "-lts"

LIC_FILES_CHKSUM = "file://COPYING;md5=6bc538ed5bd9a7fc9398086aedcd7e46"

SRCREV = "c2a4f034454f5f2fb0a879a9a894ed49709297d3"

include linux-socfpga.inc

FILESEXTRAPATHS:prepend := "${THISDIR}/config:"

SRC_URI:append:n5x = " file://jffs2.scc file://gpio_sys.scc "
SRC_URI:append:agilex = " file://jffs2.scc file://gpio_sys.scc "
SRC_URI:append:stratix10 = " file://jffs2.scc file://gpio_sys.scc "
SRC_URI:append:arria10 = " file://lbdaf.scc file://jffs2.scc file://gpio_sys.scc "
SRC_URI:append:cyclone5 = " file://lbdaf.scc "
SRC_URI:append:arria5 = " file://lbdaf.scc "
