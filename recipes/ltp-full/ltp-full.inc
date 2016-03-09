DESCRIPTION = "Linux Test Project"
HOMEPAGE = "http://ltp.sourceforge.net"
LICENSE = "GPL"
SECTION = "console/utils"
DEPENDS = "zip-native bison byacc flex"
PR = "r0"

inherit autotools

#PV = "20120903"
SRCREV = "${PN}_${PV}"
BRANCH = "master"

SRC_URI = "git://${GITSERVER}/oss/ltp-full.git;protocol=git;branch=${BRANCH}"

S = "${WORKDIR}/git"

EXTRA_OEMAKE_append = " CROSS_COMPILE=${HOST_PREFIX} SKIP_IDCHECK=1"
TARGET_CC_ARCH += "${LDFLAGS}"

FILES_${PN}-dbg += "/usr/.debug"
FILES_${PN}-dbg += "/usr/bin/.debug"
FILES_${PN}-dbg += "/usr/runtest/.debug"
FILES_${PN}-dbg += "/usr/testcases/bin/.debug"
FILES_${PN}-dbg += "/usr/testcases/bin/*/bin/.debug"
FILES_${PN}-dbg += "/usr/testcases/bin/*/test/.debug"

FILES_${PN} += "/usr/*"
FILES_${PN} += "/usr/bin/*"
FILES_${PN} += "/usr/runtest/*"
FILES_${PN} += "/usr/testcases/bin/*"
FILES_${PN} += "/usr/testcases/bin/*"
FILES_${PN} += "/bin/*"
FILES_${PN} += "/usr/testscripts/*"