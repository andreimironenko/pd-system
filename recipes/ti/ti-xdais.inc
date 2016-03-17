require ${OEBASE}/arago/recipes/ti/ti-xdais.inc

SRCREV = "xdais_${PV}"
BRANCH = "master"

S = "${WORKDIR}/git"
SRC_URI = "git://${GITSERVER}/${GITBASE}/xdais.git;protocol=git;branch=${BRANCH}"