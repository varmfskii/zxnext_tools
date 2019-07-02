#include <netdb.h> 
#include <netinet/in.h> 
#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h>

#define MAX 80 
#define PORT 8080 

void error(char *, int);
void slave(int);

int main() 
{ 
  int sockfd, connfd, len; 
  struct sockaddr_in addr, cli; 
  
  // socket create and verification 
  sockfd = socket(AF_INET, SOCK_STREAM, 0); 
  if (sockfd == -1) error("socket creation failed", 1);
  bzero(&addr, sizeof(addr)); 
  addr.sin_family = AF_INET; 
  addr.sin_addr.s_addr = htonl(INADDR_ANY); 
  addr.sin_port = htons(PORT); 
  if ((bind(sockfd, (struct sockaddr *)&addr, sizeof(addr))) != 0) error("socket bind failed", 2);
  if ((listen(sockfd, 5)) != 0) error("Listen failed", 3); 
  len = sizeof(cli); 
  connfd = accept(sockfd, (struct sockaddr *)&cli, &len); 
  if (connfd < 0) error("server acccept failed", 4); 
  slave(connfd); 
  close(sockfd); 
} 
  
// monitor slave function
void slave(int sockfd) 
{ 
  char buff[MAX], *cmd; 
  int n; 
  ssize_t len, total;
  
  for (;;) { 
    bzero(buff, MAX); 
    len=read(sockfd, buff, sizeof(buff)); 
    sscanf(buff, "%ms", &cmd);
    for(total=len; len==MAX; len=read(sockfd, buff, sizeof(buff))) printf("%d\n", total+=len);
    printf("%d: %s\n", total, cmd);
    write(sockfd, cmd, strlen(cmd)); 
    if (strncmp("exit", cmd, 4) == 0) break; 
    free(cmd);
  } 
} 

void error(char *msg, int err) {
  fprintf(stderr, "%s\n", msg);
  exit(err);
}
