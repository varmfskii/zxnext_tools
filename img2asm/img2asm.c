#include "img2asm.h"
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

void help(char *);

/*
 * img2asm: a tool for splitting image files into assembly code
 *
 * Theodore (Alex) Evans - 2019
 */

int main(int argc, char *argv[]) {
    struct option opts[] = {
      { "arm", 0, NULL, 'a' },
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
      { "size", 1, NULL, 'z' },
      { NULL, 0, NULL, 0 }
    };
    char optstring[]="ab:ghi:l:o:O:p:rsS:tz:";
    int opt, ix;
    FILE *infile, *outfile, *palfile;
    int offset=OFFSET;
    int skip=SKIP;
    int size=SIZE;
    int bits=BITS;
    int type=ASM;
    pal_t pal;
    rgb_t rgb;
    ixed_t ixed;
    char *label=LABEL;

    infile=stdin;
    outfile=stdout;
    palfile=NULL;
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
            return 0;
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
          case 'z':
            size=atoi(optarg);
            break;
          default:
            fprintf(stderr, "Illegal argument %c\n", opt);
            exit(1);
        }
    }
    if (palfile) {
      pal=readpal(1<<bits, palfile);
      fclose(palfile);
    } else {
      pal=palette(bits);
    }
    if (!pal.l) return 1;
    rgb=readppm(infile);
    if (!rgb.dat) return 1;
    fclose(infile);
    ixed=rgb2index(rgb, pal, offset, offset, skip, skip);
    free(rgb.dat);
    free(pal.dat);
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
    free(ixed.dat);
    free(ixed.pal.dat);
    fclose(outfile);
}

void help(char *name) {
  fprintf(stderr, "Usage: %s <options>\n", name);
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
  fprintf(stderr, "\t-z\t--size\t\telement size (%d)\n", SIZE);
}
