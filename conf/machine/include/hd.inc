require conf/machine/include/hd-essential.inc

KERNEL_MODULE_AUTOLOAD += "xfs"

# We know about rtc
MACHINE_FEATURES_BACKFILL_CONSIDERED += "rtc"

#Provider
PREFERRED_PROVIDER_virtual/egl ?= "hd-v3ddriver-${MACHINE}"
PREFERRED_PROVIDER_virtual/libgles1 ?= "hd-v3ddriver-${MACHINE}"
PREFERRED_PROVIDER_virtual/libgles2 ?= "hd-v3ddriver-${MACHINE}"
PREFERRED_PROVIDER_virtual/libgbm ?= "hd-v3ddriver-${MACHINE}"
PREFERRED_PROVIDER_virtual/libgl ?= "mesa"
PREFERRED_PROVIDER_virtual/mesa ?= "mesa"
PREFERRED_PROVIDER_virtual/kernel = "linux-hd"

MACHINE_FEATURES += "alsa hdmicec usbhost switchoff osdposition hdmicec blindscan-tbs HDMI"

MACHINE_EXTRA_RRECOMMENDS += "\
	gstreamer1.0-plugin-dvbmediasink \
	"

DVBMEDIASINK_CONFIG_arm = "--with-h265 --with-vb8 --with-vb9 --with-wma --with-wmv --with-pcm --with-dts --with-eac3"
DVBMEDIASINK_CONFIG_mipsel = "--with-wma --with-wmv --with-pcm --with-dts --with-eac3 \
	${@bb.utils.contains('MACHINE_FEATURES', 'h265', '--with-h265 --with-vb6 --with-vb8 --with-spark' , '', d)} \
	"

# ARM
IMAGE_CMD_hdemmc_append_arm = "\
	mkdir -p ${IMGDEPLOYDIR}/${IMAGEDIR}; \
	cp ${IMGDEPLOYDIR}/${IMAGE_NAME}.emmc.img ${IMGDEPLOYDIR}/${IMAGEDIR}/disk.img; \
	echo "${IMAGE_NAME}" > ${IMGDEPLOYDIR}/${IMAGEDIR}/imageversion; \
	cp ${IMAGE_ROOTFS}/tmp/zImage ${IMGDEPLOYDIR}/${IMAGEDIR}/${KERNEL_FILE}; \
	cp ${IMGDEPLOYDIR}/${IMAGE_NAME}${IMAGE_NAME_SUFFIX}.tar ${IMGDEPLOYDIR}/${IMAGEDIR}/rootfs.tar; \
	bzip2 ${IMGDEPLOYDIR}/${IMAGEDIR}/rootfs.tar; \
	rm -f ${IMGDEPLOYDIR}/*.zip; \
	cd ${IMGDEPLOYDIR}; \
	zip ${IMAGE_NAME}_recovery_emmc.zip ${IMAGEDIR}/disk.img ${IMAGEDIR}/imageversion; \
	zip ${IMAGE_NAME}_usb.zip ${IMAGEDIR}/imageversion ${IMAGEDIR}/${KERNEL_FILE} ${IMAGEDIR}/${ROOTFS_FILE}; \
	rm -f ${DEPLOY_DIR_IMAGE}/*.ext4; \
	rm -Rf ${IMAGEDIR}; \
	"

# MIPSEL
IMAGE_CMD_ubi_append_mipsel = " \
	mkdir -p ${IMGDEPLOYDIR}/${IMAGEDIR}; \
	cp ${IMGDEPLOYDIR}/${IMAGE_NAME}${IMAGE_NAME_SUFFIX}.ubi ${IMGDEPLOYDIR}/${IMAGEDIR}/${ROOTFS_FILE}; \
	cp ${DEPLOY_DIR_IMAGE}/vmlinux.gz-${MACHINE}.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/${KERNEL_FILE}; \
	echo "${IMAGE_NAME}" > ${IMGDEPLOYDIR}/${IMAGEDIR}/imageversion; \
	echo "rename this file to 'force' to force an update without confirmation" > ${IMGDEPLOYDIR}/${IMAGEDIR}/noforce; \
	rm -f ${IMGDEPLOYDIR}/*.zip; \
	cd ${IMGDEPLOYDIR}; \
	zip ${IMAGE_NAME}_usb.zip ${IMAGEDIR}/*; \
	rm -f ${DEPLOY_DIR_IMAGE}/*.ubi; \
	rm -f ${DEPLOY_DIR_IMAGE}/*.ubifs; \
	rm -Rf ${IMGDEPLOYDIR}/boot; \
	rm -Rf ${IMAGEDIR}; \
	"
