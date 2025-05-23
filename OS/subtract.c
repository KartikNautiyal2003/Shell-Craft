#include<stdio.h>
#include<unistd.h>
int main(void){
	        int a=3;
		int b=4;
		int sum=a+b;
		pid_t ppid;
		ppid=getppid();
		printf("Sum=%d\n",sum);
		printf("pid is %u\n",ppid);
		return 0;
}
