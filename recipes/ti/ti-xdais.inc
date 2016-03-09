require ${OEBASE}/arago/recipes/ti/ti-xdais.inc

SRCREV = "xdais_${PV}"
BRANCH = "master"

S = "${WORKDIR}/git"
SRC_URI = "git://${GITSERVER}/ti/xdais.git;protocol=git;branch=${BRANCH}"