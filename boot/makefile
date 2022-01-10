.SILENT:

CFLAGS_BOOT := -ffreestanding -flto -fno-stack-protector -fshort-wchar -finline-limit=1024 -mno-red-zone -I src -I ../common -Ofast -mno-ms-bitfields
LFLAGS_BOOT := -nostdlib -flto -Wl,-dll -shared -Wl,--subsystem,10 -e efi_main -Ofast 
TEMPDIR := ../_temp/boot
ENVDIR := ../_env
ISODIR := ../_temp/iso

BOOT_C_FILES := $(shell find ** -name *.c)
BOOT_OBJ_FILES := $(patsubst %.c, $(TEMPDIR)/%.o, $(BOOT_C_FILES))
COM_OBJ_FILES := $(shell find ../_temp/common/** -name *.o)

$(BOOT_OBJ_FILES): $(TEMPDIR)/%.o : ./%.c
	printf "\tBT: compiling %s\n" $(patsubst $(TEMPDIR)/%.o, %.c, $@)
	mkdir -p $(dir $@)
	x86_64-w64-mingw32-gcc $(CFLAGS_BOOT) -c $(patsubst $(TEMPDIR)/%.o, %.c, $@) -o $@

.PHONY: build
build: $(BOOT_OBJ_FILES)
	printf "\tBT: linking BOOTX64\n"
#linking files
	x86_64-w64-mingw32-gcc $(LFLAGS_BOOT) -o $(TEMPDIR)/BOOTX64.EFI $(BOOT_OBJ_FILES) $(COM_OBJ_FILES)
#end

	printf "\tBT: formatting and copying files\n"
#copy format img and files
	mkfs.fat -v -F 32 -S 512 -s 1 $(ISODIR)/fat.img 65565 1> /dev/null 2>/dev/null
	mmd -i $(ISODIR)/fat.img ::/EFI
	mmd -i $(ISODIR)/fat.img ::/EFI/BOOT
	mcopy -i $(ISODIR)/fat.img $(TEMPDIR)/BOOTX64.EFI ::/EFI/BOOT 

	dd if=$(ISODIR)/fat.img of=$(ENVDIR)/Aozora-OS.iso bs=512 count=65565 seek=64 conv=notrunc status=none
#end
