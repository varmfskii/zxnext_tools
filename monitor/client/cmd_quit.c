#include "client.h"
#include <stdlib.h>

void cmd_quit(char **parameters) {
  finish();
  exit(0);
}
