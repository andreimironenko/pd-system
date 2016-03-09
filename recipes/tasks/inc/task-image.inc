################################################################################
# Common/generic packages                                                      #
#                                                                              #
# Author: Andrei Mironenko <andrei.mironenko@paralleldynamic.com>              #
#                                                                              #
# Copyright(C) 2015 Parallel Dynamic Ltd.                                      #
# This file is licensed under the terms of the GNU General Public License      #
# version 2. This program  is licensed "as is" without any warranty of any     # 
# kind, whether express or implied.                                            #
################################################################################

export TASK_COMMON_RDEPENDS = 		 "\
        system-configs                \
        system-configs-${PRODUCT}     \
        system-security               \
        system-update                 \
        system-update-${PRODUCT}      \
        system-product-${PRODUCT}     \
        system-product-${PRODUCT}-configs \
        libltdl                       \
        coreutils                     \
        build-scripts                 \
 "
 
 
export TASK_COMMON_DEPENDS = "\
        build-scripts         \
"
