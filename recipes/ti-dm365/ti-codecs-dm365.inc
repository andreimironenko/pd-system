DESCRIPTION = "TI Codecs for DM365"
SECTION = "multimedia"
LICENSE = "TI"

PR="${MACHINE_KERNEL_PR}"
PR_append = "a"
require ${OEBASE}/arago/recipes/ti/ti-paths.inc
require ${OEBASE}/arago/recipes/ti/ti-staging.inc

SRC_URI = "git://${GITSERVER}/ti-dm365/codecs-dm365.git;protocol=git;branch=${BRANCH}"
S = "${WORKDIR}/git"

CODEC_SUITE_NAME="${S}"

TI_BIN_UNPK_CMDS = "Y:workdir"
PROVIDES += "ti-codecs-dm365-server"

do_install() {
    install -d ${D}${CODEC_INSTALL_DIR_RECIPE}
    cp -pPrf ${CODEC_SUITE_NAME}/* ${D}/${CODEC_INSTALL_DIR_RECIPE}
}

PACKAGES += "ti-codecs-dm365-server"
FILES_ti-codecs-dm365-server = "${installdir}/ti-codecs-server/*"
INSANE_SKIP_ti-codecs-dm365-server = True

