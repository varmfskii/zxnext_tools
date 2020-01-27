#include "imagetoasm.h"
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#define BITS 8
#define LABEL "label"
#define OFFSET 0
#define SKIP 1
#define SIZE 16
#define RAW 0
#define ASM 1
#define PGM 2
#define VERSION "1.01.01"
#define DATE "20190215"

void help(char *);
void version(void);

/*
 * imagetoasm: a tool for splitting image files into assembly code
 *
 * Theodore (Alex) Evans - 2019
 */

int main(int argc, char *argv[]) {
  struct option opts[] = {
    { "asm", 0, NULL, 'a' },
    { "bits", 1, NULL, 'b' },
    { "pgm", 0, NULL, 'g' },
    { "help", 0, NULL, 'h' },
    { "in", 1, NULL, 'i' },
    { "label", 1, NULL, 'l' },
    { "out", 1, NULL, 'o' },
    { "offset", 1, NULL, 'O' },
    { "pal", 1, NULL, 'p' },
    { "raw", 0, NULL, 'r' },
    { "sprite", 0, NULL, 's' },
    { "skip", 1, NULL, 'S' },
    { "tile", 0, NULL, 't' },
    { "version", 0, NULL, 'V' },
    { "verbose", 0, NULL, 'v' },
    { "size", 1, NULL, 'z' },
    { NULL, 0, NULL, 0 }
  };
  char optstring[]="ab:ghi:l:o:O:p:rsS:tvVz:";
  int opt, ix;
  FILE *infile, *outfile, *palfile;
  struct pam *inpam;
  int verbose=0;
  int offset=OFFSET;
  int skip=SKIP;
  int size=SIZE;
  int bits=BITS;
  int type=ASM;
  pal_t pal;
  rgb_t rgb, dec;
  ixed_t ixed;
  char *label=LABEL;

  infile=stdin;
  outfile=stdout;
  palfile=NULL;
  pnm_init(&argc, argv);
  inpam=(struct pam *)calloc(sizeof(struct pam), 1);
  while((opt=getopt_long(argc, argv, optstring, opts, &ix))!=-1) {
    switch(opt) {
    case 'b':
      bits=atoi(optarg);
      break;
    case 'g':
      type=PGM;
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
    case 'l':
      label=strdup(optarg);
      break;
    case 'o':
      if(!(outfile=fopen(optarg, "w"))) {
	fprintf(stderr, "Unable to open %s\n", optarg);
	return 1;
      }
      break;
    case 'O':
      offset=atoi(optarg);
      break;
    case 'p':
      if (!(palfile=fopen(optarg, "r"))) {
	fprintf(stderr, "Unable to open %s\n", optarg);
	return 1;
      }
      break;
    case 'r':
      type=RAW;
      break;
    case 's':
      bits=8;
      size=16;
      break;
    case 'S':
      skip=atoi(optarg);
      break;
    case 't':
      bits=4;
      size=8;
      break;
    case 'V':
      version();
      exit(0);
    case 'v':
      verbose++;
      break;
    case 'z':
      size=atoi(optarg);
      break;
    default:
      fprintf(stderr, "Illegal argument %c\n", opt);
      help(argv[0]);
      exit(1);
    }
  }
  for(int i=0; i<argc; i++) fprintf(stderr, "%s ", argv[i]);
  putc('\n', stderr);
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
  if (palfile) {
    pal=readpal(1<<bits, palfile);
    fclose(palfile);
  } else {
    pal=palette(bits);
  }
  if (!pal.l) return 1;
  rgb=readrgb(inpam);
  if (!rgb.dat) return 1;
  fclose(infile);
  dec=decimate(rgb, offset, offset, skip, skip);
  free_rgb(rgb);
  ixed=rgb2index(dec, pal);
  free_rgb(dec);
  free_pal(pal);
  switch (type) {
  case RAW:
    writeraw(outfile, ixed, size, size);
    break;
  case ASM:
    writeasm(outfile, ixed, size, size, label);
    break;
  case PGM:
    writepgm(outfile, ixed, size, size);
    break;
  default:
    fprintf(stderr, "Error\n");
  }
  free_ixed(ixed);
  fclose(outfile);
}

void help(char *name) {
  version();
  fprintf(stderr, "Usage: %s [<options>] [<infile>] [<outfile>]\n", name);
  fprintf(stderr, "\toptions with defaults in parenthesis:\n");
  fprintf(stderr, "\t-a\t--asm\t\toutput assembly code (asm)\n");
  fprintf(stderr, "\t-b\t--bits\t\tnumber of bits per pixel (%d)\n", BITS);
  fprintf(stderr, "\t-h\t--help\t\tshow this help message\n");
  fprintf(stderr, "\t-i\t--in\t\tinput file (stdin)\n");
  fprintf(stderr, "\t-l\t--label\t\tlabel in assembly file (%s)\n", LABEL);
  fprintf(stderr, "\t-o\t--out\t\toutput file (stdout)\n");
  fprintf(stderr, "\t-O\t--offset\toffset (x and y) in image (%d)\n", OFFSET);
  fprintf(stderr, "\t-p\t--pal\t\tpalette file (internal)\n");
  fprintf(stderr, "\t-r\t--raw\t\tout raw binary data (asm)\n");
  fprintf(stderr, "\t-s\t--sprite\tgenerate sprites = -b8 -z16\n");
  fprintf(stderr, "\t-S\t--skip\t\tuse ever nth pixel (%d)\n", SKIP);
  fprintf(stderr, "\t-t\t--tile\t\tgenerate tiles = -b4 -z8\n");
  fprintf(stderr, "\t-V\t--version\tshow version information\n");
  fprintf(stderr, "\t-v\t--verbose\tincrease verbosity\n");
  fprintf(stderr, "\t-z\t--size\t\telement size (%d)\n", SIZE);
}

void version(void) {
  fprintf(stderr, "imagetoasm version %s %s\n", VERSION, DATE);
  libzxntoolsver(1);
}
