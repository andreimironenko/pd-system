DESCRIPTION = "libGLES for the omap3"
LICENSE = "TI Proprietary"

PR = "r29"

COMPATIBLE_MACHINE = "(omap3|ti814x|ti816x|ti33x|ti811x)"

DEPENDS = "virtual/libx11 libxau libxdmcp"

PROVIDES += "virtual/egl"

SRCREV = "graphics-sdk_${PV}"
BRANCH = "master"

S = "${WORKDIR}/git"

EXTRA_SRC_URI ="\
		   file://${OEBASE}/arago/recipes/powervr-drivers/${PN}/cputype \
		   file://${OEBASE}/arago/recipes/powervr-drivers/${PN}/rc.pvr \
		   file://${OEBASE}/arago/recipes/powervr-drivers/${PN}/sample.desktop \
		   file://${OEBASE}/arago/recipes/powervr-drivers/${PN}/99-bufferclass.rules \
"
#file://${OEBASE}/arago/recipes/powervr-drivers/${PN}/0001-Added-sdk-make-install-file-to-graphics-sdk.patch \

SRC_URI = "git://${GITSERVER}/${GITBASE}/graphics-sdk.git;protocol=git;branch=${BRANCH}"
SRC_URI += ${EXTRA_SRC_URI}

# For accessing SUPPORT_XORG value
require powervr.inc

BINLOCATION ?= "${S}/gfx_rel"
ES2LOCATION ?= "${S}/gfx_rel_es2.x"
ES3LOCATION ?= "${S}/gfx_rel_es3.x"
ES5LOCATION ?= "${S}/gfx_rel_es5.x"
ES6LOCATION ?= "${S}/gfx_rel_es6.x"
ES8LOCATION ?= "${S}/gfx_rel_es8.x"

LIBGLESWINDOWSYSTEM ?= "libpvrPVR2D_FRONTWSEGL.so.1"

export SUPPORT_XORG

do_configure() {
	# Attempt to fix up the worst offenders for file permissions
	for i in $(find ${S} -name "*.h") $(find ${S} -name "*.c") $(find ${S} -name "Make*") ; do
		chmod 0644 $i
	done

	cp ${S}/targetfs/XSGX/lib/libdrm.so* ${STAGING_DIR_TARGET}${libdir}

	# Change PVR server's user mode library to point to DRI
		for drifile in $(find ${S} -name "libsrv_um_dri.so"); do
		if [ "$drifile" != "" ]
		then
			dir=$(dirname ${drifile})
			if [ "$SUPPORT_XORG" = "1" ]
			then
			mv ${dir}/libsrv_um_dri.so ${dir}/libsrv_um.so
			else
			rm -rf ${dir}/libsrv_um_dri.so
			fi
		fi
		done

	# Attempt to create proper library softlinks
	for sofile in $(find ${S} -name "lib*Open*.so") $(find ${S} -name "lib*srv*.so") $(find ${S} -name "lib*gl*.so") $(find ${S} -name "libpvr*.so") $(find ${S} -name "lib*GL*.so"); do
		if [ "$(readlink -n ${sofile})" = "" ] ; then
			mv $sofile ${sofile}.${IMGPV}
			ln -sf $(basename ${sofile}.${IMGPV}) ${sofile}
			ln -sf $(basename ${sofile}.${IMGPV}) ${sofile}$(echo ${IMGPV} | awk -F. '{print "." $1}')
			ln -sf $(basename ${sofile}.${IMGPV}) ${sofile}$(echo ${IMGPV} | awk -F. '{print "." $1 "." $2}')
		fi
	done

	# Due to recursive make PLAT_* isn't always passed down correctly, so use sed to fix those
	for mak in $(find ${S} -name "*.mak") ; do
		sed -i -e s:arm-none-linux-gnueabi-:${TARGET_PREFIX}:g $mak
	done

	# clear out old stuff
	find Binaries/ | xargs rm -f || true
}

# Force in GNU_HASH and paths to libs
TARGET_CC_ARCH += " ${TARGET_LINK_HASH_STYLE} -Wl,-rpath-link,${BINLOCATION} -L${BINLOCATION} \
-L${STAGING_DIR_TARGET}${libdir} -Wl,-rpath-link,${STAGING_DIR_TARGET}${libdir}"
PARALLEL_MAKE = ""

PLATFORM ?= "LinuxOMAP3"

do_compile() {
 :
}

