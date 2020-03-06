#include "paltoppm.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BITS 8
#define VERSION "1.00.00"
#define DATE "20200126"

void help(char *);
void version(void);

int main(int argc, char *argv[]) {
  int opt, ix, bits, verbose;
  char *opts="b:hi:o:Vv";
  struct option options[]={
    { "bits", 1, NULL, 'b' },
    { "help", 0, NULL, 'h' },
    { "in", 1, NULL, 'i' },
    { "out", 1, NULL, 'o' },
    { "version", 0, NULL, 'V' },
    { "verbose", 0, NULL, 'v' },
    { NULL, 0, NULL, '\0' }
  };
  FILE *infile, *outfile;
  pal_t pal;
  rgb_t rgb;
  int x, y;
  
  bits=BITS;
  infile=stdin;
  outfile=stdout;
  verbose=0;
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
  switch(bits) {
  case 1:
    x=2;
    y=1;
    break;
  case 2:
    x=2;
    y=2;
    break;
  case 4:
    x=4;
    y=4;
    break;
  case 8:
    x=16;
    y=16;
    break;
  default:
    fprintf(stderr, "Illegal bit depth %d\n", bits);
    return 1;
  }
  pal=readpal(1<<bits, infile);
  fclose(infile);
  rgb=new_rgb(x, y, 0);
  memcpy(rgb.dat[0], pal.dat, 1<<(bits+2));
  free_pal(pal);
  writergb(rgb, outfile);
  fclose(outfile);
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
  fprintf(stderr, "\t-V\t--version\tget version information\n");
  fprintf(stderr, "\t-v\t--verbose\tincrease verbosity\n");
}

void version(void) {
  fprintf(stderr, "paltoppm version %s %s\n", VERSION, DATE);
  libzxntoolsver(1);
}
