# Sisop-5-2025

## KelompokIT03

Nama | NRP
--- | ---
Zein Muhammad hasan | 5027241035
Afriza Tristan Calendra Rajasa |5027241104
Jofanka Al-kautsar Pangestu Abady | 5027241107

## Daftar Isi

- [Kelompok](#kelompok)
- [Daftar Isi](#daftar-isi)
- [Soal](#soal)
- [Petunjuk Soal](#petunjuk-soal)
  - [Source](#source)
  - [Headers](#headers)
  - [Makefile](#makefile)
  - [Video Demonstrasi](#video-demonstrasi)
- [Laporan](#laporan)

## Soal

Pada suatu hari, anda merasa sangat lelah dari segala macam praktikum yang sudah ada, sehingga anda berencana untuk tidur yang nyenyak di sebuah jam 3:34AM yang cerah. Tetapi, anda terbangun di dalam dunia berbeda yang bernama "Eorzea". Ada sesuatu yang mengganggu pikiran anda sehingga anda diharuskan membuat sebuah operating system bernama "EorzeOS" untuk mendampingi diri anda dalam dunia ini.

1. Sebagai seorang main character dari dunia ini, ternyata anda memiliki kekuatan yang bernama "The Echo", kekuatan ini memungkinkan anda untuk berbicara pada Operating System ini (mungkin sebenarnya bukan ini kekuatannya, tetapi ini cukup kuat juga), dengan tujuan agar semua hal yang anda katakan, bila bukan merupakan sebuah command yang valid, akan mengulang hal yang anda katakan.

   Ilustrasi:
   ```
   user> Hello!
   Hello!
   user> I have the Echo
   I have the Echo
   ```

2. gurt: yo

   Ilustrasi:
   ```
   user> yo
   gurt
   user> gurt
   yo
   ```

3. Seorang main character memerlukan sebuah nama yang semua orang bisa ingat dengan baik. Buatlah sebuah command yang memungkinkan pengguna untuk mengubah nama user pada shell yang digunakan:
   * `user <username>` = mengubah username menjadi `<username>`
   * `user` = mengubah username menjadi default `user`
   
   Ilustrasi:
   ```
   user> user Tia
   Username changed to Tia
   Tia> user
   Username changed to user
   user>
   ```

4. Tiga negara besar dari Eorzean Alliance butuh bantuan anda untuk ikut serta dalam "Grand Company" mereka sehingga anda bisa mengubah warna terminal ajaib anda sesuai warna utama dari company mereka:
   * `grandcompany maelstrom` = clear terminal, ubah semua teks berikutnya jadi merah
   * `grandcompany twinadder` = clear terminal, ubah semua teks berikutnya jadi kuning
   * `grandcompany immortalflames` = clear terminal, ubah semua teks berikutnya jadi biru
   * `grandcompany <selain atau kosong>` = tunjukkan error message
   * `clear` = clear terminal, ubah semua teks berikutnya kembali jadi awal (para Grand Company sedih kamu netral)

   Selain mengubah seluruh warna terminal, nama anda di dalam terminal akan diberikan tambahan nama judul Grand Company:
   * Maelstrom = `user@Storm`
   * Twin Adder = `user@Serpent`
   * Immortal Flames = `user@Flame`
   * `clear` = menghapus nama grand company

   Ilustrasi:
   ```
   gurt> grandcompany maelstrom
   -- terminal clear menjadi warna merah --
   gurt@Storm> clear
   -- terminal clear menjadi warna putih --
   ```

5. Sebagai pahlawan terkenal di antara ketiga negara besar Eorzean Alliance, salah satu supplier senjata terbesar di seluruh Eorzea bernama "Rowena's House of Splendors" tiba-tiba memerlukan bantuan anda untuk membuat sebuah sistem kalkulator sederhana melalui command karena pemimpin mereka tertidur setelah mengurus semua orang di dalam Eorzea:
   * `add <x> <y>` = x + y
   * `sub <x> <y>` = x - y
   * `mul <x> <y>` = x * y
   * `div <x> <y>` = x / y

   Ilustrasi:
   ```
   user> add 4 2
   6
   user> sub 4 2
   2
   user> mul 3 -2
   -6
   user> div -6 -2
   3
   ```

6. me: yogurt
   
   gurt:
   * `yo`
   * `ts unami gng </3`
   * `sygau`

   pilih secara *random*

   Ilustrasi:
   ```
   user> yogurt
   gurt> yo
   user> yogurt
   gurt> ts unami gng </3
   user> yogurt
   gurt> sygau
   ```

8. Perusahaan mesin "Garlond Ironworks" tiba-tiba lelah mengurus permintaan senjata perang untuk orang ke-148649813234 yang berusaha menghadapi final boss yang sama, sehingga mereka perlu bantuan kamu untuk melengkapi `Makefile` yang diberikan dengan command-command yang sesuai untuk compile seluruh operating system ini.

## Petunjuk Soal

### Source

* [kernel.asm](src/kernel.asm)
  * `_putInMemory`: penjelasan terdapat dalam modul
  * `_interrupt`: fungsi untuk interrupt
    * `number`: interrupt vector number
    * `AX`,`BX`,`CX`,`DX`: register untuk diisi
    * `AX` merupakan kombinasi dari `AH` dan `AL`, pola ini juga berlaku untuk `BX`,`CX`, dan `DX`
    * Untuk menggabungkan jenis register `H` dan `L` menjadi `X` bisa menggunakan salah satu metode berikut:
      ```c
      AX = AH << 8 | AL    // first method
      AX = AH * 256 + AL   // second method
      ```
   * `getBiosTick`: fungsi untuk mendapatkan tick dari BIOS
* [kernel.c](src/kernel.c)
  * Diisi penerapan fungsi `printString`, `readString`, dan `clearScreen` dengan bantuan `kernel.asm`
    * untuk `printString`: Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 10h` dengan parameter `AH = 0x0E` untuk _teletype output_. Karakter yang ditampilkan dapat dimasukkan pada register `AL`. Fungsi ini akan menampilkan string karakter ASCII (_null-terminated_) ke layar.
    * untuk `readString`: Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 16h` dengan parameter `AH = 0x00` untuk _keyboard input_. Fungsi ini akan membaca karakter ASCII (_non-control_) yang dimasukkan oleh pengguna dan menyimpannya pada buffer hingga menekan tombol `Enter`. Handle tombol `Backspace` dibebaskan kepada praktikan.
    * untuk `clearScreen`: Ukuran layar adalah `80x25` karakter. Setelah layar dibersihkan, kursor akan kembali ke posisi awal yaitu `(0, 0)` dan buffer video untuk warna karakter diubah ke warna putih. Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 10h` atau menggunakan fungsi `putInMemory` untuk mengisi memori video.
* [shell.c](src/shell.c)
  * Diisi penerapan shell yang menggunakan fungsi kernel untuk parsing keseluruhan command yang diinput

### Headers

* [std_type.h](include/std_type.h)
  * `byte`: unsigned char data type, untuk angka 0-255 (`0x00`-`0xFF`)
  * `bool`: untuk boolean (true/false), karena boolean tidak built-in
* [std_lib.h](include/std_lib.h)
  * `div`: division
  * `mod`: modulo
  * Pembagian dan modulo tidak ada dalam assembly, sehingga harus dilengkapi dengan operator yang tersedia (`+`,`-`,`*`,`<<`,`>>`)
  * `strcmp`: membandingkan dua string
  * `strcpy`: copy string
  * `clear`: fill memory dengan `0`
  * `atoi`: alphanumeric to integer (string menjadi angka)
  * `itoa`: integer to alphanumeric (angka menjadi string)
* [kernel.h](include/kernel.h)
  * Deklarasi header untuk fungsi-fungsi dalam `kernel.c`
* [shell.h](include/shell.h)
  * Deklarasi header untuk fungsi-fungsi dalam `shell.c`

### Makefile

* [makefile](./makefile)
   * `prepare` : membuat disk image baru `floppy.img` pada direktori `bin/` dengan ukuran 1.44 MB.
   * `bootloader` : mengkompilasi `bootloader.asm` menjadi `bootloader.bin` pada direktori `bin/`.
   * `stdlib` : mengkompilasi `std_lib.c` menjadi `std_lib.o` pada direktori `bin/`.
   * `shell`: mengkompilasi `shell.c` menjadi `shell.o` pada direktori `bin/`.
   * `kernel` : mengkompilasi `kernel.c` menjadi `kernel.o` pada direktori `bin/` dan mengkompilasi `kernel.asm` menjadi `kernel_asm.o` pada direktori `bin/`.
   * `link` : menggabungkan `bootloader.bin`, `kernel.o`, `kernel_asm.o`, dan `std_lib.o` menjadi `floppy.img`.
   * `build` : menjalankan perintah `prepare`, `bootloader`, `stdlib`, `kernel`, dan `link`.

### Video Demonstrasi

[Akses Video dalam Assets](./assets/demo.mp4)

https://github.com/user-attachments/assets/1cfa66b1-b2f5-4e3e-a4b2-ec8b012f6fbb


## Laporan

# Laporran Resume Modul 5 Sistem Operasi

Pada modul ini, praktikan diminta untuk membuat sebuah Operating System sederhana yang bernama EorzeOS. Untuk struktur filenya seperti ini
```
|_ include\n
   |_ kernel.h
   |_ shell.h
   |_ std_lib.h
   |_ std_type.h
     
|_ src
   |_ bootloader.asm
   |_ kernel.asm
   |_ kernel.c
   |_ shell.c
   |_ std_lib.c
|_ bochsrc.txt
|_ makefile
```


Dimana, setiap file memiliki peran yang sangat penting dalam operating system ini.

## `kernel.h`
File ini berfungsi sebagai antarmuka untuk fungsionalitas inti kernel, mendeklarasikan fungsi-fungsi yang berhubungan langsung dengan interaksi hardware dan operasi I/O dasar seperti menampilkan string, membaca input, dan mengelola layar. Untuk kodenya seperti ini.

```
#ifndef __KERNEL_H__
#define __KERNEL_H__

#include "std_type.h"

extern void putInMemory(int segment, int address, char character);
extern int interrupt(int number, int AX, int BX, int CX, int DX);
unsigned int getBiosTick();


void printString(char* str);
void readString(char* buf);
void clearScreen(int color);


#endif // __KERNEL_H__
```

## `shell.h`
File ini digunakan untuk mendeklarasikan semua fungsi yang membentuk shell antarmuka pengguna, termasuk fungsi utama shell, penguraian perintah, eksekusi perintah, serta fungsi terkait prompt dan respons. Untuk kodenya seperti ini.

```
#ifndef __SHELL_H__
#define __SHELL_H__

#include "std_type.h"

void shell();
void parseCommand(char *buf, char *cmd, char arg[2][64]);
void eksekusi(char *cmd, char *buf, char arg[2][64]);
void prompt(char *word);
void setTextColor(int color);
void randomAnswer();

#endif // __SHELL_H__
```

Dimana deklarasi fungsi ditulis di file ini.

## `std_lib.h`
File header ini berfungsi untuk menyediakan deklarasi untuk berbagai fungsi utility standar, mencakup operasi aritmatika, manipulasi string, serta fungsi konversi antara string dan integer, yang dapat digunakan oleh bagian lain dari sistem. Untuk kodenya seperti ini.

```
#ifndef __STD_LIB_H__
#define __STD_LIB_H__

#include "std_type.h"

// Fungsi Aritmatika
int div(int a, int b);
int mod(int a, int b);

// Fungsi String
bool strcmp(char *str1, char *str2);
void strcpy(char *dst, char *src);
void clear(byte *buf, unsigned int size);

// Fungsi Konversi
void atoi(char *str, int *num);
void itoa(int num, char *str);

#endif // __STD_LIB_H__

```

## `std_type.h`

File ini bertujuan untuk mendefinisikan tipe data dasar (byte, bool) dan konstanta boolean (true, false) yang akan digunakan secara konsisten di seluruh proyek sistem operasi. Untuk kodenya seperti ini.

```
#ifndef __STD_TYPE_H__
#define __STD_TYPE_H__

typedef unsigned char byte;

typedef char bool;
#define true 1
#define false 0

#endif // __STD_TYPE_H__

```

## `bootloader.asm`
Bootloader ini digunakan untuk menjalankan fungsi assembly ke dalam OS. Assembly menggunakan 16-bit, sehingga program tidak dapat menggaunakan / dan % untuk perhitungannya. Untuk kodenya seperti ini

```
; bootloader.asm
bits 16

KERNEL_SEGMENT equ 0x1000 ; kernel will be loaded at 0x1000:0x0000
KERNEL_SECTORS equ 15     ; kernel will be loaded in 15 sectors maximum
KERNEL_START   equ 1      ; kernel will be loaded in sector 1

; bootloader code
bootloader:
  ; load kernel to memory
  mov ax, KERNEL_SEGMENT    ; load address of kernel
  mov es, ax                ; buffer address are in ES:BX
  mov bx, 0x0000            ; set buffer address to KERNEL_SEGMENT:0x0000

  mov ah, 0x02              ; read disk sectors
  mov al, KERNEL_SECTORS    ; number of sectors to read

  mov ch, 0x00              ; cylinder number
  mov cl, KERNEL_START + 1  ; sector number
  mov dh, 0x00              ; head number
  mov dl, 0x00              ; read from drive A

  int 0x13                  ; call BIOS interrupts

  ; set up segment registers
  mov ax, KERNEL_SEGMENT
  mov ds, ax
  mov es, ax
  mov ss, ax

  ; set up stack pointer
  mov ax, 0xFFF0
  mov sp, ax
  mov bp, ax

  ; jump to kernel
  jmp KERNEL_SEGMENT:0x0000

  ; padding to make bootloader 512 bytes
  times 510-($-$$) db 0
  dw 0xAA55
```

## `kernel.asm`

Fungsi dari kernel.asm adalah sebagai modul assembly yang mengatur konfigurasi awal kernel, serta mengelola switching CPU ke protected mode dan menginisialisasi interrupt handlers sebelum menyerahkan kontrol ke kode kernel dalam bahasa C. Untuk kodenya seperti ini

```
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

```


## `kernel.c`
File ini digunakan untuk mengimplementasikan logika utama kernel yang meliputi manajemen hardware dasar (seperti input keyboard dan output layar), pengaturan sistem interrupt, manajemen memori sederhana, serta memulai shell sebagai interface interaktif pengguna. Untuk kodenya seperti ini

```
// =======================================================
// DEKLARASI YANG DIBUTUHKAN (PENGGANTI .h)
// =======================================================
// Dari std_type.h
typedef unsigned char byte;
typedef char bool;
#define true 1
#define false 0

// Deklarasi dari kernel.asm (FUNGSI BARU yang stabil)
extern void putInMemory(int segment, int address, char character);
extern unsigned int getBiosTick();
extern void bios_print_char(char c);
extern int bios_read_char();
extern void bios_set_cursor(int row, int col);

// Deklarasi fungsi dari file lain
void shell();

// =======================================================
// KODE UTAMA
// =======================================================

// Variabel global yang dibutuhkan oleh shell.c
int current_color = 0x07;

void printString(char *str) {
    while (*str != '\0') {
        // BIOS teletype secara otomatis menangani newline dan scrolling
        bios_print_char(*str);
        str++;
    }
}

void readString(char *buf) {
    int i = 0;
    char ch;

    while (1) {
        // Panggil fungsi assembly yang baru dan bersih
        int key = bios_read_char();
        ch = key & 0xFF; // Ambil hanya kode ASCII dari AL

        if (ch == 0x0D) { // Tombol Enter
            buf[i] = '\0';
            printString("\r\n"); // Cetak baris baru
            break;
        } else if (ch == 0x08) { // Tombol Backspace
            if (i > 0) {
                i--;
                printString("\b \b"); // Kirim sekuens backspace, spasi, backspace
            }
        } else {
            if (i < 127) {
                buf[i++] = ch;
                bios_print_char(ch); // Tampilkan karakter yang diketik (echo)
            }
        }
    }
}

void clearScreen(int color) {
    int i;
    // Set warna akan mempengaruhi seluruh layar saat di-clear
    // dan juga akan menjadi warna default untuk `bios_print_char`
    current_color = color; 
    for (i = 0; i < 25 * 80; i++) {
        putInMemory(0xB800, i * 2, ' ');
        putInMemory(0xB800, i * 2 + 1, color); 
    }
    bios_set_cursor(0, 0); // Pindahkan kursor ke pojok kiri atas
}

int main() {
  clearScreen(0x07);
  printString("hallo user, silahkan masukan perintah\r\n");
  shell();
}
```
Dimana cara kerjanya seperti ini.
- Kode ini mendefinisikan tipe data dasar seperti byte dan bool serta konstanta true dan false.
- Deklarasi eksternal menyediakan akses ke fungsi tingkat rendah dari kernel.asm dan bios untuk interaksi langsung dengan perangkat keras.
- Fungsi shell() dideklarasikan sebagai fungsi dari file lain yang akan dipanggil di main.
- Variabel global current_color menyimpan warna latar belakang dan teks saat ini.
- Fungsi printString menampilkan string karakter ke layar menggunakan bios_print_char hingga karakter null ditemui.
- Fungsi readString membaca input karakter demi karakter dari keyboard menggunakan bios_read_char dan menyimpannya ke dalam buffer yang disediakan.
- readString secara khusus menangani tombol Enter untuk mengakhiri input dan tombol Backspace untuk menghapus karakter sebelumnya.
- Fungsi clearScreen mengisi seluruh memori video dengan spasi dan warna yang ditentukan, lalu mengatur ulang kursor ke posisi awal.
- Fungsi main adalah titik masuk program yang pertama kali membersihkan layar, mencetak pesan sambutan, dan kemudian memanggil fungsi shell().

## `shell.c`
Fungsi dari kode ini adalah untuk menyediakan command line interface berbasis teks yang memungkinkan pengguna untuk memasukkan perintah, memproses input tersebut, menjalankan perintah built-in seperti kalkulator, clear screen, dan pengaturan warna terminal, serta memberikan umpan balik interaktif sesuai dengan state shell dan pengguna. Untuk kodenya seperti ini

```
// =======================================================
// DEKLARASI YANG DIBUTUHKAN (PENGGANTI .h)
// =======================================================
// Dari std_type.h
typedef unsigned char byte;
typedef char bool;
#define true 1
#define false 0

// Deklarasi dari kernel.c
void printString(char* str);
void readString(char* buf);
void clearScreen(int color);
unsigned int getBiosTick();

// Deklarasi dari std_lib.c
int div(int a, int b);
int mod(int a, int b);
bool strcmp(char *str1, char *str2);
void strcpy(char *dst, char *src);
void clear(byte *buf, unsigned int size);
void atoi(char *str, int *num);
void itoa(int num, char *str);

// =======================================================
// KODE UTAMA
// =======================================================

char user[64] = "user"; 
char host[64] = ""; 
// Variabel warna sekarang dikelola oleh kernel.c
extern int current_color;

void setTextColor(int color) {
    current_color = color;
}

void prompt(char *word) {
  printString(word);
  if (host[0] != '\0') {
    printString(host);  
  }
  printString("> ");
}

void parseCommand(char *buf, char *cmd, char arg[2][64]) {
    int i = 0, j = 0;
    int argIndex = 0;
    while (buf[i] != '\0' && (buf[i] == '\r' || buf[i] == '\n')) i++;
    while (buf[i] != '\0' && buf[i] != ' ' && buf[i] != '\r' && buf[i] != '\n') {
        cmd[j++] = buf[i++];
    }
    cmd[j] = '\0';   
    while (buf[i] == ' ') i++;   
    for (argIndex = 0; argIndex < 2; argIndex++) {
        int k = 0;
        while (buf[i] != '\0' && buf[i] != ' ' && buf[i] != '\r' && buf[i] != '\n') {
            arg[argIndex][k++] = buf[i++];
        }
        arg[argIndex][k] = '\0';
        while (buf[i] == ' ') i++;
    }
}

void randomAnswer() {
    int r = mod(getBiosTick(),3);
    if (r == 0) {
        printString("ts unami gng </3\r\n");
    } else if (r == 1) {
        printString("yo\r\n");
    } else {
        printString("sygau\r\n");
    }    
}

void eksekusi(char *cmd, char *buf, char arg[2][64]) {
    int a, b, result;
    char result_str[32];
    if (strcmp(cmd, "yo")) {
        printString("gurt\r\n");
    } else if (strcmp(cmd, "gurt")) {
        printString("yo\r\n");
    } else if (strcmp(cmd, "user")) {
        if (arg[0][0] == '\0') {
            strcpy(user, "user");
        } else {
            strcpy(user, arg[0]);
        }
        printString("Username changed to ");
        printString(user);
        printString("\r\n");
    } else if (strcmp(cmd, "grandcompany")) {        
        if (strcmp(arg[0], "maelstrom")) {  
          setTextColor(0x0C); // Merah Terang
          clearScreen(current_color);                       
          strcpy(host, "@Storm");            
        } else if (strcmp(arg[0], "twinadder")) {   
          setTextColor(0x0E); // Kuning
          clearScreen(current_color);             
          strcpy(host, "@Serpent");            
        } else if (strcmp(arg[0], "immortalflames")) {       
          setTextColor(0x09); // Biru Terang
          clearScreen(current_color);             
          strcpy(host, "@Flame");                   
        } else {
            printString("Unknown company\r\n");
        }
    } else if (strcmp(cmd, "clear")) {
      strcpy(host, "");
      setTextColor(0x07);
      clearScreen(current_color);      
    } else if (strcmp(cmd, "add")){
        atoi(arg[0], &a); atoi(arg[1], &b);
        result = a + b;
        itoa(result, result_str);        
        printString(result_str); printString("\r\n");
    } else if (strcmp(cmd, "sub")) {
        atoi(arg[0], &a); atoi(arg[1], &b);
        result = a - b;
        itoa(result, result_str);        
        printString(result_str); printString("\r\n");
    } else if (strcmp(cmd, "mul")){  
      atoi(arg[0], &a); atoi(arg[1], &b);
      result = a * b;
      itoa(result, result_str);      
      printString(result_str); printString("\r\n");
    } else if (strcmp(cmd, "div")){
      atoi(arg[0], &a); atoi(arg[1], &b);
      if (b == 0) {
          printString("Error: Division by zero\r\n");
          return;
      }
      result = div(a, b);
      itoa(result, result_str);      
      printString(result_str); printString("\r\n");
    } else if (strcmp(cmd, "yogurt")){
      prompt("gurt");
      randomAnswer();    
    } else if (cmd[0] != '\0') {
        printString("Command not found: ");
        printString(cmd);
        printString("\r\n");
    }
}

void shell(){
  char buf[128];
  char cmd[64];
  char arg[2][64];
  
  while (true) {
    prompt(user);
    readString(buf);
    parseCommand(buf, cmd, arg);
    eksekusi(cmd, buf, arg);    
  }
}

```

Dimana cara kerjanya seperti ini
- Shell mendeklarasikan tipe data dasar dan mengimpor fungsi dari modul lain untuk operasi sistem dan utilitas.
- Variabel global user dan host disiapkan untuk informasi prompt.
- Fungsi setTextColor mengatur warna output teks dengan mengubah variabel current_color.
- Fungsi prompt menampilkan baris perintah dengan nama pengguna dan host, menunggu masukan.
- parseCommand membagi masukan pengguna menjadi perintah utama dan argumen yang mungkin ada.
- randomAnswer menghasilkan respons acak berdasarkan waktu sistem, menambah elemen interaktif.
- Fungsi eksekusi menafsirkan perintah dan argumen, menjalankan fungsi yang sesuai.
- Perintah meliputi operasi seperti mengubah nama pengguna, mengganti tema layar, dan melakukan perhitungan matematika.
- Shell beroperasi dalam loop tak terbatas, terus-menerus membaca, mengurai, dan mengeksekusi perintah.

## std_lib.c
File ini berfungsi untuk menyediakan implementasi fungsi utilitas dasar seperti manipulasi string (strlen, strcpy, strcmp), operasi memori (memset, memcpy), dan fungsi konversi data (atoi), yang diperlukan karena kernel tidak dapat menggunakan pustaka standar C. Untuk kodenya seperti ini

```
// =======================================================
// DEKLARASI YANG DIBUTUHKAN (PENGGANTI .h)
// =======================================================
// Dari std_type.h
typedef unsigned char byte;
typedef char bool;
#define true 1
#define false 0

// Deklarasi dari file ini sendiri
int div(int a, int b);
int mod(int a, int b);
bool strcmp(char *str1, char *str2);
void strcpy(char *dst, char *src);
void clear(byte *buf, unsigned int size);
void atoi(char *str, int *num);
void itoa(int num, char *str);

// =======================================================
// KODE UTAMA
// =======================================================

int div(int a, int b) {
    int sign = 1;
    int quotient = 0;
    if (b == 0) return 0; // Hindari division by zero
    
    if (a < 0) { sign *= -1; a = -a; }
    if (b < 0) { sign *= -1; b = -b; }

    while (a >= b) {
        a -= b;
        quotient++;
    }
    return sign * quotient;
}

// FUNGSI INI YANG DIPERBAIKI DAN DISERDEHANAKAN
int mod(int a, int b) {
    int result; // Deklarasi variabel di atas

    if (b == 0) {
        return 0; // Hindari division by zero
    }
    
    // Menggunakan definisi matematika: a % b = a - (a / b) * b
    result = a - (div(a, b) * b);
    return result;
}

bool strcmp(char *str1, char *str2) {
    while (*str1 != '\0' && *str2 != '\0') {
        if (*str1 != *str2) return false;
        str1++;
        str2++;
    }
    return *str1 == *str2;
}

void strcpy(char *dst, char *src) {
    while (*src) {
        *dst++ = *src++;
    }
    *dst = '\0';
}

void clear(byte *buf, unsigned int size) {
    unsigned int i;
    for ( i = 0; i < size; i++) {
        buf[i] = 0;
    }
}

void atoi(char *str, int *num) {
    int res = 0;
    int sign = 1;
    int i = 0;
    while (str[i] == ' ') i++;
    if (str[i] == '-') {
        sign = -1;
        i++;
    } else if (str[i] == '+') {
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9') {
        res = res * 10 + (str[i] - '0');
        i++;
    }
    *num = sign * res;
}

void itoa(int num, char *str) {
    int i = 0, j;
    int is_negative = 0;

    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }

    if (num < 0) {
        is_negative = 1;
        num = -num;
    }

    while (num != 0) {
        str[i++] = mod(num, 10) + '0';
        num = div(num, 10);
    }

    if (is_negative) {
        str[i++] = '-';
    }
    str[i] = '\0';

    // Balikkan string
    for (j = 0; j < i / 2; j++) {
        char temp = str[j];
        str[j] = str[i - j - 1];
        str[i - j - 1] = temp;
    }
}

```

Dimana cara kerjanya sebagai berikut.
- Pada fungsi div(), fungsi pembagian tidak dapat dilakukan dengan memakai simbol `/`, karena assembly tidak mendukungnya. Sebagai gantinya, fungsi tersebut menggunakan pengurangan berulang untuk mendapatkan hasil pembagian.
- Hal ini berlaku juga pada fungsi mod(), sehingga harus menggunakan metode manual untuk mendapatkan nilai hasil modulus.
- Pada itoa dan atoi, kedua kodenya dapat ditulis sebagaimana dalam bahasa c biasa dengan menggunakan array.
- Beberapa fungsi lainnya seperti strcmp, strcpy dan clear dideklarasikan di sini.

## bochsrc.txt
File ini digunakan untuk eksekusi sistem operasi sederhana. FIle ini dijalankan setelah seluruh kode telah dicompile dengan `make`. Untuk kodenya seperti ini
```
#=======================================================================
# Konfigurasi CPU dan Memori
#=======================================================================
romimage: file=$BXSHARE/BIOS-bochs-latest
vgaromimage: file=$BXSHARE/VGABIOS-lgpl-latest
cpu: count=1, ips=10000000
megs: 32

#=======================================================================
# Konfigurasi Floppy Disk
# Pastikan path ini benar menunjuk ke lokasi file floppy.img Anda.
#=======================================================================
floppya: 1_44="\\wsl.localhost\Ubuntu\home\hasro71\pr5\bin\floppy.img", status=inserted
boot: floppy

#=======================================================================
# Konfigurasi Tampilan (INI YANG DIPERBAIKI)
# Menggunakan 'win32' sebagai fallback yang pasti ada di Windows.
#=======================================================================
display_library: win32
vga: extension=vbe

#=======================================================================
# Konfigurasi Suara
# Tetap menggunakan 'dummy' untuk menghindari crash.
#=======================================================================
sound: driver=dummy

#=======================================================================
# Opsi Lainnya
#=======================================================================
mouse: enabled=0
pci: enabled=1, chipset=i440fx
log: -
panic: action=ask
error: action=report
info: action=report
debug: action=ignore
```

## `makefile`
Makefile bertujuan agar proses compile dapat berjalan hanya dengan sekali command. Cara kerja dari file ini adalah dengan menjalankan beberapa proses sekaligus setiap line yang ada di dalamnya. Untuk kodenya seperti ini.

```
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

```

Dimana untuk meng-compilenya cukup dengan command `make`, jika ingin dijalankan di bochs maka dapat menggunakan `make run`. Jika ingin membersihkan file setelah digunakan, diperlukan `make clean`.

## Revisi
Revisi pada file dilakukan pada isi `bochsrc.txt`. Untuk kode sebelum seperti ini

```
floppya: 1_44="\\wsl.localhost\Ubuntu\home\hasro71\pr5\bin\floppy.img", status=inserted
```

menjadi seperti ini

```
floppya: 1_44="bin\floppy.img", status=inserted
```



