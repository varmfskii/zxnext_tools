#include "client.h"
#include <stdio.h>
#include <stdlib.h>

void error(char *text, int err) {
  if (server) finish();
  fprintf(stderr, "%s\n", text);
  exit(err);
}
