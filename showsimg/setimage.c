#include <errno.h>
#include <arch/zxn/esxdos.h>
#include "zxnext.h"
#include "showsimg.h"

void readdata(uint8_t in, uint16_t len);

void setimage(uint8_t in) {
  uint8_t i, lastpage;

  if (opts.imgsz<49152) {
    SETNEXTREG(R_MMU5, ULAPAGE);
    if (opts.imgsz==6912)
      readdata(in, 6912);
    else {
      readdata(in, 6144);
      if (opts.pixord==ORD_NORMAL) remap();
      if (opts.imgsz==12288) {
	SETNEXTREG(R_MMU5, ULAPAGE+1);
	readdata(in, 6144);
	if (opts.attrord==ORD_NORMAL) remap();
      } else {
	noattr();
      }
    }
  } else {
    lastpage=(opts.imgsz<81920)?L2PAGE+6:L2PAGE+10;
    pNextReg = R_MMU5;
    for (i=L2PAGE; i<lastpage; i++) {
      pNextDat = i;
      readdata(in, 8192);
    }
  }
}

void readdata(uint8_t in, uint16_t len) {
  errno=0;
  esx_f_read(in, (char *)0xa000, len);
  if (errno) error(errno, "Image Read", NULL);
}
