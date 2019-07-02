#ifndef GETPALETTE_H
#define GETPALETTE_H
#include <stdio.h>
#include "../libzxntools/zxntools.h"

void writeasm(pal_t pal, FILE *out, char *label);
pal_t rgb2pal(rgb_t rgb, int len);
#endif
