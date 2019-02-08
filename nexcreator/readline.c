#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "nexcreator.h"

#define BASE 256

char *readline(FILE *in) {
  char *rv;
  size_t size, i;
  int c;

  rv=malloc(BASE);
  size=BASE;
  for(i=0; (c=getc(in))!=EOF && c!='\n'; i++) {
    if (i>=size-1) {
      size*=2;
      rv=realloc(rv, size*2);
    }
    rv[i]=c;
  }
  if (i==0 && c==EOF) {
    free(rv);
    return NULL;
  }
  rv[i]='\0';
  return realloc(rv, strlen(rv)+1);
}
