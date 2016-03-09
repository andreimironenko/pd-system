# Check the defconfig file and see if it points to an in kernel
# defconfig that should be used, or if it is a complete config file

addtask setup_defconfig before do_configure after do_patch
do_setup_defconfig() {
    # Always copy the defconfig file to .config to keep consistency
    # between the case where there is a real config and the in kernel
    # tree config
    oe_runmake distclean
    cp ${OEBASE}/pd-system/recipes/linux/${PN}-${KVER}-${PSPREL}/${MACHINE}/defconfig ${S}/.config
}

do_configure() {
    oe_runmake oldconfig
}
