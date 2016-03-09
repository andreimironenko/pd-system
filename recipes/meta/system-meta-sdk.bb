################################################################################
# Arago SDK target software task definition                                    #
#                                                                              #
# Author: Andrei Mironenko <andrei.mironenko@paralleldynamic.com>              #
#                                                                              #
# Copyright(C) 2015 Parallel Dynamic Ltd.                                      #
# This file is licensed under the terms of the GNU General Public License      #
# version 2. This program  is licensed "as is" without any warranty of any,    #
# kind whether express or implied.                                             #
################################################################################
require inc/system-sdk.inc

PR = "${PRODUCT_RELEASE}"

TOOLCHAIN_HOST_TASK    = "task-sdk-host"
TOOLCHAIN_TARGET_TASK  = "task-sdk-target"
