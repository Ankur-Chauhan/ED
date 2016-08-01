/* 
 * File:   Client.cpp
 * Author: AnkurChauhan
 *
 * Created on July 26, 2016, 6:15 PM
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
#include <map>
using namespace std;

#define IP "10.250.34.210"
#define PORT 6252

void error(const char *msg)
{
    perror(msg);
    exit(0);
}



 int main()
{
    int sockfd, n;
    struct sockaddr_in serv_addr;
    struct hostent *server; 
    char buffer[256];
    char str[]="bye";
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
   

    if (sockfd < 0) 

        error("ERROR opening socket");
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr(IP);
    serv_addr.sin_port = htons(PORT);
    memset(&(serv_addr.sin_zero),'\0',8);
    
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
  
    printf("Please enter the message: ");
    
    while(1)
    {
      
      bzero(buffer,256);
    
      fgets(buffer,255,stdin);
      
      n = write(sockfd,buffer,strlen(buffer)); 
      
      //cout<<"buffer::"<<buffer[0];
      if(strncmp(str,buffer,strlen(str))==0)
      {   
        cout<<"\nprog ends";
        exit(1);
      }
      
      if (n < 0) 
        error("ERROR writing to socket");

      bzero(buffer,256);

      n = read(sockfd,buffer,255);

      if (n < 0) 
         error("ERROR reading from socket");

    printf("%s\n",buffer);
    
    }
    return 0;
}
