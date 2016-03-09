
DESCRIPTION = "${PRODUCT} image task"
LICENSE = "MIT"
PV = "${PRODUCT_RELEASE}"
PR = "r0"

inherit task

require ${OEBASE}/pd-system/recipes/tasks/inc/task-image.inc
require ${OEBASE}/pd-products/${PRODUCT}/${RELDIR}/packages.inc
require ${OEBASE}/pd-products/${PRODUCT}/${RELDIR}/libs.inc

# Runtime dependencies 
RDEPENDS_${PN} =                            "\
      ${TASK_COMMON_RDEPENDS}        \
      ${TASK_PRODUCT}                \
      ${TASK_PRODUCT_LIBS}           \
      "
# Buildtime dependencies 
DEPENDS_${PN} =                            "\
      ${TASK_COMMON_DEPENDS}        \
      "
