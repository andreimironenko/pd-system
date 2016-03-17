DESCRIPTION = "TI EDMA3 Low Level Driver (LLD)"
HOMEPAGE = "http://software-dl.ti.com/dsps/dsps_public_sw/${SRC_URI_edma3lldsite}/edma3_lld"
SECTION = "devel"
LICENSE = "BSD"

require ${OEBASE}/arago/recipes/ti/ti-paths.inc
require ${OEBASE}/arago/recipes/ti/ti-staging.inc

PR = "r2"

SRCREV = "edma3lld_${PV}"
BRANCH = "master"

S = "${WORKDIR}/git"
SRC_URI = "git://${GITSERVER}/${GITBASE}/edma3lld.git;protocol=git;branch=${BRANCH}"


do_install() {
    install -d ${D}${EDMA3_LLD_INSTALL_DIR_RECIPE}
    cp -pPrf ${S}/* ${D}${EDMA3_LLD_INSTALL_DIR_RECIPE}
}
