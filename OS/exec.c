#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
int main(void)
{
    pid_t pid;
    char *argv[]={"/bin/ls","-l",NULL};
    pid=fork();
    if(pid==-1)
        return -1;
    if(pid == 0)
    {
        int val=execve(argv[0],argv,NULL);
        if(val==-1)
            perror("ERROR\n");
    }
    else
    {
        wait(NULL);
        printf("Done with execve\n");
    }
        return 0;
}