do_install () {
	install -d ${D}${libdir}
	cp -pPR ${BINLOCATION}/*.so* ${D}${libdir}
	install -m 0644 ${BINLOCATION}/*.a ${D}${libdir}

	install -d ${D}${bindir}/
	install -m 0755 ${WORKDIR}/cputype ${D}${bindir}/

	install -m 0755 ${BINLOCATION}/*_test ${D}${bindir}/
	install -m 0755 ${BINLOCATION}/gl* ${D}${bindir}/
	install -m 0755 ${BINLOCATION}/p[dv]* ${D}${bindir}/
	install -m 0755 ${BINLOCATION}/xgles1test1 ${D}${bindir}/

	install -m 0755 ${BINLOCATION}/freedesktop/kdrive/usr/X11R6_SGX/bin/Xsgx ${D}${bindir}/|| true

	install -d ${D}${includedir}
	cp -pPR ${S}/GFX_Linux_KM/include4 ${D}${includedir}/
	cp -pPR ${S}/GFX_Linux_KM/services4 ${D}${includedir}/

	cp -pPr ${S}/include/*.h ${D}${includedir} || true
	cp -pPr ${S}/include/wsegl/*.h ${D}${includedir} || true
	cp -pPr ${S}/include/pvr2d/*.h ${D}${includedir} || true
	cp -pPr ${S}/include/OGLES/GLES ${D}${includedir}/ || true

	install -d ${D}${sysconfdir}/init.d/
	if [ "$SUPPORT_XORG" = "0" ]; then
	cp -pP ${WORKDIR}/rc.pvr ${D}${sysconfdir}/init.d/pvr-init
	fi
	if [ "$SUPPORT_XORG" = "1" ]; then
	cp -pPR ${S}/targetfs/XSGX ${D}/usr/local
	cp -pP ${WORKDIR}/rc_dri.pvr ${D}${sysconfdir}/init.d/pvr-init
	fi

	install -d ${D}${sysconfdir}
	echo "[default]" > ${D}${sysconfdir}/powervr.ini
	echo "WindowSystem=${LIBGLESWINDOWSYSTEM}" >> ${D}${sysconfdir}/powervr.ini

	# The ES2.x, ES3.x, ES5.x and ES6.x CPUs have different SGX hardware, so we need to install multiple sets of userspace

	install -d ${D}${libdir}/ES6.0
	install -d ${D}${libdir}/ES5.0
	install -d ${D}${libdir}/ES3.0
	install -d ${D}${libdir}/ES2.0
	install -d ${D}${libdir}/ES8.0

	install -d ${D}${bindir}/ES6.0
	install -d ${D}${bindir}/ES5.0
	install -d ${D}${bindir}/ES3.0
	install -d ${D}${bindir}/ES2.0
	install -d ${D}${bindir}/ES8.0


    if [ -e ${ES2LOCATION} ]
    then
        cp -pPR ${ES2LOCATION}/lib*${IMGPV} ${D}${libdir}/ES2.0/
        cp ${ES2LOCATION}/p[dv]* ${D}${bindir}/ES2.0/
    fi

    if [ -e ${ES3LOCATION} ]
    then
        cp -pPR ${ES3LOCATION}/lib*${IMGPV} ${D}${libdir}/ES3.0/
        cp ${ES3LOCATION}/p[dv]* ${D}${bindir}/ES3.0/
    fi

	if [ -e ${ES5LOCATION} ] ; then
		cp -pPR ${ES5LOCATION}/lib*${IMGPV} ${D}${libdir}/ES5.0/
		cp ${ES5LOCATION}/p[dv]* ${D}${bindir}/ES5.0/
	fi

	if [ -e ${ES6LOCATION} ] ; then
		cp -pPR ${ES6LOCATION}/lib*${IMGPV} ${D}${libdir}/ES6.0/
		cp ${ES6LOCATION}/p[dv]* ${D}${bindir}/ES6.0/
	fi

	if [ -e ${ES8LOCATION} ] ; then
		cp -pPR ${ES8LOCATION}/lib*${IMGPV} ${D}${libdir}/ES8.0/
		cp ${ES8LOCATION}/p[dv]* ${D}${bindir}/ES8.0/
	fi

	rm ${D}${bindir}/ES*/*.h ${D}${bindir}/ES*/pdsasm ${D}${bindir}/pdsasm -f || true

	
	# Delete objects and linker scripts hidden between the headers
	find ${D} -name "*.o" -delete
	find ${D} -name "*.o.cmd" -delete

	install -d ${D}${sysconfdir}/udev/rules.d
	install -m 0644 ${WORKDIR}/99-bufferclass.rules ${D}${sysconfdir}/udev/rules.d/

}

