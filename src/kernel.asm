; kernel.asm - VERSI FINAL STABIL

global _putInMemory
global _getBiosTick
global _bios_print_char
global _bios_read_char
global _bios_set_cursor

; void putInMemory(int segment, int address, char character)
_putInMemory:
	push bp
	mov bp,sp
	push ds
	mov ax,[bp+4]
	mov si,[bp+6]
	mov cl,[bp+8]
	mov ds,ax
	mov [si],cl
	pop ds
	pop bp
	ret

; unsigned int getBiosTick()
_getBiosTick:
    mov ah, 0x00
    int 0x1A
    mov ax, dx
    ret

; FUNGSI BARU: Mencetak satu karakter menggunakan BIOS teletype
; void bios_print_char(char c)
_bios_print_char:
    push bp
    mov bp, sp
    mov al, [bp+4]  ; Ambil karakter dari argumen
    mov ah, 0x0E      ; Fungsi teletype
    mov bh, 0         ; Halaman 0
    int 0x10
    pop bp
    ret

; FUNGSI BARU: Membaca satu karakter dari keyboard
; int bios_read_char() -> mengembalikan AX (Scan Code & ASCII)
_bios_read_char:
    mov ah, 0x00      ; Tunggu ketikan keyboard
    int 0x16
    ret

; FUNGSI BARU: Mengatur posisi kursor
; void bios_set_cursor(int row, int col)
_bios_set_cursor:
    push bp
    mov bp, sp
    mov dh, [bp+4]  ; Ambil baris (row)
    mov dl, [bp+6]  ; Ambil kolom (col)
    mov bh, 0         ; Halaman 0
    mov ah, 0x02      ; Fungsi set kursor
    int 0x10
    pop bp
    ret
