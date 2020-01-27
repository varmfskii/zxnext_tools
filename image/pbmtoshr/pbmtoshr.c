#include <stdio.h>
#include <getopt.h>
#include "pbmtoshr.h"

#define VERSION "1.00.00"
#define DATE "20190219"

void help(char *);
void version(void);

int main(int argc, char *argv[]) {
  FILE *in, *out;
  struct pam *inpam;
  int opt, ix, verbose;
  char *opts="2hi:o:qVv";
  struct option options[]={
    { "double", 0, NULL, '2' },
    { "help", 0, NULL, 'h' },
    { "in", 1, NULL, 'i' },
    { "out", 1, NULL, 'o' },
    { "quiet", 0, NULL, 'q' },
    { "version", 0, NULL, 'V' },
    { "verbose", 0, NULL, 'v' },
    { NULL, 0, NULL, '\0' }
  };
  bm_t bm;
  int dbl=0;
  
#ifdef DEBUG
  verbose=2;
#else
  verbose=0;
#endif
  in=stdin;
  out=stdout;
  pnm_init(&argc, argv);
  inpam=(struct pam *)calloc(sizeof(struct pam), 1);
  while((opt=getopt_long(argc, argv, opts, options, &ix))!=-1) {
    switch(opt) {
    case '2':
      dbl=1;
      break;
    case 'h':
      help(argv[0]);
      return 1;
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
  set_verbose(verbose);
  pnm_readpaminit(in, inpam, sizeof(struct pam));
  bm=readbm(inpam);
  if (!bm.dat) return 1;
  bmtoshr(bm, dbl, out);
  free_bm(bm);
}

void help(char *name) {
  version();
  fprintf(stderr, "Usage: %s [<options>] [<infile>] [<outfile>]\n", name);
  fprintf(stderr, "\toptions are\n");
  fprintf(stderr, "\t-2\t--double\t\tvertical was doubled size (false)\n");
  fprintf(stderr, "\t-h\t--help\t\tprint this help message\n");
  fprintf(stderr, "\t-i\t--in\t\tinput file (stdin)\n");
  fprintf(stderr, "\t-o\t--out\t\toutput file (stdout)\n");
  fprintf(stderr, "\t-V\t--version\tget version information\n");
  fprintf(stderr, "\t-v\t--verbose\tincrease verbosity\n");
}

void version(void) {
  fprintf(stderr, "pbmtoshr version %s %s\n", VERSION, DATE);
  libzxntoolsver(1);
}
