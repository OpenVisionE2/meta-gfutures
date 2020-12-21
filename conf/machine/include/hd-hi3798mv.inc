DISTRO_FEATURES_append = " opengl"

KERNELVERSION = "4.4.35"

# We know about rtc
MACHINE_FEATURES_BACKFILL_CONSIDERED += "rtc"

TARGET_ARCH = "arm"
DEFAULTTUNE = "cortexa15hf-neon-vfpv4"

IMAGE_CLASSES += "hd-fastboot8gb_image"
IMAGE_FSTYPES += "hdfastboot8gb"
CMDLINE ?= "console=ttyAMA0,115200n8"

SOC_FAMILY = "hisi3798mv200"
HICHIPSET = "3798mv200"
CHIPSET = "Hi3798Mv200"

KERNEL_FILE = "uImage"
ROOTFS_FILE = "rootfs.tar.bz2"
MTD_BOOTFS = "mmcblk0p4"
MTD_BLACK  = "mmcblk0"

PREFERRED_VERSION_linux-hd = "${KERNELVERSION}"

#Provider
PREFERRED_PROVIDER_virtual/kernel = "linux-hd"
PREFERRED_PROVIDER_virtual/egl ?= "hd-mali-${MACHINE}"
PREFERRED_PROVIDER_virtual/libgles1 ?= "hd-mali-${MACHINE}"
PREFERRED_PROVIDER_virtual/libgles2 ?= "hd-mali-${MACHINE}"
PREFERRED_PROVIDER_virtual/libgbm ?= "hd-mali-${MACHINE}"
PREFERRED_PROVIDER_virtual/libgl ?= "mesa"
PREFERRED_PROVIDER_virtual/mesa ?= "mesa"
PREFERRED_PROVIDER_virtual/blindscan-dvbs = "hd-dvb-modules-${MACHINE}"
PREFERRED_PROVIDER_virtual/blindscan-dvbc = "hd-dvb-modules-${MACHINE}"
PREFERRED_PROVIDER_virtual/gstreamer1.0-dvbmediasink = "gstreamer1.0-plugin-dvbmediasink"
PREFERRED_PROVIDER_virtual/enigma2-mediaservice = "enigma2-plugin-systemplugins-servicehisilicon"

require conf/machine/include/tune-cortexa15.inc
require conf/machine/include/hd-essential.inc

# E2 OSD settings
EXTRA_OECONF_append_pn-enigma2 = " --with-alphablendingacceleration=always --with-blitaccelerationthreshold=250 --with-fillaccelerationthreshold=190000"

# Gstreamer dvbmediasink
DVBMEDIASINK_CONFIG = "--with-wma --with-wmv --with-pcm --with-dts --with-eac3 --with-h265 --with-vb6 --with-vb8 --with-vb9 --with-spark"

MACHINE_FEATURES += "alsa usbhost switchoff osdposition hdmicec textlcd 7segment blindscan-dvbs blindscan-tbs hisil mali transcoding emmc hisil-recovery mountboot fastboot multitranscoding wol HDMI"

MACHINE_ESSENTIAL_EXTRA_RDEPENDS += "\
	${@bb.utils.contains("MACHINE_FEATURES", "hisil", "hd-libs-${HICHIPSET} hd-partitions-${MACHINE} hd-bootargs-${MACHINE}" , "", d)} \
	${@bb.utils.contains("MACHINE_FEATURES", "hisil-recovery", "hd-recovery-${MACHINE}" , "", d)} \
	${@bb.utils.contains("MACHINE_FEATURES", "wol", "hd-ethwol" , "", d)} \
	${@bb.utils.contains("MACHINE_FEATURES", "mali", "hd-mali-${MACHINE} kernel-module-mali-${HICHIPSET}" , "", d)} \
	"

IMAGEDIR = "hd"

