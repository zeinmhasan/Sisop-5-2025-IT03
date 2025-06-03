#include "shell.h"
#include "kernel.h"
#include "std_lib.h"

void shell(){
  char buf[128];
  char cmd[64];
  char arg[2][64];

  printString("Welcome to EorzeOS!\n");
  while (true) {
    printString("> ");
    clear((byte *)buf, 128);
    readString(buf);
    clear((byte *)cmd, 64);
    clear((byte *)arg[0], 64);
    clear((byte *)arg[1], 64);

    parseCommand(buf, cmd, arg);

    if (strcmp(cmd, "clear")) {
      clearScreen();
    } else if (strcmp(cmd, "echo")) {
      printString(arg[0]);
      printString(" ");
      printString(arg[1]);
      printString("\n");
    } else if (strcmp(cmd, "help")) {
      printString("Available commands:\n");
      printString("clear - clear screen\n");
      printString("echo - print text\n");
      printString("help - show commands\n");
    } else {
      printString("Unknown command\n");
    }
  }
}

void parseCommand(char *buf, char *cmd, char arg[2][64]) {
  int i = 0, j = 0, k = 0;
  bool inArg = false;

  while (buf[i] != 0 && buf[i] != ' ') {
    cmd[i] = buf[i];
    i++;
  }
  cmd[i] = 0;

  while (buf[i] == ' ') i++;
  while (buf[i] != 0 && buf[i] != ' ') {
    arg[0][j++] = buf[i++];
  }
  arg[0][j] = 0;

  while (buf[i] == ' ') i++;
  while (buf[i] != 0) {
    arg[1][k++] = buf[i++];
  }
  arg[1][k] = 0;
}
