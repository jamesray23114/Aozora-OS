.SILENT:

TEMPDIR := _temp
ENVDIR := _env

#===make build=== 
.PHONY: build
build:
	printf "STARTING BUILD/AOZORA-OS: (OS: )\n"

	printf "OS: making common files\n"
#create needed files
	mkdir -p $(TEMPDIR)/iso $(ENVDIR) _build
	rm -f $(TEMPDIR)/iso/fat.img $(ENVDIR)/Aozora-OS.iso 
	touch $(TEMPDIR)/iso/fat.img $(ENVDIR)/Aozora-OS.iso $(ENVDIR)/harddrive.hhd

	truncate -s 32m  	$(TEMPDIR)/iso/fat.img
	truncate -s 1244m  	$(ENVDIR)/Aozora-OS.iso
	truncate -s 10G   	 $(ENVDIR)/harddrive.hhd
#end

	printf "OS: formating iso.fat32\n"
#format iso
	parted $(ENVDIR)/Aozora-OS.iso -s -a minimal mklabel gpt
	parted $(ENVDIR)/Aozora-OS.iso -s -a minimal mkpart EFI fat32 2048s 67583s 
	parted $(ENVDIR)/Aozora-OS.iso -s -a minimal name 1 EFI-PART
	parted $(ENVDIR)/Aozora-OS.iso -s -a minimal mkpart primary 67584s 2547678s
	parted $(ENVDIR)/Aozora-OS.iso -s -a minimal name 2 AOZORA-OS-FS-PART
	parted $(ENVDIR)/Aozora-OS.iso -s -a minimal toggle 1 boot
#end

	printf "OS: building files\n"
#building subdirs
	printf "OS: STARTING BUILD/BOOT: (BT: )\n"
	make -C boot build --no-print-directory
	printf "OS: STARTING BUILD/KERNEL: (KN: )\n"
	make -C kernel build --no-print-directory
	printf "OS: STARTING BUILD/TOOLS: (TL: )\n"
	make -C tools build --no-print-directory
#end
#===end build=== 

#===make clean===
.PHONY: clean
clean:
	rm -r $(TEMPDIR) && mkdir $(TEMPDIR) && \
	rm -r $(ENVDIR) && mkdir $(ENVDIR)
#===end clean===

#===make run===
.PHONY: run
run: build

	printf "STARTING RUN/AOZORA-OS: (OS: )\n"

	rm -f $(ENVDIR)/qemu-log.txt
	qemu-system-x86_64 \
		-accel tcg,thread=single \
		-cpu qemu64 \
		-m 4096 \
		-no-reboot \
		-drive format=raw,if=pflash,file=/usr/share/ovmf/x64/OVMF.fd,readonly=on \
		-drive format=raw,if=none,file=$(ENVDIR)/Aozora-OS.iso,id=bootdisk \
		-drive format=raw,if=none,file=$(ENVDIR)/harddrive.hhd,id=harddisk \
		-device ide-hd,drive=bootdisk,bootindex=2 \
		-device ide-hd,drive=harddisk,bootindex=1 \
		-smp 1 -usb -vga std \
		-serial vc \
		-d int \
		-D $(ENVDIR)/qemu-log.txt
#===end run===

#===make run===
.PHONY: shell
shell: build

	printf "STARTING RUN/AOZORA-OS: (OS: )\n"

	rm -f $(ENVDIR)/qemu-log.txt
	qemu-system-x86_64 \
		-accel tcg,thread=single \
		-cpu qemu64 \
		-m 4096 \
		-no-reboot \
		-drive format=raw,if=pflash,file=/usr/share/ovmf/x64/OVMF.fd,readonly=on \
		-drive format=raw,file=$(ENVDIR)/Aozora-OS.iso \
		-drive format=raw,file=$(ENVDIR)/harddrive.hhd \
		-smp 1 -usb -vga std \
		-serial vc \
		-d int \
		-D $(ENVDIR)/qemu-log.txt
#===end shell===

#===make debug===	
.PHONY: debug
debug: build
	objdump -D -Mintel,i8086 -m i8086 $(TEMPDIR)disk/disk.elf > $(TEMPDIR)objdump16.asm
	objdump -D -Mintel,i386 -M i386 $(TEMPDIR)disk/disk.elf > $(TEMPDIR)objdump32.asm
	objdump -D -Mintel,x86-64 -M x86-64 $(TEMPDIR)disk/disk.elf > $(TEMPDIR)objdump64.asm
#===end debug===

#===ake push===
.PHONY: push
push: 
	git add boot
	git add kernel
	git add tools
	git add man
	git add .gitignore
	git add LICENSE
	git add makefile
	printf "Add commit message: " 
	read VAR 											; \
	MAJOR=$$(sed '1!d' _build/VERSION.txt) 				; \
	MINOR=$$(sed '2!d' _build/VERSION.txt) 				; \
	PATCH=$$(sed '3!d' _build/VERSION.txt) 				; \
	VERSTRING="Aozora-OS $$MAJOR.$$MINOR.$$PATCH -> " 	; \
	git commit -m "$$VERSTRING$$VAR" 					; \
	PATCH=$$(($$PATCH+1)) ; printf "$$MAJOR\n$$MINOR\n$$PATCH" > _build/VERSION.txt
	git push
#===end push===
