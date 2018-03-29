#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <signal.h>


struct list {
    char string[20];
    int keyval;
	int repetition;
	int total;
    struct list *next;
};

typedef struct list LIST;
void mapper(char value[20]);
void reducer(LIST *mapoutput);

int main() 
{ 
        LIST *current, *head;
        head = current = NULL;
	FILE *fp;
        int i=1;
        int d = 0;
       char c ;
      char *buffer;
       char filename[100];
       char temp[20];
  buffer = (char*) calloc(1, sizeof(char));
 // printf(" Enter File name \n ");
 // scanf(" %s \n ",filename);
 //printf("The Mapper output is : \n ");
  fp = fopen("file.txt","r"); 
   while(c=fgetc(fp) != EOF)
  {
  if(c==' '||c=='\n')
      { 
         break ;
      }
   i++;
 buffer = realloc(buffer, sizeof(char)*i);
  strncat(buffer,&c,1);
   }

   strcpy(temp,buffer);
   printf("contents stored in buffer = %s\n",temp);
   
   mapper(temp);

  printf("%s \n",buffer);
 
// }
  buffer[0]='\0';
 if(feof(fp))
      { 
         break ;
      }
}
void reducer(LIST *head);
}
void mapper(char value[20])
    { 
      
      LIST *node = malloc(sizeof(LIST));
      LIST *current, *head;
       strcpy(node->string,value);
       node->keyval = 1;
        node->next =NULL;
       if(head == NULL){
            current = head = node;
        } 
      else {
            current = current->next = node;
           
        }
    printf("(%s,%d) \n ", current->string,current->keyval);
    }
void reducer(LIST *mapoutput)
	{
         LIST *focal, *head;
         LIST *temp;
         focal = mapoutput;
for(focal=head;focal->next!=NULL;focal=focal->next)
{
int count=1;
char k[20];
char b;;
strcpy(k,focal->string);
b=k[0];
temp=focal->next;
if(focal->repetition==1)
{
break;
}
while(temp!=NULL)
{
char g[20];
char d;
int s;
int comp;
strcpy(g,temp->string);
d=g[0];
s=strcmp(b,d);
if(b!=d)
{
break;
}
comp=strcmp(k,g);
if(comp==0)
{
count++;
temp->repetition=1;
}
temp=temp->next;
focal->total=count;
}
}
printf("The Reducer output is : \n ");
for(focal=head;focal->repetition!=1;focal=focal->next)
{
 printf("(%s,%d) \n ", focal->string,focal->total);
}
} 



