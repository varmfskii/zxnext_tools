#include <stdint.h>

static char num[12];

char *string32(int32_t n) {
  uint8_t neg, i;

  neg=n<0;
  if (neg) n=-n;
  i=11;
  num[i]='\0';
  do {
    num[--i]=n%10+'0';
    n/=10;
  } while (n);
  if (neg) num[--i]='-';
  return num+i;
}
