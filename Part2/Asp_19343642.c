#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
typedef struct MP
    {
    char alpha[10];
    char word[100][20];
    int count;
    } mapper_pool;
typedef struct RP
    {
    char alpha[10];
    char word[100][20];
    int value[100];
    int count;
    } reducer_pool;
typedef struct SP
    {
    char alpha[10];
    char word[100][20];
    int value[100];
    int count;
    } sum_pool;
typedef struct LCT
    {
    char alpha[10];
    int count;
    } lc_pool;

int in1=0;
int in2=0;	
int in3=0;	
int in4=0;	
int out1=0;	
int out2=0;	
int out3=0;
int mp_num = 0;
int mupdater_done = 0;
int rp_num = 0;
int mapper_done = 0;
int reducer_done = 0;
int summarizer_done = 0;
int sp_num = 0;
int end=0;
int lc_num = 0;


void *mapperpoolupdater(void *file);
void *summarizer(void *argv);
void *mapper(void *argv);
void *reducer(void *argv);
void *wordcountwriter(void *argv);
void *lettercountwriter(void *argv);

			
pthread_mutex_t mplock;
pthread_mutex_t rplock;
pthread_mutex_t splock;
pthread_mutex_t lclock;
pthread_mutex_t sp2lock;
pthread_cond_t  mpfull;
pthread_cond_t  mpempty;
pthread_cond_t  spfull;
pthread_cond_t  spempty;
pthread_cond_t  rpfull;
pthread_cond_t  rpempty;
pthread_cond_t  lcfull;
pthread_cond_t  lcempty;
pthread_cond_t  sp2full;
pthread_cond_t  sp2empty;

mapper_pool **maplist;
reducer_pool **redlist;
sum_pool **sumlist;
lc_pool **lclist;


int sp2_num = 0;
int out4 = 0;
int out5=0;
int buffersize = 10;

//printf("hello world\n");

int main(int argc,char **argv)
{       
        int i,j;
	int z1;
	int z2;
	int z3;
	int z4;
        int z5;
		int z6;
        printf("main program begins");
        int a=1;
        int b=1;
        int c=1;
         a = atoi(argv[2]);
	 b = atoi(argv[3]);
	 c = atoi(argv[4]);
    pthread_t mputhread ;
    pthread_t wcrthread ;
    pthread_t lcwthread ;

        pthread_cond_init(&mpfull,NULL);
	pthread_cond_init(&mpempty,NULL);
        pthread_cond_init(&rpfull,NULL);
	pthread_cond_init(&rpempty,NULL);
	pthread_cond_init(&lcfull,NULL);
        pthread_cond_init(&lcempty,NULL);
	pthread_cond_init(&spfull,NULL);
	pthread_cond_init(&spempty,NULL);
	pthread_cond_init(&sp2full,NULL);
	pthread_cond_init(&sp2empty,NULL);

	pthread_mutex_init(&splock,NULL);
	pthread_mutex_init(&lclock,NULL);
	pthread_mutex_init(&rplock,NULL);
        pthread_mutex_init(&sp2lock,NULL);
        pthread_mutex_init(&mplock,NULL);
	


	pthread_t mpthread[a];
	pthread_t rthread[b];
	pthread_t sthread[c];
	maplist = malloc(buffersize * sizeof(mapper_pool));
	redlist = malloc(buffersize * sizeof(reducer_pool));
	sumlist = malloc(buffersize * sizeof(sum_pool));
	lclist = malloc(buffersize * sizeof(lc_pool));
	
	z1=pthread_create(&mputhread,NULL,mapperpoolupdater,argv[1]);
	if(z1)
		{
			printf("ERROR: %d\n",z1);
			exit(-1);
		}
	printf("mapper updater thread is created\n");
	for(i=0;i<a;i++)
	{
		z2=pthread_create(&mpthread[i],NULL,mapper,NULL);
		if(z2)
		{
			printf("ERROR: %d\n in %d thread ",z2,i);
			exit(-1);
		}
	printf("mapper thread %d is created\n",i);
	}
	for(i=0;i<a;i++)
	{
		z3=pthread_create(&rthread[i],NULL,reducer,NULL);
		if(z3)
		{
			printf("ERROR: %d\n in %d thread ",z3,i);
			exit(-1);
		}
	printf("reducer thread %d is created\n",i);
	}
	for(i=0;i<a;i++)
	{
		z4=pthread_create(&sthread[i],NULL,summarizer,NULL);
		if(z4)
		{
			printf("ERROR: %d\n in %d thread ",z4,i);
			exit(-1);
		}
	printf("summarizer thread %d is created\n",i);
	}
        z5=pthread_create(&wcrthread,NULL,wordcountwriter,NULL);
	if(z5)
		{
			printf("ERROR: %d\n",z5);
			exit(-1);
		}
		
		z6=pthread_create(&lcwthread,NULL,lettercountwriter,NULL);
	if(z6)
		{
			printf("ERROR: %d\n",z6);
			exit(-1);
		}
		
	pthread_join(mputhread,NULL);
	   for(i=0;i<a;i++)
	{
		pthread_join(mpthread[i],NULL);
	}
	for(i=0;i<b;i++)
	{
		pthread_join(rthread[i],NULL);
	}
	for(i=0;i<b;i++)
	{
		pthread_join(sthread[i],NULL);
	}
	    
       pthread_join(wcrthread,NULL);
	   pthread_join(lcwthread,NULL);
       
        for(i=0;i<7;i++)
        {
	     for(j=0;j<sumlist[i]->count;j++)
        {
       printf("(%s,%d) \n ",sumlist[i]->word[j],sumlist[i]->value[j]);
      }
       }
	printf("main program exits\n ");
	return 0;
}

