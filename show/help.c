#include <stdio.h>

void help(void) {
  puts("Usage: .show [<options>] <filename>");
  puts("options:");
  puts("\t-2: Layer 2 256x192x8");
  puts("\t-3: Layer 2 320x256x8");
  puts("\t-6: Layer 2 640x256x4");
  puts("\t-8: 8-bit palette entries");
  puts("\t-9: 9-bit palette entries");
  puts("\t-R: Radistan 128x96x4");
  puts("\t-l: LoRes 128x96x8");
  puts("\t-r: Timex HiRes 512x192x1");
  puts("\t-c: Timex HiCol 256x192/8x1");
  puts("\t-u: ULA 256x192/8x8");
  puts("\t-x: Do not wait, do not restore");
  puts("\t-+: ULA+");
}
