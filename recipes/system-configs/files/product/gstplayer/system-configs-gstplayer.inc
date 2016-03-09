# Configuration files package
do_install_prepend() {

    install -d ${D}${sysconfdir}
    install -d ${D}/usr/share/scripts
    install -d ${D}/home/root
    
    install -m 0755 ${S}/product/${PRODUCT}/mountnfs.conf   ${D}/${sysconfdir}/
    install -m 0755 ${S}/mountnfs.sh                        ${D}/usr/share/scripts/
    
    if [ ${MACHINE} = "dm814x-z3" ] ; then
        install -m 0755 ${S}/machine/${MACHINE}/display_resolution.conf   ${D}${sysconfdir}/
        install -m 0755 ${S}/machine/${MACHINE}/gstplay.sh   ${D}/home/root/
        install -m 0755 ${S}/machine/${MACHINE}/rtsplay.sh   ${D}/home/root/
    fi
}

#do_deploy_prepend () {
#    :
# }

PACKAGES += "${PN}-gstplayer"

FILES_${PN}-gstplayer  = "${sysconfdir}/mountnfs.conf"
FILES_${PN}-gstplayer  += "usr/share/scripts/mountnfs.sh"
INSANE_SKIP_${PN}-gstplayer = True

CONFFILES_${PN}-gstplayer =             "\
  ${sysconfdir}/mountnfs.conf            \
"

PACKAGES += "${PN}-${MACHINE}"

FILES_${PN}-dm814x-z3 =  "/home/root/gstplay.sh"
FILES_${PN}-dm814x-z3 += "/home/root/rtsplay.sh" 
FILES_${PN}-dm814x-z3 += "${sysconfdir}/display_resolution.conf"
INSANE_SKIP_${PN}-dm814x-z3 = True

CONFFILES_${PN}-dm814x-z3 =             "\
  ${sysconfdir}/display_resolution.conf  \
"

FILES_${PN}-dm814x-evm =  "/home/root/gstplay.sh"
FILES_${PN}-dm814x-evm += "/home/root/rtsplay.sh"
FILES_${PN}-dm814x-evm += "${sysconfdir}/display_resolution.conf"
INSANE_SKIP_${PN}-dm814x-evm = True

CONFFILES_${PN}-dm814x-evm =             "\
  ${sysconfdir}/display_resolution.conf  \
"