require ${OEBASE}/arago/recipes/ti/gst-openmax-ti.inc



COMPATIBLE_MACHINE = "(dm814x-z3|dm814x-evm)"

SRCREV = "${PN}_${PV}"
BRANCH = "master"

SRC_URI = "git://${GITSERVER}/${GITBASE}/gst-openmax.git;protocol=git;branch=${BRANCH} \
"

S = "${WORKDIR}/git"

EXTRA_AUTORECONF = ""
