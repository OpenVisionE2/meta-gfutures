KV = "4.4.35"
SRCDATE = "20200410"

PROVIDES = "virtual/blindscan-dvbs virtual/blindscan-dvbc"

require hd-dvb-modules.inc

SRC_URI[md5sum] = "06b77d2ef741eccb1ddaf720449fe677"
SRC_URI[sha256sum] = "de7a70850efea19d42458e8759cbd04a7476c44ebde602bca269a83d44fafd12"

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
