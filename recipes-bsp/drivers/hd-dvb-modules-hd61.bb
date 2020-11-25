SRCDATE = "20201125"

PROVIDES = "virtual/blindscan-dvbs virtual/blindscan-dvbc"
RDEPENDS_${PN} = "libjpeg-turbo"

require hd-dvb-modules.inc

SRC_URI[md5sum] = "4cc7d10b50b741fa48d3776fef420984"
SRC_URI[sha256sum] = "c536b6989f18a6ce6094c10ec5e22f303717d8f234ba8f4a79f0c53489af5839"

COMPATIBLE_MACHINE = "^(hd61)$"

INITSCRIPT_NAME = "suspend"
INITSCRIPT_PARAMS = "start 89 0 ."
inherit update-rc.d

do_configure[noexec] = "1"

# Generate a simplistic standard init script
do_compile_append () {
	cat > suspend << EOF
#!/bin/sh

runlevel=runlevel | cut -d' ' -f2

if [ "\$runlevel" != "0" ] ; then
	exit 0
fi

mount -t sysfs sys /sys

${bindir}/turnoff_power
EOF
}

do_install_append() {
	install -d ${D}${sysconfdir}/init.d
	install -d ${D}${bindir}
	install -m 0755 ${S}/suspend ${D}${sysconfdir}/init.d
	install -m 0755 ${S}/turnoff_power ${D}${bindir}
}

do_package_qa() {
}

FILES_${PN} += "${bindir} ${sysconfdir}/init.d"
