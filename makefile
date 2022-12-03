.SILENT:

TEMPDIR := _temp
ENVDIR := _env

#===make build=== 
.PHONY: build
build: 
	printf "STARTING BUILD/AOZORA-OS: (OS: )\n"

	printf "OS: making common files and directories\n"
#create needed files
	mkdir -p $(TEMPDIR)/iso $(ENVDIR) _build
	rm -f $(TEMPDIR)/iso/fat.img $(ENVDIR)/Aozora-OS.iso 
	touch $(TEMPDIR)/iso/fat.img $(ENVDIR)/Aozora-OS.iso $(ENVDIR)/harddrive.hhd

	truncate -s 32m  	$(TEMPDIR)/iso/fat.img
	truncate -s 1244m  	$(ENVDIR)/Aozora-OS.iso
	truncate -s 10G   	$(ENVDIR)/harddrive.hhd
#end

	printf "OS: formating iso.fat32\n"
#format iso
	parted $(ENVDIR)/Aozora-OS.iso -s -a minimal mklabel gpt
	parted $(ENVDIR)/Aozora-OS.iso -s -a minimal mkpart EFI fat32 64s 65600s 
	parted $(ENVDIR)/Aozora-OS.iso -s -a minimal name 1 EFI-PART
	parted $(ENVDIR)/Aozora-OS.iso -s -a minimal mkpart primary 65601s 2547678s
	parted $(ENVDIR)/Aozora-OS.iso -s -a minimal name 2 AOZORA-OS-FS-PART
	parted $(ENVDIR)/Aozora-OS.iso -s -a minimal toggle 1 boot
#end

	printf "OS: building files\n"
#building subdirs
	printf "OS: STARTING BUILD/COMMON: (CM: )\n"
	make -C common build --no-print-directory
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
	rm -f $(ENVDIR)/Aozora-OS.iso
#===end clean===

#===make run===
.PHONY: run
run: build

	printf "STARTING RUN/AOZORA-OS: (OS: )\n"

	rm -f $(TEMPDIR)/qemu-log.txt
	qemu-system-x86_64 \
		-machine type=q35,accel=kvm \
		-cpu host \
		-smp 8,cores=8,threads=1,sockets=1  \
		-m 4G \
		-no-reboot \
		-drive format=raw,if=pflash,file=/usr/share/ovmf/x64/OVMF.fd,readonly=on \
		-drive format=raw,if=ide,file=$(ENVDIR)/Aozora-OS.iso,id=bootdisk \
		-drive format=raw,if=ide,file=$(ENVDIR)/harddrive.hhd,id=harddisk \
		#-device ide-hd,drive=bootdisk,bootindex=1 \
		-usb \
		-vga vmware \
		-D $(TEMPDIR)/qemu-log.txt \
		-d cpu_reset \
		-serial vc \
#===end run===

#===make debug===	
.PHONY: debug
debug: build
	mkdir -p _dump
	objdump -D -Mintel,x86-64 _temp/boot/BOOTX64.EFI > _dump/boot.asm
#===end debug===

#===make push===
.PHONY: push
push: 
	git add .
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

.PHONY: full
full: clean run
