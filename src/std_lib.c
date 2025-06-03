#include "std_lib.h"

int div(int a, int b) {
  int q = 0;
  int sign = (a < 0) ^ (b < 0) ? -1 : 1;
  a = a < 0 ? -a : a;
  b = b < 0 ? -b : b;
  while (a >= b) {
    a -= b;
    q++;
  }
  return sign * q;
}

int mod(int a, int b) {
  int r = a < 0 ? -a : a;
  b = b < 0 ? -b : b;
  while (r >= b) r -= b;
  return a < 0 ? -r : r;
}

bool strcmp(char *str1, char *str2) {
  while (*str1 && *str2) {
    if (*str1 != *str2) return false;
    str1++; str2++;
  }
  return *str1 == *str2;
}

void strcpy(char *dst, char *src) {
  while (*src) {
    *dst++ = *src++;
  }
  *dst = 0;
}

void clear(byte *buf, unsigned int size) {
  for (int i = 0; i < size; i++) {
    buf[i] = 0;
  }
}

void atoi(char *str, int *num) {
  int i = 0, sign = 1;
  *num = 0;
  if (str[i] == '-') {
    sign = -1;
    i++;
  }
  while (str[i] >= '0' && str[i] <= '9') {
    *num = *num * 10 + (str[i] - '0');
    i++;
  }
  *num *= sign;
}

void itoa(int num, char *str) {
  int i = 0, sign = 0;
  if (num < 0) {
    sign = 1;
    num = -num;
  }
  do {
    str[i++] = (num % 10) + '0';
    num /= 10;
  } while (num > 0);
  if (sign) str[i++] = '-';
  str[i] = 0;

  // reverse
  for (int j = 0; j < i / 2; j++) {
    char temp = str[j];
    str[j] = str[i - j - 1];
    str[i - j - 1] = temp;
  }
}
