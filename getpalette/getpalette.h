#ifndef GETPALETTE_H
#define GETPALETTE_H
#include "../support/support.h"
#include <stdio.h>

void writeasm(pal_t pal, FILE *out, char *label);
void writeraw(pal_t pal, FILE *out);
pal_t rgb2pal(rgb_t rgb, int len);
#endif
