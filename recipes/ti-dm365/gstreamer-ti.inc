DESCRIPTION = "GSTREAMER Plugin (gstreamer-ti) for TI ARM/DSP processors"
HOMEPAGE = "https://gforge.ti.com/gf/project/gstreamer_ti/"
SECTION = "multimedia"
LICENSE = "LGPL"

# TODO :: Replace omapl137 with official support in GST (currently linking to omapl138)
# TODO :: Codec Server Environment Variables shouldn't be required
# TODO :: Add (and check) rc scripts for all targets (just copied for now) (365,6467,omapl137)
# TODO :: Check if CPPFLAGS_append is still required
# TODO :: Remove ENCODE/DECODE combo exports - these are not used anymore (check?)

inherit autotools
require ${OEBASE}/arago/recipes/ti/ti-paths.inc
require ${OEBASE}/arago/recipes/ti/ti-staging.inc

# Rebuild on kernel change since it links statically to ti-dmai, ti-codec-engine, etc
PR = "r82+${MACHINE_KERNEL_PR}"

DEPENDS = "ti-dmai gstreamer gst-plugins-base"

SRC_URI = "git://${GITSERVER}/ti-dm365/gstreamer-ti.git;protocol=git;branch=${BRANCH}"

S = "${WORKDIR}/git"

# enable c6accel elements on omapl138 and omap3
#DEPENDS_append_omapl138 = " ti-c6accel "
#EXTRA_OECONF_omapl138 = "--enable-c6accel"
#DEPENDS_append_omap3 = " ti-c6accel "
#EXTRA_OECONF_omap3 = "--enable-c6accel"
#C6ACCEL_PLATFORM_omapl138 = "omapl138"
#C6ACCEL_PLATFORM_omap3 = "omap3530"

export C6ACCEL_INSTALL_DIR
export C6ACCEL_PLATFORM

# gstreamer_ti picks up some config variables from the environment
# - variables are used in the gstreamer makefile
#   - PLATFORM, XDC_PLATFORM, XDC_TARGET, MVTOOL_DIR  
# - others used by config.bld (which it gets from the dmai config.bld)
#   - CROSS_COMPILE, PLATFORM_XDC

#PLATFORM_dm6446        = "dm6446"
#PLATFORM_dm6467        = "dm6467"
#PLATFORM_dm6467t       = "dm6467t"
#PLATFORM_omap3         = "omap3530"
#PLATFORM_dm355         = "dm355"
#PLATFORM_dm365         = "dm365"
#PLATFORM_omapl137      = "omapl137"
#PLATFORM_omapl138      = "omapl138"
#PLATFORM              ?= "<UNDEFINED_PLATFORM>"
PLATFORM                = "dm365"
GST_TI_PLATFORM = ${PLATFORM}

#XDC_PLATFORM_dm6446    = "ti.platforms.evmDM6446"
#XDC_PLATFORM_dm6467    = "ti.platforms.evmDM6467"
#XDC_PLATFORM_omap3     = "ti.platforms.evm3530"
#XDC_PLATFORM_dm355     = "ti.platforms.evmDM355"
#XDC_PLATFORM_dm365     = "ti.platforms.evmDM365"
#XDC_PLATFORM_omapl137  = "ti.platforms.evmOMAPL137"
#XDC_PLATFORM_omapl138  = "ti.platforms.evmOMAPL138"
#XDC_PLATFORM          ?= "<UNDEFINED_XDC_PLATFORM>"
XDC_PLATFORM            = "ti.platforms.evmDM365"

export PLATFORM
export GST_TI_PLATFORM
export XDC_PLATFORM
export XDC_TARGET      = "gnu.targets.arm.GCArmv5T"
export PLATFORM_XDC    = ${XDC_PLATFORM}
export MVTOOL_DIR      = "${TOOLCHAIN_PATH}"
export CROSS_COMPILE   = "${TOOLCHAIN_PATH}/bin/${TARGET_PREFIX}"
export LINK_XDC_ROOT   = "${LINK_INSTALL_DIR}"

# export codec combo (or server) locations
# Why do we need to do this?? - These will get picked up from CODEC_INSTALL_DIR?
# Sould only need this if we change from default server

export CODEC_SERVER  = "${installdir}/ti-codecs-server/cs.x64P"
CPPFLAGS_append = " -DPlatform_${PLATFORM}"

# We are still using encode/decode combo for DM6446
export ENCODE_COMBO    = "${installdir}/ti-codecs-server/encodeCombo.x64P"
export DECODE_COMBO    = "${installdir}/ti-codecs-server/decodeCombo.x64P"
# Makefile also expects to be able to find the kernel headers from the envirionment
export LINUXKERNEL_INSTALL_DIR = "${STAGING_KERNEL_DIR}"

do_configure_prepend() {
	# PSP kernel is based on older DSS. we need to replace linux/omapfb.h with mach/omapfb.h
	if ! [ -e ${STAGING_KERNEL_DIR}/include/linux/omapfb.h ] ; then
		sed -i -e s:linux/omapfb:mach/omapfb:g ${S}/src/omapfb.h || true
	fi
    ./gst-autogen.sh	
}

#RRECOMMENDS_${PN}_append_dm6446    += "ti-codecs-dm6446-server   ti-cmem-module ti-dsplink-module"
#RRECOMMENDS_${PN}_append_dm6467    += "ti-codecs-dm6467          ti-cmem-module ti-dsplink-module"
#RRECOMMENDS_${PN}_append_omap3     += "ti-codecs-omap3530-server ti-cmem-module ti-dsplink-module ti-lpm-module ti-sdma-module ti-tisdk-loadmodule"
#RRECOMMENDS_${PN}_append_dm355     += "ti-codecs-dm355           ti-cmem-module ti-dm355mm-module"
#RRECOMMENDS_${PN}_append_dm365     += "ti-codecs-dm365           ti-cmem-module ti-dm365mm-module ti-edma-module ti-irq-module ti-tisdk-loadmodule"
#RRECOMMENDS_${PN}_append_omapl137  += "ti-codecs-omapl137-server ti-cmem-module ti-dsplink-module"
#RRECOMMENDS_${PN}_append_omapl138  += "ti-codecs-omapl138-server ti-cmem-module ti-dsplink-module ti-tisdk-loadmodule"
RRECOMMENDS_${PN} += "ti-codecs-dm365 ti-cmem-module ti-dm365mm-module \ 
                              ti-edma-module ti-irq-module ti-tisdk-loadmodule"
                              
FILES_${PN}     += "${libdir}/gstreamer-0.10/*.so ${sysconfdir} ${installdir}"
FILES_${PN}-dev += "${libdir}/gstreamer-0.10/*.a ${libdir}/gstreamer-0.10/*.la"
FILES_${PN}-dbg += "${libdir}/gstreamer-0.10/.debug"