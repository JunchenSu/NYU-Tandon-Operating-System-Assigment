/**
*Purpose: Operating System Assignment1
*Author: Junchen Su
*NetId: js9133
**/


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>


#define MAX_INPUT 128
#define MAX_COMMAND 16
#define BLANK_SYMBOL " "
#define NULL_SYMBOL NULL
#define TRUE 1


void getCommand(char* argbuf,char** command){		
	for(int i = 0; i < MAX_COMMAND; i++) {
       	command[i] = strsep(&argbuf, BLANK_SYMBOL);//break argbuf to chunks and put them into command array
        	if(command[i] == NULL_SYMBOL) break;//quit if meet NULL
   	}
}


int execute(char* command[]){

	pid_t pid = fork();//fork() is used to create a same process to current process, after this code is done, 
						   //the codes below will be run by both parent process and child procss

	switch(pid){//check the return value 

		case -1:// if error happens, the fork() will return -1, and we use perror to print the error reason as well as the step where error happens
			perror("fork failed");
			return 1;

		case 0://if the return value is 0, then this value is returned by child process, so by checking the pid value, we can find child process and let it do tasks
			execvp(command[0], command);//execvp is the code that really run the command 
			perror("execvp failed");
			return 1;

		default://if everything goes well, the parent process should return the process ID of the child process
			wait(NULL);//we let the parent process wait until child done, then parent will go back to the begin of while loop(could also use waitpid())
			return 1;
	}
}


int main(){

	while(TRUE){// set loop here, once child process is done, the parent process will go back here and promot

		printf("Junchen's Shell$");

		char argbuf[MAX_INPUT + 1];//a temporary container to store keyboard input

		fgets(argbuf,MAX_INPUT,stdin);//use fgets() to get the input from keyboard

		argbuf[strlen(argbuf)-1] = '\0';//the last pointer has to be NULL when passed into shell

		char* command[MAX_COMMAND + 1];//the communication between processes is based on String, so we set the the parameter to the pointer pointing to strings

		getCommand(argbuf,command);//parse the input to get several strings

		if (strcmp(command[0],"exit") == 0) break;//check exit

		execute(command);//run the command
	}

	return 1;
}







