DESCRIPTION = "Davinci Multimedia Application Interface (DMAI) for TI ARM/DSP processors"
HOMEPAGE = "https://gforge.ti.com/gf/project/dmai/"
SECTION = "multimedia"
LICENSE = "BSD"

# TODO :: 

require ${OEBASE}/arago/recipes/ti/ti-paths.inc
require ${OEBASE}/arago/recipes/ti/ti-staging.inc

PROVIDES += "ti-dmai-apps"
PE = "1"


SRC_URI = "git://${GITSERVER}/ti-dm365/dmai.git;protocol=git;branch=${BRANCH} \
	    file://doxygen_templates.tar.gz \
        file://arago-tdox \
	"
S = "${WORKDIR}/git"

DEPENDS = "virtual/kernel alsa-lib ti-framework-components ti-codec-engine ti-xdctools"
DEPENDS += "ti-codecs-dm365"

# Define DMAI build time variables
DMAIPLATFORM  = "dm365_al"

GPPOS  = "LINUX_GCC"

DSPSUFFIX = "x64p"

# This is needed for dm355/dm365 targets in order to find ti.sdo.codecs.g711
# TODO :: review - should we just pass this in do_compile?
USER_XDC_PATH = "${CE_INSTALL_DIR}/examples"

PARALLEL_MAKE = ""

do_prepsources() {
    # run the release steps - this will delete .svn file and run doxygen to
    # generate proper documentation of the source etc.
    #find ${WORKDIR}/${DMAIBRANCH} -name .svn -type d | xargs rm -rf
    cp -pPrf ${WORKDIR}/doxygen_templates ${S}/
    cp -pPrf ${WORKDIR}/arago-tdox ${S}/tdox
    #chmod a+x ${WORKDIR}/${DMAIBRANCH}/davinci_multimedia_application_interface/release.sh
    chmod a+x ${S}/tdox
    #sed -i 's|tdox|./tdox|g' ${WORKDIR}/${DMAIBRANCH}/davinci_multimedia_application_interface/release.sh
    #(cd ${WORKDIR}/${DMAIBRANCH}/davinci_multimedia_application_interface; ./release.sh ${PV})
    #rm -rf ${WORKDIR}/${DMAIBRANCH}/davinci_multimedia_application_interface/dmai_${PV}/wince_pb
}

# run prepare sources before do_patch to ensure that sourceipk picks the right sources.
addtask prepsources after do_unpack before do_patch

do_compile () {
    # TODO :: Why do we do this?
    unset DMAI_INSTALL_DIR
    cd ${S}

    make XDC_INSTALL_DIR="${XDC_INSTALL_DIR}" PLATFORM="${DMAIPLATFORM}" clean

    #for dir in ${S}; do
    #    cd $dir
    cd ${S}
        #  TODO: Figure out how to pass the alsa require location, currently 
        #  LINUXLIBS_INSTALL_DIR is hard-coded for armv5te
        make \
            CE_INSTALL_DIR="${CE_INSTALL_DIR}" \
            CODEC_INSTALL_DIR="${CODEC_INSTALL_DIR}" \
            FC_INSTALL_DIR="${FC_INSTALL_DIR}" \
            LINUXKERNEL_INSTALL_DIR="${STAGING_KERNEL_DIR}" \
            XDC_INSTALL_DIR="${XDC_INSTALL_DIR}" \
            CODEGEN_INSTALL_DIR="${CODEGEN_INSTALL_DIR}" \
            BIOS_INSTALL_DIR="${BIOS_INSTALL_DIR}"\
            LINUXLIBS_INSTALL_DIR="${STAGING_DIR_TARGET}/usr" \
            USER_XDC_PATH="${USER_XDC_PATH}" \
            CROSS_COMPILE="${TOOLCHAIN_PATH}/bin/${TARGET_PREFIX}" \
            VERBOSE="true" \
            XDAIS_INSTALL_DIR="${XDAIS_INSTALL_DIR}" \
            LINK_INSTALL_DIR="${LINK_INSTALL_DIR}" \
            CMEM_INSTALL_DIR="${CMEM_INSTALL_DIR}" \
            LPM_INSTALL_DIR="${LPM_INSTALL_DIR}" \	
            MVTOOL_PREFIX="${TARGET_PREFIX}" \
	        C6ACCEL_INSTALL_DIR="${C6ACCEL_INSTALL_DIR}" \
            PLATFORM="${DMAIPLATFORM}" 
	#done
}

do_install () {

    # TODO :: Why do we do this?
    unset DMAI_INSTALL_DIR

    install -d ${D}/${installdir}/ti-dmai-apps
    cd ${S}
    make PLATFORM="${DMAIPLATFORM}" EXEC_DIR=${D}/${installdir}/ti-dmai-apps install 

    install -d ${D}${DMAI_INSTALL_DIR_RECIPE}
    cp -pPrf ${S}/* ${D}${DMAI_INSTALL_DIR_RECIPE}
}

PACKAGES += "ti-dmai-apps"
FILES_ti-dmai-apps = "${installdir}/ti-dmai-apps/*"
INSANE_SKIP_ti-dmai-apps = True

RDEPENDS_ti-dmai-apps  += "ti-codecs-dm365 ti-cmem-module ti-dm365mm-module ti-edma-module ti-irq-module ti-tisdk-loadmodule"

pkg_postinst_ti-dmai-apps () {
	ln -sf ${installdir}/ti-codecs-server/*.${DSPSUFFIX} ${installdir}/ti-dmai-apps/
}

