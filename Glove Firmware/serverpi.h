#ifndef SERVERPI_H_
#define SERVERPI_H_

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORTNO 51717

static char buffer[256];
static int sockfd, newsockfd,clilen;
static struct sockaddr_in serv_addr, cli_addr;
static int n;

//This function shows an error if the connection is not made
void error(char *msg);
//This function initializes the socket
void socketServerConnect();

#endif // SERVERPI_H_
