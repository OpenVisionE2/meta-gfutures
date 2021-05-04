require hd-stb-kodi.inc

SRC_URI_append = " file://HiPlayer-for-kodi-19.patch \
	file://HiPlayer-defaultplayer-19.patch \
	file://HiPlayer-Subs-19.patch \
	"

RDEPENDS_${PN} += "hd-mali-${MACHINE}"

EXTRA_OECMAKE += " \
    -DWITH_PLATFORM=mali-cortexa15 \
    -DWITH_FFMPEG=stb \
"

COMPATIBLE_MACHINE = "^(hd61)$"
