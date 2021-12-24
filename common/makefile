.SILENT:

CFLAGS_BOOT := -ffreestanding -fno-stack-protector -fshort-wchar -mno-red-zone -I ../boot/src -I ../common -Ofast -D QEMUBUILD=1  -mno-ms-bitfields
LFLAGS_BOOT := -nostdlib -dll -shared --subsystem 10 -e efi_main 
TEMPDIR := ../_temp/common
ENVDIR := ../_env               

COM_C_FILES := $(shell find ** -name *.c)
COM_OBJ_FILES := $(patsubst %.c, $(TEMPDIR)/%.o, $(COM_C_FILES))

$(COM_OBJ_FILES): $(TEMPDIR)/%.o : ./%.c
	printf "\tCM: compiling %s\n" $(patsubst $(TEMPDIR)/%.o, %.c, $@)
	mkdir -p $(dir $@)
	x86_64-w64-mingw32-gcc $(CFLAGS_BOOT) -c $(patsubst $(TEMPDIR)/%.o, %.c, $@) -o $@

.PHONY: build
build: $(COM_OBJ_FILES)