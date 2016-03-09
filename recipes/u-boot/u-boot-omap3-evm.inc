# Using relative path here causes bitbake to search in
# BBPATH for the first instance of u-boot.inc rather
# than just within the current directory.
# require recipes/u-boot/u-boot.inc

DESCRIPTION = "U-Boot - the Universal Boot Loader"
HOMEPAGE = "http://www.denx.de/wiki/U-Boot/WebHome"
SECTION = "bootloaders"
PRIORITY = "optional"
LICENSE = "GPLv2"
PROVIDES = "virtual/bootloader"

DEPENDS = "mtd-utils"


PACKAGE_ARCH = "${MACHINE_ARCH}"

EXTRA_OEMAKE  = "CROSS_COMPILE=${TARGET_PREFIX}"
EXTRA_OEMAKE += "ARCH=${TARGET_ARCH}"

COMPATIBLE_MACHINE = "dm814x-evm"

#AM: 
# "unset LDFLAGS" under do_compile by some reasons is not working, so
# disable local variable
export LDFLAGS=""

SRC_URI = "git://${GITSERVER}/bsp/u-boot-omap3.git;protocol=git;branch=${BRANCH} \
           file://boot.cmd           \
           file://default.cmd        \
           file://mkscr.sh           \
           file://fw_env.config      \ 
           file://update.cmd         \
"

BRANCH = "branch.v2010.06_TI81XXPSP_04.04.00.01"
SRCREV = "v2010.06_PD_${PV}"

S = "${WORKDIR}/git"


UBOOT_MACHINE ?= "${MACHINE}_config"
UBOOT_BINARY ?= "u-boot.bin"
UBOOT_IMAGE ?= "u-boot-${MACHINE}-${PV}-${PR}.bin"
UBOOT_SYMLINK ?= "u-boot-${MACHINE}.bin"
UBOOT_MAKE_TARGET ?= "all"

UBOOT_DEPLOY_DIR ?= "${DEPLOY_DIR_IMAGE}/u-boot-${PV}"
UBOOT_SCRIPTS_DIR ?= "${WORKDIR}"

UBOOT_MACHINE = "ti8148_evm_config"

UBOOT_NAND_CONFIG = "ti8148_evm_config_nand"
UBOOT_MIN_UART_CONFIG = "ti8148_evm_min_uart"
UBOOT_MIN_NAND_CONFIG = "ti8148_evm_min_nand"
UBOOT_MIN_SD_CONFIG = "ti8148_evm_min_sd"

UBOOT_NAND_BINARY = "u-boot.nand.bin"
UBOOT_SD_BINARY = "u-boot.sd.bin"

UBOOT_MIN_UART_BINARY = "u-boot.min.uart"
UBOOT_MIN_NAND_BINARY = "u-boot.min.nand"
UBOOT_MIN_SD_BINARY = "u-boot.min.sd"

UBOOT_NAND_IMAGE  = "u-boot.nand.bin-${MACHINE}-${PV}-${PR}"
UBOOT_SD_IMAGE  = "u-boot.sd.bin-${MACHINE}-${PV}-${PR}"

UBOOT_MIN_UART_IMAGE = "u-boot.min.uart-${MACHINE}-${PV}-${PR}"
UBOOT_MIN_NAND_IMAGE = "u-boot.min.nand-${MACHINE}-${PV}-${PR}"
UBOOT_MIN_SD_IMAGE = "u-boot.min.sd-${MACHINE}-${PV}-${PR}"

UBOOT_NAND_SYMLINK = "u-boot.nand.bin"
UBOOT_SD_SYMLINK = "u-boot.sd.bin"

UBOOT_MIN_UART_SYMLINK = "u-boot.min.uart"
UBOOT_MIN_NAND_SYMLINK = "u-boot.min.nand"
UBOOT_MIN_SD_SYMLINK = "u-boot.min.sd"

UBOOT_MAKE_TARGET = "u-boot.ti" 

TFTP_PATH = "${BUILD_PURPOSE}/${PRODUCT}.${PRODUCT_RELEASE}/${RELDIR}/${MACHINE}/img"
NFS_PATH  = "/opt/exports/${BUILD_PURPOSE}/${PRODUCT}.${PRODUCT_RELEASE}/${RELDIR}/${MACHINE}/nfs"
     
    
do_configure () {
    oe_runmake distclean 
}

