
# Welcome to Aozora-OS! 
Aozora-OS is currently in its very early development stages and as such there isnt much information to give about it.

### NEEDED PACKAGES:
- mingw-w64-gcc
- mingw-w64-binutils
- make
- qemu
- ovmf

these will need to installed manually, visit [os-dev](https://wiki.osdev.org/GCC_Cross-Compiler) for help

- x86_64-elf-gcc
- x86_64-elf-binutils 

from here you can run 'make run' to run the os, as of jan 24, 2022 this should open qemu and it should become a blank screen. right now the os doesnt do much of anything as I am more focused on writing code that will allow me to actually do useful things with the os, however code does exist to do the things mentioned below. all files meant to eventually be used by the kernel are stored in the common folder, and boot.c should contain all the needed includes to use these files already.

### update jan 24, 2022:

code has been written for all of the following:
 - handing ata disk io
 - managing memory via malloc and free (somewhat)
 - a simple stdlib
 - a simple graphics library
 - interrupt handling
 - uefi bindings using my own uefi library
