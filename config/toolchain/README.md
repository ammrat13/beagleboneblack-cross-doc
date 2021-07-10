# Toolchain Configuration

This folder contains the configuration options used when making the
cross-toolchain. It targets `arm-linux-uclibcgnueabi`.


## File Overview

BinUtils and GCC are configured purely on the command line. Their configuration
files have the options used for `configure` and the commands to build and
install them. uClibc-ng uses a Kconfig-style interface, so its `.config` file is
given here.


## Environment Variables

The build process expects some environment variables to be defined. The `TARGET`
and `PREFIX` variables are used by the configuration files, while `PATH` is used
to point GCC to BinUtils.
```
$ export TARGET=arm-linux-uclibcgnueabi
$ export PREFIX=/path/to/toolchain/
$ export PATH=${PREFIX}/bin/:${PATH}
```


## Build Process

The general flow for making the cross-toolchain is to:
1. Install Linux Headers. The C library will need these to interface with the
   operating system.
1. Install BinUtils. This package is used heavily by GCC.
2. Install GCC. It won't have all the auxilary libraries, won't support
   threading, and won't be able to produce dynamically-linked executables. We
   can't fully compile GCC without a C library for the target.
3. Install uClibc-ng. This is built for the target using the first-pass GCC.
   Even though it's limited, it's enough to compile a C library like glibc,
   musl, or uClibc-ng.
4. Install GCC again. This is the final compiler with all the features.
5. Install uClibc-ng again. This step probably isn't needed. It's just to have a
   C library compiled with the final toochain for the target.

The commands to build and install BinUtils and GCC are in their configuration
files. As for the other packages:

### To Install Linux Kernel Headers

In the source directory for the Linux kernel to be used, run
```
$ make ARCH=arm INSTALL_HDR_PATH=${PREFIX} headers_install
```

### To Install uClibc-ng

Place the configuration file as `.config` in the source directory. To configure,
build, then install, run
```
$ make CROSS_COMPILE=${TARGET}- menuconfig
$ make CROSS_COMPILE=${TARGET}- -j$(nproc)
$ make CROSS_COMPILE=${TARGET}- PREFIX=${PREFIX} install
```
