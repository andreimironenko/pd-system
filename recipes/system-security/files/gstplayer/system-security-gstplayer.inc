do_install_append () {
    install -d ${D}/home/root/.ssh
    
    install ${S}/id_rsa.db ${D}/home/root/.ssh/
    chmod 0600 ${D}/home/root/.ssh/id_rsa.db
}
FILES_${PN} = "/home/root/.ssh"
INSANE_SKIP_${PN} = True


do_deploy () {

   :
}

do_deploy[dirs] = "${S}"
addtask deploy before do_package_stage after do_compile
