DESCRIPTION = "TI AAC LC Decoder for C674x devices"
SECTION = "multimedia"
LICENSE = "TI Proprietary"

require ${OEBASE}/arago/recipes/ti/ti-paths.inc
require ${OEBASE}/arago/recipes/ti/ti-staging.inc

PVExtra="_elf"

SRCREV = "${PN}_${PV}"
BRANCH = "master"

S = "${WORKDIR}/git"

SRC_URI = "git://${GITSERVER}/ti/c674x-aaclcdec.git;protocol=git;branch=${BRANCH}"

do_install() {
    install -d ${D}${CODEC_INSTALL_DIR_RECIPE}
    cp -pPrf ${S}/* ${D}${CODEC_INSTALL_DIR_RECIPE}
}
