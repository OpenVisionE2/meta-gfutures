DESCRIPTION = "GFutures resize rootfs"
require conf/license/license-gplv2.inc

COMPATIBLE_MACHINE = "^(hd51|vs1500|hd60|bre2ze4k|hd61|axultra)$"

RDEPENDS_${PN} = "e2fsprogs-resize2fs"


SRC_URI = "file://resizerootfs"

inherit update-rc.d

INITSCRIPT_NAME = "resizerootfs"
INITSCRIPT_PARAMS = "start 7 S ."

do_install () {
    install -m 0755 -d ${D}${sysconfdir}/init.d
    install -m 0755 ${WORKDIR}/resizerootfs ${D}${sysconfdir}/init.d/resizerootfs
}
