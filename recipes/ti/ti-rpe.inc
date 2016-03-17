require ${OEBASE}/arago/recipes/ti/ti-rpe.inc

SRCREV = "rpe_${PV}"
BRANCH = "master"

S = "${WORKDIR}/git"
SRC_URI = "git://${GITSERVER}/${GITBASE}/rpe.git;protocol=git;branch=${BRANCH}"

SRC_URI += "\
           file://${OEBASE}/arago/recipes/ti/ti-rpe/aacdectest_c6a811x.cfg \
           file://${OEBASE}/arago/recipes/ti/ti-rpe/aacenctest_c6a811x.cfg \
           file://${OEBASE}/arago/recipes/ti/ti-rpe/mp3dectest_c6a811x.cfg \
"
