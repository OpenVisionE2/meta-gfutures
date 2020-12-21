KERNELVERSION = "4.10.12"

PREFERRED_VERSION_linux-hd = "${KERNELVERSION}"

IMAGE_CLASSES += "hd-emmc_image_multiboot"
IMAGE_FSTYPES += "hdemmc tar"
IMAGE_ROOTFS_SIZE ?= "589824"

TARGET_ARCH = "arm"
DEFAULTTUNE = "cortexa15hf-neon-vfpv4"

require conf/machine/include/tune-cortexa15.inc
require conf/machine/include/hd.inc

MACHINE_FEATURES += "textlcd emmc ci mountboot swap"

SOC_FAMILY = "bcm7251s"

MTD_KERNEL = "mmcblk0p2"
MTD_ROOTFS = "mmcblk0p3"

MTD_BOOTFS = "mmcblk0p1"
KERNEL_FILE = "kernel.bin"
ROOTFS_FILE = "rootfs.tar.bz2"
MTD_BLACK  = "mmcblk0"

MACHINE_ESSENTIAL_EXTRA_RDEPENDS += "\
	 ${@bb.utils.contains('MACHINE_FEATURES', 'swap', 'hd-swapcreate', '',d)} \
	"

STB_PLATFORM = "gfuturesbcmarm"

IMAGE_CMD_hdemmc_append = "\
	mkdir -p ${IMGDEPLOYDIR}/${IMAGEDIR}; \
	cp -f ${IMGDEPLOYDIR}/${IMAGE_NAME}.emmc.img ${IMGDEPLOYDIR}/${IMAGEDIR}/disk.img; \
	echo "${IMAGE_NAME}" > ${IMGDEPLOYDIR}/${IMAGEDIR}/imageversion; \
	echo "https://forum.openvision.tech/app.php/donate" > ${IMGDEPLOYDIR}/${IMAGEDIR}/donate.txt; \
	cp -f ${DEPLOY_DIR_IMAGE}/zImage ${IMGDEPLOYDIR}/${IMAGEDIR}/${KERNEL_FILE}; \
	cp -f ${IMGDEPLOYDIR}/${IMAGE_NAME}${IMAGE_NAME_SUFFIX}.tar ${IMGDEPLOYDIR}/${IMAGEDIR}/rootfs.tar; \
	bzip2 ${IMGDEPLOYDIR}/${IMAGEDIR}/rootfs.tar; \
	rm -f ${IMGDEPLOYDIR}/*.zip; \
	cd ${IMGDEPLOYDIR}; \
	zip ${IMAGE_NAME}_recovery_emmc.zip ${IMAGEDIR}/disk.img ${IMAGEDIR}/imageversion ${IMAGEDIR}/donate.txt; \
	zip ${IMAGE_NAME}_usb.zip ${IMAGEDIR}/imageversion ${IMAGEDIR}/donate.txt ${IMAGEDIR}/${KERNEL_FILE} ${IMAGEDIR}/${ROOTFS_FILE}; \
	rm -f ${DEPLOY_DIR_IMAGE}/*.ext4; \
	rm -Rf ${IMAGEDIR}; \
	"

IMAGE_CMD_prepend = "\
	rm -Rf ${IMAGE_ROOTFS}/tmp/*; \
	"

DVBMEDIASINK_CONFIG = "--with-wma --with-wmv --with-pcm --with-dts --with-eac3 --with-h265 --with-vb6 --with-vb8 --with-vb9 --with-spark"
