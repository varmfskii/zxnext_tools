#include <stdio.h>
#include <stddef.h>

char *itoa(int num, char *str, int base) {
  unsigned int unum, len, v, thresh;
  int i, digit;

  if (base<1 || base>36) return NULL;
  if (num<0 && base==10) {
    unum=-num;
  } else {
    unum=num;
  }
  thresh=unum/base;
  i=0;
  for(len=1, v=1; v<=thresh; len++) v*=base;
  //fprintf(stderr, "%d\n", len);
  if (num<0 && base==10) str[i++]='-';
  while(len) {
    len--;
    digit=unum/v;
    unum=unum%v;
    v/=base;
    if (digit<10) {
      str[i++]=digit+'0';
    } else {
      str[i++]=digit-10+'A';
    }
  }
  str[i]='\0';
  return str;
}

  
