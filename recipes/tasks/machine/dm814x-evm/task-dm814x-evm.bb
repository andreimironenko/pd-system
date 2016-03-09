################################################################################
# Task, for building basic packages which are used currently in HTC.           #
#                                                                              #
# Author: Andrei Mironenko <andrei.mironenko@paralleldynamic.com>              #
#                                                                              #
# Copyright(C) 2015 Parallel Dynamic Ltd.                                      #
# This file is licensed under the terms of the GNU General Public License      #
# version 2. This program  is licensed "as is" without any warranty of any     #
# kind, whether express or implied.                                            #
################################################################################
DESCRIPTION = "TI DM814x base packages"
LICENSE = "MIT"
PR = "r12"

inherit task

#kernel-module-iptable-nat 
#kernel-module-iptable-mangle 
#kernel-module-ipt-masquerade 

COMPATIBLE_MACHINE = "dm814x-evm"
	
# those ones can be set in machine config to supply packages needed to get machine booting
MACHINE_ESSENTIAL_EXTRA_RDEPENDS = "\
   system-configs-dm814x-evm \
"
MACHINE_ESSENTIAL_EXTRA_RRECOMMENDS = "\
"

TI_DM814X_EVM =              "\
  gst-openmax-ti             \
  ti-firmware                \
  ti-cmem-module             \
  ti-syslink                 \
  ti-syslink-module          \ 
  ti-media-controller-loader \
  ti-media-controller-utils  \
  u-boot-omap3-evm           \
  u-boot-omap3-evm-fw-utils  \
  kernel                     \
  kernel-image               \
  kernel-modules             \
  omap3-sgx-modules          \
  "

     
RDEPENDS_${PN} = "\
      ${TI_DM814X_EVM} \
      ${MACHINE_ESSENTIAL_EXTRA_RDEPENDS} \
    "

RRECOMMENDS_${PN} = "\
    ${MACHINE_ESSENTIAL_EXTRA_RRECOMMENDS} \
    "

