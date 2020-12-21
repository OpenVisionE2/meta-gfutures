KERNELVERSION = "4.10.12"

MTD_KERNEL = "mtd1"
MTD_ROOTFS = "mtd2"
KERNEL_FILE = "kernel.bin"
ROOTFS_FILE = "rootfs.bin"

PREFERRED_VERSION_linux-hd = "${KERNELVERSION}"

IMAGE_FSTYPES += "ubi"

TARGET_ARCH = "mipsel"
DEFAULTTUNE = "mips32el"

require conf/machine/include/tune-mips32.inc
require conf/machine/include/hd.inc

IMAGE_CMD_ubi_append = " \
	mkdir -p ${IMGDEPLOYDIR}/${IMAGEDIR}; \
	cp -f ${IMGDEPLOYDIR}/${IMAGE_NAME}${IMAGE_NAME_SUFFIX}.ubi ${IMGDEPLOYDIR}/${IMAGEDIR}/${ROOTFS_FILE}; \
	cp -f ${DEPLOY_DIR_IMAGE}/vmlinux.gz-${MACHINE}.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/${KERNEL_FILE}; \
	echo "${IMAGE_NAME}" > ${IMGDEPLOYDIR}/${IMAGEDIR}/imageversion; \
	echo "https://forum.openvision.tech/app.php/donate" > ${IMGDEPLOYDIR}/${IMAGEDIR}/donate.txt; \
	echo "rename this file to 'force' to force an update without confirmation" > ${IMGDEPLOYDIR}/${IMAGEDIR}/noforce; \
	rm -f ${IMGDEPLOYDIR}/*.zip; \
	cd ${IMGDEPLOYDIR}; \
	zip ${IMAGE_NAME}_usb.zip ${IMAGEDIR}/*; \
	rm -f ${DEPLOY_DIR_IMAGE}/*.ubi; \
	rm -f ${DEPLOY_DIR_IMAGE}/*.ubifs; \
	rm -Rf ${IMGDEPLOYDIR}/boot; \
	rm -Rf ${IMAGEDIR}; \
	"

IMAGE_CMD_ubifs_prepend = " \
	rm -Rf ${IMAGE_ROOTFS}/tmp/*; \
	"

DVBMEDIASINK_CONFIG = "--with-wma --with-wmv --with-pcm --with-dts --with-eac3 \
	${@bb.utils.contains('MACHINE_FEATURES', 'h265', '--with-h265 --with-vb6 --with-vb8 --with-spark' , '', d)} \
	"

MACHINE_FEATURES += "videoenhancement"
