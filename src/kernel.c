/// === kernel.c ===
#include "shell.h"
#include "kernel.h"



void printString(char *str) {
  int i = 0;
  while (str[i] != 0) {
    interrupt(0x10, 0x0E00 + str[i], 0, 0, 0);
    i++;
  }
}

void readString(char *buf) {
  int i = 0;
  char c;
  while (1) {
    c = interrupt(0x16, 0, 0, 0, 0);
    if (c == 0x0D) {
      buf[i] = 0;
      printString("\r\n");
      return;
    } else if (c == 0x08 && i > 0) {
      i--;
      printString("\b \b");
    } else if (c >= 32 && c <= 126) {
      buf[i++] = c;
      interrupt(0x10, 0x0E00 + c, 0, 0, 0);
    }
  }
}

void clearScreen() {
  int i;
  for (i = 0; i < 25 * 80; i++) {
    putInMemory(0xB800, i * 2, ' ');
    putInMemory(0xB800, i * 2 + 1, 0x07);
  }
  interrupt(0x10, 0x0200, 0, 0, 0); // reset cursor
}

int main() {
  clearScreen();
  // shell();
  return 0;
}
