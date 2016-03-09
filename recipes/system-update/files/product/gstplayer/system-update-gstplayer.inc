
do_install_prepend () {
    install -d ${D}/usr/share/update/log
    install -d ${D}${sysconfdir}/init.d
    
    install -m 0755 ${S}/product/${PRODUCT}/pre-update.sh   ${D}${sysconfdir}/init.d/
    install -m 0755 ${S}/product/${PRODUCT}/post-update.sh  ${D}${sysconfdir}/init.d/
    install -m 0755 ${S}/product/${PRODUCT}/pre-post-update.conf  ${D}${sysconfdir}/
    
    echo "#Update source possible values: http, ftp or local"> ${D}${sysconfdir}/update.conf
    echo "#export UPDATESRC=\"ftp\""                        >> ${D}${sysconfdir}/update.conf
    echo "#export UPDATESRC=\"http\""                       >> ${D}${sysconfdir}/update.conf
    echo "export UPDATESRC=\"local\""                       >> ${D}${sysconfdir}/update.conf
    echo "export HTTP_SERVER=\"$HTTP_SERVER\""              >> ${D}${sysconfdir}/update.conf
    echo "export FTP_SERVER=\"$FTP_SERVER\""                >> ${D}${sysconfdir}/update.conf
    echo "export LOCAL_BASE_PATH=\"/media/update\""         >> ${D}${sysconfdir}/update.conf
    echo "export HTTP_BASE_PATH=\"$HTTP_BASE_PATH\""        >> ${D}${sysconfdir}/update.conf
    echo "export FTP_BASE_PATH=\"$FTP_BASE_PATH\""          >> ${D}${sysconfdir}/update.conf
    echo "export UPDATEDIR=\"/usr/share/update\""        	>> ${D}${sysconfdir}/update.conf 
    echo "export TMPDIR=\"\$UPDATEDIR/tmp\""	                >> ${D}${sysconfdir}/update.conf
    echo "export LOGDIR=\"\$TMPDIR/log\""                   >> ${D}${sysconfdir}/update.conf
    echo "export LOGFILE=\"\$LOGDIR/update.log\""       >> ${D}${sysconfdir}/update.conf
   	echo "export UPDATE_RESULT_FILE=\"\$LOGDIR/update.result.flag\""   >> ${D}${sysconfdir}/update.conf
   	echo "export UPDATE_RESULT_MSG=\"\$LOGDIR/update.result.msg\""     >> ${D}${sysconfdir}/update.conf
    echo "export UPDATE_READY_FILE=\"\$LOGDIR/update.ready.flag\""     >> ${D}${sysconfdir}/update.conf
    echo "export PRE_UPDATE_RESULT_FILE=\"\$LOGDIR/pre.update.result.flag\""   >> ${D}${sysconfdir}/update.conf
   	echo "export PRE_UPDATE_RESULT_MSG=\"\$LOGDIR/pre.update.result.msg\""     >> ${D}${sysconfdir}/update.conf
   	echo "export POST_UPDATE_RESULT_FILE=\"\$LOGDIR/post.update.result.flag\""   >> ${D}${sysconfdir}/update.conf
   	echo "export POST_UPDATE_RESULT_MSG=\"\$LOGDIR/post.update.result.msg\""     >> ${D}${sysconfdir}/update.conf
    
    # As after the reflashing the system update.result.flag is not created
    # We need to create it during build time and write 0, to indicate success
    #echo 0 > ${S}/product/${PRODUCT}/update.result.flag
    #install -m 0755 ${S}/product/${PRODUCT}/update.result.flag ${D}/usr/share/update/log
}


#Create a product sub-package
PACKAGES += "${PN}-gstplayer"
FILES_${PN}-gstplayer = "${sysconfdir}/update.conf" 
FILES_${PN}-gstplayer += "${sysconfdir}/pre-post-update.conf"
FILES_${PN}-gstplayer += "${sysconfdir}/init.d/pre-update.sh"
FILES_${PN}-gstplayer += "${sysconfdir}/init.d/post-update.sh"

CONFFILES_${PN}-gstplayer =              "\
    ${sysconfdir}/update.conf             \
    ${sysconfdir}/pre-post-update.conf    \
"
