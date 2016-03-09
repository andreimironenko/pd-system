DESCRIPTION = "TI Inter Process Ccommunication (IPC) Mechanisms (for Uni- and Multi- Processor Configurations)"
HOMEPAGE = "http://software-dl.ti.com/dsps/dsps_public_sw/sdo_sb/targetcontent/ipc/index.html"

SECTION = "devel"
LICENSE = "BSD" 

require ${OEBASE}/arago/recipes/ti/ti-paths.inc
require ${OEBASE}/arago/recipes/ti/ti-staging.inc


COMPATIBLE_MACHINE = "(dm814x-z3|dm814x-evm)"

PR = "r4"

PVExtra = ""

SRCREV = "${PN}_${PV}"
BRANCH = "master"

S = "${WORKDIR}/git"

SRC_URI = "git://${GITSERVER}/ti/ipc.git;protocol=git;branch=${BRANCH}"
SRC_URI =+ "file://ipc.pc"

DEPENDS = "ti-sysbios ti-cgt6x ti-xdctools"

do_prepsources() {
    cd ${S}
    ln -sf packages/ti ti 
}
addtask prepsources after do_unpack before do_patch

do_configure() {
    sed -i -e s:@VERSION@:${PV}:g ${WORKDIR}/ipc.pc
    
    cp ${WORKDIR}/ipc.pc ${S}
}

do_install() {
    install -d ${D}${IPC_INSTALL_DIR_RECIPE}
    cp -pPrf ${S}/* ${D}${IPC_INSTALL_DIR_RECIPE}
   
    install -d ${D}/${libdir}/pkgconfig
    install ${S}/ipc.pc ${D}/${libdir}/pkgconfig/
}

FILES_ti-ipc-dev = "${libdir}/*"
