# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <time.h>
# include <sys/sem.h>
# include <semaphore.h>
# include <sys/wait.h>

typedef struct Entry{
	int data;
	int write;
	int read;
	clock_t tim;
	double time_w;
	double time_r;
	sem_t sem;
	}Entry;

int foundtypework(int readers,int  writers);

void work_reading(Entry* en,int target);

void work_writing(Entry* en,int target);

int give_readers(int rate,int peers);
