SRCDATE = "20200731"

PROVIDES = "virtual/blindscan-dvbs virtual/blindscan-dvbc"
RDEPENDS_${PN} = "libjpeg-turbo"

require hd-dvb-modules.inc

SRC_URI[md5sum] = "540b1d3dfdedac9d8186829b60c002d7"
SRC_URI[sha256sum] = "e7948ef3e71729efff46e251498ebcadd4f9399ede130e36f5ee8e50ea079316"

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
