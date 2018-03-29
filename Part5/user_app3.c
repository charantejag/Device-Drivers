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
pthread_t thread_2;


void *thrd1(void *arg)
{
	int size = 20;
	char buf[size];
	int id = 1;
	int f0;
	int err;
	printf("debug position: %s:%d\n", __func__, __LINE__);
	f0 = open("/dev/a5", O_RDWR);
	if (f0 < 0)
	{ perror("mycdrv0 could not be opened");
		return -1;}

	printf("debug position: %s:%d\n", __func__, __LINE__);
	sleep(10);
	printf("debug position: %s:%d\n", __func__, __LINE__);
	memset(buf, 0, size);
	sprintf(buf, "Thread id is %2d\n", id);
	write(f0, buf, 16);
	printf("debug position: %s:%d\n", __func__, __LINE__);
	close(f0);
	printf("debug position: %s:%d\n", __func__, __LINE__);
	return 0;
}

void *thrd2(void *arg)
{
	int f1;
	int err;
	int size = 16;
	char buf[size];

	printf("debug position: %s:%d\n", __func__, __LINE__);
	sleep(3);
	printf("debug position: %s:%d\n", __func__, __LINE__);
	f1 = open("/dev/a5", O_RDWR);
	if (f1 < 0)
	{ perror("mycdrv0 could not be opened");
		return -1;}
	printf("debug position: %s:%d\n", __func__, __LINE__);

	memset(buf, 0, size);
	read(f1, buf, size);
	printf("Data read from mycdrv0 : %s", buf);
	printf("debug position: %s:%d\n", __func__, __LINE__);

	close(f1);
	printf("debug position: %s:%d\n", __func__, __LINE__);
	return 0;
}

int main(int argc, char *argv[]) {

	int i,err;
	int dir = 0;
	char buf[100]; 
	char wbuf[100]; 
	char rbuf[100]; 
	
    pthread_create(&(thread_1), NULL, thrd1, (void*)i);
	pthread_create(&(thread_2), NULL, thrd2, NULL);
	
	
	pthread_join(thread_2, NULL);
	pthread_join(thread_1, NULL);
	return 0;
}
