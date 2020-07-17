#include <stdint.h>

void noattr(void) {
  uint8_t *addy;

  for(addy=(uint8_t *)0xb800; addy<(uint8_t *)0xbb00; addy++) *addy=0x78;
}
