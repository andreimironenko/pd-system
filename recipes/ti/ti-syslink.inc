require ${OEBASE}/arago/recipes/ti/ti-syslink.inc

COMPATIBLE_MACHINE = "(dm814x-z3|dm814x-evm)"

SRCREV = "syslink_${PV}"
BRANCH = "master"

S = "${WORKDIR}/git"
SRC_URI = "git://${GITSERVER}/ti/syslink.git;protocol=git;branch=${BRANCH}"

do_install_append_dm814x-z3 () {
    install -d ${D}/${installdir}/syslink-examples/TI814X/helloworld
    install ${D}/usr/share/ti/examples/ex01_helloworld/release/* ${D}/${installdir}/syslink-examples/TI814X/helloworld
    install -d ${D}/${installdir}/syslink-examples/TI814X/messageq
    install ${D}/usr/share/ti/examples/ex02_messageq/release/* ${D}/${installdir}/syslink-examples/TI814X/messageq
    install -d ${D}/${installdir}/syslink-examples/TI814X/notify
    install ${D}/usr/share/ti/examples/ex03_notify/release/* ${D}/${installdir}/syslink-examples/TI814X/notify
    install -d ${D}/${installdir}/syslink-examples/TI814X/sharedregion
    install ${D}/usr/share/ti/examples/ex04_sharedregion/release/* ${D}/${installdir}/syslink-examples/TI814X/sharedregion
    install -d ${D}/${installdir}/syslink-examples/TI814X/heapbufmp 
    install ${D}/usr/share/ti/examples/ex05_heapbufmp/release/* ${D}/${installdir}/syslink-examples/TI814X/heapbufmp
    install -d ${D}/${installdir}/syslink-examples/TI814X/listmp
    install ${D}/usr/share/ti/examples/ex06_listmp/release/* ${D}/${installdir}/syslink-examples/TI814X/listmp
    install -d ${D}/${installdir}/syslink-examples/TI814X/gatemp
    install ${D}/usr/share/ti/examples/ex07_gatemp/release/* ${D}/${installdir}/syslink-examples/TI814X/gatemp
    install -d ${D}/${installdir}/syslink-examples/TI814X/ringio
    install ${D}/usr/share/ti/examples/ex08_ringio/release/* ${D}/${installdir}/syslink-examples/TI814X/ringio
  }

  
do_install_append_dm814x-stib () {
    install -d ${D}/${installdir}/syslink-examples/TI814X/helloworld
    install ${D}/usr/share/ti/examples/ex01_helloworld/release/* ${D}/${installdir}/syslink-examples/TI814X/helloworld
    install -d ${D}/${installdir}/syslink-examples/TI814X/messageq
    install ${D}/usr/share/ti/examples/ex02_messageq/release/* ${D}/${installdir}/syslink-examples/TI814X/messageq
    install -d ${D}/${installdir}/syslink-examples/TI814X/notify
    install ${D}/usr/share/ti/examples/ex03_notify/release/* ${D}/${installdir}/syslink-examples/TI814X/notify
    install -d ${D}/${installdir}/syslink-examples/TI814X/sharedregion
    install ${D}/usr/share/ti/examples/ex04_sharedregion/release/* ${D}/${installdir}/syslink-examples/TI814X/sharedregion
    install -d ${D}/${installdir}/syslink-examples/TI814X/heapbufmp 
    install ${D}/usr/share/ti/examples/ex05_heapbufmp/release/* ${D}/${installdir}/syslink-examples/TI814X/heapbufmp
    install -d ${D}/${installdir}/syslink-examples/TI814X/listmp
    install ${D}/usr/share/ti/examples/ex06_listmp/release/* ${D}/${installdir}/syslink-examples/TI814X/listmp
    install -d ${D}/${installdir}/syslink-examples/TI814X/gatemp
    install ${D}/usr/share/ti/examples/ex07_gatemp/release/* ${D}/${installdir}/syslink-examples/TI814X/gatemp
    install -d ${D}/${installdir}/syslink-examples/TI814X/ringio
    install ${D}/usr/share/ti/examples/ex08_ringio/release/* ${D}/${installdir}/syslink-examples/TI814X/ringio
  }
  