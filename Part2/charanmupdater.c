#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

typedef struct MP
    {
    char alpha[10];
    char word[100][20];
    int count;
    } mapper_pool;


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
	mapper_pool **maplist;
	maplist = malloc(10 * sizeof(mapper_pool));
	while (fgets(input,sizeof(input),f1))
	{		
		in = strtok(input,"\n");
		if (flag == 0)
		{
			maplist[j] = malloc(sizeof(mapper_pool));			
			strcpy(maplist[j]->word[i],in);
			maplist[j]->alpha[0] = in[0];
			flag = 1;
			i++;
			maplist[j]->count = 1;
			continue;
		}
		else
		{
			if (maplist[j]->alpha[0] == in[0])
			{
				strcpy(maplist[j]->word[i],in);
				i++;
				maplist[j]->count++;
				continue;
			}
			else
			{
				j++;
				maplist[j] = malloc(sizeof(mapper_pool));
				//printf("new alphabet %c has entered\n",in[0]);
				i = 0;
				strcpy(maplist[j]->word[i],in);
				//printf("new word that is copied is %s\n",maplist[j]->word[i]);
				maplist[j]->alpha[0] = in[0];
				//printf("alpha has been updated to %c\n",mapdata->alpha[0]);
				i++;
				maplist[j]->count = 1;
				continue;
			}
			//printf("alpha has been updated to %c\n",mapdata->alpha[0]);
		}
	}
	for (k = 0; k <7; k++)
	{
		temp = maplist[k]->count;
		//printf("printing the elements starting with letter: %c\n",maplist[k]->alpha[0]);		
		for (l = 0; l < temp; l++)
		{
			printf("%s \n",maplist[k]->word[l]);
		}
	}

	return (0);
}
					
	 	
