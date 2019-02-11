#ifndef IMG2ASM_H
#define IMG2ASM_H
#include <stdio.h>
#include "../support/support.h"

int writeasm(FILE *out, ixed_t ixed, int txsz, int tysz, char *label);
int writepgm(FILE *out, ixed_t ixed, int txsz, int tysz);
int writeraw(FILE *out, ixed_t ixed, int txsz, int tysz);
#endif
