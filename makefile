.SILENT:

ASM_SRC_FILES := $(shell find src/ -name *.asm )
ASM_OBJ_FILES := $(patsubst src/%.asm, temp/src/%.o, $(ASM_SRC_FILES) )

$(ASM_OBJ_FILES): temp/src/%.o : src/%.asm
	mkdir -p $(dir $@) 
	nasm -w-other -i src -f elf64 $(patsubst temp/src/%.o, src/%.asm, $@) -o $@ 

# make build

.PHONY: build
build: $(ASM_OBJ_FILES)
	mkdir -p temp/disk
	x86_64-elf-ld -T build/linker.ld -o temp/disk/disk.elf $(ASM_OBJ_FILES)
	objcopy -O binary temp/disk/disk.elf temp/disk/disk.bin 

# make clean

.PHONY: clean
clean:
	rm -r temp && mkdir temp
	rm -f env/Aozora-OS.iso

# make run

.PHONY: run
run: build
	rm -f env/qemu-log.txt
	rm -f env/Aozora-OS.iso
	qemu-img dd if=temp/disk/disk.bin of=env/Aozora-OS.iso
	qemu-system-x86_64 \
		-accel tcg,thread=single \
		-cpu qemu64 \
		-m 4096 \
		-no-reboot \
		-drive format=raw,media=disk,file=env/Aozora-OS.iso \
		-drive format=raw,media=disk,file=env/harddrive.hhd \
		-serial stdio \
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
	git add .
	printf "Add commit message: " 
	read VAR 							; \
	MAJOR=$$(sed '1!d' build/VERSION) 	; \
	MINOR=$$(sed '2!d' build/VERSION) 	; \
	PATCH=$$(sed '3!d' build/VERSION) 	; \
	VERSTRING="Aozora-OS $$MAJOR.$$MINOR.$$PATCH -> " ; \
	git commit -m "$$VERSTRING$$VAR"
	git push

.PHONY: test
test: 
	MAJOR=$$(sed '1!d' build/VERSION) 	; \
	MINOR=$$(sed '2!d' build/VERSION) 	; \
	PATCH=$$(sed '3!d' build/VERSION) 	; \
	VERSTRING="Aozora-OS $$MAJOR.$$MINOR.$$PATCH -> " 
