################################################################################
#                                                                              #
# Author: Andrei Mironenko <andrei.mironenkoo@paralleldynamic.com>             #
#                                                                              #
# Copyright(C) 2015 Parallel Dynamic Ltd.                                      #
# This file is licensed under the terms of the GNU General Public License      #
# version 2. This program  is licensed "as is" without any warranty of any     #
# kind, whether express or implied.                                            #
################################################################################
# In OE each package is given 
#  PV - pacakge version
#  PR - package release 
# Where PV is a primary number and PR is auxilarily.
# In our case we use 
#  PV equals to the git release number and it's primary
#  PR equals to the number of commits since the last release PR.
PV = "${PRODUCT_RELEASE}"
PR="0"

#Arago inhereted inclusions
require ${OEBASE}/arago/recipes/images/arago-image.inc 

# Product image definition
require ${OEBASE}/pd-products/${PRODUCT}/image/system-image.inc 


###############################################################################
#  IMAGE TASK                                                                 #    
###############################################################################
IMAGE_INSTALL += "               \
    task-system-image            \
    "

export IMAGE_BASENAME = "${PRODUCT}-image.${PRODUCT_RELEASE}"