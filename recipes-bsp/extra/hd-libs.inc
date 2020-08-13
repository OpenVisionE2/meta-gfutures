DESCRIPTION = "${MACHINE} libraries"
SECTION = "base"
PRIORITY = "required"
LICENSE = "CLOSED"
DEPENDS = "zlib libpng freetype curl libxml2 libjpeg-turbo harfbuzz"
RDEPENDS_${PN} = "libbluray"

PACKAGE_ARCH = "${MACHINE_ARCH}"

PV = "${SRCDATE}"

SRC_URI = "http://downloads.mutant-digital.net/${MACHINE}/${MACHINE}-libs-${SRCDATE}.zip"

S = "${WORKDIR}"

INHIBIT_PACKAGE_STRIP = "1"

# Disable anything auto depending on hisilicon libs
EXCLUDE_FROM_SHLIBS = "1"

# The driver is a set of binary libraries to install
# there's nothing to configure or compile
do_configure[noexec] = "1"
do_compile[noexec] = "1"

do_install() {
	install -d ${D}${libdir}/hisilicon
	install -m 0755 ${S}/hisilicon/* ${D}${libdir}/hisilicon
	install -m 0755 ${S}/ffmpeg/* ${D}${libdir}/hisilicon
	if [ "${GLIBCVERSION}" = "2.25" ]; then
		install -m 0755 ${S}/glibc/* ${D}${libdir}/hisilicon
	else
		install -d ${D}${base_libdir}
		ln -sf /lib/ld-linux-armhf.so.3 ${D}${libdir}/hisilicon/ld-linux.so
	fi
}

do_package_qa() {
}

FILES_${PN} = "${libdir}/hisilicon/*"
FILES_${PN}-dev = ""

