# Software update utility package
DESCRIPTION = "System software update utilities package"
HOMEPAGE = "http://www.paralleldynamic.com"
LICENSE = "MIT"

inherit base 

#DEPENDS = ""

LICENSE = "MIT"

PR = "r0"
PE = "0"

COMPATIBLE_MACHINE = "(dm814x-z3|dm814x-evm|dm365-evm)" 

PACKAGES="${PN}"
PACKAGE_ARCH = "${MACHINE_ARCH}"

BRANCH = "master"
SRCREV = "${PV}"

SRC_URI = "git://${GITSERVER}/oe/packages/system-update.git;protocol=git;branch=${BRANCH} \
           file://product/${PRODUCT} \
           file://machine/${MACHINE} \
"

S = "${WORKDIR}/git"



do_configure () {
  :
}
 
do_compile () {
  :
}

do_install () {
    install -d ${D}${sysconfdir}/init.d
    
   #Generate update.conf 
   install -m 0755 ${S}/update.sh    ${D}${sysconfdir}/init.d/
 }


 
do_deploy () {
  :
}

do_deploy[dirs]="${S}"
addtask deploy before do_package_stage after do_compile


FILES_${PN}="${sysconfdir}/init.d/update.sh"
INSANE_SKIP_${PN} = True

require ${FILE_DIRNAME}/files/product/${PRODUCT}/system-update-${PRODUCT}.inc

