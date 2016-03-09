SECTION = "kernel"
DESCRIPTION = "Linux kernel for OMAP3 EVM from PSP, based on linux-omap3 kernel"
LICENSE = "GPLv2"
KERNEL_IMAGETYPE = "uImage"

inherit kernel
require copy-defconfig.inc
require setup-defconfig.inc

BRANCH ?= "master"

SRC_URI = "git://${GITSERVER}/bsp/linux-omap3-z3.git;protocol=git;branch=${BRANCH} \
           file://defconfig \
           "

# Requires support for SOC_FAMILY matching in COMPATIBLE_MACHINE
COMPATIBLE_MACHINE = "dm814x-z3"

S = "${WORKDIR}/git"

do_deploy_append() {
    install -d ${DEPLOY_DIR_IMAGE}
    
    #Creating symlinks
    cd ${DEPLOY_DIR_IMAGE}
    rm -f uImage.bin
    ln -sf ${KERNEL_IMAGE_BASE_NAME}.bin uImage.bin
    
    rm -f kmodules.tgz
    ln -sf ${MODULES_IMAGE_BASE_NAME}.tgz kmodules.tgz
}


#pkg_preinst_${PN}_append () {
#
#} 

pkg_postinst_kernel-image_append() {
    echo "Reflashing uImage ..." 
    flash_erase /dev/mtd3 0 0
    nandwrite -p /dev/mtd3 /boot/uImage-${KERNEL_VERSION}
}

#pkg_prerm_${PN}_append () {
#
#} 

#pkg_postrm_${PN}_append() {
#
#}