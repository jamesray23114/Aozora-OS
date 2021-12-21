.SILENT:

CFLAGS_BOOT := -ffreestanding -fno-stack-protector -fshort-wchar -mno-red-zone -I src -I ../common -Ofast -D QEMUBUILD=1  -mno-ms-bitfields
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
	x86_64-w64-mingw32-gcc $(LFLAGS_BOOT) -o $(TEMPDIR)/BOOTX64.EFI $(TEMPDIR)/boot.o 
#end

	printf "\tBT: formatting and copying files\n"
#copy format img and files
	mkfs.fat -v -F 32 -S 512 -s 1 $(ISODIR)/fat.img 65565 1> /dev/null 2>/dev/null
	mmd -i $(ISODIR)/fat.img ::/EFI
	mmd -i $(ISODIR)/fat.img ::/EFI/BOOT
	mcopy -i $(ISODIR)/fat.img $(TEMPDIR)/BOOTX64.EFI ::/EFI/BOOT 

	dd if=$(ISODIR)/fat.img of=$(ENVDIR)/Aozora-OS.iso bs=512 count=65565 seek=2048 conv=notrunc status=none
#end