void *mapperpoolupdater(void *file)
{
	*(char*)file = *(char*)file;	
	FILE *f1 = fopen(file,"r");
	char input[30];
	char *in;
	int i = 0;
	int k = 0;
	int l = 0;
	int flag = 0;
	int temp = 0;
	
	while (fgets(input,sizeof(input),f1))
	{		
		in = strtok(input,"\n");
		if (flag == 0)
		{
			maplist[in1] = malloc(sizeof(mapper_pool));			
			strcpy(maplist[in1]->word[i],in);
			maplist[in1]->alpha[0] = in[0];
			flag = 1;
			i++;
			maplist[in1]->count = 1;
			printf("the first word is added for the alphabet %c\n",maplist[in1]->alpha[0]);
			continue;
		}
		else
		{
			if (maplist[in1]->alpha[0] == in[0])
			{
				strcpy(maplist[in1]->word[i],in);
				i++;
				maplist[in1]->count++;
				continue;
			}
			else
			{   
		        	pthread_mutex_lock(&mplock);
				mp_num++;
				in1 = (in1 + 1) % buffersize;
				while (mp_num == buffersize)
				{
					printf("mapper pool updater is waiting as buffer is full\n");					
					pthread_cond_wait(&mpfull,&mplock);
				}
				
				if (mp_num == 1)
				{
					printf("mapper pool updater is signalling mapper that is buffer is not empty\n");							
					pthread_cond_broadcast(&mpempty);
				}
				//in1 = (in1 + 1) % buffersize;
				printf("new alphabet %c has entered\n",in[0]);
				pthread_mutex_unlock(&mplock);
				
				maplist[in1] = malloc(sizeof(mapper_pool));
				i = 0;
				strcpy(maplist[in1]->word[i],in);
				printf("new word that is copied is %s to the location %d \n",maplist[in1]->word[i],in1);
				maplist[in1]->alpha[0] = in[0];
				printf("alpha has been updated to %c\n",maplist[in1]->alpha[0]);
				i++;
				maplist[in1]->count = 1;
				continue;
			}
			
		}
	}
	pthread_mutex_lock(&mplock);	
	printf("Entire file is read\n ");
	mp_num++;
	mupdater_done = 1;
	if(mp_num == 1)
	{
		printf("signalling to mapper to wake up\n");
		pthread_cond_broadcast(&mpempty);
	}
	pthread_mutex_unlock(&mplock);
	printf("mapperpoolthread is exiting\n ");
	pthread_exit(NULL);	
	

}
void *mapper(void *arg) 
{     
      int k;
      int flag1=0;
      printf("entering the mapper thread\n");
	while (1)
	{	
		printf("entered the mapper thread\n");		
		pthread_mutex_lock(&mplock);
		printf("will now check the waiting condition\n");
		while (mp_num == 0)
		{
			while (mupdater_done == 1)
			{
				mapper_done = 1;
				printf("mapper thread is exiting\n");
				pthread_mutex_unlock(&mplock);				
				pthread_exit(NULL);	
			}
			printf("mapper thread will go to sleep now\n");
			pthread_cond_wait(&mpempty,&mplock);
		}
		printf("mapper thread woke up\n");
		mapper_pool *read = maplist[out1];
		printf("reading from mapper list of index %d\n",out1);
		for (k = 0;k <maplist[out1]->count;k++)
		{				
			printf("entering for loop\n");			
			if (flag1 == 0)
			{
				redlist[in2] = malloc(sizeof(reducer_pool));			
				strcpy(redlist[in2]->word[k],read->word[k]);
				printf("new alphabet added is %s\n",read->word[k]);
				redlist[in2]->value[k] = 1;
				redlist[in2]->alpha[0] = read->alpha[0];
				flag1 = 1;
				redlist[in2]->count = 1;
				printf("the first entry is made to the alphabet %c\n",redlist[in2]->alpha[0]);
				continue;
			}
			else
			{
					strcpy(redlist[in2]->word[k],read->word[k]);
					redlist[in2]->value[k] = 1;
					redlist[in2]->count++;
					printf("%s word is added to the reducer list\n",redlist[in2]->word[k]);
					continue;
			}
		}
		pthread_mutex_lock(&rplock);
		rp_num++;
		while (rp_num == buffersize)
		{
			pthread_cond_wait(&rpfull,&rplock);
		}
		if (rp_num == 1)
		{
			pthread_cond_broadcast(&rpempty);
		}
		in2 = (in2 + 1) % buffersize;
		printf("the updated value of in2 is %d\n",in2);
		flag1 = 0;
		pthread_mutex_unlock(&rplock);
		
		out1 = (out1 + 1) % buffersize;
		printf("the updated value of out1 is %d\n",out1);
		mp_num--;
		if (mp_num == buffersize - 1)
		{
			pthread_cond_signal(&mpfull);
		}
		pthread_mutex_unlock(&mplock);
	}

	pthread_exit(NULL);	
}

