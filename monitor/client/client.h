#ifndef CLIENT_H
#define CLIENT_H
#include <curses.h>

#ifdef NONET
#define DEBUG
#endif

#define PORT 8080
#define NUMERIC 0

typedef struct command {
  char *name;
  void (*routine)(char **);
} command;

typedef struct string {
  char *data;
  int len;
} string;

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
string srvr_recv();
void backspace(WINDOW *);
void error(char *, int);
void execute(char *);
void finish(void);
void init(void);
void puthex(WINDOW *, int);

int call_read(int, int, int, char *);
string call_query(void);
void call_exec(int);
void call_exit(void);
void call_write(int, int, int, char*);

void cmd_ascii(char **);
void cmd_bkpt(char **);
void cmd_block(char **);
void cmd_byte(char **);
void cmd_cont(char **);
void cmd_disp(char **);
void cmd_edit(char **);
void cmd_go(char **);
void cmd_half(char **);
void cmd_help(char **);
void cmd_inbase(char **);
void cmd_load(char **);
void cmd_mnem(char **);
void cmd_move(char **);
void cmd_outbase(char **);
void cmd_quit(char **);
void cmd_reg(char **);
void cmd_save(char **);
void cmd_sym(char **);
void cmd_word(char **);
void cmd_yank(char **);
#endif
