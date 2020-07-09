KV = "4.4.35"
SRCDATE = "20200622"

PROVIDES = "virtual/blindscan-dvbs"
RDEPENDS_${PN} = "libjpeg-turbo"

require hd-dvb-modules.inc

SRC_URI[md5sum] = "71727df0e1354442c069d86c4cbb2c83"
SRC_URI[sha256sum] = "5c8278a7676f49a4777cf25117f0c66ca349ae6661dbf5daf62c9ff0a319b385"

COMPATIBLE_MACHINE = "^(hd60)$"

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

FILES_${PN} += " ${bindir} ${sysconfdir}/init.d"

