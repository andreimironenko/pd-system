require ${OEBASE}/arago/recipes/ti/ti-media-controller-loader.inc


COMPATIBLE_MACHINE = "(dm814x-z3|dm814x-evm)"

SRCREV = "ti-media-controller_${PV}"
BRANCH = "master"

PLATFORM="ti814x-evm"

EXTRA_OEMAKE = "PLATFORM=${PLATFORM} \
        ROOTDIR=${S} \
        bios_PATH=${SYSBIOS_INSTALL_DIR} \
        ipc_PATH=${IPC_INSTALL_DIR} \
        syslink_PATH=${SYSLINK_INSTALL_DIR} \
        xdc_PATH=${XDC_INSTALL_DIR} \
        CODEGEN_PATH_A8=${TOOLCHAIN_PATH} \
        CODEGEN_PATH_DSPELF=${CODEGEN_INSTALL_DIR} \
"

SRC_URI = "git://${GITSERVER}/${GITBASE}/media-controller-utils.git;protocol=git;branch=${BRANCH} \
           file://load-hd-firmware.sh \
           file://patches \
"
#Toolchain variables used in the makefile
CC  = "${TOOLCHAIN_LONGNAME}-gcc"
AR  = "${TOOLCHAIN_LONGNAME}-ar"
LNK = "${TOOLCHAIN_LONGNAME}-ld" 

S = "${WORKDIR}/git"

#Due to some reasons do_patch is not invoked for this recipe...
do_patch() {
   quilt push 01-media-controller-cc-fix.patch
   quilt push 02-media-controller-xdc-std-fix.patch
}


do_install() {
    # Install the firmwware loader script
    install -d ${D}${sysconfdir}/init.d
    install -m 0755 ${WORKDIR}/load-hd-firmware.sh ${D}${sysconfdir}/init.d/
}
