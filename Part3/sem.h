#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


struct semaphore {
	pthread_mutex_t lock;
        pthread_cond_t nonzero;
        unsigned count;
        };
typedef struct semaphore semaphore_t;


semaphore_t *barrier_create(char *barrier_name,int value);
semaphore_t *semaphore_create(char *semaphore_name,int num);
semaphore_t *semaphore_open(char *semaphore_name);
void semaphore_post(semaphore_t *semap);
void semaphore_wait(semaphore_t *semap);
void semaphore_close(semaphore_t *semap);
void barrier_wait(char *testfilename);
void barrier_init(char *filename,int value);



semaphore_t *
semaphore_create(char *semaphore_name,int num)
{
			
        int fd;
	    int number = num;
        semaphore_t *semap;
        pthread_mutexattr_t psharedm;
        pthread_condattr_t psharedc;


        fd = open(semaphore_name, O_RDWR | O_CREAT | O_EXCL, 0666);
        if (fd < 0)
        	return (NULL);
        (void) ftruncate(fd, sizeof(semaphore_t));
        (void) pthread_mutexattr_init(&psharedm);
        (void) pthread_mutexattr_setpshared(&psharedm,PTHREAD_PROCESS_SHARED);
        (void) pthread_condattr_init(&psharedc);
        (void) pthread_condattr_setpshared(&psharedc,PTHREAD_PROCESS_SHARED);
        semap = (semaphore_t *) mmap(NULL, sizeof(semaphore_t),PROT_READ | PROT_WRITE, MAP_SHARED,fd, 0);
        close (fd);
        (void) pthread_mutex_init(&semap->lock, &psharedm);
        (void) pthread_cond_init(&semap->nonzero, &psharedc);
        semap->count = number;
	
        return (semap);
}




semaphore_t *semaphore_open(char *semaphore_name){
	int fd;
        semaphore_t *semap;
        fd = open(semaphore_name, O_RDWR, 0666);
        if (fd < 0)
        	return (NULL);
        semap = (semaphore_t *) mmap(NULL, sizeof(semaphore_t),PROT_READ | PROT_WRITE, MAP_SHARED,fd,0);
        close (fd);
        return (semap);
}



void semaphore_post(semaphore_t *semap)
{
	pthread_mutex_lock(&semap->lock);
        if (semap->count == 0)
	{
        	pthread_cond_signal(&semap->nonzero);
	}
        semap->count++;
        pthread_mutex_unlock(&semap->lock);
}



void semaphore_wait(semaphore_t *semap)
{
	pthread_mutex_lock(&semap->lock);
        while (semap->count == 0)
        {
              pthread_cond_wait(&semap->nonzero, &semap->lock);
	}
        semap->count--;
        pthread_mutex_unlock(&semap->lock);
}




void semaphore_close(semaphore_t *semap)
{
	munmap((void *) semap, sizeof(semaphore_t));
}




semaphore_t *barrier_create(char *barrier_name, int value)
{
	int fd;
	int max = value;
	semaphore_t *barr;
	pthread_mutexattr_t psharedm;
        pthread_condattr_t psharedc;
	
	fd = open(barrier_name,O_RDWR | O_CREAT | O_EXCL, 0666);
	if (fd < 0)
	{
		return(NULL);
	}
	(void) ftruncate(fd,sizeof(semaphore_t));
        (void) pthread_mutexattr_init(&psharedm);
        (void) pthread_mutexattr_setpshared(&psharedm,PTHREAD_PROCESS_SHARED);
        (void) pthread_condattr_init(&psharedc);
        (void) pthread_condattr_setpshared(&psharedc,PTHREAD_PROCESS_SHARED);	
	barr = (semaphore_t *) mmap(NULL, sizeof(semaphore_t),PROT_READ | PROT_WRITE, MAP_SHARED,fd, 0);	
	close(fd);
        (void) pthread_mutex_init(&barr->lock, &psharedm);
        (void) pthread_cond_init(&barr->nonzero, &psharedc);
        barr->count = max;	
	printf("barrier count is  %d \n",barr->count);
	return(barr);
}


void barrier_init(char *filename,int value)
{
	int fd;
	semaphore_t *barr;	
        fd = open(filename, O_RDWR, 0666);
	if (fd < 0)
	{        
		exit(-1);
	}
        barr = (semaphore_t *) mmap(NULL, sizeof(semaphore_t),PROT_READ | PROT_WRITE, MAP_SHARED,fd,0);
        close (fd);
	pthread_mutex_lock(&barr->lock);
	barr->count = value;
    pthread_mutex_unlock(&barr->lock);
}



void barrier_wait(char *testfilename)
{
	
	    int fd;
        semaphore_t *semap;
        fd = open(testfilename, O_RDWR, 0666);
        if (fd < 0)
        	exit(-1);
        semap = (semaphore_t *) mmap(NULL, sizeof(semaphore_t),PROT_READ | PROT_WRITE, MAP_SHARED,fd,0);
        close (fd);
	pthread_mutex_lock(&semap->lock);
	semap->count--;
        while (semap->count != 0)
        {            
		  pthread_cond_wait(&semap->nonzero, &semap->lock);
     	}
	pthread_cond_signal(&semap->nonzero);
	//printf("All process have already passed through barrier once \n ");
	pthread_mutex_unlock(&semap->lock);
}






