SRCDATE = "20200731"

PROVIDES = "virtual/blindscan-dvbs"
RDEPENDS_${PN} = "libjpeg-turbo"

require hd-dvb-modules.inc

SRC_URI[md5sum] = "df338068e0c827ea4587058d2fc5df4e"
SRC_URI[sha256sum] = "afb24a25aeff996994490cf7b7be343dc8ae98205d12b199dba291f2fbd85126"

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

FILES_${PN} += "${bindir} ${sysconfdir}/init.d"

