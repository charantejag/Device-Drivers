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

typedef struct LCT
    {
    char alpha[10];
    int count;
    } lc_pool;


int main (int argc, char **argv)
{
	sum_pool *test = malloc(sizeof(sum_pool));
	test->alpha[0] = 'c';
	strcpy(test->word[0],"course");
	test->value[0] = 4;
	strcpy(test->word[1],"cap");
	test->value[1] = 4;
	strcpy(test->word[2],"class");
	test->value[2] = 3;
	strcpy(test->word[3],"culture");
	test->value[3] = 1;
	strcpy(test->word[4],"concurrency");
	test->value[4] = 1;
	strcpy(test->word[5],"courage");
	test->value[5] = 2;
	test->count = 6;

	int m = 0;

	lc_pool *lclist = malloc(sizeof(lc_pool));
	lclist->alpha[0] = test->alpha[0];
	lclist->count = 0;
	for (m = 0;m < test->count;m++)
	{
		printf("1\n");		
		lclist->count = lclist->count + test->value[m];
		printf("%d\n",lclist->count);
	}

	printf(" letter and count is : (%c,%d)\n",lclist->alpha[0],lclist->count);

	return(0);

}
	














