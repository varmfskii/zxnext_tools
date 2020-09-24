#ifndef ZXNFTPC_H
#define ZXNFTPC_H
#include <time.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#ifdef CURSES
#include <curses.h>
#endif
#include "../zxnftp.h"

#define DATASZ 8192
#define LINE -1
#define LINESSZ 256
#define NUMERIC 0
#define RAW -2
#define STRING -3

#define netrxln(X) netrx((X), NULL, (LINE))
#define netrxs(X) netrx((X), NULL, (STRING))
#define nettxln(X) nettx((X), (LINE))
#define nettxs(X) nettx((X), (STRING))

typedef struct command {
  char *name;
  void (*routine)(char **);
  char *use, *help;
} command;

typedef struct string {
  char *data;
  int len;
} string;

struct neterr {
  char *s, *l;
};

#ifdef CURSES
extern WINDOW *win, *status;
#ifdef DEBUG
extern WINDOW *debug;
#endif
#endif
extern int server, w, h, disp_mode;
extern command commands[];

char **parse(char *);
char *readline(FILE *);
int cmpdir(const void *, const void *);
int cmpls(const void *, const void *);
int neterr(char *);
void error(char *, int);
void execute(char *);
void finish(void);
void gettime(struct timespec *);
void init(void);
void netrx(char *, int16_t *, int16_t);
void nettx(const char *, int16_t);
void printch(char);
void printerr(char *);
void printout(char *);
#ifdef CURSES
void backspace(WINDOW *);
void wpause(void);
#endif

char *call_get(char *, int *);
void call_id();
void call_put(char *, size_t);
void call_simple(char *, char *);

void cmd_baud(char **);
void cmd_cat(char **);
void cmd_cd(char **);
void cmd_dir(char **);
void cmd_exit(char **);
void cmd_get(char **);
void cmd_help(char **);
void cmd_lcd(char **);
void cmd_ls(char **);
void cmd_mget(char **);
void cmd_mkdir(char **);
void cmd_mput(char **);
void cmd_put(char **);
void cmd_pwd(char **);
void cmd_quit(char **);
void cmd_rm(char **);
void cmd_rmdir(char **);
void cmd_script(char **);

extern char *id;
extern char *addr;
extern int port;
extern char *fdata, *ddata, **lines;
extern size_t fdata_sz, ddata_sz, lines_sz;
#endif
