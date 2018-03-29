#include <stdio.h>
#include <stdlib.h>
#include "sem.h"
#include <time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
	int status;
	int N,M;
        int i=0;
        N = atoi(argv[1]);
	int l;
        l = N%2;
	M = atoi(argv[2]);
        pid_t id[N];
	semaphore_t *philosophersallowed;       
	semaphore_t *barriersemaphore; 
	semaphore_t *philsem[N];
	char semnamefile[100];
	philosophersallowed =	semaphore_create("charan",l);



	barriersemaphore = barrier_create("barry",N);
	barrier_init("barry",N);
	for (i=0;i<N;i++)
	{
		sprintf(semnamefile, "philosophersem%d", i);
		philsem[i] = semaphore_create(semnamefile,1);
		
	}
	for (i = 0;i <N;i++)
	{
		id[i] = fork();
		if (id[i] == 0)
		{
			int lefty,righty,j;
			lefty = i;
			righty = (lefty+1) % N;				
			char left[100];
			char right[100];
			sprintf(left,"philosophersem%d", lefty);
			sprintf(right,"philosophersem%d", righty);
	barrier_wait("barry");

// makes sure all processes pass through barrier // 

	semaphore_t *leftfork;
	semaphore_t *rightfork;

//     philosopher program//


	for (j = 0; j < M ; j++)
	{
		philosophersallowed = semaphore_open("charan");
		leftfork = semaphore_open(left);
		rightfork = semaphore_open(right);
		printf("%d philosopher is in iteration : %d  and he is THINKING \n",lefty,j+1);
		semaphore_wait(philosophersallowed);
		semaphore_wait(leftfork);
		printf("%d philosopher is in iteration : %d  and he is HUNGRY \n",lefty,j+1);
		semaphore_wait(rightfork);
		printf("%d philosopher is in iteration : %d  and he is EATING \n",lefty,j+1);
		semaphore_post(rightfork);
		semaphore_post(leftfork);
		semaphore_post(philosophersallowed);
		printf("%d philosopher is in iteration : %d  and he is THINKING \n",lefty,j+1);
	}
	semaphore_close(philosophersallowed);
	semaphore_close(leftfork);
	semaphore_close(rightfork);
	printf("Process %d is exiting \n",lefty);
	

	exit(0);
			
		}
	}
	
	// End of philosopher program //
	

	for (i = 0;i<N;i++)
	{
		wait(&status);
	}

// wait until all process are terminated//

	semaphore_close(philosophersallowed);
	for (i=0;i<N;i++)
	{
		
		semaphore_close(philsem[i]);
		
	}	
	semaphore_close(barriersemaphore);	
	printf("Main is exiting\n");
        return(0);
	
}




