require hd-stb-kodi.inc

RDEPENDS_${PN} += "hd-v3ddriver-hd51"

EXTRA_OECMAKE += " \
    -DWITH_PLATFORM=v3d-cortexa15 \
    -DWITH_FFMPEG=stb \
"

COMPATIBLE_MACHINE = "^(hd51|axultra|bre2ze4k)$"
