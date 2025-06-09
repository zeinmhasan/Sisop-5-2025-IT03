# Compiler dan Tool
CC = bcc
AS = nasm
LD = ld86

# Flags
CFLAGS = -ansi -c

# Definisi file object
C_OBJECTS = obj/kernel.o obj/shell.o obj/std_lib.o
ASM_OBJECTS = obj/kernel-asm.o

# Target Default: build semua
all: build

# Target utama: membangun floppy image
build: bin/floppy.img

# Aturan untuk membuat floppy image
bin/floppy.img: bin/bootloader.bin bin/kernel.bin
	@echo "Creating floppy image..."
	dd if=/dev/zero of=$@ bs=512 count=2880
	dd if=bin/bootloader.bin of=$@ bs=512 count=1 conv=notrunc
	dd if=bin/kernel.bin of=$@ bs=512 seek=1 conv=notrunc

# Aturan untuk membuat kernel.bin
bin/kernel.bin: $(C_OBJECTS) $(ASM_OBJECTS)
	@echo "Linking kernel..."
	mkdir -p bin
	$(LD) -o $@ -d $(ASM_OBJECTS) $(C_OBJECTS)

# --- ATURAN KOMPILASI EKSPLISIT ---
# Kita tidak menggunakan -Iinclude karena semua deklarasi sudah ada di dalam file .c

# Aturan umum untuk mengompilasi file C
obj/%.o: src/%.c
	@echo "Compiling $<..."
	mkdir -p obj
	$(CC) $(CFLAGS) -o $@ $<

# Aturan untuk mengompilasi file Assembly kernel
obj/kernel-asm.o: src/kernel.asm
	@echo "Assembling kernel.asm..."
	mkdir -p obj
	$(AS) -f as86 $< -o $@

# Aturan untuk mengompilasi bootloader
bin/bootloader.bin: src/bootloader.asm
	@echo "Assembling bootloader..."
	mkdir -p bin
	$(AS) -f bin $< -o $@

# Target untuk menjalankan Bochs
run: build
	bochs -f bochsrc.txt

# Target untuk membersihkan file
clean:
	@echo "Cleaning up..."
	rm -rf obj bin
