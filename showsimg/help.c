#include <stdio.h>

void help(void) {
  puts(".showsimg 1.04.00");
  puts("Theodore (Alex) Evans 2020");
  puts("Usage: .showsimg [<options>] <filename>");
  puts("options:");
  puts("\t-2: Layer 2 256x192x8");
  puts("\t-3: Layer 2 320x256x8");
  puts("\t-6: Layer 2 640x256x4");
  puts("\t-M: MLT HiColor");
  puts("\t-R: Radastan 128x96x4");
  puts("\t-S: Save state");
  puts("\t-c: Timex HiCol 256x192/8x1");
  puts("\t-h: This help");
#ifdef DEBUG
  puts("\t-i: Information about image");
#endif
  puts("\t-l: LoRes 128x96x8");
  puts("\t-m: MC HiColor");
  puts("\t-n: NXI Layer 2");
  puts("\t-r: Timex HiRes 512x192x1");
  puts("\t-s: Restore state");
  puts("\t-u: ULA 256x192/8x8");
  puts("\t-x: Do not wait, do not restore");
}
