#ifndef ZXNFTP_H
#define ZXNFTP_H
#include <curses.h>

#ifdef NONET
#define DEBUG
#endif

#define BLKSZ 200
#define DATASZ 8192
#define LINE 0xfe
#define LINESSZ 256
#define NUMERIC 0
#define RAW 0xfd
#define STRING 0xff

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

extern WINDOW *win, *status;
#ifdef DEBUG
extern WINDOW *debug;
#endif
extern int server, w, h, disp_mode;
extern command commands[];
#ifdef NONET
extern unsigned char mem[];
#endif

char **parse(char *);
int cmpls(const void *, const void *);
int cmpdir(const void *, const void *);
int neterr(char *);
void backspace(WINDOW *);
void error(char *, int);
void execute(char *);
void finish(void);
void init(void);
void netrx(char *, uint8_t *, uint8_t);
void nettx(const char *, uint8_t);
void wpause(void);

char *call_get(char *, int *);
void call_id();
void call_put(char *, size_t);
void call_simple(char *, char *);

void cmd_cat(char **);
void cmd_cd(char **);
void cmd_dir(char **);
void cmd_exit(char **);
void cmd_get(char **);
void cmd_help(char **);
void cmd_ls(char **);
void cmd_mget(char **);
void cmd_mkdir(char **);
void cmd_mput(char **);
void cmd_put(char **);
void cmd_pwd(char **);
void cmd_quit(char **);
void cmd_rm(char **);
void cmd_rmdir(char **);

extern char *id;
extern char *addr;
extern int port;
extern char *data, **lines;
extern size_t data_sz, lines_sz;
#endif
