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
DESCRIPTION = "HTC specific packages"
LICENSE = "MIT"
PR = "r12"

inherit task

COMPATIBLE_MACHINE = "dm365-htc"

# those ones can be set in machine config to supply packages needed to get machine booting
MACHINE_ESSENTIAL_EXTRA_RDEPENDS ?= ""
MACHINE_ESSENTIAL_EXTRA_RRECOMMENDS ?= ""

# ti-codecs-dm365-server 
MACHINE_DM365_HTC = "\
 ti-dmai \
 ti-xdctools \
 ti-codecs-dm365 \
 ti-framework-components \
 ti-xdais \
 u-boot-davinci-htc \
 kernel                     \
 kernel-image               \
 kernel-modules             \
"

#Failed:
#ti-linuxutils \
#gstreamer-ti  \ 
#ti-dm365mm-module \
 
# minimal set of packages - needed to boot
RDEPENDS_${PN} = "\
      ${MACHINE_DM365_HTC}   \
      ${MACHINE_ESSENTIAL_EXTRA_RDEPENDS} \
    "

RRECOMMENDS_${PN} = "\
    ${MACHINE_ESSENTIAL_EXTRA_RRECOMMENDS} \
    "

