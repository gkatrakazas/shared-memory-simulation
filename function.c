# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <time.h>
# include <sys/sem.h>
# include <semaphore.h>
# include <sys/wait.h>

#include "function.h"

int foundtypework(int readers,int  writers){ //reader==1 , writer==0
 	if( ( rand()%2 ) ==1 ){
 		if( readers>0 ){
 			return 1;
 		}
 		return 0;
 	}else{
 		if(writers>0){
 			return 0;
 		}
 		return 1;
 	}
 }
 
void work_reading(Entry* en,int target){
	en[target].tim=clock();
	int value;
	value=en[target].data;
	en[target].read++;
	printf("peer with id:%d  READ  entry:%d, data:%d\n",getpid(),target,value);
	en[target].tim=clock() - en[target].tim;
	en[target].time_r=en[target].tim + en[target].time_r;
 }

void work_writing(Entry* en,int target){
	int value;
	en[target].tim=clock();
	sem_wait(&en[target].sem); //blocking other peers
	value=en[target].data +1;
	en[target].data=value;
	en[target].write++;
	printf("peer with id:%d  WRITE entry:%d, data:%d \n",getpid(),target,value);
	sem_post(&en[target].sem);
	en[target].tim=clock() - en[target].tim;
	en[target].time_w=en[target].tim + en[target].time_w;
}

int give_readers(int rate,int peers){
	float r=(float)rate/100*peers;
	int r3=(int)r;
	float r2=r-r3;
	if (r2>=0.5){
		return r3+1;
	}
	return r3;
}

