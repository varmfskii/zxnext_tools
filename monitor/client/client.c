#include <arpa/inet.h>
#include <netdb.h> 
#include <netinet/in.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h>
#include <sys/socket.h> 
#include <unistd.h>

#define MAX 80 
#define PORT 8080 

void error(char *, int);
void master(int);

int main() 
{ 
  int sockfd, connfd; 
  struct sockaddr_in servaddr, cli; 
  
  sockfd = socket(AF_INET, SOCK_STREAM, 0); 
  if (sockfd == -1) error("socket creation failed", 1); 
  bzero(&servaddr, sizeof(servaddr)); 
  servaddr.sin_family = AF_INET; 
  servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
  servaddr.sin_port = htons(PORT); 
  if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0)
    error("connection with the server failed", 2);
  master(sockfd); 
  close(sockfd); 
} 

void master(int sockfd) 
{ 
  char buff[MAX]; 
  int n, c;
  ssize_t len;
  
  for (;;) { 
    printf("Enter the string : "); 
    for(n=0; n<MAX-1 && (c=getchar())!=EOF && c!='\n'; n++) buff[n]=c;
    buff[n]='\0';
    if (n) write(sockfd, buff, strlen(buff)); 
    bzero(buff, sizeof(buff)); 
    if (c==EOF) {
      write(sockfd, "exit", 4);
      len=read(sockfd, buff, sizeof(buff)); 
      break;
    }
    len=read(sockfd, buff, sizeof(buff)); 
    printf("From Server: %s\n", buff); 
    if ((strncmp(buff, "exit", 4)) == 0) { 
      printf("Client Exit...\n"); 
      break; 
    }
  } 
} 

void error(char *msg, int err) {
  fprintf(stderr, "%s\n", msg);
  exit(err);
}
