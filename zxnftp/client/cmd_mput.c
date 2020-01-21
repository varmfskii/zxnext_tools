#include <dirent.h>
#include <fnmatch.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include "zxnftp.h"

void cmd_mput(char **params) {
  DIR *local;
  FILE *in;
  int i;
  struct dirent *entry;
  struct stat st;
  char buf[BLKSZ];
  
  if (!params[1]) {
    printerr("No patterns, usage: mget <patt> [<patt> ...]\n");
    return;
  }
  local=opendir(".");
  for(;;) {
    if (!(entry=readdir(local))) break;
    if (entry->d_type!=DT_REG) continue;
    for(i=1; params[1]; i++)
      if (!fnmatch(params[i], entry->d_name, 0)) {
	stat(entry->d_name, &st);
	if (st.st_size>fdata_sz) {
	  fdata_sz=st.st_size;
	  free(fdata);
	  fdata=(char *)malloc(fdata_sz);
	}
	if (!(in=fopen(entry->d_name, "r"))) {
	  sprintf(buf, "unable to open local file: %s\n", entry->d_name);
	  break;
	}
	fread(fdata, st.st_size, 1, in);
	fclose(in);
	call_put(entry->d_name, st.st_size);
	break;
      }
  }
  closedir(local);
  return;
}
