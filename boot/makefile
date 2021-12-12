.SILENT:

CFLAGS_BOOT := -ffreestanding -fshort-wchar -mno-red-zone -I ../_build/gnu-efi/inc -I ../_build/gnu-efi/inc/x86_64 -I ../_build/gnu-efi/inc/protocol -I src/ -Ofast
LFLAGS_BOOT := -nostdlib -Wl,-dll -shared -Wl,--subsystem,10 -e efi_main 
TEMPDIR := ../_temp/boot
ENVDIR := ../_env
ISODIR := ../_temp/iso

.PHONY: build
build:
	mkdir -p $(TEMPDIR)

	printf "\tBT: running wingcc\n"
#building files
	x86_64-w64-mingw32-gcc $(CFLAGS_BOOT) -c -o $(TEMPDIR)/boot.o   src/boot.c
	x86_64-w64-mingw32-gcc $(CFLAGS_BOOT) -c -o $(TEMPDIR)/data.o   ../_build/gnu-efi/lib/data.c
	x86_64-w64-mingw32-gcc $(LFLAGS_BOOT) -o $(TEMPDIR)/BOOTX64.EFI $(TEMPDIR)/boot.o $(TEMPDIR)/data.o
#end

	printf "\tBT: formatting and copying files\n"
#copy format img and files
	mformat -i $(ISODIR)/fat.img -h 8 -t 8 -n 8192 -c 1 -F
	mmd -i $(ISODIR)/fat.img ::/EFI
	mmd -i $(ISODIR)/fat.img ::/EFI/BOOT
	mcopy -i $(ISODIR)/fat.img $(TEMPDIR)/BOOTX64.EFI ::/EFI/BOOT 

	dd if=$(ISODIR)/fat.img of=$(ENVDIR)/Aozora-OS.iso bs=512 count=65565 seek=2048 conv=notrunc status=none
#end