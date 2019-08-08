#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include <fnmatch.h>
#include "zxnftp.h"

void cmd_mget(char **params) {
  int nlines, i, j, ix, len;
  FILE *out;
  char buf[BLKSZ], dir[BLKSZ];
  
  // error check
  if (!params[1]) {
    waddstr(win, "No patterns usage mget <patt> [<patt> ...]\n");
    return;
  }
  // get remote directory
  nettxln("PD");
  netrxln(dir);
  nettxln("LS");
  if (neterr(NULL)) return;
  nettxln(dir);
  if (neterr(NULL)) return;
  for(ix=i=0; ; i++) {
    nettxln("RR");
    netrxln(buf);
    if (!strncmp("OK", buf, 2)) break;
    netrxln(buf);
    len=strlen(buf);
    if (ix+len+1>ddata_sz) {
      ddata_sz*=2;
      ddata=(char *)realloc(ddata, ddata_sz);
    }
    if (i+1>lines_sz) {
      lines_sz*=2;
      lines=(char **)realloc(lines, lines_sz*(sizeof (char *)));
    }
    lines[i]=ddata+ix;
    strcpy(ddata+ix, buf);
    ix+=len+1;
  }
  nlines=i;
  for(i=0; i<nlines; i++) {
    if (!strcmp(lines[i], ".") || !strcmp(lines[i], "..")) continue; 
    for(j=1; params[j]; j++) {
      if (!fnmatch(params[j], lines[i], 0)) {
	fdata=call_get(lines[i], &len);
	waddstr(win, lines[i]);
	waddch(win, '\n');
	if (!fdata) {
	  waddstr(win, "Error: no data\n");
	  break;
	}
	if (!(out=fopen(lines[i], "w"))) {
	  waddstr(win, "Error: unable to open ");
	  waddstr(win, lines[i]);
	  waddch(win, '\n');
	  break;
	}
	fwrite(fdata, len, 1, out);
	fclose(out);
	break;
      }
    }
  }
  return;
}
