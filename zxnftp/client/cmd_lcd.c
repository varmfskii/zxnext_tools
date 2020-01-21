#include <unistd.h>
#include "zxnftp.h"

void cmd_lcd(char **params) {
  if (!params[1] || params[2]) {
    printerr("Incorrect number of arguments. lcd <dir>\n");
    return;
  }
  if (chdir(params[1])) printerr("Unable to change directory\n");
  return;
}
