#include <arpa/inet.h>
#include <locale.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#ifdef CURSES
#include <curses.h>
#endif
#include "zxnftp.h"

void init(void) {
  struct sockaddr_in address;
  char line[BLKSZ], *home;
  int i, c, colon;
  FILE *in;
  struct timeval tv;

  home=getenv("HOME");
  if (home)
    sprintf(line, "%s/.zxnftprc", home);
  else
    strcpy(line, ".zxnftprc");
  fdata=(char *)malloc(DATASZ);
  fdata_sz=DATASZ;
  ddata=(char *)malloc(DATASZ);
  ddata_sz=DATASZ;
  lines=(char **)malloc(LINESSZ*(sizeof (char *)));
  lines_sz=LINESSZ;
  if (!(in=fopen("zxnftp.conf", "r")) &&
      !(in=fopen(line, "r")) &&
      !(in=fopen("/etc/zxnftp.conf", "r"))) { 
    fprintf(stderr, "Unable to open configuration file\n");
    exit(1);
  }
  for(i=colon=0; i<BLKSZ && (c=getc(in))!=EOF && c!='\n'; i++) {
    line[i]=c;
    if (c==':') colon=i;
  }
  fclose(in);
  line[i]='\0';
  line[colon]='\0';
  addr=strdup(line);
  port=atoi(line+colon+1);
  // init socket
  server=socket(AF_INET, SOCK_STREAM, 0); 
  if (server == -1) error("socket creation failed", 1); 
  address.sin_family = AF_INET; 
  address.sin_addr.s_addr = inet_addr(addr); 
  address.sin_port = htons(port); 
  if (connect(server, (struct sockaddr *)&address, sizeof(address)) != 0)
    error("connection with the server failed", 2);
  tv.tv_sec=3;
  tv.tv_usec=0;
  setsockopt(server, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
  call_id();
  //init windows
#ifdef CURSES
  setlocale(LC_ALL, "");
  initscr();
  getmaxyx(stdscr, h, w);
  
  win=newwin(h-1, w, 1, 0);
  scrollok(win, TRUE);
  status=newwin(1, w, 0, 0);
  noecho();
  raw();
  nl();
  wclear(status);
  wclear(win);
  waddstr(win, "ZXNFTP client v1.0\n");
  waddstr(win, "connected to server: ");
  waddstr(win, line);
  waddch(win, ':');
  waddstr(win, line+colon+1);
  waddch(win, '\n');
  waddstr(win, "server id: ");
  waddstr(win, id);
  waddch(win, '\n');
#endif
} 
