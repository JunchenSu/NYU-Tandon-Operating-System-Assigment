/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "checkCOOL.h"
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <signal.h>
#include <arpa/inet.h> 
#include <unistd.h>


#define BUFSIZ 1024

void
checkcool_1(char *host,char *input)
{
	CLIENT *clnt;
	char * *result_1;

#ifndef	DEBUG
	clnt = clnt_create (host, checkCOOL, VERSION, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	if(strstr(input,"C00L")){
		result_1 = check_1(&input, clnt);
	} else{
		printf("no cool included\n");
	}
	//if (result_1 == (char **) NULL) {
		//clnt_perror (clnt, "call failed");
	//}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host = "127.0.0.1";
	char input[BUFSIZ+1]; 
    while(1){
        printf("Please enter a alpha numeric string: ");
        scanf("%s",input);
        checkcool_1(host, input);   
     }
exit (0);
}
