/* 
 * File:  Server.cpp
 * Author: AnkurChauhan
 *
 * Created on July 27, 2016, 6:53 PM
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>


using namespace std;

#define PORT 6252


void error(const char *msg)
{
    perror(msg);
    exit(1);
}


int main()
{
   int sockfd, newsockfd, n,pid;
   socklen_t clilen;
   char buffer[256],str[]="bye";
   struct sockaddr_in serv_addr, cli_addr;   
  
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
     if (sockfd < 0) 
         error("ERROR opening socket");

   bzero((char *) &serv_addr, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_port = htons(PORT);
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   
   if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
         error("ERROR on binding");
   
   listen(sockfd,5);
   clilen = sizeof(cli_addr);
  for(;;)
  {   // clilen = sizeof(cli_addr);
       newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
      //cout<<"\n sockfd:"<<sockfd;
       
       if(newsockfd < 0) 
          error("ERROR on accept");
       pid=fork();
       
       if(pid<0)
         error("ERROR creating child process");
       
       if(pid>0)
         close(newsockfd);
       else
       {
         close(sockfd);
          while(1)
          {
            bzero(buffer,256);
            n = read(newsockfd,buffer,255);
            if (n < 0) error("ERROR reading from socket");
            printf("The Conversation: %s\n",buffer);
            //cout<<"buffer::"<<buffer[0];
            if(strncmp(str,buffer,strlen(str))==0)
            {   
              cout<<"\nprog ends";
              exit(1);
            }

            bzero(buffer,256);
            fgets(buffer,256,stdin);
            n = write(newsockfd,buffer,256);
            if (n < 0) error("ERROR writing to socket");
          }
        }
    }

   return 0;
}


