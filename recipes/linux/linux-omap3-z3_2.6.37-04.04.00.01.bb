require linux-omap3-z3.inc

COMPATIBLE_MACHINE = "(dm814x-z3|dm814x-stib)"

KVER = "2.6.37"
PSPREL = "04.04.00.01"

SCRIPTS_DIR = "${WORKDIR}"

BRANCH  = "branch.z3.v2.6.37_TI81XXPSP_04.04.00.01.patch2"
SRCREV = "v${KVER}-${PSPREL}"