do_compile () {
    unset LDFLAGS
    unset CFLAGS
    unset CPPFLAGS
        
    #Build u-boot-min-uart
    oe_runmake clean 
    oe_runmake TFTP_PATH=${TFTP_PATH} ${UBOOT_MIN_UART_CONFIG} 
    oe_runmake ${UBOOT_MAKE_TARGET}
        
    #Build u-boot-min-nand
    oe_runmake clean 
    oe_runmake TFTP_PATH=${TFTP_PATH} ${UBOOT_MIN_NAND_CONFIG}
    oe_runmake ${UBOOT_MAKE_TARGET}
    
    #Build u-boot-min-sd
    oe_runmake clean 
    oe_runmake TFTP_PATH=${TFTP_PATH} ${UBOOT_MIN_SD_CONFIG}
    oe_runmake ${UBOOT_MAKE_TARGET}
    
    #Build u-boot.nand.bin 
    oe_runmake clean
    oe_runmake TFTP_PATH=${TFTP_PATH} ${UBOOT_NAND_CONFIG}
    oe_runmake ${UBOOT_MAKE_TARGET}
    cp u-boot.bin ${UBOOT_NAND_BINARY}
    
    #Build u-boot.sd.bin
    oe_runmake clean
    oe_runmake TFTP_PATH=${TFTP_PATH} ${UBOOT_SD_CONFIG}
    oe_runmake ${UBOOT_MAKE_TARGET}
    cp u-boot.bin ${UBOOT_SD_BINARY}
    
    #Build mkimage for the target platform
    oe_runmake tools clean
    oe_runmake HOSTCC="${TARGET_PREFIX}gcc" HOSTSTRIP="${TARGET_PREFIX}strip" tools
    cp tools/mkimage tools/mkimage-${TARGET_ARCH}
    
    #Build u-boot host tools
    oe_runmake tools clean
    oe_runmake tools env HOSTCC="${CC}" HOSTSTRIP="${STRIP}" 
}

do_install () {
    install -d ${D}/boot
    install -d ${D}/boot/img
    install -d ${D}${base_sbindir}
    install -d ${D}${sysconfdir}/init.d
    install -d ${D}${sysconfdir}/rc5.d
        
    install ${S}/tools/mkimage-${TARGET_ARCH} ${D}${base_sbindir}/mkimage
    
    install ${S}/${UBOOT_NAND_BINARY} ${D}/boot/img/${UBOOT_NAND_IMAGE}
    ln -sf ${UBOOT_NAND_IMAGE} ${D}/boot/img/${UBOOT_NAND_BINARY}
    
    install ${S}/${UBOOT_SD_BINARY} ${D}/boot/img/${UBOOT_SD_IMAGE}
    ln -sf ${UBOOT_SD_IMAGE} ${D}/boot/img/${UBOOT_SD_BINARY}
    
    install ${S}/${UBOOT_MIN_UART_BINARY} ${D}/boot/img/${UBOOT_MIN_UART_IMAGE}
    ln -sf ${UBOOT_MIN_UART_IMAGE} ${D}/boot/img/${UBOOT_MIN_UART_BINARY}
    
    install ${S}/${UBOOT_MIN_NAND_BINARY} ${D}/boot/img/${UBOOT_MIN_NAND_IMAGE}
    ln -sf ${UBOOT_MIN_NAND_IMAGE} ${D}/boot/img/${UBOOT_MIN_NAND_BINARY}
    
    install ${S}/${UBOOT_MIN_SD_BINARY} ${D}/boot/img/${UBOOT_MIN_SD_IMAGE}
    ln -sf ${UBOOT_MIN_SD_IMAGE} ${D}/boot/img/${UBOOT_MIN_SD_BINARY}
    
    install -m 0755 ${UBOOT_SCRIPTS_DIR}/default.cmd        ${D}/boot/img
    mkimage -A arm -O linux -T script -C none -a 0 -e 0 -n 'Execute uImage' -d ${D}/boot/img/default.cmd ${D}/boot/img/default.scr    

    install -m 0755 ${UBOOT_SCRIPTS_DIR}/update.cmd         ${D}/boot/
    mkimage -A arm -O linux -T script -C none -a 0 -e 0 -n 'Execute uImage' -d ${D}/boot/update.cmd ${D}/boot/disable.update.scr
      
    install -m 0755 ${UBOOT_SCRIPTS_DIR}/boot.cmd           ${D}/boot/
    echo "setenv nfs_root ${NFS_PATH}" >>                   ${D}/boot/boot.cmd
    mkimage -A arm -O linux -T script -C none -a 0 -e 0 -n 'Execute uImage' -d ${D}/boot/boot.cmd ${D}/boot/boot.dhcp.scr
   
    
    install -m 0755 ${UBOOT_SCRIPTS_DIR}/mkscr.sh           ${D}/boot/
            
    if [ -e ${UBOOT_SCRIPTS_DIR}/fw_env.config ] ; then
        install -m 644 ${UBOOT_SCRIPTS_DIR}/fw_env.config ${D}${sysconfdir}/fw_env.config
        install -m 755 ${S}/tools/env/fw_printenv ${D}${base_sbindir}/fw_printenv
        install -m 755 ${S}/tools/env/fw_printenv ${D}${base_sbindir}/fw_setenv
    fi
    
    cd ${D}/boot
    rm -f boot.scr
    ln -sf boot.dhcp.scr boot.scr
}

