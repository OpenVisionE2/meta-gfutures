KV = "4.4.35"
SRCDATE = "20200624"

PROVIDES = "virtual/blindscan-dvbs virtual/blindscan-dvbc"
RDEPENDS_${PN} = "libjpeg-turbo"

require hd-dvb-modules.inc

SRC_URI[md5sum] = "949d6410ac7c91dc04cbaa52c53bf82b"
SRC_URI[sha256sum] = "f8273f9c20f3b27f910eda507c8e135bc6ddd61c206253c4ac378e7e5103a6b8"

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
