#include<stdio.h>
#include <unistd.h>
int main()
{
int x = fork();
// child process:
if(x == 0)
{
sleep(5);
printf("Child Process id is : %d and parent process id is : %d
\n",getpid(),getppid());
}
//parent process:
else if(x > 0){
printf ("Parent Process id is: %d \n",getpid());
}
return 0;
}