FILES_${PN} = "/boot /boot/img ${base_sbindir}/mkimage ${sysconfdir}"
# no gnu_hash in uboot.bin, by design, so skip QA
INSANE_SKIP_${PN} = True

PACKAGES += "${PN}-fw-utils"
FILES_${PN}-fw-utils = "${sysconfdir} ${base_sbindir}"
# u-boot doesn't use LDFLAGS for fw files, needs to get fixed, but until then:
INSANE_SKIP_${PN}-fw-utils = True

do_deploy () {
    install -d ${DEPLOY_DIR_IMAGE}
    install -d ${UBOOT_DEPLOY_DIR}
    
    #Copy binaries to deploy folder
    install ${S}/${UBOOT_NAND_BINARY} ${UBOOT_DEPLOY_DIR}/${UBOOT_NAND_IMAGE}
    package_stagefile_shell ${UBOOT_DEPLOY_DIR}/${UBOOT_NAND_IMAGE}
    
    install ${S}/${UBOOT_SD_BINARY} ${UBOOT_DEPLOY_DIR}/${UBOOT_SD_IMAGE}
    package_stagefile_shell ${UBOOT_DEPLOY_DIR}/${UBOOT_SD_IMAGE}
    
    install ${S}/${UBOOT_MIN_UART_BINARY} ${UBOOT_DEPLOY_DIR}/${UBOOT_MIN_UART_IMAGE}
    package_stagefile_shell ${UBOOT_DEPLOY_DIR}/${UBOOT_MIN_UART_IMAGE}
    
    install ${S}/${UBOOT_MIN_NAND_BINARY} ${UBOOT_DEPLOY_DIR}/${UBOOT_MIN_NAND_IMAGE}
    package_stagefile_shell ${UBOOT_DEPLOY_DIR}/${UBOOT_MIN_NAND_IMAGE}
    
    install ${S}/${UBOOT_MIN_SD_BINARY} ${UBOOT_DEPLOY_DIR}/${UBOOT_MIN_SD_IMAGE}
    package_stagefile_shell ${UBOOT_DEPLOY_DIR}/${UBOOT_MIN_SD_IMAGE}
    
    install ${S}/tools/mkimage-${TARGET_ARCH} ${UBOOT_DEPLOY_DIR}/mkimage
    package_stagefile_shell ${UBOOT_DEPLOY_DIR}/mkimage

    install -m 0775 ${UBOOT_SCRIPTS_DIR}/default.cmd        ${UBOOT_DEPLOY_DIR}
    package_stagefile_shell                      ${UBOOT_DEPLOY_DIR}/default.cmd
    
           
    #Creating symlinks
    cd ${UBOOT_DEPLOY_DIR}
    
    rm -f ${UBOOT_NAND_SYMLINK}
    ln -sf ${UBOOT_NAND_IMAGE} ${UBOOT_NAND_SYMLINK}
    package_stagefile_shell ${UBOOT_DEPLOY_DIR}/${UBOOT_NAND_SYMLINK}
    
    rm -f ${UBOOT_SD_SYMLINK}
    ln -sf ${UBOOT_SD_IMAGE} ${UBOOT_SD_SYMLINK}
    package_stagefile_shell ${UBOOT_DEPLOY_DIR}/${UBOOT_SD_SYMLINK}
    
    rm -f ${UBOOT_MIN_UART_SYMLINK}
    ln -sf ${UBOOT_MIN_UART_IMAGE} ${UBOOT_MIN_UART_SYMLINK}
    package_stagefile_shell ${UBOOT_DEPLOY_DIR}/${UBOOT_MIN_UART_SYMLINK}
    
    rm -f ${UBOOT_MIN_NAND_SYMLINK}
    ln -sf ${UBOOT_MIN_NAND_IMAGE} ${UBOOT_MIN_NAND_SYMLINK}
    package_stagefile_shell ${UBOOT_DEPLOY_DIR}/${UBOOT_MIN_NAND_SYMLINK}
    
    rm -f ${UBOOT_MIN_SD_SYMLINK}
    ln -sf ${UBOOT_MIN_SD_IMAGE} ${UBOOT_MIN_SD_SYMLINK}
    package_stagefile_shell ${UBOOT_DEPLOY_DIR}/${UBOOT_MIN_SD_SYMLINK}
    
    cd ${DEPLOY_DIR_IMAGE}
    rm -rf u-boot
    ln -sf `basename ${UBOOT_DEPLOY_DIR}` u-boot
    package_stagefile_shell ${DEPLOY_DIR_IMAGE}/u-boot 
}


do_deploy[dirs] = "${S}"
addtask deploy before do_package_stage after do_compile

