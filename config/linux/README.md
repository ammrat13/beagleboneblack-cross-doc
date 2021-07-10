# Linux Configuration

This folder provides the configuration files used for U-Boot and the Linux
Kernel.


## File Overview

Both U-Boot and Linux use Kconfig. The `.config` files are provided.
Additionally, U=Boot has some of its configuration in header files, so a `patch`
file is provided for those options.

Finally, U-Boot looks for an environment in `u-boot.env`. Use `u-boot.env.txt`
to generate it, then place it in the root of the "boot partition."


## Filesystem Structure

The U-Boot configuration provided assumes the following structure for the
BeagleBone's boot medium:

The board will be booting off MMC0 (the SD card). That MMC will have a DOS
partition table.

The first partition will be formatted as FAT32. It will contain the SPL named
`/MLO` and U-Boot named `/u-boot.img`. It will also have the environment for
U-Boot in `/u-boot.env`.

The second patition will be formatted as Ext4. It will have an FIT image for the
kernel at `/boot/image.itb`.


## Environment Variables

The build process listed below expects the `TARGET` environment variable to be
defined to what it was set to when building the toolchain:
```
$ export TARGET=arm-linux-uclibcgnueabi
```

It also expects the environment variables for the first and second partitions'
mount points
```
$ export SD_P1_MNT=/path/to/dev/mmcblkp1/mount
$ export SD_P2_MNT=/path/to/dev/mmcblkp2/mount
```

Furthermore, it expects the compiler from the toolchain to be in the `PATH`.


## Build Process

### U-Boot

Move the configuration file for U-Boot into the source directory as `.config`.
Apply the patch with `path -i u-boot-2020.07.patch`. Configure and build with
```
$ make CROSS_COMPILE=${TARGET}- menuconfig
$ make CROSS_COMPILE=${TARGET}- -j$(nproc)
```

The SPL generated is expected to be used for MMC Raw Mode Booting
([§26.1.8.5.5](https://www.ti.com/lit/ug/spruh73q/spruh73q.pdf)). To convert it
to an image suitable for FAT Mode
([§26.1.8.5.6](https://www.ti.com/lit/ug/spruh73q/spruh73q.pdf)), remove the
Table of Contents by running
```
$ dd bs=512 skip=1 if=MLO of=MLO.cut
$ mv -v MLO.cut MLO
```

Finally, move `MLO` and `u-boot.img` to `${SD_P1_MNT}/`. Remember to also
generate and move `u-boot.env` there if it's needed.

### Linux

Move the kernel's configuration file into the source directory as `.config`.
Configure and build with
```
$ make ARCH=arm CROSS_COMPILE=${TARGET}- LOADADDR=0x80000000 menuconfig
$ make ARCH=arm CROSS_COMPILE=${TARGET}- LOADADDR=0x80000000 zImage dtbs modules
```

Install the modules to their desired location as
```
$ make ARCH=arm CROSS_COMPILE=${TARGET}- LOADADDR=0x80000000 INSTALL_MOD_PATH=${SD_P2_MNT} modules_install
```

Create the FIT image for the kernel using the files in `code/linux-fit` in this
repository. The zImage and DTB files can be found in the kernel's source
directory under `arch/arm/boot/` and `arch/arm/boot/dts` respectively.


## Configuration Options

### U-Boot

The base for the configuration was `am335x_evm_defconfig`. I don't remember the
exact changes made. I do remember heavily stripping down the SPL to the point
where all it can do is boot from MMC.

### Linux

The base for the configuration was `bb.org_defconfig` provided with the
[official BeagleBoard kernel](https://github.com/beagleboard/linux). No changes
have been made so far.
