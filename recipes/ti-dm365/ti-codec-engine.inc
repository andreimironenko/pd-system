DESCRIPTION = "Codec Engine for TI ARM/DSP processors"
HOMEPAGE = "http://software-dl.ti.com/dsps/dsps_public_sw/sdo_sb/targetcontent/ce"
SECTION = "devel"
LICENSE = "BSD"

# TODO :: Add Codec Engine Library Rebuild
# TODO :: Add Examples APP_LOCAL build as well?
# TODO :: Check DEPENDS - are the DSP side packages required for ARM-only products?

require ${OEBASE}/arago/recipes/ti/ti-paths.inc
require ${OEBASE}/arago/recipes/ti/ti-staging.inc

PROVIDES += "ti-codec-engine-examples"

PR = "${MACHINE_KERNEL_PR}"
PR_append = "a"
PVExtra = ""

SRC_URI = "git://${GITSERVER}/${GITBASE}/codec-engine-dm365.git;protocol=git;branch=${BRANCH}"

S = "${WORKDIR}/git"

DEPENDS = "ti-framework-components ti-xdais ti-xdctools ti-linuxutils"

# SOC_FAMILY configuration

# Define DEVICES variable
CEEXAMPLESDEVICES      = "DM365"

# Define GPPOS variable
CEEXAMPLESGPPOS        = "LINUX_GCC"

# Define PROGRAM variable
EEXAMPLESPROGRAMS     = "APP_LOCAL"

do_configure() {

    # No way to pass this via ENV?
    sed -i  \
        -e s:arm-none-linux-gnueabi-:${TARGET_PREFIX}:g \
        ${S}/examples/xdcpaths.mak
}

do_prepsources() {

      for i in codecs extensions servers apps ; do
                cd ${S}/examples/ti/sdo/ce/examples/$i
                make DEVICE="${CEEXAMPLESDEVICES}" \
                     GPPOS="${CEEXAMPLESGPPOS}" \
                     PROGRAMS="${CEEXAMPLESPROGRAMS}" \
                     CE_INSTALL_DIR="${S}" \
                     XDC_INSTALL_DIR="${XDC_INSTALL_DIR}" \
                     BIOS_INSTALL_DIR="${SYSBIOS_INSTALL_DIR}" \
                     BIOSUTILS_INSTALL_DIR="${BIOSUTILS_INSTALL_DIR}" \
                     OSAL_INSTALL_DIR="${OSAL_INSTALL_DIR}" \
                     IPC_INSTALL_DIR="${IPC_INSTALL_DIR}" \
                     LINK_INSTALL_DIR="${SYSLINK_INSTALL_DIR}" \
                     XDAIS_INSTALL_DIR="${XDAIS_INSTALL_DIR}" \
                     FC_INSTALL_DIR="${FC_INSTALL_DIR}" \
                     CMEM_INSTALL_DIR="${CMEM_INSTALL_DIR}" \
                     LPM_INSTALL_DIR="${LPM_INSTALL_DIR}" \
                     EDMA3_LLD_INSTALL_DIR="${EDMA3_LLD_INSTALL_DIR}" \
                     CGTOOLS_V5T="${TOOLCHAIN_PATH}" \
                     CC_V5T="bin/${TARGET_PREFIX}gcc" \
                     CGTOOLS_C64P="${CODEGEN_INSTALL_DIR}" \
                     CGTOOLS_C674="${CODEGEN_INSTALL_DIR}" \
                     CGTOOLS_C674ELF="${CODEGEN_INSTALL_DIR}" \
                     ti.targets.elf.C674="${CODEGEN_INSTALL_DIR}" \
                     clean
             # '.make' target was used in CE < 2.26, but its no longer
             # supported in CE >= 2.26. Now we are moved to >=2.26 
             # hence commenting out the .make target.
                     # .make clean
        done
        
}

addtask prepsources after do_configure before do_compile

