SECTION = "kernel"
DESCRIPTION = "Linux kernel for OMAP3 EVM from PSP, based on linux-omap3 kernel"
LICENSE = "GPLv2"
KERNEL_IMAGETYPE = "uImage"

inherit kernel
require copy-defconfig.inc
require setup-defconfig.inc

BRANCH  ?= "branch.v2.6.37_TI81XXPSP_04.04.00.01.patch2"
SRCREV  = "v${PV}"
SRC_URI = "git://${GITSERVER}/bsp/linux-omap3.git;protocol=git;branch=${BRANCH} \
           "

# Requires support for SOC_FAMILY matching in COMPATIBLE_MACHINE
COMPATIBLE_MACHINE = "dm814x-evm"

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
