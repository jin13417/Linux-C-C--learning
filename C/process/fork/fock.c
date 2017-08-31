#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
int main()
{
	pid_t pid;
	if(pid = fork() == -1)
	{ 
	     	perror("fork,error");
			exit(-1);
	}
	else if (pid ==0)
	{
		printf("child process:pid =%d ppid=%d\n",getpid(),getppid());
	}
	else 
	{
		printf("child process:pid =%d ppid=%d\n",getpid(),getppid());
	}
	return 0;
}




