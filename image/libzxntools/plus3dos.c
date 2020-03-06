#include "zxntools.h"
#include <string.h>

uint32_t plus3dos(uint8_t *data) {
  uint8_t sum;
  uint32_t size;
  int i;
  
  if(strncmp((char *)data, "PLUS3DOS\032", 9)) return 0;
  for(size=0, i=14; i>10; i--) size=(size<<8)|(data[i]);
  for(sum=0, i=0; i<127; i++) sum+=data[i];
  if(sum!=data[127]) return 0;
  return size;
}
