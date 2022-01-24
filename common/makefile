.SILENT:

CFLAGS_BOOT := -ffreestanding -flto -fno-stack-protector -fshort-wchar -finline-limit=1024 -mno-red-zone -I ../boot/src -I ../common -Ofast -mno-ms-bitfields 
TEMPDIR := ../_temp/common
ENVDIR := ../_env               

INT_C_FILES := $(shell find ** -name *.int.c)
COM_C_FILES := $(shell find ** -name *.c ! -name *.int.c)
COM_OBJ_FILES := $(patsubst %.c, $(TEMPDIR)/%.o, $(COM_C_FILES))
INT_OBJ_FILES := $(patsubst %.c, $(TEMPDIR)/%.o, $(INT_C_FILES))

$(COM_OBJ_FILES): $(TEMPDIR)/%.o : ./%.c
	printf "\tCM: compiling %s\n" $(patsubst $(TEMPDIR)/%.o, %.c, $@)
	mkdir -p $(dir $@)
	x86_64-w64-mingw32-gcc $(CFLAGS_BOOT) -c $(patsubst $(TEMPDIR)/%.o, %.c, $@) -o $@

$(INT_OBJ_FILES): $(TEMPDIR)/%.o : ./%.c
	printf "\tCM: compiling %s\n" $(patsubst $(TEMPDIR)/%.o, %.c, $@)
	mkdir -p $(dir $@)
	x86_64-w64-mingw32-gcc $(CFLAGS_BOOT) -mgeneral-regs-only -c $(patsubst $(TEMPDIR)/%.o, %.c, $@) -o $@

.PHONY: build
build: $(COM_OBJ_FILES) $(INT_OBJ_FILES)