#include <stdlib.h>
#include <string.h>
#include "showsimg.h"

void guessmode(uint32_t size, char *name) {
  char *ext;

  ext=getext(name);
  opts.mode=UNKNOWN;
  if (!strcmp(ext, "scr")) {
    opts.mode=ULA;
  } else if (!strcmp(ext, "shc")) {
    opts.mode=HICOL;
  } else if (!strcmp(ext, "shr")) {
    opts.mode=HIRES;
  } else if (!strcmp(ext, "sl2")) {
    if (size>=81920l)
      opts.mode=L2_320;
    else
      opts.mode=L2_256;
  } else if (!strcmp(ext, "slr")) {
    if (size>=12288)
      opts.mode=LORES;
    else
      opts.mode=RAD;
  } else if (size==6912 || size==6976) {
    opts.mode = ULA;
  } else if (size==12288 || size==12352) {
    opts.mode = HICOL;
  } else if (size==12353 || size==12289) {
    opts.mode = HIRES;
  } else if (size==81936l || size==81952l) {
    opts.mode = L2_640;
  } else if (size>=81920l) {
    opts.mode = L2_320;
  } else if (size>=49152l) {
    opts.mode = L2_256;
  } else if (size>=12288) {
    opts.mode = LORES;
  } else if (size>=6912) {
    opts.mode = ULA;
  } else if (size>=6144) {
    opts.mode = RAD;
  } else {
    error(4, "Unable to guess mode", NULL);
  }
}
