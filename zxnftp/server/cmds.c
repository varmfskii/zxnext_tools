#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <arch/zxn.h>
#include <arch/zxn/esxdos.h>
#include "zxnftp.h"

struct esx_stat stat;
struct esx_dirent_lfn dirent;
struct esx_dirent_slice *slice;
struct tm dt;
struct esx_stat stat;
uint8_t f;
int16_t len;
uint32_t rlen, flen;
//char bbuf[8192+BLKSZ];

/* handle simple commands that translate as a single call */
void cmd_simple(const char *name, uint8_t (*fn)(char *)) {
  nettx("OK\r\n", 4);
  netrxln(buf);
  errno=0;
  f=fn(buf);
  if (f==0xff || errno)
    senderr();
  else {
    nettx("OK\r\n", 4);
    printf("%s %s\n", name, buf);
  }
}

/* change directories, simple */
void cmd_cd(void) {
  cmd_simple("cd", esx_f_chdir);
}

/* change drive */
void cmd_drive(void) {
  nettx("OK\r\n", 4);
  netrxln(buf);
  errno=0;
  f=esx_dos_set_drive(buf[0]);
  if (f==0xff || errno)
    senderr();
  else {
    nettx("OK\r\n", 4);
    printf("drive %c\n", buf[0]);
  }
}

/* get a file from server */
void cmd_get(void) {
  nettx("OK\r\n", 4);
  netrxln(buf);
  errno=0;
  f=esx_f_open(buf, ESX_MODE_OPEN_EXIST|ESX_MODE_R);
  if (f==0xff || errno) {
    senderr();
    return;
  }
  esx_f_fstat(f, &stat);
  printf("get %s: ", buf);
  sprintf(buf, "%ld", stat.size);
  printf("%s bytes\n", buf);
  nettxln(buf);
  for(;;) {
    netrxln(buf);
    if (strcmp("RR", buf)) {
      nettxln("XX");
      break;
    }
    len=esx_f_read(f, buf, BLKSZ);
    if (!len) {
      nettx("OK\r\n", 4);
      break;
    }
    nettx(buf, len);
  }
  esx_f_close(f);
}

/* send server id */
void cmd_id(void) {
  puts("id");
  nettxln(ID);
}

/* handle directory listing */
void do_ls(void) {
  errno=0;
  f=esx_f_opendir_ex(buf, ESX_DIR_USE_LFN);
  if (f==0xff || errno) {
    senderr();
    return;
  }
  printf("ls %s\n", buf);
  nettx("OK\r\n", 4);
  for(;;) {
    netrxln(buf);
    if (strcmp("RR", buf)) {
      nettxln("XX");
      break;
    }
    errno=0;
    if (!esx_f_readdir(f, &dirent)) {
      nettx("OK\r\n", 4);
      break;
    }
    if (errno) {
      senderr();
      break;
    }
    slice=esx_slice_dirent(&dirent);
    tm_from_dostm(&dt, &(slice->time));
    sprintf(buf, "%02x\n%02u/%02u/%04u\n%02u:%02u:%02u",
	    dirent.attr, dt.tm_mday, dt.tm_mon+1, dt.tm_year+1900,
	    dt.tm_hour, dt.tm_min, dt.tm_sec);
    nettxln(buf);
    nettxln(dirent.name);
  }
  esx_f_close(f);
}

/* list a directory */
void cmd_ls(void) {
  nettx("OK\r\n", 4);
  netrxln(buf);
  do_ls();
}

/* create a directory, simple */
void cmd_mkdir(void) {
  cmd_simple("mkdir", esx_f_mkdir);
}

/* display the current directory */
void cmd_pwd(void) {
  puts("pwd");
  esx_f_getcwd(buf);
  nettxln(buf);
}

/* put a file to the server */
void cmd_put(void) {
  size_t tlen;
  int16_t bblen;
  
  nettx("OK\r\n", 4);
  netrxln(buf);
  errno=0;
  f=esx_f_open(buf, ESX_MODE_OPEN_CREAT_NOEXIST|ESX_MODE_W);
  if (f==0xff || errno) {
    senderr();
    return;
  }
  nettx("OK\r\n", 4);
  printf("put %s: ", buf);
  netrxln(buf);
  // not a number
  if (buf[0]<'0' || buf[0]>'9') {
    nettx("XX\r\n", 4);
    return;
  }
  sscanf(buf, "%ld", &flen);
  printf("%ld bytes\n", flen);
  esx_f_seek(f, flen-1, ESX_SEEK_SET);
  esx_f_write(f, bbuf, 1);
  esx_f_seek(f, 0, ESX_SEEK_SET);
  for(bblen=rlen=0; rlen<flen; rlen+=len) {
    nettx("RR\r\n", 4);
    netrx(bbuf+bblen, &tlen, RAW);
    len=tlen;
    errno=0;
    bblen+=len;
    if (bblen>=8192) {
      esx_f_write(f, bbuf, 8192);
      memcpy(bbuf, bbuf+8192, bblen-8192);
      bblen-=8192;
    }
    if (errno) {
      senderr();
      esx_f_close(f);
      return;
    }
  }
  esx_f_write(f, bbuf, bblen);
  esx_f_ftrunc(f, flen);
  esx_f_close(f);
  nettx("OK\r\n", 4);
}

/* shutdown server */
void cmd_quit(void) {
  puts("quit");
  nettx("OK\r\n", 4);
  cmdresponse("AT+CIPCLOSE=0\r\n");
  cmdresponse("AT+CIPSERVER=0\r\n");
  setbaud(115200);
  cmdresponse("AT+RST\r\n");
  NEXT_SEL=0x07;
  NEXT_RW=old_clock;
  puts("server done");
  exit(0);
}

/* remove a directory, simple */
void cmd_rmdir(void) {
  cmd_simple("rmdir", esx_f_rmdir);
}

/* remoce a file, simple */
void cmd_rm(void) {
  cmd_simple("rm", esx_f_unlink);
}

/* quit a session on the server, leave server running */
void cmd_exit(void) {
  puts("exit");
  nettx("OK\r\n", 4);
  cmdresponse("AT+CIPCLOSE=0\r\n");
}

void cmd_baud(void) {
  uint32_t bps;
  
  nettx("OK\r\n", 4);
  netrxln(buf);
  nettx("OK\r\n", 4);
  bps=atol(buf);
  printf("%ld baud\n", bps);
  setbaud(bps);
}
