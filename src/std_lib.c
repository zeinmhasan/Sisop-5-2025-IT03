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
