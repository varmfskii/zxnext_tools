#include <curses.h>
#include <string.h>
#include "zxnftp.h"

struct neterr errs[]={
	      { "OK", "no error\n" },
	      { "EX", "file/directory already exists\n" },
	      { "ID", "is a directory\n" },
	      { "N0", "directory not empty\n" },
	      { "ND", "is not a directory\n" },
	      { "NE", "file/directory does not exist\n" },
	      { "UK", "unrecognized command\n" },
	      { NULL, NULL }};

int neterr(char *err) {
  char buf[BLKSZ];
  int i;
  
  if (!err) {
    netrxln(buf);
    if (!strcmp("OK", buf)) return 0;
  } else
    strcmp(buf, err);
#ifdef DEBUG
  waddstr(debug, buf);
  waddch(debug, '\n');
  wrefresh(debug);
#endif
  waddstr(win, "Error: ");
  for (i=0; errs[i].s; i++)
    if (!strcmp(errs[i].s, buf)) {
      waddstr(win, errs[i].l);
      return i;
    }
  waddstr(win, "unknown error\n");
  return i;
}
