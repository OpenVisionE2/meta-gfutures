KV = "4.4.35"
SRCDATE = "20200429"

PROVIDES = "virtual/blindscan-dvbs"

require hd-dvb-modules.inc

SRC_URI[md5sum] = "a3133a36da9a54d8e4545984c000555c"
SRC_URI[sha256sum] = "a9d50a77fefe6c35bfb2a0581e1ea76417c5b56b282d0e9b8038d6c60b5c0452"

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

