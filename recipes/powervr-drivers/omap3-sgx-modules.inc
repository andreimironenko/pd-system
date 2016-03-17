DESCRIPTION = "Kernel drivers for the PowerVR SGX chipset found in the omap3 SoCs"
LICENSE = "GPLv2"

# download required binary distribution from:
# http://software-dl.ti.com/dsps/dsps_public_sw/sdo_sb/targetcontent/gfxsdk/latest/index_FDS.html
# see libgles-omap3.inc for detailed installation instructions
require powervr.inc

SGXPV = "4_04_00_02"
IMGPV = "1.6.16.4117"

inherit module

OMAPES="6.x"
FBDEV="yes"

MACHINE_KERNEL_PR_append = "i"

SRCREV = "graphics-sdk_4.04.00.02"
BRANCH = "master"

S = "${WORKDIR}/git"

SRC_URI = "git://${GITSERVER}/${GIBASE}/graphics-sdk.git;protocol=git;branch=${BRANCH}"
SRC_URI += ${EXTRA_SRC_URI}


PVRBUILD = "release"

PACKAGE_STRIP = "no"

export SUPPORT_XORG

TI_PLATFORM_omap3 = "omap3630"
TI_PLATFORM_ti816x = "ti81xx"
TI_PLATFORM_ti814x = "ti81xx"
TI_PLATFORM_ti811x = "ti81xx"
TI_PLATFORM_ti33x = "ti335x"

MODULESLOCATION_omap3 =  "dc_omapfb3_linux"
MODULESLOCATION_ti816x = "dc_ti81xx_linux"
MODULESLOCATION_ti814x = "dc_ti81xx_linux"
MODULESLOCATION_ti811x = "dc_ti81xx_linux"
MODULESLOCATION_ti33x =  "dc_ti335x_linux"

#AM: 
# "unset LDFLAGS" under do_compile by some reasons is not working, so
# disable local variable
export LDFLAGS=""

EXTRA_OEMAKE = "HOME=${WORKDIR}"

# Set installation folder (typically, OMAP35x_Graphics_***)
EXTRA_OEMAKE += "GRAPHICS_INSTALL_DIR=${S}" 

# Location of demo executables and install information
EXTRA_OEMAKE += "GFX_DEMOS_EXECPATH=${S}/gfxsdkdemos"

# Toolchain path
# CSTOOL_DIR=/proj/AVME10/mahesh/Graphics/toolchain/arm-2009q1
#CSTOOL_DIR=/proj/productization/workdir/mahesh/toolchain/Sourcery_G++_Lite/bin
EXTRA_OEMAKE += "CSTOOL_PREFIX=${TARGET_PREFIX}-"
EXTRA_OEMAKE += "CSTOOL_DIR=${OEBASE}/arago-tmp/${PRODUCT}/${RELDIR}/sysroots"
EXTRA_OEMAKE += "CSTOOL_PATH="${CSTOOL_DIR}/x86_64-linux/usr/${FEED_ARCH}/bin"
EXTRA_OEMAKE += "CSTOOL_LIBSTDC++_PATH=${CSTOOL_DIR}/${TARGET_PREFIX}/usr/lib"


EXTRA_OEMAKE += "OMAPES=${OMAPES}"

# Set the kernel installation path
#EXTRA_OEMAKE += "KERNEL_INSTALL_DIR=${D}"
EXTRA_OEMAKE += "KERNEL_INSTALL_DIR=$OEBASE/pd-system-dev/recipes/linux/linux-omap3-evm-2.6.37-git"
# Target NFS root file system location
#TARGETFS_INSTALL_DIR=/home/netrauser/groups/psp/nfs_prathap
EXTRA_OEMAKE += "TARGETFS_INSTALL_DIR=${S}/install"

EXTRA_OEMAKE += "SUPPORT_XORG=${SUPPORT_XORG}"


MAKE_TARGETS = "BUILD=${PVRBUILD} TI_PLATFORM=${TI_PLATFORM} SUPPORT_XORG=${SUPPORT_XORG} OMAPES=${OMAPES} FBDEV=${FBDEV}"

MAKE_TARGETS += "HOME=${WORKDIR}"
MAKE_TARGETS += "GRAPHICS_INSTALL_DIR=${S}" 
MAKE_TARGETS += "GFX_DEMOS_EXECPATH=${S}/gfxsdkdemos"
MAKE_TARGETS += "CSTOOL_PREFIX=${TARGET_PREFIX}"
MAKE_TARGETS += "CSTOOL_DIR=${OEBASE}/arago-tmp/${PRODUCT}/${RELDIR}/sysroots"
MAKE_TARGETS += "CSTOOL_PATH=${CSTOOL_DIR}/x86_64-linux/usr/${FEED_ARCH}/bin"
MAKE_TARGETS += "CSTOOL_LIBSTDC++_PATH=${CSTOOL_DIR}/${TARGET_PREFIX}/usr/lib"
MAKE_TARGETS += "OMAPES=${OMAPES}"
MAKE_TARGETS += "KERNEL_INSTALL_DIR=$OEBASE/pd-system-dev/recipes/linux/linux-omap3-evm-2.6.37-git"
MAKE_TARGETS += "TARGETFS_INSTALL_DIR=${S}/install"
MAKE_TARGETS += "SUPPORT_XORG=${SUPPORT_XORG}"
MAKE_TARGETS += "CROSS_COMPILE=${TARGET_PREFIX}"



do_compile() {
  mkdir -p ${D}/lib/modules/${KERNEL_VERSION}/kernel/drivers/gpu/pvr
  make ${MAKE_TARGETS} all_km
}


do_install() {
	mkdir -p ${D}/lib/modules/${KERNEL_VERSION}/kernel/drivers/gpu/pvr
	cp ${S}/gfx_rel_es${OMAPES}/pvrsrvkm.ko ${D}/lib/modules/${KERNEL_VERSION}/kernel/drivers/gpu/pvr
	if [ "$SUPPORT_XORG" = "1" ]; then
	   cp ${S}/services4/3rdparty/linux_drm/drm.ko ${D}/lib/modules/${KERNEL_VERSION}/kernel/drivers/gpu/pvr
	else
	   cp ${S}/gfx_rel_es${OMAPES}/omaplfb.ko  ${D}/lib/modules/${KERNEL_VERSION}/kernel/drivers/gpu/pvr
	fi
	cp ${S}/gfx_rel_es${OMAPES}/bufferclass_ti.ko ${D}/lib/modules/${KERNEL_VERSION}/kernel/drivers/gpu/pvr
}

FILES_${PN} = "/lib/modules/${KERNEL_VERSION}/kernel/drivers/gpu/pvr"
# no gnu_hash in uboot.bin, by design, so skip QA
INSANE_SKIP_${PN} = True