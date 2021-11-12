HOMEPAGE = "http://www.denx.de/wiki/U-Boot/WebHome"
SECTION = "bootloaders"

DEPENDS += "coreutils-native bc-native bison-native dtc-native flex-native"
DEPENDS += "python3-setuptools-native swig-native u-boot-mkimage-native"
DEPENDS += "u-boot-tools virtual/kernel"

LICENSE = "GPLv2+"
LIC_FILES_CHKSUM ?= "file://Licenses/README;md5=30503fd321432fc713238f582193b78e"
PE = "1"

UBOOT_REPO ?= "git://github.com/altera-opensource/u-boot-socfpga.git"
UBOOT_PROT ?= "https"

UBOOT_VERSION_PREFIX ?= "socfpga_"
UBOOT_VERSION ?= "v2020.07"
UBOOT_BRANCH ?= "${UBOOT_VERSION_PREFIX}${UBOOT_VERSION}"

SRCREV ?= "${AUTOREV}"
PV:append = "+git${SRCPV}"

S = "${WORKDIR}/git"
B = "${WORKDIR}/build"

RPROVIDES:${PN} += "u-boot"

SRC_URI = "${UBOOT_REPO};protocol=${UBOOT_PROT};branch=${UBOOT_BRANCH}"

UBOOT_CONFIG[agilex-socdk] = "socfpga_agilex_defconfig"
UBOOT_CONFIG[agilex-socdk-atf] = "socfpga_agilex_atf_defconfig"
UBOOT_CONFIG[agilex-socdk-qspi] = "socfpga_agilex_qspi_defconfig"
UBOOT_CONFIG[agilex-socdk-qspi-atf] = "socfpga_agilex_qspi_atf_defconfig"
UBOOT_CONFIG[stratix10-socdk] = "socfpga_stratix10_defconfig"
UBOOT_CONFIG[stratix10-socdk-atf] = "socfpga_stratix10_atf_defconfig"
UBOOT_CONFIG[stratix10-socdk-qspi] = "socfpga_stratix10_qspi_defconfig"
UBOOT_CONFIG[stratix10-socdk-qspi-atf] = "socfpga_stratix10_qspi_atf_defconfig"
UBOOT_CONFIG[arria10-socdk] = "socfpga_arria10_defconfig"
UBOOT_CONFIG[arria10-socdk-nand] = "socfpga_arria10_nand_defconfig"
UBOOT_CONFIG[arria10-socdk-qspi] = "socfpga_arria10_qspi_defconfig"
UBOOT_CONFIG[cyclone5-socdk] = "socfpga_cyclone5_defconfig"
UBOOT_CONFIG[de0-nano-soc] = "socfpga_de0_nano_soc_defconfig"
UBOOT_CONFIG[de10-nano-soc] = "socfpga_de10_nano_defconfig"
UBOOT_CONFIG[mcvevk] = "socfpga_mcvevk_defconfig"
UBOOT_CONFIG[sockit] = "socfpga_sockit_defconfig"
UBOOT_CONFIG[socrates] = "socfpga_socrates_defconfig"
UBOOT_CONFIG[sr1500] = "socfpga_sr1500_defconfig"
UBOOT_CONFIG[arria5-socdk] = "socfpga_arria5_defconfig"
UBOOT_CONFIG[n5x-socdk-atf] = "socfpga_n5x_atf_defconfig"

