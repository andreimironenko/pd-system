DESCRIPTION = "TI SYS/BIOS v6 Kernel"
HOMEPAGE = "http://software-dl.ti.com/dsps/dsps_public_sw/sdo_sb/targetcontent/bios/sysbios"
SECTION = "devel"
LICENSE = "BSD"

require ${OEBASE}/arago/recipes/ti/ti-paths.inc
require ${OEBASE}/arago/recipes/ti/ti-staging.inc

PR = "r5"
PVExtra = ""

SRCREV = "bios_${PV}"
BRANCH = "master"

S = "${WORKDIR}/git"
SRC_URI = "git://${GITSERVER}/ti/bios.git;protocol=git;branch=${BRANCH}"


do_install() {
    install -d ${D}${SYSBIOS_INSTALL_DIR_RECIPE}
    cp -pPrf ${S}/* ${D}${SYSBIOS_INSTALL_DIR_RECIPE}
}

