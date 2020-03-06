/* pm.h - interface to format-independent part of libpbm.
**
** Copyright (C) 1988, 1989, 1991 by Jef Poskanzer.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
*/

#ifndef _PM_H_
#define _PM_H_

#include "pm_config.h"

#include <sys/types.h>
#include <ctype.h>
#include <stdio.h>
#include <errno.h>
#include <setjmp.h>
#include <sys/stat.h>

#ifdef VMS
#include <perror.h>
#endif

/* GNU_PRINTF_ATTR lets the GNU compiler check pm_message() and pm_error()
   calls to be sure the arguments match the format string, thus preventing
   runtime segmentation faults and incorrect messages.
*/
#ifdef __GNUC__
#define GNU_PRINTF_ATTR __attribute__ ((format (printf, 1,2)))
#else
#define GNU_PRINTF_ATTR
#endif


/* PURE_FN_ATTR is the attribute you add to a function declaration
   that indicates it's a true function -- has no side effects and return
   value is not influenced by anything except its arguments.
*/
#ifdef __GNUC__
#define PURE_FN_ATTR __attribute__ ((const))
#else
#define PURE_FN_ATTR
#endif

#undef MAX
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#undef MIN
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#undef ABS
#define ABS(a) ((a) >= 0 ? (a) : -(a))
#undef SGN
#define SGN(a)		(((a)<0) ? -1 : 1)
#undef ODD
#define ODD(n) ((n) & 1)
#undef ROUND
#define ROUND(X) (((X) >= 0) ? (int)((X)+0.5) : (int)((X)-0.5))
#undef ROUNDU
#define ROUNDU(X) ((unsigned int)((X)+0.5))
#undef SQR
#define SQR(a) ((a)*(a))

/* Definitions to make Netpbm programs work with either ANSI C or C
   Classic.

   This is obsolete, as all compilers recognize the ANSI syntax now.

   We are slowly removing all the ARGS invocations from the programs
   (and replacing them with explicit ANSI syntax), but we have a lot
   of programs where we have removed ARGS from the definition but not
   the prototype, and we have discovered that the Sun compiler
   considers the resulting mismatch between definition and prototype
   to be an error.  So we make ARGS create the ANSI syntax
   unconditionally to avoid having to fix all those mismatches.  */

#if 0
#if __STDC__
#define ARGS(alist) alist
#else /*__STDC__*/
#define ARGS(alist) ()
#define const
#endif /*__STDC__*/
#endif
#define ARGS(alist) alist


extern int pm_plain_output;
    /* Output functions are to produce plain (as opposed to raw) format
       regardless of their 'plainformat' arguments.
    */

void 
pm_init(const char * const progname, unsigned int const flags);

void 
pm_proginit(int* const argcP, char* argv[]);

void
pm_setMessage(int const newState, int * const oldStateP);

FILE * 
pm_tmpfile(void);

void
pm_make_tmpfile(FILE **       const filePP,
                const char ** const filenameP);

void
pm_nextimage(FILE * const file, int * const eofP);

/* Variable-sized arrays definitions. */

char** 
pm_allocarray (int const cols, int const rows, int const size );

char* 
pm_allocrow (int const cols, int const size);

void 
pm_freearray (char** const its, int const rows);

void 
pm_freerow(char* const itrow);


/* Obsolete -- use shhopt instead */
int 
pm_keymatch (char* const str, const char* const keyword, int const minchars);


int 
pm_maxvaltobits (int const maxval);

int 
pm_bitstomaxval (int const bits);

unsigned int PURE_FN_ATTR
pm_lcm (unsigned int const x, 
        unsigned int const y,
        unsigned int const z,
        unsigned int const limit);

void
pm_setjmpbuf(jmp_buf * const jmpbufP);

void
pm_setjmpbufsave(jmp_buf *  const jmpbufP,
                 jmp_buf ** const oldJmpbufPP);

void GNU_PRINTF_ATTR
pm_message (const char format[], ...);     

void GNU_PRINTF_ATTR
pm_error (const char reason[], ...);       

/* Obsolete - use helpful error message instead */
void
pm_perror (const char reason[]);           

/* Obsolete - use shhopt and man page instead */
void 
pm_usage (const char usage[]);             

FILE* 
pm_openr (const char* const name);
         
