#include <stdlib.h>
#include <ctype.h>
#include "nexcreator.h"

#define START 1
#define NORM 2
#define QUOTE 3

char **parseCSV(char *line) {
  int i, j, fields, f, ix, state;
  char **rv;
  
  if (!line[0]) fields=0;
  /* find number of fields */
  fields=1;
  state=NORM;
  for(i=0; line[i]; i++)
    if (state!=QUOTE) {
      if (line[i]==',')
	fields++;
      else if (line[i]=='"')
	state=QUOTE;
      else if (line[i]==';') {
	line[i]='\0';
	break;
      }
    } else if (line[i]=='"')
      state=NORM;
  rv=malloc(sizeof(char *)*(fields+1));
  if (!fields) {
    rv[0]=NULL;
    return rv;
  }
  /* split up fields */
  state=START;
  for(i=ix=f=0; line[i]; i++) {
    switch (state) {
    case START:
      if (isspace(line[i])) break;
      ix=i;
      state=NORM;
    case NORM:
      switch(line[i]) {
      case ',':
	rv[f++]=&(line[ix]);
	line[i]='\0';
	for(j=i-1; j>=0 && isspace(line[j]); j--) line[j]='\0';
	state=START;
	break;
      case '"':
	state=QUOTE;
	break;
      }
    case QUOTE:
      if (line[i]=='"') state=NORM;
    }
  }
  for(j=i-1; j>=0 && isspace(line[j]); j--) line[j]='\0';
  rv[f++]=&line[ix];
  rv[f]=NULL;
  return rv;
}
