#include "getpalette.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#define BITS 8

void help(char *);

int main(int argc, char *argv[]) {
  int opt, ix, bits;
  char *opts="b:hi:o:";
  struct option options[]={
    { "bits", 1, NULL, 'b' },
    { "help", 0, NULL, 'h' },
    { "in", 1, NULL, 'i' },
    { "out", 1, NULL, 'o' },
    { NULL, 0, NULL, '\0' }
  };
  FILE *infile, *outfile;
  rgb_t rgb;
  pal_t pal;
  bits=BITS;
  
  infile=stdin;
  outfile=stdout;
  while((opt=getopt_long(argc, argv, opts, options, &ix))!=-1) {
    switch(opt) {
    case 'b':
      bits=atoi(optarg);
      if (bits!=1 && bits!=2 && bits!=4 && bits!=8) {
	fprintf(stderr, "Unsupported bit depth %d\n", bits);
	return 1;
      }
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
  writepal(pal, outfile);
  free(pal.dat);
  return 0;
}

void help(char *name) {
  fprintf(stderr, "Usage: %s <options>\n", name);
}
