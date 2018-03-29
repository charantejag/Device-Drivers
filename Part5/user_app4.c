#include <linux/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define CDRV_IOC_MAGIC 'Z'
#define E2_IOCMODE1 _IOWR(CDRV_IOC_MAGIC, 1, int)
#define E2_IOCMODE2 _IOWR(CDRV_IOC_MAGIC, 2, int)



pthread_t thread_1;


void *thrd1(void *arg)
{
	int f0,f1;
	printf("debug position: %s:%d\n", __func__, __LINE__);
	f0 = open("/dev/a5", O_RDWR);
	if (f0 < 0)
	{ perror("mycdrv0 could not be opened");
		return -1;}

	printf("debug position: %s:%d\n", __func__, __LINE__);
	sleep(10);
	printf("debug position: %s:%d\n", __func__, __LINE__);
	f1 = open("/dev/a5", O_RDWR);
	if (f1 < 0)
	{ perror("mycdrv0 could not be opened");
		return -1;}
	printf("debug position: %s:%d\n", __func__, __LINE__);
	close(f0);
	printf("debug position: %s:%d\n", __func__, __LINE__);
	return 0;
}


int main(int argc, char *argv[]) {

	int i;
	int rc;
	char buf[100]; 
	char wbuf[100]; 
	char rbuf[100]; 
    
	pthread_create(&(thread_1), NULL, thrd1, NULL);
	pthread_join(thread_1, NULL);
	return 0;
}
