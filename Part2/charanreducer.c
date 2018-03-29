#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

typedef struct SP
    {
    char alpha[10];
    char word[100][20];
    int value[100];
    int count;
    } sum_pool;


int main (int argc, char **argv)
{
	FILE *f1 = fopen(argv[1],"r");
	char input[30];
	char *in;
	int i = 0;
	int j = 0;
	int k = 0;
	int l = 0;
	int m = 0;
	int stop = 0;
	int flag = 0;
	int temp = 0;
	sum_pool **sumlist;
	sumlist = malloc(10 * sizeof(sum_pool));
	while (fgets(input,sizeof(input),f1))
	{		
		in = strtok(input,"\n");
		printf("incoming word is %s\n",in);
		if (flag == 0)
		{
			sumlist[j] = malloc(sizeof(sum_pool));			
			strcpy(sumlist[j]->word[i],in);
			sumlist[j]->value[i] = 1;
			sumlist[j]->alpha[0] = in[0];
			flag = 1;
			i++;
			sumlist[j]->count = 1;
			continue;
		}
		else
		{
				m = 0;	
				for (m = 0;m < sumlist[j]->count; m++)
				{
					if (strcmp(sumlist[j]->word[m],in) == 0)
					{
						printf("the matched word is %s and it is found at %d position\n",in,m);
									
						sumlist[j]->value[m]++;
						stop = 1;
						break;
					}
				}
				if (stop == 1)
				{
					stop = 0;
					continue;
				}
				
				sumlist[j]->count += 1;
				temp = sumlist[j]->count;
				printf("temp is %d\n",temp);
				printf("the new word added is %s and the position is %d\n",in,m);
				//printf("m value is %d\n",m);
				strcpy(sumlist[j]->word[m],in);
				sumlist[j]->value[m] = 1;
		}
				

	}
		
				
		for (l = 0; l < sumlist[j]->count; l++)
		{
			printf("(%s,%d) \n",sumlist[j]->word[l],sumlist[j]->value[l]);
		}
	

	return (0);
}
					
	 	
