.SILENT:

TEMPDIR := _temp
ENVDIR := _env

#===make build=== 
.PHONY: build
build: 
	/usr/bin/time -f "make finished in %e seconds" make notime

.PHONY: notime
notime:
	printf "STARTING BUILD/AOZORA-OS: (OS: )\n"

	printf "OS: making common files\n"
#create needed files
	mkdir -p $(TEMPDIR)/iso $(_env)
	rm -f $(TEMPDIR)/iso/fat.img $(ENVDIR)/Aozora-OS.iso 
	touch $(TEMPDIR)/iso/fat.img $(ENVDIR)/Aozora-OS.iso $(ENVDIR)/harddrive.hhd

	truncate -s 4096k  $(TEMPDIR)/iso/fat.img
	truncate -s 1280m  $(ENVDIR)/Aozora-OS.iso
	truncate -s 10G    $(ENVDIR)/harddrive.hhd
#end

	printf "OS: formating iso.fat16\n"
#format iso
	parted $(ENVDIR)/Aozora-OS.iso -s -a minimal mklabel gpt
	parted $(ENVDIR)/Aozora-OS.iso -s -a minimal mkpart EFI fat16 2048s 10240s 
	parted $(ENVDIR)/Aozora-OS.iso -s -a minimal name 1 EFI-PART
	parted $(ENVDIR)/Aozora-OS.iso -s -a minimal mkpart primary 10241s 2621406s
	parted $(ENVDIR)/Aozora-OS.iso -s -a minimal name 2 AOZORA-OS-FS-PART
	parted $(ENVDIR)/Aozora-OS.iso -s -a minimal toggle 1 boot
#end

	printf "OS: building files\n"
#building subdirs
	printf "OS: STARTING BUILD/BOOT: (BT: )\n"
	make -C boot build
	printf "OS: STARTING BUILD/KERNEL: (KN: )\n"
	make -C kernel build
	printf "OS: STARTING BUILD/TOOLS: (TL: )\n"
	make -C tools build
#end
#===end build=== 

#===make clean===
.PHONY: clean
clean:
	/usr/bin/time -f "make finished in %e seconds" \
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
		-drive format=raw,if=pflash,file=/usr/share/ovmf/OVMF.fd,readonly=on \
		-drive format=raw,file=$(ENVDIR)/Aozora-OS.iso \
		-drive format=raw,file=$(ENVDIR)/harddrive.hhd \
		-smp 1 -usb -vga std \
		-d int \
		-D $(ENVDIR)/qemu-log.txt
#===end run===

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
	git add src
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
