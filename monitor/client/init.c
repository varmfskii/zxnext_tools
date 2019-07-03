#include "client.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <curses.h>
#include <locale.h>
#include <unistd.h>

void init(void) {
  struct sockaddr_in address;
  
#ifndef NONET
  // init socket
  server=socket(AF_INET, SOCK_STREAM, 0); 
  if (server == -1) error("socket creation failed", 1); 
  address.sin_family = AF_INET; 
  address.sin_addr.s_addr = inet_addr("127.0.0.1"); 
  address.sin_port = htons(PORT); 
  if (connect(server, (struct sockaddr *)&address, sizeof(address)) != 0)
    error("connection with the server failed", 2);
#endif
  //init windows
  setlocale(LC_ALL, "");
  initscr();
  getmaxyx(stdscr, h, w);
  
  win=newwin(h-1, w, 1, 0);
  status=newwin(1, w, 0, 0);
  noecho();
  raw();
  nl();
  refresh();
} 
