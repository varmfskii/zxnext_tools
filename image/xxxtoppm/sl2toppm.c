#include <stdio.h>
#include <getopt.h>
#include "sl2toppm.h"

#define VERSION "2.00.00"
#define DATE "20200119"

void help(char *);
void version(void);

int verbose=0;
int pref=320;

int main(int argc, char *argv[]) {
  FILE *in, *out;
  int opt, ix, offset, palsz;
  ixed_t ixed;
  char *opts="36hi:o:Vv";
  struct option options[]={
    { "640", 0, NULL, '3' },
    { "320", 0, NULL, '6' },
    { "help", 0, NULL, 'h' },
    { "in", 1, NULL, 'i' },
    { "out", 1, NULL, 'o' },
    { "version", 0, NULL, 'V' },
    { "verbose", 0, NULL, 'v' },
    { NULL, 0, NULL, '\0' }
  };

  in=stdin;
  out=stdout;
  while((opt=getopt_long(argc, argv, opts, options, &ix))!=-1) {
    switch(opt) {
    case '3':
      pref=320;
      break;
    case '6':
      pref=640;
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
    case 'V':
      version();
      break;
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

  ixed=readsl2(in);
  writeixed(ixed, 0, out);
  free_ixed(ixed);
}

void help(char *name) {
  version();
  fprintf(stderr, "Usage: %s [<options>] [<infile>] [<outfile>]\n", name);
  fprintf(stderr, "\toptions are\n");
  fprintf(stderr, "\t-3\t--320\t\tprefer 320x256x8\n");
  fprintf(stderr, "\t-6\t--640\t\tprefer 640x256x4\n");
  fprintf(stderr, "\t-h\t--help\t\tprint this help message\n");
  fprintf(stderr, "\t-i\t--in\t\tinput file (stdin)\n");
  fprintf(stderr, "\t-o\t--out\t\toutput file (stdout)\n");
  fprintf(stderr, "\t-V\t--version\tget version information\n");
  fprintf(stderr, "\t-v\t--verbose\tincrease verbosity\n");
}

void version(void) {
  fprintf(stderr, "sl2toppm version %s %s\n", VERSION, DATE);
  libzxntoolsver(1);
}
