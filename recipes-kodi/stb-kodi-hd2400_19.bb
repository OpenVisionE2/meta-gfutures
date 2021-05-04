require hd-stb-kodi.inc

RDEPENDS_${PN} += "hd-v3ddriver-${MACHINE}"

EXTRA_OECMAKE += " \
    -DWITH_PLATFORM=v3d-mipsel \
    -DWITH_FFMPEG=stb \
"

COMPATIBLE_MACHINE = "^(hd2400)$"
