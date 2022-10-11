#include<stdio.h>
#include <unistd.h>
int main()
{
int x = fork();
// child process:
if(x == 0){
printf("Process id of Child: %d\n",getpid());
printf("Its parent id: %d\n",getppid());
}
// parent process
else
{
sleep(5);
printf("Parent Process id is: %d \n",getpid());
}
return 0;
}