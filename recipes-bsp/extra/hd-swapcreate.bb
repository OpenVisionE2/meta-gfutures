SUMMARY = "GFutures create swap"
LICENSE = "CLOSED"

SRC_URI="file://createswap.sh"

do_install() {
    install -d ${D}${INIT_D_DIR}
    install -d ${D}${sysconfdir}/rc3.d
    install -m 0755 ${WORKDIR}/createswap.sh ${D}${INIT_D_DIR}/createswap.sh
    ln -sf ../init.d/createswap.sh ${D}${sysconfdir}/rc3.d/S98createswap
}

COMPATIBLE_MACHINE = "^(hd51|vs1500|axultra|bre2ze4k)$"
