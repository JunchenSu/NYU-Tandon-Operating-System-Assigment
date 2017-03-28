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

#define TEXT_SIZE 1024

typedef struct 
{
	char text[TEXT_SIZE];
	int isRead;
}SHM;

int main() {

	key_t key = 1994;
	int shmid;
	SHM *shm;
	shmid = shmget(key,sizeof(SHM),IPC_CREAT|0666);
	char localText[BUFSIZ + 1];

	if(shmid == -1) {
		perror("shmget failed\n");
		exit(1);
	}
	else {
		printf("Create shared memory with ID: %d\n", shmid);
	}

	shm = (SHM *)shmat(shmid,NULL,0);

	if (shm == (SHM*)-1) {
		perror("shmat failed");
		exit(1);
	}

	shm->isRead = 1;//initialized the communication,wait for receiver to send a new tex

	while(1) {

		if(shm->isRead == 0) {
			strncpy(localText, shm->text,TEXT_SIZE);//copy text from shared mem to local user space
			FILE *secret;
			int i = 0; 
			int count = 0;
			while(i<strlen(localText)) {
				if(localText[i] >= '0' && localText[i] <= '9') {
					count++;
				}
				i++;
			}
			printf("The number of digits is %d\n",count);
			secret = fopen("secret.out","w");
			if (secret == NULL) {
				perror("fopen");
				exit(1);
			}
			fprintf(secret, "The input is: %s the digits of this input is: %d\n",localText,count);
			fclose(secret);
			shm->isRead = 1;
		} else {
			sleep(1);
		}

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