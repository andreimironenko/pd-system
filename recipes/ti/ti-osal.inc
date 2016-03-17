require ${OEBASE}/arago/recipes/ti/ti-osal.inc

SRCREV = "osal_${PV}"
BRANCH = "master"

S = "${WORKDIR}/git"
SRC_URI = "git://${GITSERVER}/${GITBASE}/osal.git;protocol=git;branch=${BRANCH}"