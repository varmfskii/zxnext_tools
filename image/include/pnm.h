/* pnm.h - header file for libpnm portable anymap library
*/

#ifndef _PNM_H_
#define _PNM_H_

#include "ppm.h"
typedef pixel xel;
typedef pixval xelval;
#define PNM_OVERALLMAXVAL PPM_OVERALLMAXVAL
#define PNM_MAXMAXVAL PPM_MAXMAXVAL
#define PNM_GET1(x) PPM_GETB(x)
#define PNM_ASSIGN1(x,v) PPM_ASSIGN(x,0,0,v)
#define PNM_ASSIGN(x,r,g,b) PPM_ASSIGN(x,r,g,b)
#define PNM_EQUAL(x,y) PPM_EQUAL(x,y)
#define PNM_FORMAT_TYPE(f) PPM_FORMAT_TYPE(f)
#define PNM_DEPTH(newp,p,oldmaxval,newmaxval) \
    PPM_DEPTH(newp,p,oldmaxval,newmaxval)

/* Declarations of routines. */

void pnm_init ARGS(( int* argcP, char* argv[] ));

void
pnm_nextimage(FILE *file, int * const eofP);

#define pnm_allocarray( cols, rows ) ((xel**) pm_allocarray( cols, rows, sizeof(xel) ))
#define pnm_allocrow( cols ) ((xel*) pm_allocrow( cols, sizeof(xel) ))
#define pnm_freearray( xels, rows ) pm_freearray( (char**) xels, rows )
#define pnm_freerow( xelrow ) pm_freerow( (char*) xelrow )

xel** pnm_readpnm ARGS(( FILE* file, int* colsP, int* rowsP, xelval* maxvalP, int* formatP ));
void pnm_readpnminit ARGS(( FILE* file, int* colsP, int* rowsP, xelval* maxvalP, int* formatP ));
void pnm_readpnmrow ARGS(( FILE* file, xel* xelrow, int cols, xelval maxval, int format ));

void pnm_writepnm ARGS(( FILE* file, xel** xels, int cols, int rows, xelval maxval, int format, int forceplain ));
void pnm_writepnminit ARGS(( FILE* file, int cols, int rows, xelval maxval, int format, int forceplain ));
void pnm_writepnmrow ARGS(( FILE* file, xel* xelrow, int cols, xelval maxval, int format, int forceplain ));

void
pnm_check(FILE * file, const enum pm_check_type check_type, 
          const int format, const int cols, const int rows, const int maxval,
          enum pm_check_code * const retval_p);


xel 
pnm_backgroundxel (xel** xels, int cols, int rows, xelval maxval, int format);

xel 
pnm_backgroundxelrow (xel* xelrow, int cols, xelval maxval, int format);

xel 
pnm_whitexel (xelval maxval, int format);

xel 
pnm_blackxel(xelval maxval, int format);

void 
pnm_invertxel(xel* x, xelval maxval, int format);

void 
pnm_promoteformat(xel** xels, int cols, int rows, xelval maxval, int format, 
                  xelval newmaxval, int newformat);
void 
pnm_promoteformatrow(xel* xelrow, int cols, xelval maxval, int format, 
                     xelval newmaxval, int newformat);

pixel
xeltopixel(xel const inputxel);

#endif /*_PNM_H_*/
