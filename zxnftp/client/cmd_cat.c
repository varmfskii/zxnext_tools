#ifdef CURSES
#include <curses.h>
#else
#include <stdio.h>
#endif
#include <stdlib.h>
#include "zxnftp.h"

void cmd_cat(char **params) {
  int i, len;
  char *filedata;
  
  if (!params[1] || params[2]) {
#ifdef CURSES
    waddstr(win, "Error: Incorrect number of arguments. cat <file>\n");
#else
    fputs("Error: Incorrect number of arguments. cat <file>\n", stderr);
#endif
    return;
  }
  filedata=call_get(params[1], &len);
  if (!filedata) return;
#ifdef CURSES
  for(i=0; i<len; i++) waddch(win, filedata[i]);
  waddstr(win, "\nOk\n");
#else
  fwrite(filedata, 1, len, stdout);
  puts("\nOk");
#endif
}
