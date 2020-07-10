#include "ppmtosl2.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERSION "2.01.00"
#define DATE "20200710"

void help(char *);
void version(void);

char *name;
int width, height, depth, swap;

int main(int argc, char *argv[]) {
  int opt, ix;
  int i, verbose;
  char *opts="236dhi:lo:p:rsVvx:y:";
  struct option options[]={
    { "128x96", 0, NULL, 'l' },
    { "256x192", 0, NULL, '2' },
    { "320x256", 0, NULL, '3' },
    { "640x256", 0, NULL, '6' },
    { "depth", 1, NULL, 'd' },
    { "hires", 0, NULL, 'H' },
    { "help", 0, NULL, 'h' },
    { "in", 1, NULL, 'i' },
    { "lores", 0, NULL, 'l' },
    { "out", 1, NULL, 'o' },
    { "pal", 1, NULL, 'p' },
    { "radistan", 0, NULL, 'r' },
    { "swap", 0, NULL, 's' },
    { "version", 0, NULL, 'V' },
    { "verbose", 0, NULL, 'v' },
    { NULL, 0, NULL, '\0' }
  };
  FILE *infile, *outfile, *pin;
  struct pam *inpam;
  pal_t pal;
  ixed_t ixed;
    
#ifdef DEBUG
  verbose=2;
#else
  verbose=0;
#endif
  infile=stdin;
  outfile=stdout;
  pin=NULL;
  inpam=(struct pam *)calloc(sizeof(struct pam),1);
  pnm_init(&argc, argv);
  for(name=argv[0], i=0; argv[0][i]; i++)
    if (argv[0][i]=='/') name=argv[0]+i+1;
  if (!strcmp(name, "ppmtoslr")) {
    width=128;
    height=96;
  } else {
    width=256;
    height=192;
  }
  depth=8;
  swap=0;
  while((opt=getopt_long(argc, argv, opts, options, &ix))!=-1) {
    switch(opt) {
    case '2':
    case 'H':
      width=256;
      height=192;
      depth=8;
      swap=0;
      break;
    case '3':
      width=320;
      height=256;
      depth=8;
      swap=1;
      break;
    case '6':
      width=640;
      height=256;
      depth=4;
      swap=1;
      break;
    case 'd':
      depth=atoi(optarg);
      if (depth!=1 && depth!=2 && depth!=4 && depth!=8) {
	fprintf(stderr, "Illegal depth: %s\n", optarg);
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
    case 'l':
      width=128;
      height=96;
      depth=8;
      swap=0;
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
    case 'r':
      width=128;
      height=96;
      depth=4;
      swap=0;
      break;
    case 's':
      swap=!swap;
      break;
    case 'V':
      version();
      exit(0);
    case 'v':
      verbose++;
      break;
    case 'x':
      if ((width=atoi(optarg))<1) {
	fprintf(stderr, "Illegal x-size %s\n", optarg);
	return 1;
      }
      break;
    case 'y':
      if ((height=atoi(optarg))<1) {
	fprintf(stderr, "Illegal y-size %s\n", optarg);
	return 1;
      }
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
  set_verbose(verbose);
  pnm_readpaminit(infile, inpam, sizeof(struct pam));
  if (pin) {
    pal=readpal(1<<depth, pin);
    fclose(pin);
  }  else
    pal=palette(depth);
  ixed=readixed(inpam, pal);
  free_pal(pal);
  writezxn(ixed, width, height, depth, swap, outfile);
  if (pin) nextpal(ixed.pal, outfile);
  free_ixed(ixed);
  if (outfile!=stdout) fclose(outfile);
  return 0;
}

void help(char *name) {
  version();
  fprintf(stderr, "Usage: %s [<options>] [<infile>] [<outfile>]\n", name);
  fprintf(stderr, "\toptions are\n");
  fprintf(stderr, "\t-2\t--256x192\t\t256x192x8 image\n");
  fprintf(stderr, "\t-3\t--320x256\t\t320x256x8 image\n");
  fprintf(stderr, "\t-6\t--640x256\t\t640x256x4 image\n");
  fprintf(stderr, "\t-d\t--depth\t\tbits per pixel (%d)\n", depth);
  fprintf(stderr, "\t-H\t--hires\t\t256x192x8 image\n");
  fprintf(stderr, "\t-h\t--help\t\tprint this help message\n");
  fprintf(stderr, "\t-i\t--in\t\tinput file (stdin)\n");
  fprintf(stderr, "\t-l\t--lores\t\t128x96x8 image\n");
  fprintf(stderr, "\t-o\t--out\t\toutput file (stdout)\n");
  fprintf(stderr, "\t-p\t--pal\t\tpalette file (internal)\n");
  fprintf(stderr, "\t-r\t--radistan\t\t128x96x4 image\n");
  fprintf(stderr, "\t-s\t--swap\t\tswap x and y axes\n");
  fprintf(stderr, "\t-V\t--version\tget version information\n");
  fprintf(stderr, "\t-v\t--verbose\tincrease verbosity\n");
  fprintf(stderr, "\t-x\t--width\twidth in pixels (%d)\n", width);
  fprintf(stderr, "\t-y\t--height\theight in pixels (%d)\n", height);
}

void version(void) {
  fprintf(stderr, "%s version %s %s\n", name, VERSION, DATE);
  libzxntoolsver(1);
}
