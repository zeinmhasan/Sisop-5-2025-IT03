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
