KV = "4.4.35"
SRCDATE = "20200429"

PROVIDES = "virtual/blindscan-dvbs virtual/blindscan-dvbc"

require hd-dvb-modules.inc

SRC_URI[md5sum] = "5a4dc505676cecd994f78ba88a7a3806"
SRC_URI[sha256sum] = "973d9bbe05df8ec7b4e85bf200e26114d5098d832d8202c0ae22b030b80ca7a3"

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
