#include "getpalette.h"
#include "../support/support.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BITS 8
#define RAW 0
#define ASM 1
#define LABEL "palette"

void help(char *);

int main(int argc, char *argv[]) {
  int opt, ix, bits, type;
  char *opts="ab:hi:l:o:r";
  char *label;
  struct option options[]={
    { "asm", 0, NULL, 'a' },
    { "bits", 1, NULL, 'b' },
    { "help", 0, NULL, 'h' },
    { "in", 1, NULL, 'i' },
    { "label", 1, NULL, 'l' },
    { "out", 1, NULL, 'o' },
    { "raw", 0, NULL, 'r' },
    { NULL, 0, NULL, '\0' }
  };
  FILE *infile, *outfile;
  rgb_t rgb;
  pal_t pal;
  bits=BITS;
  type=RAW;
  label=LABEL;
    
  infile=stdin;
  outfile=stdout;
  while((opt=getopt_long(argc, argv, opts, options, &ix))!=-1) {
    switch(opt) {
    case 'a':
      type=ASM;
      break;
    case 'b':
      bits=atoi(optarg);
      if (bits!=1 && bits!=2 && bits!=4 && bits!=8) {
	fprintf(stderr, "Unsupported bit depth %d\n", bits);
	return 1;
      }
      break;
    case 'h':
      help(argv[0]);
      return 0;
      break;
    case 'i':
      if(!(infile=fopen(optarg, "r"))) {
	fprintf(stderr, "Unable to open %s\n", optarg);
	return 1;
      }
      break;
    case 'l':
      label=strdup(optarg);
      break;
    case 'o':
      if(!(outfile=fopen(optarg, "w"))) {
	fprintf(stderr, "Unable to open %s\n", optarg);
	return 1;
      }
      break;
    default:
      fprintf(stderr, "Illegal option %c\n", opt);
    }
  }
  rgb=readppm(infile);
  pal=rgb2pal(rgb, 1<<bits);
  free(rgb.dat);
  switch (type) {
  case RAW:
    writeraw(pal, outfile);
    break;
  case ASM:
    writeasm(pal, outfile, label);
    break;
  default:
    fprintf(stderr, "Unsupported type\n");
  }
  free(pal.dat);
  return 0;
}

void help(char *name) {
  fprintf(stderr, "Usage: %s <options>\n", name);
  fprintf(stderr, "\toptions are\n");
  fprintf(stderr, "\t-a\t--asm\tset output type to asm (raw)\n");
  fprintf(stderr, "\t-b\t--bits\tbit depth of palette (%d)\n", BITS);
  fprintf(stderr, "\t-h\t--help\tprint this help message\n");
  fprintf(stderr, "\t-i\t--in\tinput file (stdin)\n");
  fprintf(stderr, "\t-l\t--label\tset label for assembly file (%s)\n", LABEL);
  fprintf(stderr, "\t-o\t--out\toutput file (stdout)\n");
  fprintf(stderr, "\t-r\t--raw\tset output type to raw (raw)\n");
}
