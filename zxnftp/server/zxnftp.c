#include <arch/zxn.h>
#include <arch/zxn/esxdos.h>
#include <errno.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include "zxnftp.h"

struct cmd {
  const char *name;
  void (*fn)(void);
};

#ifdef DOTN
char pool[8192+3*BLKSZ];
#endif
//char bbuf[8192+BLKSZ], buf[BLKSZ], line[BLKSZ];
char *bbuf, *buf, *line;
char old_clock;

const struct cmd cmds[]={
		   { "BD", cmd_baud },
		   { "CD", cmd_cd },
		   { "DR", cmd_drive },
		   { "GT", cmd_get },
		   { "ID", cmd_id },
		   { "LS", cmd_ls },
		   { "MD", cmd_mkdir },
		   { "PD", cmd_pwd },
		   { "PT", cmd_put },
		   { "QU", cmd_quit },
		   { "RD", cmd_rmdir },
		   { "RM", cmd_rm },
		   { "XX", cmd_exit },
		   { NULL, NULL }};

int main() {
  int16_t f, i, j, len;

  // select 28 MHz clock
  NEXT_SEL=0x07;
  old_clock=NEXT_RW;
  NEXT_RW=0x03;
  // ensure uart is connected to ESP and not Pi
  UART_CTL=0x00;
#ifdef DOTN
  bbuf=pool;
#else
  if (!(bbuf=(char *)malloc(8192+3*BLKSZ))) {
    puts("Memory allocation failed");
    return 1;
  }
#endif
  buf=bbuf+8192+BLKSZ;
  line=buf+BLKSZ;
  puts("ZXNFTP server id: " ID);
  ioctl(1, IOCTL_OTERM_PAUSE, 0);
  puts("starting server");
  errno=0;
  if ((f=esx_f_open(CONFIG1, ESX_MODE_OPEN_EXIST|ESX_MODE_R))==0xff &&
      (f=esx_f_open(CONFIG2, ESX_MODE_OPEN_EXIST|ESX_MODE_R))==0xff &&
      (f=esx_f_open(CONFIG3, ESX_MODE_OPEN_EXIST|ESX_MODE_R))==0xff) {
    puts("Unable to open configuration file");
    return 1;
  }
  i=0;
  for(;;) {
    if (!(len=esx_f_read(f, buf,  BLKSZ))) break;
    for(j=0; j<len; j++) 
      if (buf[j]=='\n' || buf[j]=='\r') {
	line[i++]='\r';
	line[i++]='\n';
	line[i]='\0';
	uartwrite(line, i);
	if (uartresponse()!=OK) {
	  line[i-2]='\0';
	  printf("Command failed: %s\n", line);
	  return 1;
	}
	i=0;
      } else
	line[i++]=buf[j];
  }
  esx_f_close(f);
  puts("server started");
  for(;;) {
    netrxln(buf);
    errno=0; // clear errors
    for(i=0; cmds[i].name; i++)
      if (!strcmp(cmds[i].name, buf)) {
	//puts(cmds[i].name);
	cmds[i].fn();
	break;
      }
    if (!cmds[i].name) {
      puts("unknown command");
      nettxln("UK");
    }
  }
  //return 0;
}
