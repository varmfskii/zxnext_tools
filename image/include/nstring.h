#ifndef _NSTRING_H
#define _NSTRING_H

#include <stdarg.h>
#include <string.h>

/* Here is are string functions that respect the size of the array
   into which you are copying -- E.g. STRSCPY truncates the source string as
   required so that it fits, with the terminating null, in the destination
   array.
*/
#define STRSCPY(A,B) \
	(strncpy((A), (B), sizeof(A)), *((A)+sizeof(A)-1) = '\0')
#define STRSCMP(A,B) \
	(strncmp((A), (B), sizeof(A)))
#define STRSCAT(A,B) \
    (strncpy(A+strlen(A), B, sizeof(A)-strlen(A)), *((A)+sizeof(A)-1) = '\0')

/* The standard C library routines isdigit(), for some weird 
   historical reason, does not take a character (type 'char') as its
   argument.  Instead it takes an integer.  When the integer is a whole
   number, it represents a character in the obvious way using the local
   character set encoding.  When the integer is negative, the results
   are undefined.

   Passing a character to isdigit(), which expects an integer, results in
   isdigit() sometimes getting a negative number.

   On some systems, when the integer is negative, it represents exactly
   the character you want it to anyway (e.g. -1 is the character that is
   encoded 0xFF).  But on others, it does not.

   (The same is true of other routines like isdigit()).

   Therefore, we have the substitutes for isdigit() etc. that take an
   actual character (type 'char') as an argument.
*/

#define ISALNUM(C) (isalnum((unsigned char)(C)))
#define ISALPHA(C) (isalpha((unsigned char)(C)))
#define ISBLANK(C) (isblank((unsigned char)(C)))
#define ISCNTRL(C) (iscntrl((unsigned char)(C)))
#define ISDIGIT(C) (isdigit((unsigned char)(C)))
#define ISGRAPH(C) (isgraph((unsigned char)(C)))
#define ISLOWER(C) (islower((unsigned char)(C)))
#define ISPRINT(C) (isprint((unsigned char)(C)))
#define ISPUNCT(C) (ispunct((unsigned char)(C)))
#define ISSPACE(C) (isspace((unsigned char)(C)))
#define ISUPPER(C) (isupper((unsigned char)(C)))
#define ISXDIGIT(C) (isxdigit((unsigned char)(C)))
#define TOUPPER(C) ((char)toupper((unsigned char)(C)))


/* These are all private versions of commonly available standard C
   library subroutines whose names are the same except with the N at
   the end.  Because not all standard C libraries have them all,
   Netpbm must include them in its own libraries, and because some
   standard C libraries have some of them, Neptbm must use different
   names for them.
   
   The GNU C library has all of them.  All but the oldest standard C libraries
   have snprintf().

   There is one difference between the asprintf() family and that found in 
   other libraries:  The return value is a const char * instead of a char *.
   The const is more correct.  

   strfree() is strictly a Netpbm invention, to allow proper type checking
   when freeing storage allocated by the Netpbm asprintfN().  */

int snprintfN(char *, size_t, const char *, /*args*/ ...)
#ifdef __GNUC__
  __attribute__ ((format (printf, 3, 4)))
#endif
;
int vsnprintfN(char *, size_t, const char *, va_list);
int asprintfN(const char **ptr, const char *fmt, /*args*/ ...)
#ifdef __GNUC__
  __attribute__ ((format (printf, 2, 3)))
#endif
;
int vasprintfN(const char **ptr, const char *fmt, va_list ap);
int asnprintfN(const char **ptr, size_t str_m, const char *fmt, ...)
#ifdef __GNUC__
  __attribute__ ((format (printf, 3, 4)))
#endif
;

int 
vasnprintfN(const char **ptr, size_t str_m, const char *fmt, va_list ap);

void 
strfree(const char * const string);

const char *
strsepN(char ** const stringP, const char * const delim);

#endif

