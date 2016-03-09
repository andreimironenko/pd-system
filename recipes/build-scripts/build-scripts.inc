LICENSE = "MIT"

PR = "r0"
PE = "0"

COMPATIBLE_MACHINE = "(dm814x-z3|dm814x-evm|dm365-htc|dm365-evm|dm814x-stib|dm814x-ht5)" 

PACKAGES = "${PN}"
PACKAGE_ARCH = "${MACHINE_ARCH}"

HTC_DEPLOY_DIR = "${DEPLOY_DIR_IMAGE}/htc"
       
SRC_URI = "git://${GITSERVER}/oe/packages/build-scripts.git;protocol=git;branch=${BRANCH} \
"

BRANCH = "master"
SRCREV = "${PN}_${PV}"

S = "${WORKDIR}/git"
        
do_configure () {
  :
}
 
do_compile () {
  :
}

do_install () {
    install -d ${D}${sysconfdir}

    CURDIR=${PWD}
    BUILD_DATE=`date`
    
    cd ${OEBASE}/arago
    ARAGO_VERSION=`git describe`
    
    cd ${OEBASE}/arago-bitbake
    BITBAKE_VERSION=`git describe`
    
    cd ${OEBASE}/arago-oe-dev
    OE_VERSION=`git describe`
    
    cd ${OEBASE}/pd-apps
    APPS_VERSION=`git describe`
    
    cd ${OEBASE}/pd-system
    SYSTEM_VERSION=`git describe`
    
    if [ "${RELDIR}" = "dev" ] ; then
        cd ${OEBASE}/pd-system-dev
        SYSTEM_DEV_VERSION=`git describe`
       
        cd ${OEBASE}/pd-apps-dev
        APPS_DEV_VERSION=`git describe`
    fi
   
    echo "Build Date: $BUILD_DATE" > ${D}${sysconfdir}/build.date
    
    cd ${CURDIR}
    echo "Build Date: $BUILD_DATE" > ${WORKDIR}/product.version
    echo "Product ID: ${PRODUCT}" >> ${WORKDIR}/product.version
    echo "Product release: ${PRODUCT_RELEASE}" >> ${WORKDIR}/product.version
    echo "Machine: ${MACHINE}" >> ${WORKDIR}/product.version
    echo "CPU instruction set: ${FEED_ARCH}" >> ${WORKDIR}/product.version
    echo "Compiler: ${TARGET_SYS}" >> ${WORKDIR}/product.version
    echo "Build purpose: ${BUILD_PURPOSE}" >> ${WORKDIR}/product.version
    echo "Build type: ${RELDIR}" >> ${WORKDIR}/product.version
    echo "" >> ${WORKDIR}/product.version
    
    echo "Versions:" >> ${WORKDIR}/product.version
    echo "arago: ${ARAGO_VERSION}" >> ${WORKDIR}/product.version
    echo "arago-bitbake: ${BITBAKE_VERSION}" >> ${WORKDIR}/product.version
    echo "arago-oe-dev: ${OE_VERSION}" >> ${WORKDIR}/product.version
    echo "pd-apps: ${APPS_VERSION}" >> ${WORKDIR}/product.version
    echo "pd-system: ${SYSTEM_VERSION}" >> ${WORKDIR}/product.version
    if [ "${RELDIR}" = "dev" ] ; then
        echo "pd-system-dev: ${SYSTEM_DEV_VERSION}" >> ${WORKDIR}/product.version
        echo "pd-apps-dev: ${APPS_DEV_VERSION}" >> ${WORKDIR}/product.version
    fi
    
    #Exporting build environment variables
    echo "export RELDIR=${RELDIR}" >  ${WORKDIR}/buildenv.sh
    echo "export BUILD_PURPOSE=${BUILD_PURPOSE}" >> ${WORKDIR}/buildenv.sh
    echo "export PRODUCT=${PRODUCT}" >> ${WORKDIR}/buildenv.sh
    echo "export PRODUCT_RELEASE=${PRODUCT_RELEASE}" >> ${WORKDIR}/buildenv.sh
    echo "export MACHINE=${MACHINE}" >> ${WORKDIR}/buildenv.sh
    echo "export FEED_ARCH=${FEED_ARCH}" >> ${WORKDIR}/buildenv.sh
    echo "export OEBASE=${OEBASE}" >> ${WORKDIR}/buildenv.sh
}


do_deploy () {
    #Creating deploy folder
    install -d ${DEPLOY_DIR_IMAGE}
    install -d ${DEPLOY_DIR_IMAGE}/scripts
    
    #Copying product version to the deploy folder
    install -m 644 ${WORKDIR}/product.version ${DEPLOY_DIR_IMAGE}/
    package_stagefile_shell ${DEPLOY_DIR_IMAGE}/product.version
    
    #Copying all scripts to the deploy folder 
    install -m 755 ${S}/makerelease.sh   ${DEPLOY_DIR_IMAGE}/scripts/
    install -m 755 ${S}/makerelease.inc  ${DEPLOY_DIR_IMAGE}/scripts/
    
    install -m 755 ${S}/machine/${MACHINE}/*    ${DEPLOY_DIR_IMAGE}/scripts/
    install -m 755 ${S}/product/${PRODUCT}/*    ${DEPLOY_DIR_IMAGE}/scripts/
  
    #Exporting build environment variables
    install -m 755 ${WORKDIR}/buildenv.sh  ${DEPLOY_DIR_IMAGE}/scripts/
    package_stagefile_shell ${DEPLOY_DIR_IMAGE}/scripts/*
}


do_deploy[dirs] = "${S}"
addtask deploy before do_package_stage after do_install

FILES_${PN} = "${sysconfdir}/build.date"
INSANE_SKIP_${PN} = True

