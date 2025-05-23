#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.>
#include<sys/wait.h>
int main(void)
{
	pid_t pid;
	pid_t ppid;
	pid=fork();
	if(pid==-1)
	{
		perror("Unsuccessful\n");
		return 1;
	}
	if(pid==0)
	{
		
		printf("I am child\n");
	}
	else
	{
		sleep(30);
		printf("I am parent");
	}

	return 0;
}