FILE*    
pm_openw (const char* const name);
         
FILE *
pm_openr_seekable(const char name[]);

void     
pm_close (FILE* const f);

void 
pm_closer (FILE* const f);
          
void      
pm_closew (FILE* const f);



void
pm_readchar(FILE * const ifP,
            char * const cP);

static __inline__ void
pm_readcharu(FILE *          const ifP,
             unsigned char * const cP) {
    pm_readchar(ifP, (char *) cP);
}

void
pm_writechar(FILE * const ofP,
             char   const c);

static __inline__ void
pm_writecharu(FILE *        const ofP,
              unsigned char const c) {
    pm_writechar(ofP, (char) c);
}

int
pm_readbigshort(FILE *  const ifP, 
                short * const sP);

static __inline__ int
pm_readbigshortu(FILE*            const ifP, 
                 unsigned short * const sP) {
    return pm_readbigshort(ifP, (short *) sP);
}

int
pm_writebigshort(FILE * const ofP,
                 short  const s);

static __inline__ int
pm_writebigshortu(FILE *          const ofP,
                  unsigned short  const s) {
    return pm_writebigshort(ofP, (short) s);
}

int
pm_readbiglong(FILE * const ifP, 
               long * const lP);

static __inline__ int
pm_readbiglongu(FILE *          const ifP,
                unsigned long * const lP) {
    return pm_readbiglong(ifP, (long *) lP);
}

int
pm_writebiglong(FILE * const ofP,
                long   const l);

static __inline__ int
pm_writebiglongu(FILE *        const ofP,
                 unsigned long const l) {
    return pm_writebiglong(ofP, (long) l);
}

int
pm_readlittleshort(FILE  * const ifP,
                   short * const sP);

static __inline__ int
pm_readlittleshortu(FILE  *          const ifP,
                    unsigned short * const sP) {
    return pm_readlittleshort(ifP, (short *) sP);
}

int
pm_writelittleshort(FILE * const ofP,
                    short  const s);

static __inline__ int
pm_writelittleshortu(FILE *          const ofP,
                     unsigned short  const s) {
    return pm_writelittleshort(ofP, (short) s);
}

int
pm_readlittlelong(FILE * const ifP,
                  long * const lP);

static __inline__ int
pm_readlittlelongu(FILE *          const ifP,
                   unsigned long * const lP) {
    return pm_readlittlelong(ifP, (long *) lP);
}

int
pm_writelittlelong(FILE * const ofP,
                   long   const l);

static __inline__ int
pm_writelittlelongu(FILE *        const ofP,
                    unsigned long const l) {
    return pm_writelittlelong(ofP, (long) l);
}

int 
pm_readmagicnumber(FILE * const ifP);

char* 
pm_read_unknown_size(FILE * const ifP, 
                     long * const buf);

unsigned int
pm_tell(FILE * const fileP);

void
pm_tell2(FILE *       const fileP, 
         pm_filepos * const fileposP,
         unsigned int const fileposSize);

void
pm_seek2(FILE *             const fileP, 
         const pm_filepos * const fileposP,
         unsigned int       const fileposSize);

void
pm_seek(FILE * const fileP, unsigned long filepos);

enum pm_check_code {
    PM_CHECK_OK,
    PM_CHECK_UNKNOWN_TYPE,
    PM_CHECK_TOO_LONG,
    PM_CHECK_UNCHECKABLE,
    PM_CHECK_TOO_SHORT
};

enum pm_check_type {
    PM_CHECK_BASIC
};

void
pm_check(FILE *               const file, 
         enum pm_check_type   const check_type, 
         pm_filepos           const need_raster_size,
         enum pm_check_code * const retval_p);

char *
pm_arg0toprogname(const char arg0[]);



void *malloc2(int, int);
void *malloc3(int, int, int);
void overflow2(int, int);
void overflow3(int, int, int);
void overflow_add(int, int);

#endif


#ifdef __WIN32__
#ifdef NETPBM_USE_DLL
#ifndef BUILD_DLL
   __attribute__((dllimport))
#endif	/* BUILD_DLL */
#endif /* NETPBM_USE_DLL */
   extern char exec_parent[MAX_PATH]; /* parent directory of program */
#endif /* __WIN32__ */

