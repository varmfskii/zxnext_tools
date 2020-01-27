#include <stdio.h>
#include <getopt.h>
#include "ppmtoscr.h"

#define VERSION "2.00.00"
#define DATE "20200126"

void help(char *);
void version(void);


int main(int argc, char *argv[]) {
  FILE *in, *out, *pin;
  struct pam *inpam;
  int opt, ix, verbose;
  char *opts="hi:o:p:qVv";
  struct option options[]={
    { "help", 0, NULL, 'h' },
    { "in", 1, NULL, 'i' },
    { "out", 1, NULL, 'o' },
    { "pal", 1, NULL, 'p' },
    { "quiet", 0, NULL, 'q' },
    { "version", 0, NULL, 'V' },
    { "verbose", 0, NULL, 'v' },
    { NULL, 0, NULL, '\0' }
  };
  ixed_t ixed;
  pal_t pal;
  
#ifdef DEBUG
  verbose=2;
#else
  verbose=0;
#endif
  in=stdin;
  out=stdout;
  pin=NULL;
  pnm_init(&argc, argv);
  inpam=(struct pam *)calloc(sizeof(struct pam), 1);
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
    case 'p':
      if(!(pin=fopen(optarg, "r"))) {
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
  set_verbose(verbose);
  pnm_readpaminit(in, inpam, sizeof(struct pam));
  if (pin) {
    pal=readpal(16, pin);
    fclose(pin);
  }  else
    pal=palette(4);
  ixed=readixed(inpam, pal);
  free_pal(pal);
  writescr(ixed, out);
  if (pin) nextpal(ixed.pal, out);
  free_ixed(ixed);
}

void help(char *name) {
  version();
  fprintf(stderr, "Usage: %s [<options>] [<infile>] [<outfile>]\n", name);
  fprintf(stderr, "\toptions are\n");
  fprintf(stderr, "\t-h\t--help\t\tprint this help message\n");
  fprintf(stderr, "\t-i\t--in\t\tinput file (stdin)\n");
  fprintf(stderr, "\t-o\t--out\t\toutput file (stdout)\n");
  fprintf(stderr, "\t-p\t--pal\t\tpalette file (builtin)\n");
  fprintf(stderr, "\t-V\t--version\tget version information\n");
  fprintf(stderr, "\t-v\t--verbose\tincrease verbosity\n");
}

void version(void) {
  fprintf(stderr, "ppmtoscr version %s %s\n", VERSION, DATE);
  libzxntoolsver(1);
}
