# Configuration files package

LICENSE = "MIT"

PR = "r0"
PE = "0"

DEPENDS = "quilt"

COMPATIBLE_MACHINE = "(dm814x-z3|dm814x-evm)" 

PACKAGES="${PN}"
PACKAGE_ARCH = "${MACHINE_ARCH}"

BRANCH = "master"
SRCREV = "${PV}"

SRC_URI = "git://${GITSERVER}/oe/packages/system-configs.git;protocol=git;branch=${BRANCH}"

S = "${WORKDIR}/git"


do_configure () {
  :
}
 
do_compile () {
  :
}

do_install () {
   install -d ${D}/${bindir}
   install -m 0755 ${S}/setconfig.sh    ${D}${bindir}/
   
   ln -sf setconfig.sh ${D}${bindir}/setconfig
 }



do_deploy () {
  :
}

do_deploy[dirs] = "${S}"
addtask deploy before do_package_stage after do_compile

FILES_${PN} = "${bindir}"
INSANE_SKIP_${PN} = True

#CONFFILES_${PN} = " \
#"


require ${FILE_DIRNAME}/files/product/${PRODUCT}/system-configs-${PRODUCT}.inc

