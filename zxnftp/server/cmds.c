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
uint8_t f, len;
uint32_t rlen, flen;

/* handle simple commands that translate as a single call */
void cmd_simple(const char *name, uint8_t (*fn)(char *)) {
  nettxln("OK");
  netrxln(buf);
  f=0xff;
  f=fn(buf);
  if (f==0xff)
    senderr();
  else {
    nettxln("OK");
    printf("%s %s\n", name, buf);
  }
}

/* change directories, simple */
void cmd_cd(void) {
  cmd_simple("cd", esx_f_chdir);
}

/* change drive */
void cmd_drive(void) {
  nettxln("OK");
  netrxln(buf);
  f=0xff;
  f=esx_dos_set_drive(buf[0]);
  if (f==0xff)
    senderr();
  else {
    nettxln("OK");
    printf("drive %c\n", buf[0]);
  }
}

/* get a file from server */
void cmd_get(void) {
  nettxln("OK");
  netrxln(buf);
  f=0xff;
  f=esx_f_open(buf, ESX_MODE_OPEN_EXIST|ESX_MODE_R);
  if (f==0xff) {
    senderr();
    return;
  }
  esx_f_fstat(f, &stat);
  printf("get %s: ", buf);
  sprintf(buf, "%d", stat.size);
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
      nettxln("OK");
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
  f=0xff;
  f=esx_f_opendir_ex(buf, ESX_DIR_USE_LFN);
  if (f==0xff) {
    senderr();
    return;
  }
  printf("ls %s\n", buf);
  nettxln("OK");
  for(;;) {
    netrxln(buf);
    if (strcmp("RR", buf)) {
      nettxln("XX");
      break;
    }
    if (!esx_f_readdir(f, &dirent) || errno) {
      nettxln("OK");
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

/* list current directory */
void cmd_l_(void) {
  esx_f_getcwd(buf);
  do_ls();
}

/* list a directory */
void cmd_ls(void) {
  nettxln("OK");
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
  
  nettxln("OK");
  netrxln(buf);
  f=0xff;
  f=esx_f_open(buf, ESX_MODE_OPEN_CREAT_NOEXIST|ESX_MODE_W);
  if (f==0xff) {
    senderr();
    return;
  }
  nettxln("OK");
  printf("put %s: ", buf);
  netrxln(buf);
  sscanf(buf, "%ld", &flen);
  printf("%ld bytes\n", flen);
  for(rlen=0; rlen<flen; rlen+=len) {
    nettxln("RR");
    netrx(buf, &tlen, RAW);
    len=tlen;
    errno=0;
    esx_f_write(f, buf, len);
    if (errno) {
      senderr();
      esx_f_close(f);
      return;
    }
  }
  esx_f_close(f);
  nettxln("OK");
}

/* shutdown server */
void cmd_quit(void) {
  puts("quit");
  nettxln("OK");
  cmdresponse("AT+CIPCLOSE=0\r\n");
  cmdresponse("AT+CIPSERVER=0\r\n");
  cmdresponse("ATE1\r\n");
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
  nettxln("OK");
  cmdresponse("AT+CIPCLOSE=0\r\n");
}
