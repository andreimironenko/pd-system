DESCRIPTION = "GStreamer based RTSP server"
HOMEPAGE = "http://gstreamer.freedesktop.org/src/gst-rtsp-server/"
SECTION = "system"
LICENSE = "GPL"

inherit autotools 

DEPENDS = "gst-plugin-base gst-plugin-bad gst-plugin-good gst-plugin-ugly gst-rtsp"
RDEPENDS = "gst-plugin-base gst-plugin-bad gst-plugin-good gst-plugin-ugly gst-rtsp"

SRC_URI = "git://${GITSERVER}/${GITBASE}/rr-rtsp-server.git;protocol=git;branch=${BRANCH}"

BRANCH ?= "master"
S = "${WORKDIR}/git"

