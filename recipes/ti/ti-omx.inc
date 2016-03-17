DESCRIPTION = "TI OMX Components"
SECTION = "devel"
LICENSE = "BSD"

require ${OEBASE}/arago/recipes/ti/ti-omx.inc


COMPATIBLE_MACHINE = "(dm814x-z3|dm814x-evm)"

SRCREV = "omx_${PV}"
BRANCH = "master"

SRC_URI = "git://${GITSERVER}/${GITBASE}/omx.git;protocol=git;branch=${BRANCH} \
           file://sdk.mk \
           file://patches \
"

S = "${WORKDIR}/git"

#Due to some reasons do_patch is not invoked for this recipe...
do_patch() {
   quilt push 01-omx-cc-fix.patch
}



do_prepsources() {
    cp ${WORKDIR}/sdk.mk ${S}
}

addtask prepsources after do_unpack before do_patch
