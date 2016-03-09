################################################################################
# GLIBC dev version libraries, this file is only used for SDK builds.          #
# It's a generic for all platforms/products and only dependent on toolchain    #
# and target os which is linux...                                              #
#                                                                              #
# Author: Andrei Mironenko <andrei.mironenko@paralleldynamic.com>              #
#                                                                              #
# Copyright(C) 2015 Parallel Dynamic Ltd.                                      #
# This file is licensed under the terms of the GNU General Public License      #
# version 2. This program  is licensed "as is" without any warranty of any     #
# kind, whether express or implied.                                            #
################################################################################
export TASK_GLIBC_DEV  =      "\
    libstdc++-dev              \               
    linux-libc-headers-dev     \      
    libgcc-dev                 \
    virtual-libc-dev           \
"


