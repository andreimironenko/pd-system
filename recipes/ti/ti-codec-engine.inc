SRCREV = "codec_engine_${PV}"
BRANCH = "master"

S = "${WORKDIR}/git"

SRC_URI = "git://${GITSERVER}/ti/codec_engine.git;protocol=git;branch=${BRANCH}"
