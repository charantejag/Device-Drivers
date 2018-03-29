#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
int count=0;
int main(int argc,char *argv[])
{
  
   char ch;
   FILE *fp;
    const char s[2] = " \n";
    char *str;
    char *focal;
    str = (char*)malloc(500*sizeof(char));
    focal = (char*)malloc(500*sizeof(char));
    fp = fopen(argv[1],"r"); 
   while( ( ch = fgetc(fp) ) != EOF )
   {
  str[count]=ch;
        count=count+1;
  }
    focal = strtok(str, s);
    str=NULL;
    count=0;
   while( focal != NULL ) 
   {
    printf("(%s,1)\n", focal );
      focal = strtok(NULL, s);
   }
 free(focal);
 free(str);
 fclose(fp);
   return 0;
}
