#ifndef CLIENT_H
#define CLIENT_H
#include <curses.h>

#define PORT 8080

extern WINDOW *win, *status;
extern int server, w, h;

char **parse(char *);
void backspace(WINDOW *);
void error(char *, int);
void execute(char *);
void finish(void);
void init(void);
void puthex(WINDOW *, int);
#endif
