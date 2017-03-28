/**
* Name：Junchen Su
* Date: March 2 2017
* Purpose: Assignment2
**/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <ctype.h>


#define TEXT_SIZE 1024

typedef struct 
{
	char text[TEXT_SIZE];
	int isRead;
}SHM;//define a variable type in shared memory, which has a flag
	// used to determine if the text have been read by processor

int main() {

	key_t key = 1994;// key = 0/IPC_PRIVATE
	int shmid;//the shared memory identifier associated with the key
	SHM *shm;
	shmid = shmget(key,sizeof(SHM),IPC_CREAT|0666);
	//find the shared memory in shm_segs whose key value is the key we set
	//if can't find, check the shmflg, check if this flag request to 
	//create a new shared memory, if not, return error; vice versa.
	char input[BUFSIZ + 1];

	if(shmid == -1) {
		perror("shmget failed");
		exit(1);
	}
	else printf("Create shared memory with ID: %d\n", shmid);
	

	shm = (SHM *)shmat(shmid,NULL,0);//return a pointer, pointing to shared mem add
	//shmat() maps the shared memory segment associated with the shared memory
    //identifier shmid into the address space of the calling process.
	//NULL means attach to the first avaliable addr choosed by kernel

	if (shm == (SHM*)-1) {
		perror("shmat failed\n");
		exit(1);
	}

	while(1) {

		while(shm->isRead == 0) {
			sleep(1);//when the text hasn't been read yet
		}
		printf("Please enter a alpha numeric string: ");
		fgets(input, BUFSIZ, stdin);
		/*if (strncmp(input, "quit",4) == 0) {
			
			break;
		}*/
		if(strncmp(input,"quit",4) == 0) {
			break;
		}
		int i =0;
		/*while(i<strlen(input)) {
			if ((input[i] >= '0' && input[i] <= '9') || (input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z')) i++;
			else {
				printf("invalid input\n");
				break;
			} 	
		}*/
		if(strstr(input,"C00L") != NULL) {
			strncpy(shm->text,input,TEXT_SIZE);
			shm->isRead = 0;
			} else shm->isRead = 1;		
	}

	if(shmdt(shm) == -1) {
		perror("shmdt failed\n");
		exit(1);
	}//dettach

	if (shmctl(shmid, IPC_RMID, 0) == -1) {
		perror("ipc didn't close");
		exit(1);
	}//check close
	exit(EXIT_SUCCESS);
	
}