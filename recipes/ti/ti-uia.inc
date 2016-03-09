require ${OEBASE}/arago/recipes/ti/ti-uia.inc

PVExtra = ""

COMPATIBLE_MACHINE = "(dm814x-z3|dm814x-evm)"

SRCREV = "uia_${PV}"
BRANCH = "master"

SRC_URI = "git://${GITSERVER}/ti/uia.git;protocol=git;branch=${BRANCH} \
           file://sdk.mk \
           file://patches \
"

S = "${WORKDIR}/git"

RANLIB = "${TOOLCHAIN_LONGNAME}-ranlib"

do_prepsources() {
    cp ${WORKDIR}/sdk.mk ${S}
}
addtask prepsources after do_unpack before do_patch

do_patch() {
 quilt push 01-uia-makefile.patch
 quilt push 02-uia-lib-makefile.patch
}

INSANE_SKIP_${PN} = True
