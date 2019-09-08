#ifndef IMAGETOASM_H
#define IMAGETOASM_H
#include <stdio.h>
#include "../libzxntools/zxntools.h"

int writeasm(FILE *out, ixed_t ixed, int txsz, int tysz, char *label);
int writepgm(FILE *out, ixed_t ixed, int txsz, int tysz);
int writeraw(FILE *out, ixed_t ixed, int txsz, int tysz);
#endif
