/* Client pour les sockets
 *    socket_client ip_server port
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char **argv)
{
  int sockfd, newsockfd, clilen, chilpid, ok, nleft, nbwriten;
  unsigned long int c;
  unsigned long int c2;
  struct sockaddr_in cli_addr, serv_addr;

  if (argc != 3)
  {
    printf("usage  socket_client server port\n");
    exit(0);
  }

  /*
   *  partie client
   */
  printf("client starting\n");

  /* initialise la structure de donnee */
  bzero((char *)&serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
  serv_addr.sin_port = htons(atoi(argv[2]));

  /* ouvre le socket */
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    printf("socket error\n");
    exit(0);
  }

  /* effectue la connection */
  if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
  {
    printf("socket error\n");
    exit(0);
  }
  
  int response;
  recv(sockfd, &response, 4, 0);
  close(sockfd);
  long seconds = ntohl(response) - 2208988800U;

  printf("Time: %s", ctime(&seconds));
  return 1;
}
