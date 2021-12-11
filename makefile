.SILENT:

# files for building boot loader

CFLAGS_BOOT := -ffreestanding -fshort-wchar -mno-red-zone -I build/gnu-efi/inc -I build/gnu-efi/inc/x86_64 -I build/gnu-efi/inc/protocol -I src/ -Ofast
LFLAGS_BOOT := -nostdlib -Wl,-dll -shared -Wl,--subsystem,10 -e efi_main 

.PHONY: build
build: 
#create files / directories
	mkdir -p temp/iso 		
	mkdir -p temp/efi

	rm -f temp/iso/fat.img env/Aozora-OS.iso 

	touch temp/iso/fat.img env/Aozora-OS.iso env/harddrive.hhd

	truncate -s 4096k  temp/iso/fat.img
	truncate -s 1280m  env/Aozora-OS.iso
	truncate -s 10G    env/harddrive.hhd

#build and link files

	x86_64-w64-mingw32-gcc $(CFLAGS_BOOT) -c -o temp/efi/boot.o   src/boot/boot.c
	x86_64-w64-mingw32-gcc $(CFLAGS_BOOT) -c -o temp/efi/data.o   build/gnu-efi/lib/data.c
	x86_64-w64-mingw32-gcc $(LFLAGS_BOOT) -o temp/efi/BOOTX64.EFI temp/efi/boot.o temp/efi/data.o

#format iso
	parted env/Aozora-OS.iso -s -a minimal mklabel gpt
	parted env/Aozora-OS.iso -s -a minimal mkpart EFI fat16 2048s 10240s 
	parted env/Aozora-OS.iso -s -a minimal name 1 EFI-PART
	parted env/Aozora-OS.iso -s -a minimal mkpart primary 10241s 2621406s
	parted env/Aozora-OS.iso -s -a minimal name 2 AOZORA-OS-FS-PART
	parted env/Aozora-OS.iso -s -a minimal toggle 1 boot

#copy uefi files to fat image

	mformat -i temp/iso/fat.img -h 1 -t 1 -n 8192 -c 1
	mmd -i temp/iso/fat.img ::/EFI
	mmd -i temp/iso/fat.img ::/EFI/BOOT
	mcopy -i temp/iso/fat.img temp/efi/BOOTX64.EFI ::/EFI/BOOT 

#copy files to finished iso
	dd if=temp/iso/fat.img of=env/Aozora-OS.iso bs=512 count=8192 seek=2048 conv=notrunc

## make clean

.PHONY: clean
clean:
	rm -r temp && mkdir temp
	rm -r env && mkdir env

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
		-drive format=raw,file=env/Aozora-OS.iso \
		-drive format=raw,file=env/harddrive.hhd \
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
	printf "Add commit message: " 
	read VAR 											; \
	MAJOR=$$(sed '1!d' build/VERSION.txt) 				; \
	MINOR=$$(sed '2!d' build/VERSION.txt) 				; \
	PATCH=$$(sed '3!d' build/VERSION.txt) 				; \
	VERSTRING="Aozora-OS $$MAJOR.$$MINOR.$$PATCH -> " 	; \
	git commit -m "$$VERSTRING$$VAR" 					; \
	PATCH=$$(($$PATCH+1)) ; printf "$$MAJOR\n$$MINOR\n$$PATCH" > build/VERSION.txt
	git push
