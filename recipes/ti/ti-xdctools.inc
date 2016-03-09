DESCRIPTION = "TI XDCtools (RTSC - Real Time Software Components - http://rtsc.eclipse.org)"
HOMEPAGE = "http://software-dl.ti.com/dsps/dsps_public_sw/sdo_sb/targetcontent/rtsc"
SECTION = "devel"
LICENSE = "BSD, GPLv2"

PR = "r2"

require ${OEBASE}/arago/recipes/ti/ti-paths.inc
require ${OEBASE}/arago/recipes/ti/ti-staging.inc

SRCREV = "xdctools_${PV}"
BRANCH = "master"

SRC_URI = "git://${GITSERVER}/ti/xdctools.git;protocol=git;branch=${BRANCH}"

S = "${WORKDIR}/git"

do_install() {
    install -d ${D}${XDC_INSTALL_DIR_RECIPE}
    cp -pPrf ${S}/* ${D}${XDC_INSTALL_DIR_RECIPE}
}

# Prevent internal libs from getting picked up
PRIVATE_LIBS = " \
libncdb.so \
libcdb.so \
libjavaplugin_oji.so \
libjavaplugin_jni.so \
libjsound.so \
libinstrument.so \
libjawt.so \
libzip.so \
libjava_crw_demo.so \
libjavaplugin_nscp_gcc29.so \
libhprof.so \
libcmm.so \
libjdwp.so \
libmlib_image.so \
libjpeg.so \
libverify.so \
libjavaplugin_nscp.so \
libmanagement.so \
libunpack.so \
librmi.so \
libJdbcOdbc.so \
libawt.so \
libnet.so \
libjaas_unix.so \
libnio.so \
libdcpr.so \
libioser12.so \
libjsoundalsa.so \
libjava.so \
libfontmanager.so \
libdt_socket.so \
libmawt.so \
libjvm.so \
libhpi.so \
lib.so \
libcairo.so.2 \
"
