#include <curses.h>
#include <string.h>
#include <stdlib.h>
#include "zxnftp.h"

void cmd_dir(char **params) {
  int16_t len;
  int i, ix, mo, dy, yr, h, m, s, attr, y, x, nlines;
  char buf[BLKSZ], attrstr[9], temp[100];
  
  getmaxyx(win, y, x);
  if (params[1]) {
    nettxln("LS");
    if (neterr(NULL)) return;
    nettxln(params[1]);
  } else
    nettxln("L.");
  if (neterr(NULL)) return;
  for(i=0; ; i++) {
    nettxln("RR");
    netrxln(buf); // attributes
    if (!strncmp("OK", buf, 2)) break;
    sscanf(buf, "%02x\n%02u/%02u/%04u\n%02u:%02u:%02u",
	   &attr, &dy, &mo, &yr, &h, &m, &s);
    strcpy(attrstr, "--------");
    if (attr&0x80) attrstr[0]='1';
    if (attr&0x40) attrstr[0]='1';
    if (attr&0x20) attrstr[0]='a';
    if (attr&0x10) attrstr[0]='d';
    if (attr&0x08) attrstr[0]='v';
    if (attr&0x04) attrstr[0]='s';
    if (attr&0x02) attrstr[0]='h';
    if (!attr&0x01) attrstr[0]='w';
    netrxln(buf); // name
    len=strlen(buf);
    if (i+1>lines_sz) {
      lines_sz*=2;
      lines=(char **)realloc(lines, lines_sz*(sizeof (char *)));
    }
    lines[i]=data+ix;
    if (ix+30+len>data_sz) {
      data_sz*=2;
      data=(char *)realloc(data, data_sz);
    }
    sprintf(data+ix, "%s %02u/%02u/%04u %02u:%02u:%02u %s",
	    attrstr, dy, mo, yr, h, m, s, buf);
    ix+=30+len;
  }
  nlines=i;
  qsort(lines, nlines, sizeof(char *), cmpdir);
  for(i=0; i<nlines; i++) {
    waddstr(win, lines[i]);
    waddch(win, '\n');
    if (i%(y-1)==y-2) wpause();
  }
  waddstr(win, "Ok\n");
  return;
}
