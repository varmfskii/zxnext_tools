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
  }
  for (i=0; errs[i].s; i++)
    if (!strcmp(errs[i].s, buf)) {
      printerr(errs[i].l);
      return i;
    }
  printerr("unknown error\n");
  return i;
}
