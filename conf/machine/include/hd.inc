require conf/machine/include/hd-essential.inc

# We know about rtc
MACHINE_FEATURES_BACKFILL_CONSIDERED += "rtc"

#Provider
PREFERRED_PROVIDER_virtual/libgl ?= "mesa"
PREFERRED_PROVIDER_virtual/mesa ?= "mesa"
PREFERRED_PROVIDER_virtual/kernel = "linux-hd"

MACHINE_FEATURES += "alsa hdmicec usbhost switchoff osdposition blindscan-tbs HDMI"

MACHINE_ESSENTIAL_EXTRA_RDEPENDS += "\
	"

RCTYPE ?= "16"
RCNAME ?= "hd1100"
