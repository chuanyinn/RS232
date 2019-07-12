// filename - query.c
// Rev.A
#include <bios.h>
#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
// misc defines
#define COM1 0
#define XMIT_MASK 0x0610
#define CHAR_MASK 0x00FF
#define STATUS_MASK 0xFF00
#define TIMEDOUT 0x8000
#define ESC 0x1B
#define CR 0x0D
#define LF 0x0A
// rs232 buffer
char cRS232Buffer[32];
// example command
char cUnitsCmd[] = "@\x27\r\n";
// misc vars
short i;
short nComStatus;
unsigned nChar = 0x0;
unsigned nKeyCode = 0x0;
// misc routines
short sendcommand(char *);
void main(int argc, char *argv[]) {
 // init RS232 port COM1, 2400 baud, 8 data bits, no
parity, 1 stop bit
 _bios_serialcom(_COM_INIT, COM1,
 _COM_2400|_COM_CHR8|_COM_NOPARITY|_COM_STOP1);
 // loop until the Esc key is pressed 
  do {
 switch(_toupper(nKeyCode)) {
 case 'U':
 nComStatus = sendcommand(cUnitsCmd);
 break;

 default:
 break;
 }

 // continue reading rs232 while !keystroke
 while (!kbhit()) {
 // read rs232
 i = 0;
 cRS232Buffer[0] = '\0';
 while((nChar = _bios_serialcom(_COM_RECEIVE, COM1,
0)) != LF
 && !(nChar&STATUS_MASK)) {
 cRS232Buffer[i++] = (char)(nChar&CHAR_MASK);
 }

 // if no error print string
 if(!(nChar&STATUS_MASK)) {
 printf("%s\n", cRS232Buffer);
 }
 }

 nKeyCode = _getch();

 } while (nKeyCode != ESC);
 }
// sends command string out serial port
short sendcommand(char *pString) {
short n;
short nStringLen;
short nComStatus;
 nStringLen = (short)strlen(pString);
 for(n = 0; n < nStringLen; n++) {
 while ((short)_bios_serialcom(_COM_STATUS, COM1,
0)&XMIT_MASK != 0);
 nComStatus = (short)_bios_serialcom(_COM_SEND, COM1,
(unsigned)pString[n]);
 }

 return(nComStatus);
 } 