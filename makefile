#.SILENT:

ASM_SRC_FILES := $(shell find src -name *.asm)
ASM_OBJ_FILES := $(patsubst src/%.asm, temp/src/%.o, $(ASM_SRC_FILES) )

$(ASM_OBJ_FILES): temp/src/%.o : src/%.asm
	mkdir -p $(dir $@) 
	nasm -w-other -f elf64 $(patsubst temp/src/%.o, src/%.asm, $@) -o $@ 

# make build

.PHONY: build
build: $(ASM_OBJ_FILES)
	mkdir -p temp/disk
	x86_64-elf-ld -T linker.ld -o temp/disk/disk.elf $(ASM_OBJ_FILES)
	objcopy -O binary temp/disk/disk.elf out/disk.bin 

# make clean

.PHONY: clean
clean:
	rm -r temp && mkdir temp	
	rm -r out && mkdir out

# make run

.PHONY: run
run: build
	qemu-img dd if=out/disk.bin of=out/disk.hhd
	qemu-system-x86_64 -hda out/disk.hhd

# make debug
	
.PHONY: debug
debug: build
	objdump -D -Mintel,i8086 -m i8086 -b binary out/disk.bin

#make push

.PHONY: push
push: 
	git add .
	printf "Add commit message: "
	read VAR; git commit -m "$$VAR"
	git push