SRCREV = "codec_engine_${PV}"
BRANCH = "master"

S = "${WORKDIR}/git"

SRC_URI = "git://${GITSERVER}/${GITBASE}/codec-engine.git;protocol=git;branch=${BRANCH}"
