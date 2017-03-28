/**
*Author: Junchen Su
*Purpose: Operating System Assigment3
*Date: 3/24/2017
*/
#include <stdio.h> 
#include <unistd.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> //define htons()
#include <string.h> 
#include <sys/types.h> 
#include <netinet/in.h> //define sockaddr_in


#define BUFSIZ 1024
 
int main()
{
    int cfd;//client file descriptor, used to associate with a socket
    struct sockaddr_in s_add,c_add;
    while(1)
    {
        cfd = socket(AF_INET, SOCK_STREAM, 0);//AP_INET: IPV4, SOCK_STREAM: TCP, 0: protocol number, set to 0
        if(cfd == -1) 
        {
            printf("socket creation fail !\n");
            return -1;
        }
        /*
        sockaddr_in contains 3 variables: sin_family, sin_port, sin_addr
        sin_family: address family: AF_INET
        sin_port: port in network byte order
        sin_addr: internet address
        */
        s_add.sin_family = AF_INET;				//set protocol
        s_add.sin_addr.s_addr = inet_addr("192.168.0.11");	//set IP addr
        s_add.sin_port = htons(9008);			//converts the unsigned short integer hostshort from host byte order to network byte order. 
        printf("Please enter a alpha numeric string: ");
        char input[BUFSIZ + 1];
        fgets(input, BUFSIZ, stdin);
        if(strncmp(input,"quit",4) == 0) {
          break;
         }
        if(strstr(input,"C00L")){ //connect client to the socket once meet input requirement
          if(connect(cfd,(struct sockaddr *)(&s_add), sizeof(struct sockaddr)) == -1) 
          {
            printf("connect fail !\r\n");
            return -1;
          }
          /*
          The connect() function shall attempt to make a connection on a socket. The function takes the following arguments:
          socket: Specifies the file descriptor associated with the socket.
          address: Points to a sockaddr structure containing the peer address. 
          address_len: Specifies the length of the sockaddr structure pointed to by the address argument
          */       
          int writ = write(cfd,input,strlen(input));	//write the context in input to cfd
          if(-1 == writ) 
          {
            printf("write fail!\n");
            return -1;
          } 
          close(cfd);
          
       }
    }
    return 0;
}
