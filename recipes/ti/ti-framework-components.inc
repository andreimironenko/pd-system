DESCRIPTION = "TI Framework Components"
HOMEPAGE = "http://software-dl.ti.com/dsps/dsps_public_sw/sdo_sb/targetcontent/fc"
SECTION = "devel"
LICENSE = "BSD"

require ${OEBASE}/arago/recipes/ti/ti-paths.inc
require ${OEBASE}/arago/recipes/ti/ti-staging.inc

COMPATIBLE_MACHINE = "(dm814x-z3|dm814x-evm)"

PR = "r1"

PVExtra = ""

SRCREV = "framework-components_${PV}"
BRANCH = "master"

S = "${WORKDIR}/git"

SRC_URI = "git://${GITSERVER}/${GITBASE}/framework_components.git;protocol=git;branch=${BRANCH}"


do_install() {
    install -d ${D}${FC_INSTALL_DIR_RECIPE}
    cp -pPrf ${S}/* ${D}${FC_INSTALL_DIR_RECIPE}
}

