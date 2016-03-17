# Security package includes default RSA key-pairs & customer specific
# keys and some product SSH configuration
DESCRIPTION = "System security package"
HOMEPAGE = "http://www.paralleldynamic.com"
SECTION = "system"
LICENSE = "MIT"

PR = "r0"
PE = "0"

COMPATIBLE_MACHINE = "(dm814x-z3|dm814x-evm|dm365-evm)" 


PACKAGES = "${PN}"
PACKAGE_ARCH = "${MACHINE_ARCH}"

SRC_URI = "git://${GITSERVER}/${GITBASE}/system-security.git;protocol=git;branch=${BRANCH} \
"

BRANCH = "master"
SRCREV = "${PN}_${PV}"

S = "${WORKDIR}/git"
        
        
do_configure () {
  :
}
 
do_compile () {
  :
}

do_install () {
    install -d ${D}/home/root/.ssh
    
    touch ${D}/home/root/.ssh/authorized_keys 
    cat  ${S}/id_rsa.pub >>  ${D}/home/root/.ssh/authorized_keys
    cat  ${S}/customer.id_rsa.pub >>  ${D}/home/root/.ssh/authorized_keys
    chmod 0600 ${D}/home/root/.ssh/authorized_keys
}
FILES_${PN} = "/home/root/.ssh"
INSANE_SKIP_${PN} = True


include ./files/${PRODUCT}/system-security-${PRODUCT}.inc
