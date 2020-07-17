#include <stdint.h>

static const uint16_t hmap[]=
  { 0x0000, 0x0100, 0x0200, 0x0300, 0x0400, 0x0500, 0x0600, 0x0700 };
static const uint16_t lmap[] =
  { 0x0000, 0x0020, 0x0040, 0x0060, 0x0080, 0x00A0, 0x00C0, 0x00E0 };

void remap(void) {
  uint8_t t, a, b, c;
  uint16_t base, block, addy1, addy2;
  
  base=0xa000;
  //for(block=0; block<0x800; block++) base[block]=0x00;
  for(block=0; block<0x1800; block+=0x800)
    for(a=0; a<7; a++)
      for(b=a+1; b<8; b++) {
	addy1 = base|block|hmap[a]|lmap[b];
	addy2 = base|block|hmap[b]|lmap[a];
	for(c=0; c<0x20; c++) {
	  t=*(char *)(addy1|c);
	  *(char *)(addy1|c)=*(char *)(addy2|c);
	  *(char *)(addy2|c)=t;
	}
      }
}
