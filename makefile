.SILENT:

ASM_SRC_FILES := $(shell find src/ -name *.asm )
ASM_OBJ_FILES := $(patsubst src/%.asm, temp/src/%.o, $(ASM_SRC_FILES) )

C_SRC_FILES := $(shell find src/ -name *.c )
C_OBJ_FILES := $(patsubst src/%.c, temp/src/%.o, $(C_SRC_FILES) )

ALL_OBJ_FILES := $(ASM_OBJ_FILES) $(C_OBJ_FILES)

CFLAGS_EFI := -ffreestanding -fshort-wchar -mno-red-zone -I build/gnu-efi/inc -I path/to/gnu-efi/inc/x86_64  -I path/to/gnu-efi/inc/protocol -Ofast
LFLAGS_EFI := -nostdlib -Wl,-dll -shared -Wl,--subsystem,10 -e efi_main 

#make buildefi

.PHONY: build
build:
#create files / directories
	mkdir -p temp/iso 
	mkdir -p temp/efi

	touch temp/iso/fat.img env/Aozora-OS.iso 

	dd if=/dev/zero of=temp/iso/fat.img bs=1k count=4096 
	dd if=/dev/zero of=env/Aozora-OS.iso bs=20k count=64k 

#format iso
	parted env/Aozora-OS.iso -s -a minimal mklabel gpt
	parted env/Aozora-OS.iso -s -a minimal mkpart EFI fat16 2048s 35116s 
	parted env/Aozora-OS.iso -s -a minimal name 1 EFI-PART
	parted env/Aozora-OS.iso -s -a minimal mkpart primary 35117s 2615263s
	parted env/Aozora-OS.iso -s -a minimal name 2 AOZORA-OS-FS-PART
	parted env/Aozora-OS.iso -s -a minimal toggle 1 boot

#build and link files

	x86_64-w64-mingw32-gcc $(CFLAGS_EFI) -c -o temp/efi/boot.o src/boot/boot.c
	x86_64-w64-mingw32-gcc $(CFLAGS_EFI) -c -o temp/efi/data.o build/gnu-efi/lib/data.c
	x86_64-w64-mingw32-gcc $(LFLAGS_EFI) -o temp/efi/BOOTX64.EFI temp/efi/boot.o temp/efi/data.o

#copy uefi files to fat image

	mformat -i temp/iso/fat.img -h 1 -t 1 -n 33068 -c 1
	mmd -i temp/iso/fat.img ::/EFI
	mmd -i temp/iso/fat.img ::/EFI/BOOT
	mcopy -i temp/iso/fat.img temp/efi/BOOTX64.EFI ::/EFI/BOOT 

#copy files to finished iso
	dd if=temp/iso/fat.img of=env/Aozora-OS.iso bs=512 count=35116 seek=2048 conv=notrunc

#$(ASM_OBJ_FILES): temp/src/%.o : src/%.asm
#	mkdir -p $(dir $@) 
#	nasm -w-other -i src -f elf64 $(patsubst temp/src/%.o, src/%.asm, $@) -o $@ 
#
#$(C_OBJ_FILES): temp/src/%.o : src/%.c
#	mkdir -p $(dir $@)
#	x86_64-elf-gcc -ffreestanding -fno-asynchronous-unwind-tables -Qn -c -Ofast -I src $(patsubst temp/src/%.o, src/%.c, $@) -o $@

## make build

#.PHONY: build
#build: $(ALL_OBJ_FILES)
#	mkdir -p temp/disk
#	x86_64-elf-ld -T build/linker.ld -o temp/disk/disk.elf $(ALL_OBJ_FILES)
#	objcopy -O binary temp/disk/disk.elf temp/disk/disk.bin 

## make clean

.PHONY: clean
clean:
	rm -r temp && mkdir temp
	rm -f env/Aozora-OS.iso

# make run

.PHONY: run
run: build
	rm -f env/qemu-log.txt
	qemu-system-x86_64 \
		-accel tcg,thread=single \
		-cpu qemu64 \
		-m 4096 \
		-no-reboot \
		-drive format=raw,if=pflash,file=/usr/share/ovmf/OVMF.fd,readonly=on \
		-drive file=env/Aozora-OS.iso \
		-smp 1 -usb -vga std \
		-d int \
		-D env/qemu-log.txt


# make debug
	
.PHONY: debug
debug: build
	objdump -D -Mintel,i8086 -m i8086 temp/disk/disk.elf > temp/objdump16.asm
	objdump -D -Mintel,i386 -M i386 temp/disk/disk.elf > temp/objdump32.asm
	objdump -D -Mintel,x86-64 -M x86-64 temp/disk/disk.elf > temp/objdump64.asm

#make push

.PHONY: push
push: 
	git add src
	git add .gitignore
	git add LICENSE
	git add makefile
	git add build/linker.ld
	printf "Add commit message: " 
	read VAR 											; \
	MAJOR=$$(sed '1!d' build/VERSION.txt) 				; \
	MINOR=$$(sed '2!d' build/VERSION.txt) 				; \
	PATCH=$$(sed '3!d' build/VERSION.txt) 				; \
	VERSTRING="Aozora-OS $$MAJOR.$$MINOR.$$PATCH -> " 	; \
	git commit -m "$$VERSTRING$$VAR" 					; \
	PATCH=$$(($$PATCH+1)) ; printf "$$MAJOR\n$$MINOR\n$$PATCH" > build/VERSION.txt
	git push
