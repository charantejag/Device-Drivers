#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <signal.h>
int main(int argc, char * argv[]){
int fd[2];
char string[2000];
pipe(fd);
pid_t x=fork();
if (x==0)
{
close(fd[1]);
dup2(fd[0],0);
execl("./Reducer","./Reducer",string,NULL);
}
else
{
pid_t y=fork();
 if(y==0)
 {
close(fd[0]);
dup2(fd[1],1);
execl("./Mapper","./Mapper",argv[1],NULL);
}
}
}
