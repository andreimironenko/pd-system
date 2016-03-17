require ${OEBASE}/arago/recipes/ti/ti-media-controller-utils.inc

COMPATIBLE_MACHINE = "(dm814x-z3|dm814x-stib)"

SRCREV = "ti-media-controller_${PV}"
BRANCH = "master"

SRC_URI = "git://${GITSERVER}/${GITBASE}/media-controller-utils.git;protocol=git;branch=${BRANCH} \
          file://patches \
          "
S = "${WORKDIR}/git"

#Due to some reasons do_patch is not invoked for this recipe...
do_patch() {
   quilt push 01-media-controller-cc-fix.patch
}

FILES_${PN} += "${installdir}/ti-mcutils-tree/src/mm_host_util/mm_dm81xxbm_512M.bin" 
FILES_${PN} += "${installdir}/ti-mcutils-tree/src/mm_host_util/mm_dm81xxbm.bin" 