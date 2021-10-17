x86_64_asm_source_files := $(shell find src/impl/x86_64 -name *.asm)
x86_64_asm_object_files := $(patsubst src/impl/x86_64/%.asm, build/x86_64/%.o, $(x86_64_asm_source_files))
cpp_source_files := $(shell find src/impl/x86_64 -name *.cpp)
cpp_object_files := $(patsubst src/impl/x86_64/%.cpp, build/x86_64/%.o, $(cpp_source_files))
kernel_source_files := $(shell find src/impl/kernel -name *.cpp)
kernel_object_files := $(patsubst src/impl/kernel/%.cpp, build/kernel/%.o, $(kernel_source_files))
library_source_files := $(shell find src/impl/lib -name *.cpp)
library_object_files := $(patsubst src/impl/lib/%.cpp, build/lib/%.o, $(library_source_files))

$(kernel_object_files) : build/kernel/%.o : src/impl/kernel/%.cpp
	mkdir -p $(dir $@) && \
	x86_64-elf-g++ -c -I src/intf -ffreestanding -fpermissive $(patsubst build/kernel/%.o, src/impl/kernel/%.cpp, $@) -o $@

$(cpp_object_files) : build/x86_64/%.o : src/impl/x86_64/%.cpp
	mkdir -p $(dir $@) && \
	x86_64-elf-g++ -c -I src/intf -ffreestanding $(patsubst build/x86_64/%.o, src/impl/x86_64/%.cpp, $@) -o $@ -lstdc++

$(library_object_files) : build/lib/%.o : src/impl/lib/%.cpp
	mkdir -p $(dir $@) && \
	x86_64-elf-g++ -c -I src/intf -ffreestanding $(patsubst build/lib/%.o, src/impl/lib/%.cpp, $@) -o  $@ -lstdc++

$(x86_64_asm_object_files): build/x86_64/%.o : src/impl/x86_64/%.asm
	mkdir -p $(dir $@) && \
	nasm -f elf64 $(patsubst build/x86_64/%.o, src/impl/x86_64/%.asm, $@) -o $@

.PHONY: build-x86_64
build-x86_64: $(x86_64_asm_object_files) $(cpp_object_files) $(kernel_object_files) $(library_object_files)
	mkdir -p dist/x86_64 && \
	x86_64-elf-ld -n -o dist/x86_64/kernel.bin -T targets/x86_64/linker.ld $(x86_64_asm_object_files) $(cpp_object_files) $(kernel_object_files) $(library_object_files) && \
	cp dist/x86_64/kernel.bin targets/x86_64/iso/boot/kernel.bin && \
	grub-mkrescue /usr/lib/grub/i386-pc -o dist/x86_64/kernel.iso targets/x86_64/iso