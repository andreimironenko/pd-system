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
PARALLEL_MAKE=""

EXTRA_OEMAKE  = "CROSS_COMPILE=${TARGET_PREFIX}"
EXTRA_OEMAKE += "ARCH=${TARGET_ARCH}"

#AM: 
# "unset LDFLAGS" under do_compile by some reasons is not working, so
# disable local variable
export LDFLAGS=""

SRC_URI = "git://${GITSERVER}/bsp/u-boot-omap3-z3.git;protocol=git;branch=${BRANCH} \
           file://boot.cmd           \
           file://default.cmd        \
           file://mkscr.sh           \
           file://fw_env.config      \ 
           file://update.cmd         \
"

S = "${WORKDIR}/git"


UBOOT_MACHINE ?= "${MACHINE}_config"
UBOOT_BINARY ?= "u-boot.bin"
UBOOT_IMAGE ?= "u-boot-${MACHINE}-${PV}-${PR}.bin"
UBOOT_SYMLINK ?= "u-boot-${MACHINE}.bin"
UBOOT_MAKE_TARGET ?= "all"

UBOOT_DEPLOY_DIR ?= "${DEPLOY_DIR_IMAGE}/u-boot-${PV}"
UBOOT_SCRIPTS_DIR ?= "${WORKDIR}"

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
    
    #Build u-boot.bin for nand flash
    oe_runmake clean
    oe_runmake TFTP_PATH=${TFTP_PATH} ${UBOOT_NAND_CONFIG}
    oe_runmake ${UBOOT_MAKE_TARGET}
    oe_runmake tools clean
    
    #Build mkimage for the target platform
    oe_runmake HOSTCC="${TARGET_PREFIX}gcc" HOSTSTRIP="${TARGET_PREFIX}strip" tools env
    cp tools/mkimage tools/mkimage-${TARGET_ARCH}
    cp tools/env/fw_printenv tools/env/fw_printenv-${TARGET_ARCH}
    
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
    
    install ${S}/${UBOOT_BINARY} ${D}/boot/img/${UBOOT_IMAGE}
    ln -sf ${UBOOT_IMAGE} ${D}/boot/img/${UBOOT_BINARY}
    
    install ${S}/${UBOOT_MIN_UART_BINARY} ${D}/boot/img/${UBOOT_MIN_UART_IMAGE}
    ln -sf ${UBOOT_MIN_UART_IMAGE} ${D}/boot/img/${UBOOT_MIN_UART_BINARY}
    
    install ${S}/${UBOOT_MIN_NAND_BINARY} ${D}/boot/img/${UBOOT_MIN_NAND_IMAGE}
    ln -sf ${UBOOT_MIN_NAND_IMAGE} ${D}/boot/img/${UBOOT_MIN_NAND_BINARY}

    install -m 0755 ${UBOOT_SCRIPTS_DIR}/default.cmd        ${D}/boot/img/default.cmd
    sed -i '1isetenv nfs_root ${NFS_PATH}'                      ${D}/boot/img/default.cmd
    mkimage -A arm -O linux -T script -C none -a 0 -e 0 -n 'Execute uImage' -d ${D}/boot/img/default.cmd ${D}/boot/img/default.scr   
     
    
    install -m 0755 ${UBOOT_SCRIPTS_DIR}/mkscr.sh           ${D}/boot/
            
    install -m 644 ${UBOOT_SCRIPTS_DIR}/fw_env.config ${D}${sysconfdir}/fw_env.config
    install -m 755 ${S}/tools/env/fw_printenv-${TARGET_ARCH} ${D}${base_sbindir}/fw_printenv
    ln -sf fw_printenv ${D}${base_sbindir}/fw_setenv
}

