#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppmtoslr.h"

#define VERSION "1.02.00"
#define DATE "20190221"

void help(char *);
void version(void);

int verbose=0;

int main(int argc, char *argv[]) {
  int opt, ix;
  char *opts="hi:o:p:Vv";
  struct option options[]={
    { "help", 0, NULL, 'h' },
    { "in", 1, NULL, 'i' },
    { "out", 1, NULL, 'o' },
    { "pal", 1, NULL, 'p' },
    { "version", 0, NULL, 'V' },
    { "verbose", 0, NULL, 'v' },
    { NULL, 0, NULL, '\0' }
  };
  FILE *infile, *outfile, *pin;
  rgb_t rgb;
  pal_t pal;
  ixed_t ixed;
    
  infile=stdin;
  outfile=stdout;
  pin=NULL;
  while((opt=getopt_long(argc, argv, opts, options, &ix))!=-1) {
    switch(opt) {
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
    case 'p':
      if(!(pin=fopen(optarg, "r"))) {
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
      if(!(infile=fopen(argv[optind], "r"))) {
	fprintf(stderr, "Unable to open %s\n", argv[optind]);
	return 1;
      }
      optind++;
  }
  if (optind<argc && outfile==stdout) {
      if(!(outfile=fopen(argv[optind], "w"))) {
	fprintf(stderr, "Unable to open %s\n", argv[optind]);
	return 1;
      }
      optind++;
  }
  rgb=readrgb(infile);
  if (infile!=stdin) fclose(infile);
  if (pin) {
    pal=readpal(0x100, pin);
    fclose(pin);
  }  else
    pal=palette(8);
  ixed=rgb2index(rgb, pal);
  free_rgb(rgb);
  free_pal(pal);
  writeslr(ixed, outfile);
  if (pin) nextpal(ixed.pal, outfile);
  free_ixed(ixed);
  if (outfile!=stdout) fclose(outfile);
  return 0;
}

void help(char *name) {
  version();
  fprintf(stderr, "Usage: %s [<options>] [<infile>] [<outfile>]\n", name);
  fprintf(stderr, "\toptions are\n");
  fprintf(stderr, "\t-h\t--help\t\tprint this help message\n");
  fprintf(stderr, "\t-i\t--in\t\tinput file (stdin)\n");
  fprintf(stderr, "\t-o\t--out\t\toutput file (stdout)\n");
  fprintf(stderr, "\t-p\t--pal\t\tpalette file (internal)\n");
  fprintf(stderr, "\t-V\t--version\tget version information\n");
  fprintf(stderr, "\t-t\t--verbose\tincrease verbosity\n");
}

void version(void) {
  fprintf(stderr, "ppmtoslr version %s %s\n", VERSION, DATE);
  libzxntoolsver(1);
}
