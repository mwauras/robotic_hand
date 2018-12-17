#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define PORTNO 51717

static char buffer[256];
static int sockfd,newsockfd,clilen;
static struct sockaddr_in serv_addr,cli_addr;
static int n;

void error(char *msg);
//This function connects the client to the serverpi
int socketClientConnect();
//This function returns the buffer used in file descriptor of the socket
uint16_t * getBuffer();
