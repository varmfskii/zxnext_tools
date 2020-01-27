#include "getpalette.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BITS 8
#define VERSION "2.00.00"
#define DATE "20190226"

void help(char *);
void version(void);

int main(int argc, char *argv[]) {
  int opt, ix, bits;
  char *opts="b:hi:o:Vv";
  struct option options[]={
    { "bits", 1, NULL, 'b' },
    { "help", 0, NULL, 'h' },
    { "in", 1, NULL, 'i' },
    { "out", 1, NULL, 'o' },
    { "verrion", 0, NULL, 'V' },
    { "verbose", 0, NULL, 'v' },
    { NULL, 0, NULL, '\0' }
  };
  FILE *infile, *outfile;
  struct pam *inpam;
  rgb_t rgb;
  pal_t pal;
  int verbose;

  verbose=0;
  bits=BITS;
  infile=stdin;
  outfile=stdout;
  pnm_init(&argc, argv);
  inpam=(struct pam *)calloc(sizeof(struct pam), 1);
  while((opt=getopt_long(argc, argv, opts, options, &ix))!=-1) {
    switch(opt) {
    case 'b':
      bits=atoi(optarg);
      if (bits!=1 && bits!=2 && bits!=4 && bits!=8) {
	fprintf(stderr, "Unsupported bit depth %d\n", bits);
	return 1;
      }
      break;
    case 'h':
      help(argv[0]);
      exit(0);
    case 'i':
      if(!(infile=fopen(optarg, "r"))) {
	fprintf(stderr, "Unable to open %s\n", optarg);
	return 1;
      }
      break;
    case 'o':
      if(!(outfile=fopen(optarg, "w"))) {
	fprintf(stderr, "Unable to open %s\n", optarg);
	return 1;
      }
      break;
    case 'V':
      version();
      exit(0);
    case 'v':
      verbose++;
      break;
    default:
      fprintf(stderr, "Illegal option %c\n", opt);
      help(argv[0]);
      exit(1);
    }
  }
  if (optind<argc && infile==stdin) {
    if (!(infile=fopen(argv[optind], "r"))) {
      fprintf(stderr, "Unable to open %s\n", argv[optind]);
      return 1;
    }
    optind++;
  }
  if (optind<argc && outfile==stdout) {
    if (!(outfile=fopen(argv[optind], "w"))) {
      fprintf(stderr, "Unable to open %s\n", argv[optind]);
      return 1;
    }
    optind++;
  }
  set_verbose(verbose);
  pnm_readpaminit(infile, inpam, sizeof(struct pam));
  rgb=readrgb(inpam);
  pal=rgb2pal(rgb, 1<<bits);
  free_rgb(rgb);
  writepal(pal, outfile);
  free_pal(pal);
  return 0;
}

void help(char *name) {
  version();
  fprintf(stderr, "Usage: %s [<options>] [<infile>] [<outfile>]\n", name);
  fprintf(stderr, "\toptions are\n");
  fprintf(stderr, "\t-b\t--bits\t\tbit depth of palette (%d)\n", BITS);
  fprintf(stderr, "\t-h\t--help\t\tprint this help message\n");
  fprintf(stderr, "\t-i\t--in\t\tinput file (stdin)\n");
  fprintf(stderr, "\t-o\t--out\t\toutput file (stdout)\n");
  fprintf(stderr, "\t-V\t--version0\tget version information\n");
  fprintf(stderr, "\t-v\t--verbose\tincrease verbosity\n");
}

void version(void) {
  fprintf(stderr, "getpalette version %s %s\n", VERSION, DATE);
  libzxntoolsver(1);
}
