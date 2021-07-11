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


## Post-Build

The installed dynamic libraries might need to be moved to `/lib/` on the
target's root filesystem. Copy over:
* `${PREFIX}/lib/`
    * `ld-uClibc-1.0.38.so`
    * `ld-uClibc.so.0`
    * `ld-uClibc.so.1`
    * `libuClibc-1.0.38.so`
    * `libc.so.0`
    * `libc.so.1`
* `${PREFIX}/${TARGET}/lib/`
    * `libgcc_s.so.1`
    * `libstdc++.so.6.0.29`
    * `libstdc++.so.6`
    * `libstdc++.so`

Some of these files are symlinks, so be sure to use `-P` with `cp`.


## Configuration Options

### BinUtils and GCC

The two packages have many options in common:
* `--prefix`: The root of the install tree
* `--program-prefix`: What to prepend to the installed programs
* `--with-sysroot`: Where to look for target headers and libraries
* `--target`: The platform the built programs should compile to
* `--disable-multilib`: Don't build for different calling conventions or
  variants
* `--disable-nls`: Don't build translations

GCC has some additional options:
* `--enable-languages`: What frontends to build
* `--disable-shared`: Don't build shared versions of the libraries built
* `--disable-threads`: Don't use multithreading
* `--with-native-system-header-dir`: Where to look for the target headers under
  the `sysroot` - default is `/usr/include/`

We don't build the entirety of GCC, only some parts:
* `gcc`: The compiler itself
* `target-libgcc`: A required support library for GCC - see
  [osdev.org](https://wiki.osdev.org/Libgcc#:~:text=The%20GNU%20Compiler%20Collection%20uses,helper%20routines%20and%20runtime%20support.)
* `target-libstdc++-v3`: The C++ standard library

### uClibc-ng

The base for the configuration was `defconfig`. The following changes were made:
* "Target Architecture" to "arm"
* "Target Architecture Features and Options":
    * "Build for EABI" to "y". This way, we're using the EABI calling convention
      instead of the OABI convention. This is what we configured GCC to do by
      setting the target with `uclibcgnueabi` instead of `uclibc`.
    * "Target Processor Endianness" to "Little Endian"
    * "Enable full C99 math library support" to "y". Do this so we get a `libm`.
    * "Enable XSI math extensions to the ISO C standard (bessel)" to "y"
    * "Linux kernel header location" to "${PREFIX}/include/". Environment
      variables are supported for this, so we'll take advantage of that.
* "General Library Settings":
    * "Enable library loader LD_PRELOAD environment" to "n". I'd rather use a
      file than an environment variable.
    * "Enable library loader preload file (ld.so.preload)" to "y". I'd rather
      use a file than an environment variable.
    * "Use executables RUNPATH/RPATH when searching for libraries." to "y"
    * "Enable GNU hash style support" to "y"
    * "Thread support" to "Linuxthreads". Even though this is a single-core
      processor, it would be nice to have a threading library.
* "Advanced Library Settings":
    * "libcrypt SHA256 support" to "y"
    * "libcrypt SHA512 support" to "y"
* "Networking Support":
    * "DNS resolver functions" to "y". This is needed for `nslookup` in BusyBox.
* "Library Installation Options":
    * "uClibc runtime library directory" to "/". We want to install directly in
      the sysroot.
    * "uClibc development environment directory" to "/". We want to install
      directly in the sysroot.
