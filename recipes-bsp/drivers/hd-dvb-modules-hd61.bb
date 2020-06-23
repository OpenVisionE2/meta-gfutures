KV = "4.4.35"
SRCDATE = "20200622"

PROVIDES = "virtual/blindscan-dvbs virtual/blindscan-dvbc"

require hd-dvb-modules.inc

SRC_URI[md5sum] = "dd113c0ef0fff1a6298b32f16f1d0872"
SRC_URI[sha256sum] = "499e78d52773dc161dd44f3b2258af1254ac378d94148964c0f73a1bc14ed4a6"

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

FILES_${PN} += " ${bindir} ${sysconfdir}/init.d"
