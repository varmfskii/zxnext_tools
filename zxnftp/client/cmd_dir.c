#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef CURSES
#include <curses.h>
#endif
#include "zxnftp.h"

void cmd_dir(char **params) {
  int16_t len;
  int i, ix, mo, dy, yr, h, m, s, attr, y, nlines;
  char buf[BLKSZ], dir[BLKSZ], *p, attrstr[9];

  if (params[1] && params[2]) {
    printerr("Incorrect number of arguments, usage dir [<dir>]\n");
    return;
  }    
#ifdef CURSES
  getmaxyx(win, y, i);
#endif
  if (params[1]) {
    p=params[1];
  } else {
    nettxln("PD");
    netrxln(dir);
    p=dir;
  }
  nettxln("LS");
  if (neterr(NULL)) return;
  nettxln(p);
  if (neterr(NULL)) return;
  for(i=0; ; i++) {
    nettxln("RR");
    netrxln(buf); // attributes
    if (!strncmp("OK", buf, 2)) break;
    sscanf(buf, "%02x\n%02u/%02u/%04u\n%02u:%02u:%02u",
	   &attr, &dy, &mo, &yr, &h, &m, &s);
    strcpy(attrstr, "--------");
    if (attr&0x80) attrstr[0]='1';
    if (attr&0x40) attrstr[1]='1';
    if (attr&0x20) attrstr[2]='a';
    if (attr&0x10) attrstr[3]='d';
    if (attr&0x08) attrstr[4]='v';
    if (attr&0x04) attrstr[5]='s';
    if (attr&0x02) attrstr[6]='h';
    if (!attr&0x01) attrstr[7]='w';
    netrxln(buf); // name
    len=strlen(buf);
    if (i+1>lines_sz) {
      lines_sz*=2;
      lines=(char **)realloc(lines, lines_sz*(sizeof (char *)));
    }
    lines[i]=ddata+ix;
    if (ix+30+len>ddata_sz) {
      ddata_sz*=2;
      ddata=(char *)realloc(ddata, ddata_sz);
    }
    sprintf(ddata+ix, "%s %02u/%02u/%04u %02u:%02u:%02u %s",
	    attrstr, dy, mo, yr, h, m, s, buf);
    ix+=30+len;
  }
  nlines=i;
  qsort(lines, nlines, sizeof(char *), cmpdir);
  for(i=0; i<nlines; i++) {
    printout(lines[i]);
    printch('\n');
#ifdef CURSES
    if (i%(y-1)==y-2) wpause();
#endif
  }
  printout("Ok\n");
  return;
}
