# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/ipc.h>
# include <time.h>
# include <sys/sem.h>
# include <semaphore.h>
# include <sys/shm.h>
# include <sys/wait.h>

#include "function.h"

int main ( int argc , char * argv []) {

	pid_t pid;
	Entry* en;

	int readers;
	int writers;
	int target;
	int type_work;

	srand(time(NULL));

	if ( argc !=4) {
		printf ("Error,this program can accept 4 arguments: ./prog_name ,peers number , entries number, percent_rate=readers/peers*100  \n");
		return -1;
	}

	int peers  = atoi (argv[1]);
	int entries= atoi (argv[2]);
	int rate   = atoi (argv[3]); ///percent of readers/peers*100

	readers=give_readers(rate,peers);
	writers=peers-readers;

	int shmid=shmget(IPC_PRIVATE,entries * sizeof(Entry),IPC_CREAT | 0666);
	if (shmid<0){
		perror("Error while creating shared memory.\n");
		return -1;
	}

	en=(Entry*)shmat(shmid,NULL,0);
	if(!en){
		perror("Error while attaching to shared memory.\n");
		return -1;
	}

	printf("\nEntry before start:\n");
	for(int i=0; i<entries;i++){
		en[i].read=0;
		en[i].write=0;
	    en[i].data=0;
	    en[i].time_w=0.0;
	    en[i].time_r=0.0;
		sem_init(&en[i].sem,1,1);
		printf("entry[%d]=%d  \n",i,en[i].data);
	}
	printf( "\n");
	printf("Peers is ready to start! .................................\n\n");

	for(int j=0; j<peers;j++) {

		target=rand()%entries;    //found which entry read or write
		type_work=foundtypework(readers,writers);     //found read or write

		if (type_work==1) readers--;
		if (type_work==0) writers--;

		pid=fork();
		if(pid==-1){
			perror("Error while creating child");
			return -1;
		}
		else if (pid==0){
			printf("peer with id:%d created, target entry:%d, type of work:%d \n",getpid(),target,type_work);

			if(type_work==1){
				work_reading(en,target);   ///// going to read entry
			}else if(type_work==0){
				work_writing(en,target);   ///// going to write entry
			}

			exit(0);
		}//end if
	}//end for

	for(int i=0;i<peers;i++){
		pid=wait(NULL);
		printf("peer with id:%d exited\n",pid);
	}
	printf("..........................................................\n\n");
	printf("Entry after Reads end Writes:\n");
	for(int i=0;i<entries;i++){
		double average_w=0.0;
		double average_r=0.0;
		if(en[i].write>0) average_w=en[i].time_w/en[i].write;
		if(en[i].read>0 ) average_r=en[i].time_r/en[i].read;
		printf("entry[%d]=%d ,writes=%d ,time=%lf | reads=%d ,time=%lf\n",i,en[i].data,en[i].write,average_w,en[i].read,average_r);
	}
	for(int i=0;i<entries;i++){
		sem_destroy(&en[i].sem);
	}
	if(shmdt(en)<0){
		perror("Error while detaching shared memory. \n");
	}
	if (shmctl(shmid,IPC_RMID,NULL)<0){
		perror("Error while deleting shared memory.\n");
	}

	exit(0);
}