do_compile:prepend() {
	if [ -n "${COMPILE_PREPEND_FILES}" ]; then
		if [ -n "${UBOOT_CONFIG}" ]; then
			for config in ${UBOOT_MACHINE}; do
				i=$(expr $i + 1);
				for type in ${UBOOT_CONFIG}; do
					j=$(expr $j + 1);
					if [ $j -eq $i ]; then
						for file in ${COMPILE_PREPEND_FILES}; do
							if [ "${file}" = "linux.dtb" ]; then
								cp ${DEPLOY_DIR_IMAGE}/socfpga_${MACHINE}_socdk.dtb ${B}/${config}/linux.dtb
								cp ${DEPLOY_DIR_IMAGE}/socfpga_${MACHINE}_socdk.dtb ${S}/linux.dtb
							elif [ "${file}" = "u-boot.txt" ]; then
								cp ${DEPLOY_DIR_IMAGE}/u-boot.txt ${B}/${config}/u-boot.txt
								cp ${DEPLOY_DIR_IMAGE}/u-boot.txt ${S}/u-boot.txt
							else
								cp ${DEPLOY_DIR_IMAGE}/${file} ${B}/${config}/${file}
								cp ${DEPLOY_DIR_IMAGE}/${file} ${S}/${file}
							fi
						done
					fi
				done
				unset j
			done
			unset i
		else
			for file in ${COMPILE_PREPEND_FILES}; do
				if [ "${file}" = "linux.dtb" ]; then
					cp ${DEPLOY_DIR_IMAGE}/socfpga_${MACHINE}_socdk.dtb ${B}/${config}/linux.dtb
					cp ${DEPLOY_DIR_IMAGE}/socfpga_${MACHINE}_socdk.dtb ${S}/linux.dtb
				elif [ "${file}" = "u-boot.txt" ]; then
					cp ${DEPLOY_DIR_IMAGE}/u-boot.txt ${B}/${config}/u-boot.txt
					cp ${DEPLOY_DIR_IMAGE}/u-boot.txt ${S}/u-boot.txt
				else
					cp ${DEPLOY_DIR_IMAGE}/${file} ${B}/${config}/${file}
					cp ${DEPLOY_DIR_IMAGE}/${file} ${S}/${file}
				fi
			done
		fi
	fi
}

do_install:append() {
	if [ "${MACHINE}" = "agilex" ] || [ "${MACHINE}" = "stratix10" ] || [ "${MACHINE}" = "n5x" ]; then
		if [ -n "${UBOOT_CONFIG}" ]; then
			for config in ${UBOOT_MACHINE}; do
				i=$(expr $i + 1);
				for type in ${UBOOT_CONFIG}; do
					j=$(expr $j + 1);
					if [ $j -eq $i ]; then
						cp ${B}/${config}/u-boot.itb ${B}/${config}/u-boot-${type}.itb
						install -D -m 644 ${B}/${config}/u-boot-${type}.itb ${D}/boot/u-boot-${type}-${PV}-${PR}.itb
						ln -sf u-boot-${type}-${PV}-${PR}.itb ${D}/boot/u-boot.itb-${type}
						ln -sf u-boot-${type}-${PV}-${PR}.itb ${D}/boot/u-boot.itb
						rm -rf  ${D}/boot/*.img*
					fi
				done
				unset j
			done
			unset i
		else
			cp ${B}/u-boot.itb ${B}/u-boot-${UBOOT_CONFIG}.itb
			install -D -m 644 ${B}/u-boot-${config}.itb ${D}/boot/u-boot-${UBOOT_CONFIG}-${PV}-${PR}.itb
			ln -sf u-boot-${UBOOT_CONFIG}-${PV}-${PR}.itb ${D}/boot/u-boot.itb-${UBOOT_CONFIG}
			ln -sf u-boot-${UBOOT_CONFIG}-${PV}-${PR}.itb ${D}/boot/u-boot.itb
			rm -rf  ${D}/boot/*.img*
		fi
	fi
}

do_deploy:append() {
	if [ -n "${DEPLOY_APPEND_FILES}" ]
	then
		if [ -n "${UBOOT_CONFIG}" ]
		then
			for config in ${UBOOT_MACHINE}; do
				i=$(expr $i + 1);
				for type in ${UBOOT_CONFIG}; do
					j=$(expr $j + 1);
					if [ $j -eq $i ]
					then
						for file in ${DEPLOY_APPEND_FILES}; do
							if [ "${MACHINE}" = "n5x" ]; then
								install -m 744 ${B}/${config}/${file} ${DEPLOYDIR}/${file}
							else
								:
							fi
						done
					fi
				done
				unset j
			done
			unset i
		else
			for file in ${DEPLOY_APPEND_FILES}; do
				if [ "${MACHINE}" = "n5x" ]; then
					install -m 744 ${B}/${config}/${file} ${DEPLOYDIR}/${file}
				else
					:
				fi
			done
		fi
	fi
}

require ${COREBASE}/meta/recipes-bsp/u-boot/u-boot.inc
