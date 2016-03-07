#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

void error(const char *msg) {
  perror(msg);
  exit(0);
}

int main(int argc, char *argv[]) {
  int sockfd, portno, n;
  struct sockaddr_in serv_addr;

  char buffer[256];

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    error("ERROR opening socket");
  }
    
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(1234);
  inet_aton("127.0.0.1", &serv_addr.sin_addr);
  
  if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)  {
    error("ERROR connecting");
  }

  const char* req = "{  \
   \"id\":1, \
   \"method\":\"RPCFunc.Echo\", \
   \"params\":[ \
      \"apple\" \
   ] \
}";
  n = write(sockfd, req, strlen(req));
  if (n < 0) {
    error("ERROR writing to socket");
  }
  
  bzero(buffer,256);
  n = read(sockfd,buffer,255);
  if (n < 0)  {
    error("ERROR reading from socket");
  }
  
  printf("Received: %s\n",buffer);
  close(sockfd);
  return 0;
}
