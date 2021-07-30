# BeagleBone Black Cross Libraries and Documentation

This repository hosts my experiements with embedded and bare-metal programming
on the BeagleBone Black. It has some code I wrote to run on the bare-metal, as
well as my notes on cross-compiling a BusyBox/Linux environment.

The directory structure is as follows:
* `config/` has notes detailing the configuration of the toolchain, bootloader,
  operating system, and user-space programs. It's mostly markdown notes, bash
  scripts for `configure` and `make`, and Kconfig configurations.
* `code/`
    * `bare-metal/` contains an application to run as an MLO
    * `linux/`
        * `fit/` has the image source file used to generate the uImage binary
          for uBoot.
        * `rootfs/` has the files on the root file-system of the kernel.