PACKAGES =+ "${PN}-rawdemos \
             ${PN}-x11demos \
             ${PN}-rawtrainingcourses \
             ${PN}-x11trainingcourses \
"

PACKAGES += "xserver-kdrive-powervrsgx \
             ${PN}-tests "

PACKAGES =+ "${PN}-blitwsegl ${PN}-flipwsegl ${PN}-frontwsegl ${PN}-linuxfbwsegl ${PN}-x11wsegl ${PN}-driwsegl"

FILES_${PN}-blitwsegl = "${libdir}/libpvrPVR2D_BLITWSEGL.so.* ${libdir}/*/libpvrPVR2D_BLITWSEGL.so.*"
FILES_${PN}-flipwsegl = "${libdir}/libpvrPVR2D_FLIPWSEGL.so.* ${libdir}/*/libpvrPVR2D_FLIPWSEGL.so.*"
FILES_${PN}-frontwsegl = "${libdir}/libpvrPVR2D_FRONTWSEGL.so.* ${libdir}/*/libpvrPVR2D_FRONTWSEGL.so.*"
FILES_${PN}-linuxfbwsegl = "${libdir}/libpvrPVR2D_LINUXFBWSEGL.so.* ${libdir}/*/libpvrPVR2D_LINUXFBWSEGL.so.*"
FILES_${PN}-x11wsegl = "${libdir}/libpvrPVR2D_X11WSEGL.so* ${libdir}/*/libpvrPVR2D_X11WSEGL.so*"
FILES_${PN}-driwsegl = "${libdir}/libpvrPVR2D_DRIWSEGL.so* ${libdir}/*/libpvrPVR2D_DRIWSEGL.so*"
CONFFILES_${PN} = "${sysconfdir}/powervr.ini"

FILES_${PN} = "${sysconfdir} ${libdir}/lib*.so.* ${libdir}/ES*/* ${bindir}/pvrsrvinit ${bindir}/cputype ${bindir}/*/*"
FILES_xserver-kdrive-powervrsgx = "${bindir}/Xsgx"
FILES_${PN}-tests = "${bindir}/*"
FILES_${PN}-dbg = "${libdir}/.debug/* ${bindir}/.debug/* \
                   ${libdir}/ES*/.debug ${bindir}/*/.debug\
                   ${bindir}/SGX/demos/*/.debug/* \
                   ${bindir}/SGX/trainingcourses/*/.debug/* \
	"

FILES_${PN}-rawdemos = "${bindir}/SGX/demos/Raw/*"
FILES_${PN}-x11demos = "${bindir}/SGX/demos/X11/* ${prefix}/share/applications "
RRECOMMENDS_${PN}-x11demos = "${PN}-driwsegl"

FILES_${PN}-rawtrainingcourses = "${bindir}/SGX/trainingcourses/Raw/*"
FILES_${PN}-x11trainingcourses = "${bindir}/SGX/trainingcourses/X11/*"
RRECOMMENDS_${PN}-x11trainingcourses = "${PN}-driwsegl"

# The libs need the kernel-modules
RRECOMMENDS_${PN} = "omap3-sgx-modules"

# The initscript calls fbset, cputype calls devmem2
RDEPENDS_${PN} += "fbset devmem2"

#HACK! These are binaries, so we can't guarantee that LDFLAGS match :(
INSANE_SKIP_${PN} = True
INSANE_SKIP_${PN}-blitwsegl = True
INSANE_SKIP_${PN}-flipwsegl = True
INSANE_SKIP_${PN}-frontwsegl = True
INSANE_SKIP_${PN}-linuxfbwsegl = True
INSANE_SKIP_${PN}-x11wsegl = True
INSANE_SKIP_${PN}-driwsegl = True
INSANE_SKIP_${PN}-tests = True
INSANE_SKIP_xserver-kdrive-powervrsgx = True

# Quality control is really poor on these SDKs, so hack around the latest madness:
FILES_${PN} += "${libdir}/*.so "
FILES_${PN}-dev = "${includedir}"

inherit update-rc.d

INITSCRIPT_NAME = "pvr-init"
INITSCRIPT_PARAMS = "start 30 5 2 . stop 05 0 1 6 ."

# Append to update-rc.d postinst
pkg_postinst_${PN}_append() {
rm -f /etc/powervr-esrev

ln -sf /usr/lib/libXdmcp.so.6.0.0 /usr/lib/libXdmcp.so.0
ln -sf /usr/lib/libXau.so.6.0.0 /usr/lib/libXau.so.0

}
