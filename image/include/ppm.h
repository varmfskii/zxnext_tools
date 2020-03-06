/* Interface header file for PPM-related functions in libnetpbm */

#ifndef _PPM_H_
#define _PPM_H_

#include "pgm.h"

typedef gray pixval;

#ifdef PPM_PACKCOLORS

#define PPM_MAXMAXVAL 1023
typedef unsigned long pixel;
#define PPM_GETR(p) (((p) & 0x3ff00000) >> 20)
#define PPM_GETG(p) (((p) & 0xffc00) >> 10)
#define PPM_GETB(p) ((p) & 0x3ff)

/************* added definitions *****************/
#define PPM_PUTR(p, red) ((p) |= (((red) & 0x3ff) << 20))
#define PPM_PUTG(p, grn) ((p) |= (((grn) & 0x3ff) << 10))
#define PPM_PUTB(p, blu) ((p) |= ( (blu) & 0x3ff))
/**************************************************/

#define PPM_ASSIGN(p,red,grn,blu) (p) = ((pixel) (red) << 20) | ((pixel) (grn) << 10) | (pixel) (blu)
#define PPM_EQUAL(p,q) ((p) == (q))

#else /*PPM_PACKCOLORS*/

#define PPM_OVERALLMAXVAL PGM_OVERALLMAXVAL
#define PPM_MAXMAXVAL PGM_MAXMAXVAL
typedef struct
    {
    pixval r, g, b;
    } pixel;
#define PPM_GETR(p) ((p).r)
#define PPM_GETG(p) ((p).g)
#define PPM_GETB(p) ((p).b)

/************* added definitions *****************/
#define PPM_PUTR(p,red) ((p).r = (red))
#define PPM_PUTG(p,grn) ((p).g = (grn))
#define PPM_PUTB(p,blu) ((p).b = (blu))
/**************************************************/

#define PPM_ASSIGN(p,red,grn,blu) do { (p).r = (red); (p).g = (grn); (p).b = (blu); } while ( 0 )
#define PPM_EQUAL(p,q) ( (p).r == (q).r && (p).g == (q).g && (p).b == (q).b )

#endif /*PPM_PACKCOLORS*/


/* Magic constants. */

#define PPM_MAGIC1 'P'
#define PPM_MAGIC2 '3'
#define RPPM_MAGIC2 '6'
#define PPM_FORMAT (PPM_MAGIC1 * 256 + PPM_MAGIC2)
#define RPPM_FORMAT (PPM_MAGIC1 * 256 + RPPM_MAGIC2)
#define PPM_TYPE PPM_FORMAT


#include "ppmcmap.h"

/* Macro for turning a format number into a type number. */

#define PPM_FORMAT_TYPE(f) ((f) == PPM_FORMAT || (f) == RPPM_FORMAT ? PPM_TYPE : PGM_FORMAT_TYPE(f))


/* Declarations of routines. */

void ppm_init(int * argcP, char* argv[]);

#define ppm_allocarray( cols, rows ) ((pixel**) pm_allocarray( cols, rows, sizeof(pixel) ))
#define ppm_allocrow( cols ) ((pixel*) pm_allocrow( cols, sizeof(pixel) ))
#define ppm_freearray( pixels, rows ) pm_freearray( (char**) pixels, rows )
#define ppm_freerow( pixelrow ) pm_freerow( (char*) pixelrow )

pixel**
ppm_readppm(FILE *   const fileP, 
            int *    const colsP, 
            int *    const rowsP, 
            pixval * const maxvalP);

void
ppm_readppminit(FILE *   const fileP, 
                int *    const colsP, 
                int *    const rowsP, 
                pixval * const maxvalP, 
                int *    const formatP);

void
ppm_readppmrow(FILE*  const fileP, 
               pixel* const pixelrow, 
               int    const cols, 
               pixval const maxval, 
               int    const format);

void
ppm_writeppm(FILE *  const fileP, 
             pixel** const pixels, 
             int     const cols, 
             int     const rows, 
             pixval  const maxval, 
             int     const forceplain);

void
ppm_writeppminit(FILE*  const fileP, 
                 int    const cols, 
                 int    const rows, 
                 pixval const maxval, 
                 int    const forceplain);

void
ppm_writeppmrow(FILE *  const fileP, 
                pixel * const pixelrow, 
                int     const cols, 
                pixval  const maxval, 
                int     const forceplain);

void
ppm_check(FILE *               const fileP, 
          enum pm_check_type   const check_type, 
          int                  const format, 
          int                  const cols, 
          int                  const rows, 
          pixval               const maxval,
          enum pm_check_code * const retval_p);

void
ppm_nextimage(FILE * const fileP, 
              int *  const eofP);

pixel 
ppm_parsecolor(const char* colorname, pixval maxval);

pixel
ppm_parsecolor2(const char * const colorname,
                pixval       const maxval,
                int          const closeOk);

char*
ppm_colorname(const pixel* const colorP, 
              pixval       const maxval, 
              int          const hexok);

void
ppm_readcolordict(const char *      const fileName,
                  int               const mustOpen,
                  unsigned int *    const nColorsP,
                  const char ***    const colornamesP,
                  pixel **          const colorsP,
                  colorhash_table * const chtP);

void
ppm_readcolornamefile(const char *      const fileName, 
                      int               const mustOpen,
                      colorhash_table * const chtP, 
                      const char ***    const colornamesP);

void
ppm_freecolornames(const char ** colornames);

#define PPM_ISGRAY(pixel) \
    (PPM_GETR(pixel) == PPM_GETG(pixel) && PPM_GETR(pixel) == PPM_GETB(pixel))

/* Color scaling macro -- to make writing ppmtowhatever easier. */

#define PPM_DEPTH(newp,p,oldmaxval,newmaxval) \
    PPM_ASSIGN( (newp), \
	( (int) PPM_GETR(p) * (newmaxval) + (oldmaxval) / 2 ) / (oldmaxval), \
	( (int) PPM_GETG(p) * (newmaxval) + (oldmaxval) / 2 ) / (oldmaxval), \
	( (int) PPM_GETB(p) * (newmaxval) + (oldmaxval) / 2 ) / (oldmaxval) )

#define PPM_DISTANCE(p1,p2) ( \
  SQR(PPM_GETR(p1)-PPM_GETR(p2)) + \
  SQR(PPM_GETG(p1)-PPM_GETR(p2)) + \
  SQR(PPM_GETB(p1)-PPM_GETB(p2)) )

/* Luminance, Chrominance macros. */

/* The following are weights of the red, green, and blue components
   respectively in the luminosity of a color
*/
#define PPM_LUMINR (0.2989)
#define PPM_LUMING (0.5866)
#define PPM_LUMINB (0.1145)

#define PPM_LUMIN(p) ( PPM_LUMINR * PPM_GETR(p) \
                       + PPM_LUMING * PPM_GETG(p) \
                       + PPM_LUMINB * PPM_GETB(p) )
#define PPM_CHROM_B(p) ( -0.16874 * PPM_GETR(p) \
                         - 0.33126 * PPM_GETG(p) \
                         + 0.5 * PPM_GETB(p) )
#define PPM_CHROM_R(p) ( 0.5 * PPM_GETR(p) \
                         - 0.41869 * PPM_GETG(p) \
                         - 0.08131 * PPM_GETB(p) )

pixel
color_from_ycbcr(unsigned int const y, 
                 int          const cb, 
                 int          const cr);

#endif /*_PPM_H_*/


