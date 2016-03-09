DESCRIPTION = "TI DSP/BIOS v5 Kernel"
HOMEPAGE = "http://software-dl.ti.com/dsps/dsps_public_sw/sdo_sb/targetcontent/bios/dspbios"
SECTION = "devel"
LICENSE = "TI"

require ${OEBASE}/arago/recipes/ti/ti-paths.inc
require ${OEBASE}/arago/recipes/ti/ti-staging.inc

PR = "r1"

SRCREV = "bios_${PV}"
BRANCH = "master"

S = "${WORKDIR}/git"
SRC_URI = "git://${GITSERVER}/ti/bios.git;protocol=git;branch=${BRANCH}"

do_install() {
    install -d ${D}${BIOS_INSTALL_DIR_RECIPE}
    cp -pPrf ${S}/* ${D}${BIOS_INSTALL_DIR_RECIPE}
}

