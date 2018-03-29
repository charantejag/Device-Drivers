#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct list {
    char string[20];
	int total;
    struct list *next;
} node;


int main()
{
        char *word = NULL;
        size_t size = 0;
        ssize_t text;
        int check = 0;
        char *key;
        node *head = malloc(sizeof(node));
        node *current;
        while ((text =  getline(&word, &size, stdin)) != -1)
                {
                        key = strtok(word,"(,1)\n");
                        if (head == NULL)
                        {
                                strcpy(head->string,key);
                                head->total = 1;
                                continue;
                        }
                        
                        current = head;
                        
                        while (current != NULL)
                        {
                                if (strcmp(key,current->string) == 0)
                                {
                                        current->total = current->total+1;
                                        check = 1;
                                        break;
                                }
                                
                                current = current->next;
                                
                        }
                        
                        if (check == 1)
                        {
                                
                                check = 0;
                                continue;
                                
                        }
                        
                        current = head;
                        while (current->next != NULL)
                        {
                                current = current->next;
                                
                        }
                        current->next = malloc(sizeof(node));
                        strcpy(current->next->string,key);
                        current->next->total = 1;                
           }
           
           current = head;
           while (current != NULL)
           {
                printf("(%s,%d)\n",current->string,current->total);
                current = current->next;
                
           }
            return(0);
            
}            
            
            
            
                     
                        
                        
                        
                        
                        
                        
