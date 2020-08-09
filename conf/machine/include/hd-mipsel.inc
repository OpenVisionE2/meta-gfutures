KERNELVERSION = "4.10.12"

MTD_KERNEL = "mtd1"
MTD_ROOTFS = "mtd2"
KERNEL_FILE = "kernel.bin"
ROOTFS_FILE = "rootfs.bin"

PREFERRED_VERSION_linux-hd = "${KERNELVERSION}"

IMAGE_FSTYPES += "ubi"

TARGET_ARCH = "mipsel"
DEFAULTTUNE = "mips32el"

require conf/machine/include/tune-mips32.inc
require conf/machine/include/hd.inc