void  *reducer(void *argv)
{   
    int k,m;
    int flag2=0;
	printf("entering the REDUCER thread\n");
	while (1)
	{	
        printf("entered the REDUCER thread\n");
		pthread_mutex_lock(&rplock);
		printf("will now check the waiting condition\n");
		while (rp_num == 0)
		{
			while (mapper_done == 1)
			{
				reducer_done = 1;
                printf("REDUCER thread is exiting\n");	
		pthread_mutex_unlock(&rplock);				
				pthread_exit(NULL);	
			}
			printf("REDUCER thread will go to sleep now\n");
			pthread_cond_wait(&rpempty,&rplock);
		}
		printf("REDUCER thread woke up\n");
		reducer_pool *read = redlist[out2];
		printf("reading from REDUCER list of index %d\n",out2);
		for (k = 0;k < redlist[out2]->count;k++)
		{
			printf("entering for loop\n");
			if (flag2 == 0)
			{
				sumlist[in3] = malloc(sizeof(sum_pool));			
				strcpy(sumlist[in3]->word[k],read->word[k]);
				printf("the REDUCER new word added is %s\n",read->word[k]);
				sumlist[in3]->value[k] = 1;
				sumlist[in3]->alpha[0] = read->alpha[0];
				flag2 = 1;
				printf("flag OF REDUCER is updated to 1\n");
				sumlist[in3]->count = 1;
				printf("the first entry is made by the REDUCER to the alphabet %c\n",read->alpha[0]);
				continue;
			}	
			else
			{
				m = 0;	
				for (m = 0;m < sumlist[in3]->count; m++)
				{
					if (strcmp(sumlist[in3]->word[m],read->word[k]) == 0)
					{
						printf("the matched word is %s and it is found at %d position \n",read->word[k],in3);
									
						sumlist[in3]->value[m]++;
						end = 1;
						break;
					}
				}
				if (end == 1)
				{
					end = 0;
					continue;
				}
				
				sumlist[in3]->count += 1;
				//temp = sumlist[in3]->count;
				strcpy(sumlist[in3]->word[m],read->word[k]);
				printf("new word is %s added by REDUCER and it is found at %d position\n",read->word[k],in3);
				sumlist[in3]->value[m] = 1;
			}
		}
		pthread_mutex_lock(&splock);
		sp_num++;
		
		while (sp_num == buffersize)
		{
			pthread_cond_wait(&spfull,&splock);
		}
		if (sp_num == 1)
		{
			pthread_cond_broadcast(&spempty);
		}
		in3 = (in3 + 1) % buffersize;
		printf("the updated value of in3 is %d\n",in3);
		flag2 = 0;
		printf("flag OF REDUCER is changed to 1\n");
		pthread_mutex_unlock(&splock);
		pthread_mutex_lock(&sp2lock);
		sp2_num++;
		while (sp2_num == buffersize)
		{
			pthread_cond_wait(&sp2full,&splock);
		}
		if (sp2_num == 1)
		{
			pthread_cond_broadcast(&sp2empty);
		}
		pthread_mutex_unlock(&sp2lock);
		out2 = (out2 + 1) % buffersize;
		printf("the updated value of out2 is %d\n",out2);
		rp_num--;
		if (rp_num == buffersize - 1)
		{
			pthread_cond_signal(&rpfull);
		}
		pthread_mutex_unlock(&rplock);
				

	}
		
	pthread_exit(NULL);		
}
void *summarizer(void *argv)
{
	int k = 0;
	printf("entering the summarizer thread\n");
	while (1)
	{	 
	    printf("entered the smmarizer thread\n");
		pthread_mutex_lock(&splock);
		printf("will now check the waiting condition in summarizer \n");
		while (sp_num == 0)
		{
			while (reducer_done == 1)
			{
				summarizer_done = 1;
                printf("summarizer thread is exiting\n");
		pthread_mutex_unlock(&splock);				
				pthread_exit(NULL);	
			}
			printf("summarizer thread will go to sleep now\n");
			pthread_cond_wait(&spempty,&splock);
		}

	    printf("summarizer thread woke up\n");
		
		sum_pool *read = sumlist[out3];
            
	     printf("reading from reduer list of index %d\n",out3);
		 
		lclist[in4] = malloc(sizeof(lc_pool));
		lclist[in4]->alpha[0] = read->alpha[0];
		lclist[in4]->count = 0;
		for (k = 0;k < sumlist[out3]->count;k++)
		{
		    //printf("entering for loop in summarizer\n");
		    
			lclist[in4]->count = lclist[in4]->count + read->value[k];
		}
		printf("count is (%c,%d) \n ",lclist[in4]->alpha[0],lclist[in4]->count);
		pthread_mutex_lock(&lclock);
		lc_num++;
		while (lc_num == buffersize)
		{
			pthread_cond_wait(&lcfull,&lclock);
		}
		if (lc_num == 1)
		{
			pthread_cond_broadcast(&lcempty);
		}
		in4 = (in4 + 1) % buffersize;
		pthread_mutex_unlock(&lclock);
		out3 = (out3 + 1) % buffersize;
		sp_num--;
		if (sp_num == buffersize - 1)
		{
			pthread_cond_signal(&spfull);
		}
		pthread_mutex_unlock(&splock);
	}
	
	pthread_exit(NULL);	
	 
	 

}
void *wordcountwriter(void *arg)
{    
    int m;
	printf("entering wordcountwriter thread\n");
	while (1)
	{
		pthread_mutex_lock(&sp2lock);
		while (sp2_num == 0)
		{
			while (reducer_done == 1)
			{
				
				pthread_mutex_unlock(&sp2lock);
				printf("word count writer thread is exiting\n");
				pthread_exit(NULL);
			}
			printf("word count writer is waiting\n");
			pthread_cond_wait(&sp2empty,&sp2lock);
		}

//wordcountwriter
		
		
		sum_pool *read = sumlist[out4];
		FILE *fp;
		fp = fopen("wordcount.txt","a");
		for(m=0;m<read->count;m++)
		{
			fprintf(fp,"(%s,%d)\n",read->word[m],read->value[m]);
			printf(" the word %s is added to the file , its count is %d \n ",read->word[m],read->value[m]);
			
		}
		fclose(fp);
		out4 = (out4 + 1)% buffersize;
		sp2_num--;
		if (sp2_num == buffersize -1)
		{
			pthread_cond_broadcast(&sp2full);
		}
		pthread_mutex_unlock(&sp2lock);
		sleep(5);
	}
	printf(" wordcountwriter thread is Exiting\n ");
	pthread_exit(NULL);
    
}	

void *lettercountwriter(void *arg)
{    
    int m;
	printf("entering lettercountwriter thread\n");
	while (1)
	{
		pthread_mutex_lock(&lclock);
		while (lc_num == 0)
		{
			while (summarizer_done == 1)
			{
				printf("letter count writer thread is exiting\n");
				pthread_mutex_unlock(&lclock);
				pthread_exit(NULL);
			}
			printf("letter count writer is waiting\n");
			pthread_cond_wait(&lcempty,&lclock);
		}

//lettercountwritter//
		
		
		lc_pool *read = lclist[out5];
		FILE *fp;
		fp = fopen("lettercount.txt","a");
		
			fprintf(fp,"(%c,%d)\n",read->alpha[0],read->count);
			printf(" the word %c is added to the file , its count is %d \n ",read->alpha[0],read->count);
			
		
		out5 = (out5 + 1)% buffersize;
		lc_num--;
		if (lc_num == buffersize -1)
		fclose(fp);
		{
			pthread_cond_broadcast(&lcfull);
		}
		pthread_mutex_unlock(&lclock);
		sleep(5);
	}
	printf(" lettercountwriter thread is Exiting\n ");
	pthread_exit(NULL);
    
}  