do_compile () {

       for i in codecs extensions servers apps ; do
                cd ${S}/examples/ti/sdo/ce/examples/$i
                make DEVICE="${CEEXAMPLESDEVICES}" \
                     GPPOS="${CEEXAMPLESGPPOS}" \
                     PROGRAMS="${CEEXAMPLESPROGRAMS}" \
                     CE_INSTALL_DIR="${S}" \
                     XDC_INSTALL_DIR="${XDC_INSTALL_DIR}" \
                     BIOS_INSTALL_DIR="${SYSBIOS_INSTALL_DIR}" \
                     BIOSUTILS_INSTALL_DIR="${BIOSUTILS_INSTALL_DIR}" \
                     OSAL_INSTALL_DIR="${OSAL_INSTALL_DIR}" \
                     IPC_INSTALL_DIR="${IPC_INSTALL_DIR}" \
                     LINK_INSTALL_DIR="${SYSLINK_INSTALL_DIR}" \
                     XDAIS_INSTALL_DIR="${XDAIS_INSTALL_DIR}" \
                     FC_INSTALL_DIR="${FC_INSTALL_DIR}" \
                     CMEM_INSTALL_DIR="${CMEM_INSTALL_DIR}" \
                     LPM_INSTALL_DIR="${LPM_INSTALL_DIR}" \
                     EDMA3_LLD_INSTALL_DIR="${EDMA3_LLD_INSTALL_DIR}" \
                     CGTOOLS_V5T="${TOOLCHAIN_PATH}" \
                     CC_V5T="bin/${TARGET_PREFIX}gcc" \
                     CGTOOLS_C64P="${CODEGEN_INSTALL_DIR}" \
                     CGTOOLS_C674="${CODEGEN_INSTALL_DIR}" \
                     CGTOOLS_C674ELF="${CODEGEN_INSTALL_DIR}" \
                     ti.targets.elf.C674="${CODEGEN_INSTALL_DIR}" \
                     all
        done
}

do_install() {

	install -d ${D}/${installdir}/ti-codec-engine-examples
	if [ -e ${S}/examples/apps/system_files/evm${CEEXAMPLESDEVICES}/loadmodules.sh ]; then
		cp ${S}/examples/apps/system_files/evm${CEEXAMPLESDEVICES}/loadmodules.sh ${D}/${installdir}/ti-codec-engine-examples
	elif [ -e ${WORKDIR}/loadmodules.sh ]; then
		cp ${WORKDIR}/loadmodules.sh ${D}/${installdir}/ti-codec-engine-examples
	fi

	cd ${S}/examples/ti/sdo/ce/examples

	# Install the apps, servers and test data, mirroring the source directory structure
	#  - Put the servers inside the same folder as the executable
	#  - TODO - Check nested dirs (e.g. dualcpu_separateconfig)

        # Put all servers in separate tree.
        for i in $(find . -name "*.${DSPSUFFIX}"); do
                install -d ${D}/${installdir}/ti-codec-engine-examples/servers/`dirname ${i} | cut -f3 -d /`
                install ${i} ${D}/${installdir}/ti-codec-engine-examples/servers/`dirname ${i} | cut -f3 -d /`
        done

	for i in $(find . -name "*.xv5T"); do
		install -d ${D}/${installdir}/ti-codec-engine-examples/`dirname ${i} | cut -f3 -d /`
		install ${i} ${D}/${installdir}/ti-codec-engine-examples/`dirname ${i} | cut -f3 -d /`
	done

	for i in $(find . -name "*.dat"); do
                if [ -e ${D}/${installdir}/ti-codec-engine-examples/`dirname ${i} | cut -f3 -d /` ]; then
	                install ${i} ${D}/${installdir}/ti-codec-engine-examples/`dirname ${i} | cut -f3 -d /`
                fi
        done

	# For each directory, softlink to the app server, except special cases
	cd ${D}/${installdir}/ti-codec-engine-examples
	for i in $(find . -type d | grep -v servers); do
		{
		pwd
		cd ${D}/${installdir}/ti-codec-engine-examples/$i
		if [ $(basename $i) == "audio1_ires" ] ; then 
			ln -s ../servers/audio1_ires/audio1_ires.${DSPSUFFIX}
		elif [ $(basename $i) == "server_api_example" ] ; then
			ln -s ../servers/server_api_example/audio_copy.${DSPSUFFIX}
                elif [ $(basename $i) != "." ] ; then
			ln -s ../servers/all_codecs/all_DSP.${DSPSUFFIX}
		else
			echo Skipping $i
		fi
		}
	done

        # Install/Stage the Source Tree
        install -d ${D}${CE_INSTALL_DIR_RECIPE}
        cp -pPrf ${S}/* ${D}${CE_INSTALL_DIR_RECIPE}
}

PACKAGES += "ti-codec-engine-examples"

RDEPENDS_ti-codec-engine-examples                 = " ti-cmem-module"
RDEPENDS_ti-codec-engine-examples_append_dm6446   = " ti-dsplink-module ti-lpm-module"
RDEPENDS_ti-codec-engine-examples_append_dm6467   = " ti-dsplink-module"
RDEPENDS_ti-codec-engine-examples_append_omap3    = " ti-dsplink-module ti-lpm-module"
RDEPENDS_ti-codec-engine-examples_append_omapl137 = " ti-dsplink-module"
RDEPENDS_ti-codec-engine-examples_append_omapl138 = " ti-dsplink-module"
RDEPENDS_ti-codec-engine-examples_append_ti816x = " ti-syslink-module"
RDEPENDS_ti-codec-engine-examples_append_ti814x = " ti-syslink-module"
FILES_ti-codec-engine-examples = "${installdir}/ti-codec-engine-examples/*"
INSANE_SKIP_ti-codec-engine-examples = True

