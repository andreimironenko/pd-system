#Citate from "Bitbake user manual":
#..
#List of host utilities which will run on the host. These could include scripts,
#buildsystem software like cmake, or an  emulator like qemu. For this 
#dependencies it is imported that they inherit sdk and by convention end with
# -sdk in the PN
#..

require ${OEBASE}/arago-oe-dev/recipes/tasks/task-sdk-host.bb
DESCRIPTION = "SDK host utilities"
ALLOW_EMPTY = "1"

PR = "${PRODUCT_RELEASE}"

#At the moment we don't have any requirement for additional tools besides those
#listed in task-sdk-host.bb. If there could be a need for this, add the new pa-
#ckage to the list below.
RDEPENDS_${PN} += "\
 ${@base_conditional('TOOLCHAIN_INCLUDE_IN_SDK', '1', 'binutils-cross-sdk gcc-cross-sdk gdb-cross-sdk', '', d)} \
 "
    
