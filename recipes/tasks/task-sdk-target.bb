################################################################################
# SDK target software task definition                                          #
#                                                                              #
# Author: Andrei Mironenko <andrei.mironenko@paralleldynamic.com>              #
#                                                                              #
# Copyright(C) 2015 Parallel Dynamic Ltd.                                      #
# This file is licensed under the terms of the GNU General Public License      #
# version 2. This program  is licensed "as is" without any warranty of any     #
# kind, whether express or implied.                                            #
################################################################################

#Citate from "Bitbake user manual":
#"...
# Your SDK should provide your user with header files and libraries he will 
# need when doing application development. In OpenEmbedded the ${PN}-dev is 
# providing the header files, pkg-config files and symbolic links to libraries 
# to allow using the library. The SDK should install these development packages
# to the SDK.
#..."

DESCRIPTION = "${PRODUCT} SDK, release ${PRODUCT_RELEASE} target packages"
ALLOW_EMPTY = "1"
PR = "${PRODUCT}.${PRODUCT_RELEASE}"

PACKAGES = "${PN}"

require ${OEBASE}/pd-system/recipes/tasks/inc/task-glibc-sdk.inc
require ${OEBASE}/pd-products/${PRODUCT}/meta/sdk-target.inc
require ${OEBASE}/pd-products/${PRODUCT}/rel/libs.inc

#Include the dependency from the package lists
RDEPENDS_${PN} =           "\
${TASK_GLIBC_DEV}   \
${TASK_PRODUCT_LIBS} \
"