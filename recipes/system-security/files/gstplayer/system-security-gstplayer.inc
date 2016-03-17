do_install_append () {
  :
}
#FILES_${PN} = "/home/root/.ssh"
#INSANE_SKIP_${PN} = True


do_deploy () {

   :
}

do_deploy[dirs] = "${S}"
addtask deploy before do_package_stage after do_compile
