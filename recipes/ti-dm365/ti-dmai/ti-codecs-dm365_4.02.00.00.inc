DESCRIPTION = "TI Codecs for DM365"
SECTION = "multimedia"
LICENSE = "TI"

PR="${MACHINE_KERNEL_PR}"
PR_append = "a"
require ${OEBASE}/arago/recipes/ti/ti-paths.inc
require ${OEBASE}/arago/recipes/ti/ti-staging.inc

PV="4_02_00_00"

#CODEC_SUITE_NAME="${WORKDIR}/${PN}_${PV}"

SRC_URI = "git://${GITSERVER}/${GITBASE}/codec-engine-dm365.git;protocol=git;branch=${BRANCH}"
S = "${WORKDIR}/git"

CODEC_SUITE_NAME="${S}"

TI_BIN_UNPK_CMDS = "Y:workdir"
PROVIDES += "ti-codecs-dm365-server"

do_prepsources() {

    mkdir -p ${CODEC_SUITE_NAME}/packages/ti/sdo/codecs
    mkdir -p ${CODEC_SUITE_NAME}/packages/ittiam/codecs
    cp -a "${WORKDIR}/dm365_h264dec_02_00_00_10_production/packages/ti/sdo/codecs/h264dec" "${CODEC_SUITE_NAME}/packages/ti/sdo/codecs"
    cp -a "${WORKDIR}/dm365_h264enc_02_00_00_10_production/packages/ti/sdo/codecs/h264enc" "${CODEC_SUITE_NAME}/packages/ti/sdo/codecs"
    cp -a "${WORKDIR}/dm365_mpeg4dec_hdvicp_02_00_00_05_production/packages/ti/sdo/codecs/mpeg4dec_hdvicp" "${CODEC_SUITE_NAME}/packages/ti/sdo/codecs"
    cp -a "${WORKDIR}/dm365_mpeg4enc_hdvicp_02_00_00_08_production/packages/ti/sdo/codecs/mpeg4enc_hdvicp" "${CODEC_SUITE_NAME}/packages/ti/sdo/codecs"
    cp -a "${WORKDIR}/dm365_mpeg2dec_01_00_00_06_production/packages/ti/sdo/codecs/mpeg2dec" "${CODEC_SUITE_NAME}/packages/ti/sdo/codecs"
    cp -a "${WORKDIR}/dm365_mpeg2enc_01_00_00_07_production/packages/ti/sdo/codecs/mpeg2enc" "${CODEC_SUITE_NAME}/packages/ti/sdo/codecs"
    cp -a "${WORKDIR}/dm365_vc1dec_01_00_00_06_production/packages/ti/sdo/codecs/vc1dec" "${CODEC_SUITE_NAME}/packages/ti/sdo/codecs"
    cp -a "${WORKDIR}/dm365_mpeg4dec_01_10_00_01_production/packages/ti/sdo/codecs/mpeg4dec" "${CODEC_SUITE_NAME}/packages/ti/sdo/codecs"
    cp -a "${WORKDIR}/dm365_mpeg4enc_01_10_00_03_production/packages/ti/sdo/codecs/mpeg4enc" "${CODEC_SUITE_NAME}/packages/ti/sdo/codecs"
    cp -a "${WORKDIR}/dm365_jpegdec_01_00_00_10_production/packages/ti/sdo/codecs/jpegdec" "${CODEC_SUITE_NAME}/packages/ti/sdo/codecs"
    cp -a "${WORKDIR}/dm365_jpegenc_01_00_00_09_production/packages/ti/sdo/codecs/jpegenc" "${CODEC_SUITE_NAME}/packages/ti/sdo/codecs"
    cp -a "${WORKDIR}/dm365_aaclcdec_6_1_00_production/aac_dec_6_1_00_production_dm365_mvl/packages-production/ittiam/codecs/aac_dec" "${CODEC_SUITE_NAME}/packages/ittiam/codecs"
    cp -a "${WORKDIR}/dm365_aaclcenc_3_5_00_production/aaclc_enc_3_5_00_production_dm365_mvl/packages-production/ittiam/codecs/aaclc_enc" "${CODEC_SUITE_NAME}/packages/ittiam/codecs"
    cp -a "${WORKDIR}/dm365_g711dec_2_0_00_production/g711_dec_2_0_00_production_dm365_mvl/packages-production/ittiam/codecs/g711_dec" "${CODEC_SUITE_NAME}/packages/ittiam/codecs"
    cp -a "${WORKDIR}/dm365_g711enc_2_0_00_production/g711_enc_2_0_00_production_dm365_mvl/packages-production/ittiam/codecs/g711_enc" "${CODEC_SUITE_NAME}/packages/ittiam/codecs"
}

do_install() {
    install -d ${D}${CODEC_INSTALL_DIR_RECIPE}
    cp -pPrf ${CODEC_SUITE_NAME}/* ${D}/${CODEC_INSTALL_DIR_RECIPE}
}

PACKAGES += "ti-codecs-dm365-server"
FILES_ti-codecs-dm365-server = "${installdir}/ti-codecs-server/*"
INSANE_SKIP_ti-codecs-dm365-server = True

