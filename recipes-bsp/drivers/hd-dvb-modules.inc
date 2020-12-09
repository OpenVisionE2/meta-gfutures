DESCRIPTION = "Hardware drivers for ${MACHINE}"
SECTION = "base"
PRIORITY = "required"
LICENSE = "CLOSED"

PACKAGE_ARCH = "${MACHINE_ARCH}"

PV = "${KV}+${SRCDATE}"

SRC_URI = "http://source.mynonpublic.com/gfutures/${MACHINE}-drivers-${KV}-${SRCDATE}.zip"

S = "${WORKDIR}"

INHIBIT_PACKAGE_STRIP = "1"

FILES_${PN} += "${sysconfdir}/modules-load.d/_${MACHINE}.conf ${nonarch_base_libdir}/modules/${KV}/extra"

do_compile() {
}

do_install() {
	install -d ${D}${nonarch_base_libdir}/modules/${KV}/extra
	install -d ${D}${sysconfdir}/modules-load.d
	install -m 0755 ${S}/*.ko ${D}${nonarch_base_libdir}/modules/${KV}/extra
	for i in ${MACHINE}_1 ${MACHINE}_2 ${MACHINE}_3 ${MACHINE}_4; do
		echo $i >> ${D}${sysconfdir}/modules-load.d/_${MACHINE}.conf
	done
}

pkg_prerm_${PN}() {
	if [ "x$D" == "x" ]; then
		if [ -f ${nonarch_base_libdir}/modules/${KV}/extra/hi_play.ko ] ; then
			rm -f ${nonarch_base_libdir}/modules/${KV}/extra/hi_play.ko;
		fi
	fi
}
