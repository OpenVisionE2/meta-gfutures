DISTRO_FEATURES_remove += "x11 wayland directfb"

MACHINE_ESSENTIAL_EXTRA_RDEPENDS += "\
	hd-dvb-modules-${MACHINE} \
	${@bb.utils.contains("MACHINE_FEATURES", "emmc", "hd-resizerootfs partitions-by-name" , "", d)} \
	"

BOX_BRAND = "gfutures"
