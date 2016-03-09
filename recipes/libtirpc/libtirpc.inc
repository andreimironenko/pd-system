DESCRIPTION = "Libtirpc is a port of Suns Transport-Independent RPC library to Linux." 
HOMEPAGE = "http://sourceforge.net/projects/libtirpc/"
SECTION = "console/misc"
LICENSE = "GPLv2"

DEPENDS = ""

inherit autotools 

SRC_URI = "git://linux-nfs.org/~steved/libtirpc;protocol=git;branch=${BRANCH}"

SRCREV = "${PV}"
BRANCH = "master"

S = "${WORKDIR}/git"

EXTRA_OECONF = "--disable-gssapi" 
