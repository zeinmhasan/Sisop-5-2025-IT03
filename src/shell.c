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
