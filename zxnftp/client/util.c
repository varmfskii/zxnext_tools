#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif
#include "zxnftp.h"

#define LINELEN 256


int cmpls(const void *x, const void *y) {
  return strcmp(*(const char **)x, *(const char **)y);
}

int cmpdir(const void *x, const void *y) {
  return strcmp(29+*(const char **)x, 29+*(const char **)y);
}

#ifdef CURSES
void wpause() {
  waddstr(win, "<any key to continue>\n");
  wrefresh(win);
  getch();
}
#endif

void error(char *err, int num) {
  finish();
  fprintf(stderr, "%s\n", err);
  exit(num);
}

#ifdef CURSES
void backspace(WINDOW *win) {
  waddch(win, '\b');
  wdelch(win);
}
#endif

void finish(void) { 
  close(server); 
#ifdef CURSES
  endwin();
#endif
} 

char *readline(FILE *in) {
  size_t len=LINELEN;
  int i, c;
  char *line;
  
  if (!(line=malloc(len))) return NULL;
  for(i=0; (c=getc(in))!=EOF && c!='\n'; i++) {
    if (i>=len-1) {
      len*=2;
      line=realloc(line, len);
    }
    line[i]=c;
  }
  line[i]='\0';
  return line;
}

void gettime(struct timespec *ts) {
#ifdef __MACH__
  clock_serv_t cclock;
  mach_timespec_t mts;
  host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
  clock_get_time(cclock, &mts);
  ts->tv_sec=mts.tv_sec;
  ts->tv_nsec=mts.tv_nsec;
#else
  clock_gettime(CLOCK_REALTIME, ts);
#endif
}
