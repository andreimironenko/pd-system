DESCRIPTION = "TI DSP Code Generation Tools"
HOMEPAGE = "https://www-a.ti.com/downloads/sds_support/TICodegenerationTools/download.htm"
SECTION = "devel"
LICENSE = "TI"

require ${OEBASE}/arago/recipes/ti/ti-paths.inc
require ${OEBASE}/arago/recipes/ti/ti-staging.inc

PR = "r4"

COMPATIBLE_MACHINE = "(dm814x-z3|dm814x-evm)"


SRCREV = "cgt6x_${PV}"
BRANCH = "master"


SRC_URI = "git://${GITSERVER}/ti/cgt6x.git;protocol=git;branch=${BRANCH}"

S = "${WORKDIR}/git"


do_install() {
    install -d ${D}${CODEGEN_INSTALL_DIR_RECIPE}
    cp -pPrf ${S}/* ${D}${CODEGEN_INSTALL_DIR_RECIPE}
}

 