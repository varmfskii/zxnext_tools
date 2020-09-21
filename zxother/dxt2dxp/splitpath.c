#include <string.h>
#include <stdio.h>

void splitpath(char *path, char *drive, char *dir, char *file, char *ext) {
  int i, lastslash, lastdot;

  lastslash=-1;
  lastdot=-1;
  for(i=0; path[i]; i++) {
    if(path[i]=='/') lastslash=i;
    if(path[i]=='.') lastdot=i;
  }
  drive[0]='\0';
  if (lastslash>=0) {
    strncpy(dir, path, lastslash+1);
    dir[lastslash+1]='\0';
    if (lastdot>lastslash+1) {
      strncpy(file, path+lastslash+1, lastdot-lastslash-1);
      file[lastslash-lastdot]='\0';
      strcpy(ext, path+lastdot);
    } else {
      strcpy(file, path+lastslash+1);
      ext[0]='\0';
    }
  } else {
    dir[0]='\0';
    if (lastdot>0) {
      strncpy(file, path, lastdot);
      file[lastdot]=0;
      strcpy(ext, path+lastdot);
    } else {
      strcpy(file, path);
      ext[0]='\0';
    }
  }
}
