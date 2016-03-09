require ${OEBASE}/arago/recipes/ti/ti-linuxutils.inc

PE = "1"

SRCREV = "linuxutils_${PV}"
BRANCH = "master"


S = "${WORKDIR}/git"
SRC_URI = "git://${GITSERVER}/ti/linuxutils.git;protocol=git;branch=${BRANCH}"
SRC_URI += "file://sdk.mk \
"

do_prepsources() {
    cp ${WORKDIR}/sdk.mk ${S}
}
addtask prepsources after do_unpack before do_patch