IMAGE_CMD_hdfastboot8gb_append = " \
	mkdir -p ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}; \
	mkdir -p ${IMGDEPLOYDIR}/${IMAGEDIRRECOVERY}/${MACHINE}; \
	bzip2 ${IMGDEPLOYDIR}/${IMAGE_NAME}${IMAGE_NAME_SUFFIX}.tar; \
	cp -f ${DEPLOY_DIR_IMAGE}/uImage ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/uImage; \
	cp -f ${IMGDEPLOYDIR}/${IMAGE_NAME}${IMAGE_NAME_SUFFIX}.tar.bz2 ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/rootfs.tar.bz2; \
	echo "${IMAGE_NAME}" > ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/imageversion; \
	echo "https://forum.openvision.tech/app.php/donate" > ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/donate.txt; \
	echo "${IMAGE_NAME}_usb.zip" > ${IMGDEPLOYDIR}/${IMAGEDIR}/unforce_${MACHINE}.txt; \
	echo "Rename the unforce_${MACHINE}.txt to force_${MACHINE}.txt and move it to the root of your usb-stick" > ${IMGDEPLOYDIR}/${IMAGEDIR}/force_${MACHINE}_READ.ME; \
	echo "When you enter the recovery menu then it will force to install the image ${IMAGE_NAME}_usb.zip in the image-slot1" >> ${IMGDEPLOYDIR}/${IMAGEDIR}/force_${MACHINE}_READ.ME; \
	cp -f ${IMGDEPLOYDIR}/bootoptions.img ${IMGDEPLOYDIR}/${IMAGEDIRRECOVERY}/${MACHINE}/bootoptions.img; \
	cp -f ${DEPLOY_DIR_IMAGE}/hd-partitions-${MACHINE}/fastboot.bin ${IMGDEPLOYDIR}/${IMAGEDIRRECOVERY}/fastboot.bin; \
	cp -f ${DEPLOY_DIR_IMAGE}/hd-partitions-${MACHINE}/bootargs-8gb.bin ${IMGDEPLOYDIR}/${IMAGEDIRRECOVERY}/bootargs.bin; \
	cp -f ${DEPLOY_DIR_IMAGE}/hd-partitions-${MACHINE}/${MACHINE}/fastboot.bin ${IMGDEPLOYDIR}/${IMAGEDIRRECOVERY}/${MACHINE}/fastboot.bin; \
	cp -f ${DEPLOY_DIR_IMAGE}/hd-partitions-${MACHINE}/${MACHINE}/bootargs-8gb.bin ${IMGDEPLOYDIR}/${IMAGEDIRRECOVERY}/${MACHINE}/bootargs.bin; \
	cp -f ${DEPLOY_DIR_IMAGE}/hd-partitions-${MACHINE}/${MACHINE}/pq_param.bin ${IMGDEPLOYDIR}/${IMAGEDIRRECOVERY}/${MACHINE}/pqparam.bin; \
	cp -f ${DEPLOY_DIR_IMAGE}/hd-partitions-${MACHINE}/${MACHINE}/baseparam.img ${IMGDEPLOYDIR}/${IMAGEDIRRECOVERY}/${MACHINE}/baseparam.img; \
	cp -f ${DEPLOY_DIR_IMAGE}/hd-partitions-${MACHINE}/${MACHINE}/logo.img ${IMGDEPLOYDIR}/${IMAGEDIRRECOVERY}/${MACHINE}/logo.img; \
	cp -f ${DEPLOY_DIR_IMAGE}/hd-partitions-${MACHINE}/${MACHINE}/recovery.bin ${IMGDEPLOYDIR}/${IMAGEDIRRECOVERY}/${MACHINE}/recovery.bin; \
	echo "${MACHINE}-${DATE}-RECOVERY" > ${IMGDEPLOYDIR}/${IMAGEDIRRECOVERY}/${MACHINE}/recoveryversion; \
	echo "***** ATTENTION *****" >${IMGDEPLOYDIR}/${IMAGEDIRRECOVERY}/recovery_${MACHINE}_READ.ME; \
	echo "This RECOVERY only need when you have issue access the MULTIBOOT MENU" >>${IMGDEPLOYDIR}/${IMAGEDIRRECOVERY}/recovery_${MACHINE}_READ.ME; \
	echo "The ${IMAGE_NAME}_recovery_usb.zip should been install normally once (or if there is an update.)" >>${IMGDEPLOYDIR}/${IMAGEDIRRECOVERY}/recovery_${MACHINE}_READ.ME; \
	echo "This is needed for avoid images conflicts as the partition layout (bootargs) is of huge essential." >>${IMGDEPLOYDIR}/${IMAGEDIRRECOVERY}/recovery_${MACHINE}_READ.ME; \
	echo "A small change can destroy all your install images. So we can better leave it and not install it if it's not need." >>${IMGDEPLOYDIR}/${IMAGEDIRRECOVERY}/recovery_${MACHINE}_READ.ME; \
	rm -f ${IMGDEPLOYDIR}/*.zip; \
	cd ${IMGDEPLOYDIR}/${IMAGEDIRRECOVERY}; \
	zip -r ../${IMAGE_NAME}_recovery_emmc.zip *; \
	cd ..; \
	rm -Rf ${IMAGEDIRRECOVERY}; \
	cd ${IMGDEPLOYDIR}/${IMAGEDIR}; \
	zip -r ../${IMAGE_NAME}_usb.zip unforce_${MACHINE}.txt force_${MACHINE}_READ.ME ${MACHINE}/imageversion ${MACHINE}/donate.txt ${MACHINE}/uImage ${MACHINE}/rootfs.tar.bz2; \
	cd ..; \
	rm -Rf ${IMAGEDIR}; \
	"

IMAGE_CMD_prepend = "\
	rm -Rf ${IMAGE_ROOTFS}/tmp/*; \
	"

STB_PLATFORM = "gfutureshisil"

EXTRA_ALSA = "mv200"
