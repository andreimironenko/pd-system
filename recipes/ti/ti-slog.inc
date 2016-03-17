require ${OEBASE}/arago/recipes/ti/ti-slog.inc

SRCREV = "slog_${PV}"
BRANCH = "master"

S = "${WORKDIR}/git"
SRC_URI = "git://${GITSERVER}/${GITBASE}/slog.git;protocol=git;branch=${BRANCH}"