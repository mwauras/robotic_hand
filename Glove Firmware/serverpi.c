/* A simple server in the internet domain using TCP*/
#include "serverpi.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORTNO 51717
#define SEESAW_ADC_BASE 0x09

static char buffer[256];
static int sockfd, newsockfd,clilen;
static struct sockaddr_in serv_addr, cli_addr;
static int n;
//This function shows an error if the connection is not made
void error(char *msg){
    perror(msg);
    exit(1);
}

//This function initializes the socket
void socketServerConnect(){

   //Creates the socket file descriptor
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if (sockfd < 0)
      error("ERROR opening socket");

  //clears buffer
   bzero((char *) &serv_addr, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(PORTNO);
   if (bind(sockfd, (struct sockaddr *) &serv_addr,
            sizeof(serv_addr)) < 0)
            error("ERROR on binding");

   //listens for 2nd pi to pair
   listen(sockfd,5);
   clilen = sizeof(cli_addr);

   //creates new file descriptor for socket once paired with 2nd pi
   newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
   if (newsockfd < 0)
        error("ERROR on accept");
   printf("Connection Successful\n");
}
