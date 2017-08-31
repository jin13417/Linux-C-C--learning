#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define N 1

int main()
{
	int status;
	int pid;
	if((pid = fork() )== -1)
		perror("fork error");
	else
		if(pid == 0)
		{
		  printf("%d\n",getpid());
			//exit(N);//结束子进程；
			while (1);
		}
	pid = wait(&status);
	printf("pid = %d  status = %x \n",pid, status);
	return 0;
}

