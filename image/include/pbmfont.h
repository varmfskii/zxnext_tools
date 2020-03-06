/* pbmfont.h - header file for font routines in libpbm
*/

struct glyph {
	int width, height;
	int x, y;
	int xadd;
	const char* bmap;
};

struct font {
	int maxwidth, maxheight;
	int x, y;
	struct glyph* glyph[256];
	/* for compatibility with old pbmtext routines */
	/* oldfont is 0 if the font is BDF derived */
	bit** oldfont;
	int fcols, frows;
};

struct font* pbm_defaultfont(const char* const which);
struct font* pbm_dissectfont ARGS(( bit** font, int frows, int fcols ));
struct font* pbm_loadfont(const char * const filename);
struct font* pbm_loadpbmfont(const char * const filename);
struct font* pbm_loadbdffont(const char * const filename);
void pbm_dumpfont ARGS(( struct font* fn ));
int mk_argvn ARGS(( char* s, char* vec[], int max ));
