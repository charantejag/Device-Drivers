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
pthread_t thread_3;

void *thrd1(void *arg)
{
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
	err = ioctl(f0, E2_IOCMODE2, 0);
	if (err == -1)
	{ perror("\n***error in ioctl***\n	");
		return -1; }
	printf("debug position: %s:%d\n", __func__, __LINE__);
	close(f0);
	printf("debug position: %s:%d\n", __func__, __LINE__);
	return 0;
}

void *thrd2(void *arg)
{
	int f1;
	int err;

	printf("debug position: %s:%d\n", __func__, __LINE__);
	sleep(3);
	printf("debug position: %s:%d\n", __func__, __LINE__);
	f1 = open("/dev/a5", O_RDWR);
	if (f1 < 0)
	{ perror("mycdrv0 could not be opened");
		return -1;}
	printf("debug position: %s:%d\n", __func__, __LINE__);

	err = ioctl(f1, E2_IOCMODE1, 0);
	if (err == -1)
	{ perror("\n***error in ioctl***\n	");
		return -1; }
	printf("debug position: %s:%d\n", __func__, __LINE__);

	close(f1);
	printf("debug position: %s:%d\n", __func__, __LINE__);
	return 0;
}

void *thrd3(void *arg)
{
	int f2;
	int err;

	printf("debug position: %s:%d\n", __func__, __LINE__);
	sleep(5);
	printf("debug position: %s:%d\n", __func__, __LINE__);
	f2 = open("/dev/a5", O_RDWR);
	if (f2 < 0)
	{ perror("mycdrv0 could not be opened");
		return -1;}
	printf("debug position: %s:%d\n", __func__, __LINE__);

	err = ioctl(f2, E2_IOCMODE2, 0);
	if (err == -1)
	{ perror("\n***error in ioctl***\n	");
		return -1; }
	printf("debug position: %s:%d\n", __func__, __LINE__);

	close(f2);
	printf("debug position: %s:%d\n", __func__, __LINE__);
	return 0;
}

int main(int argc, char *argv[]) {

	int i,j,err;
	char buf[50]; 
	char writebuf[50]; 
	char readbuf[50]; 
	pthread_create(&(thread_1), NULL, thrd1, NULL);
	pthread_create(&(thread_2), NULL, thrd2, NULL);
	pthread_create(&(thread_3), NULL, thrd3, NULL);
	pthread_join(thread_3, NULL);
	pthread_join(thread_2, NULL);
	pthread_join(thread_1, NULL);
	return 0;
}
