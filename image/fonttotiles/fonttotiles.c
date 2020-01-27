#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#define VERSION "1.00.01"
#define DATE "20190917"
#define INK 15
#define PAPER 0

void help(char *);
void version(void);

int ink=INK;
int paper=PAPER;

int main(int argc, char *argv[]) {
  int verbose;
  int i, c, v;
  int opt, ix;
  char *opts="b:f:hI:i:o:P:Vv";
  struct option options[]={
    { "bg", 1, NULL, 'b' },
    { "fg", 1, NULL, 'f' },
    { "help", 0, NULL, 'h' },
    { "ink", 1, NULL, 'I' },
    { "in", 1, NULL, 'i' },
    { "out", 1, NULL, 'o' },
    { "paper", 1, NULL, 'P' },
    { "version", 0, NULL, 'V' },
    { "verbose", 0, NULL, 'v' },
    { NULL, 0, NULL, '\0' }
  };
  FILE *infile, *outfile;
    
  verbose=0;
  infile=stdin;
  outfile=stdout;
  while((opt=getopt_long(argc, argv, opts, options, &ix))!=-1) {
    switch(opt) {
    case 'b':
    case 'P':
      if (!sscanf(optarg, "%d", &paper) || paper<0 || paper>15) {
	fprintf(stderr, "Illegal paper value: %s\n", optarg);
	return 1;
      }
      break;
    case 'f':
    case 'I':
      if (!sscanf(optarg, "%d", &ink) || ink<0 || ink>15) {
	fprintf(stderr, "Illegal ink value: %s\n", optarg);
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
  //set_verbose(verbose);
  for(i=0; i<32*8*4; i++) putc('\0', outfile);
  while((c=getc(infile))!=EOF) {
    for(i=0; i<4; i++) {
      v=((c&0x80)?(ink<<4):(paper<<4))|((c&0x40)?ink:paper);
      c<<=2;
      putc(v, outfile);
    }
  }
  fclose(infile);
  fclose(outfile);
  return 0;
}

void help(char *name) {
  version();
  fprintf(stderr, "Usage: %s [<options>] [<infile>] [<outfile>]\n", name);
  fprintf(stderr, "\toptions are\n");
  fprintf(stderr, "\t-b\t--bg\t\tset paper color (%d)\n", paper);
  fprintf(stderr, "\t-f\t--fg\t\tset ink color (%d)\n", ink);
  fprintf(stderr, "\t-h\t--help\t\tprint this help message\n");
  fprintf(stderr, "\t-I\t--ink\t\tset ink color (%d)\n", ink);
  fprintf(stderr, "\t-i\t--in\t\tinput file (stdin)\n");
  fprintf(stderr, "\t-o\t--out\t\toutput file (stdout)\n");
  fprintf(stderr, "\t-P\t--paper\t\tset paper color (%d)\n", paper);
  fprintf(stderr, "\t-V\t--version\tget version information\n");
  fprintf(stderr, "\t-v\t--verbose\tincrease verbosity\n");
}

void version(void) {
  fprintf(stderr, "fonttotiles version %s %s\n", VERSION, DATE);
  //libzxntoolsver(1);
}
