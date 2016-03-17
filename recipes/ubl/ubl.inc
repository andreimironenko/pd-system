DESCRIPTION = "TI Booting and Flashing Utilities"
HOMEPAGE = "http://www.ti.com"
SECTION = "bootloaders"
LICENSE = "GPLv2"

DEPENDS = "mtd-utils"

COMPATIBLE_MACHINE = "(dm365-htc|dm365-evm)"
EXTRA_OEMAKE = "CROSSCOMPILE=${TARGET_PREFIX}"

SRC_URI = "git://${GITSERVER}/${GITBASE}/flash-utils-dm365.git;protocol=git;branch=${BRANCH}"

#No configuration is required
do_configure() {
 :
 }
 
do_compile() {
  oe_runmake 
 }

do_install() {
 install -d ${D}/ubl
 install ${S}/DM36x/GNU/ubl/*.bin ${D}/ubl
}

FILES_${PN} = "/ubl"
# no gnu_hash in uboot.bin, by design, so skip QA
INSANE_SKIP_${PN} = True

do_deploy () {
 install -d ${DEPLOY_DIR_IMAGE}/ubl
 install ${S}/DM36x/GNU/ubl/*.bin ${DEPLOY_DIR_IMAGE}/ubl
}

addtask deploy before do_package_stage after do_compile