do_deploy () {
    install -d ${DEPLOY_DIR_IMAGE}
    install -d ${UBOOT_DEPLOY_DIR}
    
    #Copy binaries to deploy folder
    install ${S}/${UBOOT_BINARY} ${UBOOT_DEPLOY_DIR}/${UBOOT_IMAGE}
    package_stagefile_shell ${UBOOT_DEPLOY_DIR}/${UBOOT_IMAGE}
    
    install ${S}/${UBOOT_MIN_UART_BINARY} ${UBOOT_DEPLOY_DIR}/${UBOOT_MIN_UART_IMAGE}
    package_stagefile_shell ${UBOOT_DEPLOY_DIR}/${UBOOT_MIN_UART_IMAGE}
    
    install ${S}/${UBOOT_MIN_NAND_BINARY} ${UBOOT_DEPLOY_DIR}/${UBOOT_MIN_NAND_IMAGE}
    package_stagefile_shell ${UBOOT_DEPLOY_DIR}/${UBOOT_MIN_NAND_IMAGE}
    
    install ${S}/tools/mkimage-${TARGET_ARCH} ${UBOOT_DEPLOY_DIR}/mkimage
    package_stagefile_shell ${UBOOT_DEPLOY_DIR}/mkimage

    install -m 0775 ${UBOOT_SCRIPTS_DIR}/default.cmd            ${UBOOT_DEPLOY_DIR}/default.cmd
    sed -i '1isetenv nfs_root ${NFS_PATH}'                      ${D}/boot/img/default.cmd
    package_stagefile_shell                                     ${UBOOT_DEPLOY_DIR}/default.cmd
           
    #Creating symlinks
    cd ${UBOOT_DEPLOY_DIR}
    
    rm -f ${UBOOT_SYMLINK}
    ln -sf ${UBOOT_IMAGE} ${UBOOT_SYMLINK}
    package_stagefile_shell ${UBOOT_DEPLOY_DIR}/${UBOOT_SYMLINK}
    
    rm -f ${UBOOT_MIN_UART_SYMLINK}
    ln -sf ${UBOOT_MIN_UART_IMAGE} ${UBOOT_MIN_UART_SYMLINK}
    package_stagefile_shell ${UBOOT_DEPLOY_DIR}/${UBOOT_MIN_UART_SYMLINK}
    
    rm -f ${UBOOT_MIN_NAND_SYMLINK}
    ln -sf ${UBOOT_MIN_NAND_IMAGE} ${UBOOT_MIN_NAND_SYMLINK}
    package_stagefile_shell ${UBOOT_DEPLOY_DIR}/${UBOOT_MIN_NAND_SYMLINK}
    
    cd ${DEPLOY_DIR_IMAGE}
    rm -rf u-boot
    ln -sf `basename ${UBOOT_DEPLOY_DIR}` u-boot
    package_stagefile_shell ${DEPLOY_DIR_IMAGE}/u-boot 
}

do_deploy[dirs] = "${S}"
addtask deploy before do_package_stage after do_compile

FILES_${PN}  = "${base_sbindir}/mkimage"
FILES_${PN} += "/boot/img/*"
FILES_${PN} += "/boot/mkscr.sh"

# no gnu_hash in uboot.bin, by design, so skip QA
INSANE_SKIP_${PN} = True

PACKAGES += "${PN}-fw-utils"
FILES_${PN}-fw-utils = "${base_sbindir}/fw_printenv" 
FILES_${PN}-fw-utils += "${base_sbindir}/fw_setenv"
FILES_${PN}-fw-utils += "${sysconfdir}/fw_env.config"

# u-boot doesn't use LDFLAGS for fw files, needs to get fixed, but until then:
INSANE_SKIP_${PN}-fw-utils = True

CONFFILES_${PN}-fw-utils =             "\
  ${sysconfdir}/fw_env.config           \
"

#pkg_preinst_${PN}_append () {
#
#} 

pkg_postinst_${PN}_append() {

    # Reflash u-boot.bin
    flash_erase /dev/mtd1 0 0
    nandwrite -p /dev/mtd1 /boot/img/u-boot.bin
    
    # Updating u-boot default environment
    flash_erase /dev/mtd2 0 0
    nandwrite -p /dev/mtd2 /boot/img/default.scr
}

#pkg_prerm_${PN}_append () {
#
#} 

#pkg_postrm_${PN}_append() {
#
#}
