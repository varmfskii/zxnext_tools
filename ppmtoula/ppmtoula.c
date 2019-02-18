#include <stdio.h>
#include <getopt.h>
#include "ppmtoula.h"

#define VERSION "1.00.00"
#define DATE "20190217"

void help(char *);
void version(void);

#ifdef DEBUG
int verbose=2;
#else
int verbose=0;
#endif

int main(int argc, char *argv[]) {
  FILE *in, *out;
  int opt, ix;
  char *opts="hi:o:qVv";
  struct option options[]={
    { "help", 0, NULL, 'h' },
    { "in", 1, NULL, 'i' },
    { "out", 1, NULL, 'o' },
    { "quiet", 0, NULL, 'q' },
    { "version", 0, NULL, 'V' },
    { "verbose", 0, NULL, 'v' },
    { NULL, 0, NULL, '\0' }
  };
  rgb_t rgb;
  ixed_t ixed;
  pal_t pal;
  
  in=stdin;
  out=stdout;
  while((opt=getopt_long(argc, argv, opts, options, &ix))!=-1) {
    switch(opt) {
    case 'h':
      help(argv[0]);
      return 0;
    case 'i':
      if (!(in=fopen(optarg, "r"))) {
	fprintf(stderr, "Unable to open %s\n", optarg);
	return 1;
      }
      break;
    case 'o':
      if (!(out=fopen(optarg, "w"))) {
	fprintf(stderr, "Unable to open %s\n", optarg);
	return 1;
      }
      break;
    case 'q':
      if (verbose) verbose--;
      break;
    case 'V':
      version();
      return 0;
    case 'v':
      verbose++;
      break;
    default:
      return 1;
    }
  }
  if (optind<argc && in==stdin) {
    if (!(in=fopen(argv[optind], "r"))) {
      fprintf(stderr, "Unable to open %s\n", argv[optind]);
      return 1;
    }
    optind++;
  }
  if (optind<argc && out==stdout) {
    if (!(out=fopen(argv[optind], "w"))) {
      fprintf(stderr, "Unable to open %s\n", argv[optind]);
      return 1;
    }
    optind++;
  }
  rgb=readrgb(in);
  pal=palette(4);
  ixed=rgb2index(rgb, pal);
  free_rgb(rgb);
  free_pal(pal);
  writeula(ixed, out);
  free_ixed(ixed);
  /*
   * body
   */
}

void help(char *name) {
  version();
  fprintf(stderr, "Usage: %s [<options>] [<infile>] [<outfile>]\n", name);
  fprintf(stderr, "\toptions are\n");
  fprintf(stderr, "\t-h\t--help\t\tprint this help message\n");
  fprintf(stderr, "\t-i\t--in\t\tinput file (stdin)\n");
  fprintf(stderr, "\t-o\t--out\t\toutput file (stdout)\n");
  fprintf(stderr, "\t-V\t--version\tget version information\n");
  fprintf(stderr, "\t-v\t--verbose\tincrease verbosity\n");
}

void version(void) {
  fprintf(stderr, "ppmtoula version %s %s\n", VERSION, DATE);
  libzxntoolsver(1);
}
