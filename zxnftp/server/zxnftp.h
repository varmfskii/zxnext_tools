 #ifndef ZXNFTPS_H
#define ZXNFTPS_H
#include <stdint.h>
#include "../zxnftp.h"

#define BSIZE 255
#define CONFIG1 "zxnftp.cfg"
#define CONFIG2 "c:/sys/zxnftp.cfg"
#define CONFIG3 "/sys/zxnftp.cfg"
#define ERROR 1
#define ID "ZXNFTP 1.0"
#define LINE 0xff
#define OK 0
#define SEND_FAIL 3
#define SEND_OK 2
#define STRING 0
#define RAW 1
#define UARTWRITES(X) uartwrite(X, strlen(X))
#define UART_BUSY 0x02
#define UART_DATA 0x01
#define UART_FULL 0x04
#define netrxln(X) netrx((X), NULL, (LINE))
#define netrxs(X) netrx((X), NULL, (STRING))
#define nettxln(X) nettx((X), (LINE))
#define nettxs(X) nettx((X), (STRING))
#define netclose() cmdresponse("AT+CIPCLOSE=0\r\n")

char cmdresponse(char *);
char setbaud(int32_t);
char uartresponse(void);
void cmd_baud(void);
void cmd_cd(void);
void cmd_drive(void);
void cmd_exit(void);
void cmd_get(void);
void cmd_id(void);
void cmd_l_(void);
void cmd_ls(void);
void cmd_mkdir(void);
void cmd_put(void);
void cmd_pwd(void);
void cmd_quit(void);
void cmd_rm(void);
void cmd_rmdir(void);
void cmd_simple(const char *, uint8_t (*fn)(char *));
void netrx(char *, int16_t *, int16_t);
void nettx(const char *, int16_t);
void senderr(void);
void uartread(char *, int16_t);
void uartwrite(const char *, int16_t);

__sfr __banked __at 0x133b TX;
__sfr __banked __at 0x143b RX;
__sfr __banked __at 0x153b UART_CTL;
__sfr __banked __at 0x243b NEXT_SEL;
__sfr __banked __at 0x253b NEXT_RW;
__sfr __at 0xff TIMEX;

//extern char buf[], bbuf[], line[];
extern char *buf, *bbuf, *line;
extern char old_clock;

inline char uartreadc(void) {
  while(!TX&UART_DATA);
  return RX;
}

inline void uartwritec(char c) {
  while(TX&UART_BUSY);
  TX=c;
}
#endif
