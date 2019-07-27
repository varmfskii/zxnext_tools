#ifndef ZXNFTPS_H
#define ZXNFTPS_H
#include <stdint.h>
#include "../zxnftp.h"

#define BSIZE 255
#define CONFIG "zxnftp.cfg"
#define ERROR 1
#define ID "ZXNFTP 0.2 alpha"
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

int16_t cmdresponse(char *);
int16_t uartchar(void);
int16_t uartresponse(void);
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
uint8_t setbaud(int32_t);
void uartwrite(const char *, int16_t);

__sfr __banked __at 0x133b TX;
__sfr __banked __at 0x143b RX;

extern char buf[], bbuf[], line[];
#endif
