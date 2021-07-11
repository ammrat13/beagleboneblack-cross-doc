# BusyBox Configuration

This folder contains the configuration file and patch file used for building
BusyBox.


## File Overview

BusyBox uses a Kconfig-style interface, so its `.config` file is given here. I
also elected to patch BusyBox slightly, so the `patch` file is also given.


## Environment Variables

The build process given below expects some environment variables to be defined.
It expects `TARGET` to be set to what it was when building the toolchain, and it
expects an environment variable for the root filesystem's mount point.
```
$ export TARGET=arm-linux-uclibcgnueabi
$ export ROOT_MNT=/path/to/dev/mmcblkp2/mount
```

It also expects the compiler from the toolchain to be in the `PATH`.


## Build Process

Move the configuration file into the source directory as `.config`. Apply the
patch with `patch -i busybox-1.33.1.patch`. Configure and build with
```
$ make CROSS_COMPILE=${TARGET}- menuconfig
$ make CROSS_COMPILE=${TARGET}- -j$(nproc)
```

If you symlinked `/sbin/`, `/usr/bin/`, and `/usr/sbin/` to `/bin/`, then edit
the links BusyBox will create with
```
$ sed -E -e 's@^(/sbin|/usr/bin|/usr/sbin)@/bin@' -i busybox.links
```

Finally, install to the root filesystem (using `sudo` as needed) with
```
$ make CROSS_COMPILE=${TARGET}- CONFIG_PREFIX=${ROOT_MNT} install
```

## Configuration Options

The base for the configuration was `defconfig`. The following changes were made:
* "Settings":
    * "Support utmp file" to "n". uClibc-ng was compiled without support for
      this, so we don't use it here. If you want to use it, set "General Library
      Settings" > "utmpx based support for tracking login/logouts to/from the
      system" to "y" in uClibc-ng.
* "Networking Utilities":
    * "Enable IPv6 support" to "n". uClibc-ng was compiled without IPv6, so we
      don't use it here. If you want to use it, set "Networking Support" > "IP
      version 6 support" to "y" in uClibc-ng.

The patch file is needed because uClibc-ng was built without SuSv3
compatibility. If you want that, set "General Library Settings" > "Enable SuSv3
LEGACY functions" to "y" in uClibc-ng.
