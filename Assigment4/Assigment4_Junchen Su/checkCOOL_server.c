/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "checkCOOL.h"
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <signal.h>
#include <arpa/inet.h> 
#include <sys/socket.h>
#include <unistd.h>


#define BUFSIZ 1024

int totalLines = 0;                  
int totalDigits = 0;          
void checkStatus(int sig){   //functions to run when ctrl+c
    printf("Total input lines:%d \n",totalLines);
    printf("Total input digist:%d \r\n",totalDigits);
    exit(0);
}


char **
check_1_svc(char **input, struct svc_req *rqstp)
{
	static char * result;
	char buf[BUFSIZ+1];
	strcpy(buf,*input);
	signal(SIGINT,checkStatus);
	FILE *secret;
	int i = 0, count = 0;
	while(i<strlen(buf)) {
                if(buf[i] >= '0' && buf[i] <= '9') {
                    count++;
                }
                i++;
     }
     printf("The input is %s, it has %d digits.\n",buf,count);
     totalLines++;
     totalDigits += count;
     secret = fopen("secret.out","w");
     fprintf(secret, "The input is: %s the digits of this input is: %d\n",buf,count);
     fclose(secret);
	 result = "input received";

	 return &result;
}
