require ${OEBASE}/arago/recipes/ti/ti-firmware-dm814x.inc


COMPATIBLE_MACHINE = "(dm814x-z3|dm814x-evm)"


SRCREV = "firmware-dm814x_${PV}"
BRANCH = "master"

SRC_URI = "git://${GITSERVER}/${GITBASE}/firmware-ti814x.git;protocol=git;branch=${BRANCH} \
"

S = "${WORKDIR}/git"
