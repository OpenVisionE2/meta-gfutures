DISTRO_FEATURES_remove += "x11 wayland directfb"

MACHINE_ESSENTIAL_EXTRA_RDEPENDS += "\
	hd-dvb-modules-${MACHINE} \
	${@bb.utils.contains("MACHINE_FEATURES", "emmc", "hd-resizerootfs partitions-by-name" , "", d)} \
	${@bb.utils.contains("MACHINE_FEATURES", "v3d-nxpl", "hd-v3ddriver-${MACHINE}" , "", d)} \
	"

BOX_BRAND = "gfutures"
