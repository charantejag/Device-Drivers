#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

typedef struct RP
    {
    char alpha[10];
    char word[100][20];
    int value[100];
    int count;
    } reducer_pool;


int main (int argc, char **argv)
{
	FILE *f1 = fopen(argv[1],"r");
	char input[30];
	char *in;
	int i = 0;
	int j = 0;
	int k = 0;
	int l = 0;
	int flag = 0;
	int temp = 0;
	reducer_pool **redlist;
	redlist = malloc(10 * sizeof(reducer_pool));
	while (fgets(input,sizeof(input),f1))
	{		
		in = strtok(input,"\n");
		if (flag == 0)
		{
			redlist[j] = malloc(sizeof(reducer_pool));			
			strcpy(redlist[j]->word[i],input);
			redlist[j]->value[i] = 1;
			redlist[j]->alpha[0] = input[0];
			flag = 1;
			i++;
			redlist[j]->count = 1;
			continue;
		}
		else
		{
			if (redlist[j]->alpha[0] == input[0])
			{
				strcpy(redlist[j]->word[i],input);
				redlist[j]->value[i] = 1;
				i++;
				redlist[j]->count++;
				continue;
			}
			else
			{
				j++;
				redlist[j] = malloc(sizeof(reducer_pool));
				//printf("new alphabet %c has entered\n",input[0]);
				i = 0;
				strcpy(redlist[j]->word[i],input);
				redlist[j]->value[i] = 1;
				//printf("new word that is copied is %s\n",redlist[j]->word[i]);
				redlist[j]->alpha[0] = input[0];
				//printf("alpha has been updated to %c\n",reddata->alpha[0]);
				i++;
				redlist[j]->count = 1;
				continue;
			}
			//printf("alpha has been updated to %c\n",reddata->alpha[0]);
		}
	}
	for (k = 0; k <7; k++)
	{
		temp = redlist[k]->count;
		//printf("printing the elements starting with letter: %c\n",redlist[k]->alpha[0]);		
		for (l = 0; l < temp; l++)
		{
			printf("(%s,%d) \n",redlist[k]->word[l],redlist[k]->value[l]);
		}
	}

	return (0);
}
					
	 	
