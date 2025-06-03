prepare:
	mkdir -p build
	dd if=/dev/zero of=build/floppy.img bs=512 count=2880
bootloader:
	nasm -f bin src/bootloader.asm -o build/bootloader.bin
	dd if=build/bootloader.bin of=build/floppy.img bs=512 count=1 conv=notrunc

shell: src/shell.c include/shell.h include/std_lib.h include/std_type.h
	bcc -ansi -c src/shell.c -Iinclude -o build/shell.o
	
kernel: src/kernel.asm src/kernel.c include/kernel.h include/std_lib.h include/std_type.h shell
	nasm -f as86 src/kernel.asm -o build/kernel-asm.o
	bcc -ansi -c src/kernel.c -Iinclude -o build/kernel.o
	ld86 -o build/kernel.bin -d build/kernel.o build/kernel-asm.o build/shell.o
	dd if=build/kernel.bin of=build/floppy.img bs=512 seek=1 conv=notrunc

build: prepare bootloader kernel

clean: rm -rf build
